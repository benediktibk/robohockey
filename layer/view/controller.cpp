#include "layer/view/controller.h"
#include "layer/view/model.h"
#include "layer/view/graph.h"
#include "layer/autonomous/fieldobject.h"
#include "common/point.h"
#include "ui_view.h"
#include <QtGui/QGraphicsEllipseItem>
#include <QtGui/QGraphicsScene>
#include <math.h>
#include <assert.h>

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::View;
using namespace RoboHockey::Layer::Autonomous;
using namespace std;

Controller::Controller(Model &model) :
	QMainWindow(0),
	m_ui(new Ui::View),
	m_model(model),
	m_graph(new Graph()),
	m_scene(new QGraphicsScene()),
	m_pixelPerMeter(80),
	m_robotDiameter(0.5),
	m_targetSpotDiameter(0.2),
	m_trueString("TRUE"),
	m_falseString("FALSE"),
	m_numberOfDigitsRightOfComma(3),
	m_closed(false)
{
	m_ui->setupUi(this);
	m_ui->centralwidget->layout()->addWidget(m_graph);
	m_ui->centralwidget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	m_graph->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_ui->currentPosition->setText("0, 0");

	QPolygonF triangle;
	triangle.append(QPointF(-0.225 * m_pixelPerMeter,-0.175 * m_pixelPerMeter));
	triangle.append(QPointF(-0.225 * m_pixelPerMeter,0.175 * m_pixelPerMeter));
	triangle.append(QPointF(0.225 * m_pixelPerMeter,0));
	triangle.append(QPointF(-0.225 * m_pixelPerMeter,-0.175 * m_pixelPerMeter));

	QRectF fieldLinesRect1(m_pixelPerMeter * QPointF(0,-3), m_pixelPerMeter * QPointF(5,0));
	QRectF fieldLinesRect2(m_pixelPerMeter * QPointF(5.0/12.0,-3), m_pixelPerMeter * QPointF(5 - 5.0/12.0,0));
	QRectF fieldLinesRect3(m_pixelPerMeter * QPointF(5.0/3.0,-3), m_pixelPerMeter * QPointF(5 - 5.0/3.0,0));
	QRectF fieldLinesRect4(m_pixelPerMeter * QPointF(0,-3), m_pixelPerMeter * QPointF(5/2.0,0));

	QRectF goal1(m_pixelPerMeter * QPointF(5.0/12.0,-2), m_pixelPerMeter * QPointF(5.0/6.0,-1));
	QRectF goal2(m_pixelPerMeter * QPointF(5 - 5.0/6.0,-2), m_pixelPerMeter * QPointF(5 - 5/12.0,-1));

	m_scene->addRect(goal1)->setBrush(Qt::yellow);
	m_scene->addRect(goal2)->setBrush(Qt::blue);
	m_scene->addRect(fieldLinesRect1);
	m_scene->addRect(fieldLinesRect2);
	m_scene->addRect(fieldLinesRect3);
	m_scene->addRect(fieldLinesRect4);

	m_triangle = m_scene->addPolygon(triangle);

	m_graph->setScene(m_scene);
	m_graph->setSceneRect(0, 0, 4, 6);
	m_graph->resize(900, 600);
	m_graph->setBackgroundBrush(QBrush(Qt::white, Qt::SolidPattern));

	connect(&model, SIGNAL(robotDataChanged()), this, SLOT(update()));
	connect(&model, SIGNAL(dataForViewChanged()), this, SLOT(updateTargets()));
	connect(&model, SIGNAL(robotDataChanged()), this, SLOT(updateObjects()));
	connect(m_graph, SIGNAL(clicked(QPointF)), this, SLOT(mouseClickInGraph(QPointF)));
	connect(m_ui->bluePuckButton, SIGNAL(clicked()), this, SLOT(puckColorChanged()));
	connect(m_ui->yellowPuckButton, SIGNAL(clicked()), this, SLOT(puckColorChanged()));
	connect(m_ui->anyPuckButton, SIGNAL(clicked()), this, SLOT(puckColorChanged()));
}

Controller::~Controller()
{
	delete m_ui;
	m_ui = 0;
	delete m_graph;
	m_graph = 0;
	delete m_scene;
	m_scene = 0;

	 for (vector<QGraphicsEllipseItem*>::iterator i = m_targetPositions.begin(); i != m_targetPositions.end(); ++i)
		delete *i;
	 m_targetPositions.clear();
}

void Controller::closeEvent(QCloseEvent*)
{
	m_closed = true;
}

bool Controller::isClosed() const
{
	return m_closed;
}

Controller::Controller(const Controller &) :
	QMainWindow(0),
	m_model(*new Model)
{ }

void Controller::operator=(const Controller &)
{ }

QString Controller::convertIntoString(bool value) const
{
	if (value)
		return m_trueString;
	else
		return m_falseString;
}

QString Controller::convertIntoString(double value) const
{
	return QString::number(value, 'f', m_numberOfDigitsRightOfComma);
}

QString Controller::convertIntoString(const Point &value) const
{
	QString xString = convertIntoString(value.getX());
	QString yString = convertIntoString(value.getY());
	QString result;
	result.append("(");
	result.append(xString);
	result.append(", ");
	result.append(yString);
	result.append(")");
	return result;
}

FieldObjectColor Controller::getSeletectedPuckColor() const
{
	if (m_ui->bluePuckButton->isChecked())
		return FieldObjectColorBlue;
	else if (m_ui->yellowPuckButton->isChecked())
		return FieldObjectColorYellow;
	else if(m_ui->anyPuckButton->isChecked())
		return FieldObjectColorUnknown;
	else
	{
		assert(false);
		return FieldObjectColorUnknown;
	}
}

void Controller::on_turnAround_clicked()
{
	m_model.setTurnAround(true);
}

void Controller::on_turnToButton_clicked()
{
	QString textPosX;
	QString textPosY;
	double turnPosX;
	double turnPosY;
	textPosX = m_ui->turnToEditX->displayText();
	turnPosX = textPosX.toDouble();
	textPosY = m_ui->turnToEditY->displayText();
	turnPosY = textPosY.toDouble();
	m_model.setTurnTo(true);
	m_model.turnToPoint(turnPosX, turnPosY);
}

void Controller::on_stop_clicked()
{
	m_model.setStop(true);
}

void Controller::update()
{
	const RobotPosition &robotPosition = m_model.getCurrentPosition();
	const Point &position = robotPosition.getPosition();
	m_ui->currentPosition->setText(convertIntoString(position));
	m_ui->stuckAtObstacle->setText(convertIntoString(m_model.stuckAtObstacle()));
	m_ui->reachedTarget->setText(convertIntoString(m_model.reachedTarget()));
	m_ui->isMoving->setText(convertIntoString(m_model.isMoving()));
	m_ui->cantReachTarget->setText(convertIntoString(m_model.cantReachTarget()));
	m_ui->isPuckCollected->setText(convertIntoString(m_model.isPuckCollected()));
	m_ui->isPuckCollectable->setText(convertIntoString(m_model.isPuckCollectable()));
	m_ui->isRotating->setText(convertIntoString(m_model.isRotating()));

	if (m_model.isClosestPuckValid())
	{
		double distanceToClosestPuck = position.distanceTo(m_model.getClosestPuckPosition());
		m_ui->distanceToClosestPuck->setText(convertIntoString(distanceToClosestPuck));
		m_ui->closestPuckPosition->setText(convertIntoString(m_model.getClosestPuckPosition()));
	}
	else
	{
		m_ui->closestPuckPosition->setText("invalid");
		m_ui->distanceToClosestPuck->setText("invalid");
	}

	const Point &target = m_model.getCurrentTarget();
	QString targetString = QString("%1, %2").arg(convertIntoString(target.getX())).arg(convertIntoString(target.getY()));
	QString distanceToTargetString = convertIntoString(position.distanceTo(target));
	m_ui->targetPosition->setText(targetString);
	m_ui->distanceToTarget->setText(distanceToTargetString);
}

void Controller::mouseClickInGraph(QPointF point)
{
	vector<Point> target = m_model.getAllTargetPoints();
	target.push_back(Point(point.x() / (double) m_pixelPerMeter, -1.0 * point.y() / (double) m_pixelPerMeter));
	m_model.setTargetPoints(target);
}

void Controller::on_collectPuckInFront_clicked()
{
	m_model.setCollectPuckInFront(true);
}

void Controller::on_calibratePosition_clicked()
{
	m_model.setCalibratePosition(true);
}

void Controller::on_leavePuckInFront_clicked()
{
	m_model.setLeavePuckInFront(true);
}

void Controller::on_pushButton_clicked()
{

}

void Controller::puckColorChanged()
{
	m_model.setPuckColor(getSeletectedPuckColor());
}

void Controller::updateTargets()
{
	vector<Point> target = m_model.getAllTargetPoints();
	size_t size_target = target.size();

	while (size_target < m_targetPositions.size())
	{
		m_scene->removeItem(m_targetPositions.back());
		m_targetPositions.pop_back();
	}

	while(size_target > m_targetPositions.size())
	{
		QGraphicsEllipseItem* item = new QGraphicsEllipseItem();
		m_targetPositions.push_back(item);
		m_scene->addItem(item);
	}

	for (size_t i = 0; i < m_targetPositions.size(); ++i)
	{
		QGraphicsEllipseItem &currentItem = *(m_targetPositions[i]);
		const Point &currentPoint = target[i];
		double current_x_position = currentPoint.getX();
		double current_y_position = currentPoint.getY();
		current_x_position = current_x_position * m_pixelPerMeter - 0.5 * m_targetSpotDiameter * m_pixelPerMeter;
		current_y_position = current_y_position * m_pixelPerMeter + 0.5 * m_targetSpotDiameter * m_pixelPerMeter;
		currentItem.setRect(current_x_position, -1.0 * current_y_position, m_targetSpotDiameter * m_pixelPerMeter, m_targetSpotDiameter * m_pixelPerMeter);
		currentItem.setBrush(Qt::green);
	}
}

void Controller::updateObjects()
{
	vector<FieldObject> object = m_model.getAllFieldObjects();
	size_t size_object = object.size();

	while (size_object < m_objectPositions.size())
	{
		m_scene->removeItem(m_objectPositions.back());
		m_objectPositions.pop_back();
	}

	while(size_object > m_objectPositions.size())
	{
		QGraphicsEllipseItem* item = new QGraphicsEllipseItem();
		m_objectPositions.push_back(item);
		m_scene->addItem(item);
	}

	for (size_t i = 0; i < m_objectPositions.size(); ++i)
	{
		QGraphicsEllipseItem &currentItem = *(m_objectPositions[i]);
		const FieldObject &currentObject = object[i];
		const Circle &currentCircle = currentObject.getCircle();
		double diameter = currentCircle.getDiameter();
		Point center = currentCircle.getCenter();
		diameter = diameter * m_pixelPerMeter;
		center = center * m_pixelPerMeter;
		double centerX = center.getX();
		double centerY = center.getY();
		currentItem.setRect(centerX, -1.0 * centerY, diameter, diameter);

		if (currentObject.getColor() == FieldObjectColorBlue)
			currentItem.setBrush(Qt::blue);
		else if (currentObject.getColor() == FieldObjectColorGreen)
			currentItem.setBrush(Qt::green);
		else if (currentObject.getColor() == FieldObjectColorYellow)
			currentItem.setBrush(Qt::yellow);
		else
			currentItem.setBrush(Qt::white);
	}

	const RobotPosition &robotPosition = m_model.getCurrentPosition();
	const Point &position = robotPosition.getPosition();
	double positionX = position.getX() * m_pixelPerMeter - 0.5 * m_pixelPerMeter * m_robotDiameter;
	double positionY = position.getY() * m_pixelPerMeter - 0.5 * m_pixelPerMeter * m_robotDiameter;
	m_triangle->setPos(positionX + 0.25 * m_pixelPerMeter, -1.0 * positionY - 0.25 * m_pixelPerMeter);
	m_triangle->setRotation(-1.0 * 360 * robotPosition.getOrientation().getValueBetweenMinusPiAndPi() / (2 * M_PI));
	m_triangle->setBrush(Qt::blue);
}

