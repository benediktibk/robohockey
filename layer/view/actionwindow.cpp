#include "layer/view/actionwindow.h"
#include "ui_actionwindow.h"

using namespace RoboHockey::Layer::View;

ActionWindow::ActionWindow() :
	QDialog(0),
	m_ui(new Ui::ActionWindow)
{
	m_ui->setupUi(this);
}

ActionWindow::~ActionWindow()
{
	delete m_ui;
}

ActionWindow::ActionWindow(const ActionWindow &) :
	QDialog(0)
{ }

void ActionWindow::operator=(const ActionWindow &)
{ }
