#include "layer/view/controller.h"
#include "ui_view.h"
#include "common/point.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::View;
using namespace std;

Controller::Controller(Model &model) :
    QMainWindow(0),
	m_ui(new Ui::View),
    m_model(model),
    m_graph(new Graph(model))
{
    m_ui->setupUi(this);
    m_ui->centralwidget->layout()->addWidget(m_graph);
    m_ui->centralwidget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    m_graph->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_ui->currentPosition->setText("0, 0");
	connect(&model, SIGNAL(robotDataChanged()), this, SLOT(update()));
}

Controller::~Controller()
{
	delete m_ui;
    delete m_graph;
    m_graph = 0;
	m_ui = 0;
}

Controller::Controller(const Controller &) :
    QMainWindow(0),
	m_model(*new Model)
{ }

void Controller::operator=(const Controller &)
{ }

void Controller::on_turnAround_clicked()
{
    m_model.turnAround();
}

void Controller::update()
{
	const RobotPosition &robotPosition = m_model.getCurrentPosition();
	const Point &position = robotPosition.getPosition();
	double positionX = position.getX();
	double positionY = position.getY();
	QString positionXstring = QString::number(positionX);
	QString positionYstring = QString::number(positionY);
	QString resultPosition;
	resultPosition.append(positionXstring);
	resultPosition.append(", ");
	resultPosition.append(positionYstring);
	m_ui->currentPosition->setText(resultPosition);

	if(m_model.stuckAtObstacle() == 1)
		m_ui->stuckAtObstacle->setText("TRUE");
	else
		m_ui->stuckAtObstacle->setText("FALSE");

	if(m_model.reachedTarget() == 1)
		m_ui->reachedTarget->setText("TRUE");
	else
		m_ui->reachedTarget->setText("FLASE");

	const Point &target = m_model.getCurrentTarget();
	QString targetString = QString("%1, %2").arg(target.getX()).arg(target.getY());
	QString distanceToTargetString = QString("%1").arg(position.distanceTo(target));
	m_ui->targetPosition->setText(targetString);
	m_ui->distanceToTarget->setText(distanceToTargetString);
	
    if(m_model.isMoving() == 1)
    {
        m_ui->isMoving->setText("TRUE");
    }
    else
    {
        m_ui->isMoving->setText("FALSE");
    }

}


