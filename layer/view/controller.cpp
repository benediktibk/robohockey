#include "layer/view/controller.h"
#include "ui_view.h"

using namespace RoboHockey::Layer::View;

Controller::Controller() :
	QDialog(0),
	m_ui(new Ui::View)
{
	m_ui->setupUi(this);
}

Controller::~Controller()
{
	delete m_ui;
}

Controller::Controller(const Controller &) :
	QDialog(0)
{ }

void Controller::operator=(const Controller &)
{ }
