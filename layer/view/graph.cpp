#include <QPointF>
#include <vector>
#include <math.h>
#include "layer/view/model.h"
#include "layer/view/graph.h"
#include "common/point.h"
#include <QtGui/QGraphicsEllipseItem>
#include "layer/autonomous/fieldobject.h"

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::View;
using namespace RoboHockey::Layer::Autonomous;

Graph::Graph(Model &model) :
	QGraphicsView(),
	m_model(model),
	m_robot(new QGraphicsEllipseItem),
	m_pixelPerMeter(80),
	m_robotDiameter(0.5),
	m_targetSpotDiameter(0.2)

{
	m_scene = new QGraphicsScene();
	m_scene->addItem(m_robot);
	QPolygonF triangle;
	triangle.append(QPointF(-0.225 * m_pixelPerMeter,-0.175 * m_pixelPerMeter));
	triangle.append(QPointF(-0.225 * m_pixelPerMeter,0.175 * m_pixelPerMeter));
	triangle.append(QPointF(0.225 * m_pixelPerMeter,0));
	triangle.append(QPointF(-0.225 * m_pixelPerMeter,-0.175 * m_pixelPerMeter));
	m_triangle = m_scene->addPolygon(triangle);
   // this->setSceneRect(50,50,350,350);

	connect(&model, SIGNAL(targetPositionsChanged()), this, SLOT(updateTargets()));
	connect(&model, SIGNAL(robotDataChanged()), this, SLOT(updateObjects()));
	this->setScene(m_scene);
	this->setSceneRect(0,0,4,6);
	this->resize(900,600);
	this->setBackgroundBrush(QBrush(Qt::white, Qt::SolidPattern));
}

Graph::~Graph()
{
	m_scene = 0;
	delete m_scene;

	 for (vector<QGraphicsEllipseItem*>::iterator i = m_targetPositions.begin(); i != m_targetPositions.end(); ++i)
		delete *i;
	 m_targetPositions.clear();
}

void Graph::mousePressEvent(QMouseEvent *ev)
{
	QPointF point= mapToScene(ev->pos());
	QGraphicsView::mousePressEvent(ev);
	vector<Point> target = m_model.getAllTargetPoints();
	target.push_back(Point(point.x() / (double) m_pixelPerMeter, -1.0 * point.y() / (double) m_pixelPerMeter));
	m_model.setData(target);
}

void Graph::updateTargets()
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

void Graph::updateObjects()
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
		currentItem.setRect(centerX - 0.5 * diameter, -1.0 * centerY + 0.5 * diameter, diameter, diameter);
		currentItem.setBrush(Qt::red);
	}

	const RobotPosition &robotPosition = m_model.getCurrentPosition();
	const Point &position = robotPosition.getPosition();
	double positionX = position.getX() * m_pixelPerMeter - 0.5 * m_pixelPerMeter * m_robotDiameter;
	double positionY = position.getY() * m_pixelPerMeter - 0.5 * m_pixelPerMeter * m_robotDiameter;
    m_triangle->setPos(positionX + 0.225 * m_pixelPerMeter, -1.0 * positionY - 0.175 * m_pixelPerMeter);
    m_triangle->setRotation(-1.0 * 360 * robotPosition.getOrientation().getValueBetweenMinusPiAndPi() / (2 * M_PI));
	m_triangle->setBrush(Qt::blue);
}
