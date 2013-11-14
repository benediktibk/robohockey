#include "layer/view/controller.h"
#include "ui_view.h"
#include "common/point.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::View;
using namespace std;

Controller::Controller(Model &model) :
	QDialog(0),
    m_ui(new Ui::View),
    m_model(model)
{
    m_ui->setupUi(this);
    m_ui->currentPosition->setText("0,0");
    connect(&model, SIGNAL(robotDataChanged()), this, SLOT(update()));
}

Controller::~Controller()
{
	delete m_ui;
}

Controller::Controller(const Controller &) :
    QDialog(0),
    m_model(*new Model)

{ }

void Controller::operator=(const Controller &)
{ }

void RoboHockey::Layer::View::Controller::on_turnAround_clicked()
{
    //turnAround();
}

void Controller::update()
{
    const Point robotPosition = m_model.getCurrentPosition();
    double positionX = robotPosition.getX();
    double positionY = robotPosition.getY();
    QString positionXstring = QString::number(positionX);
    QString positionYstring = QString::number(positionY);
    QString resultPosition;
    resultPosition.append(positionXstring);
    resultPosition.append(", ");
    resultPosition.append(positionYstring);
    m_ui->currentPosition->setText(resultPosition);

    if(m_model.stuckAtObstacle() == 1)
    {
        m_ui->stuckAtObstacle->setText("TRUE");
    }
    else
    {
        m_ui->stuckAtObstacle->setText("FALSE");
    }

    if(m_model.reachedTarget() == 1)
    {
        m_ui->reachedTarget->setText("TRUE");
    }
    else
    {
        m_ui->reachedTarget->setText("FLASE");
    }

    if(m_model.isMoving() == 1)
    {
        m_ui->isMoving->setText("TRUE");
    }
    else
    {
        m_ui->isMoving->setText("FALSE");
    }

}
