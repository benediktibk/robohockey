#include "layer/view/viewer.h"
#include "ui_viewer.h"

using namespace RoboHockey::Layer::View;

Viewer::Viewer() :
	QDialog(0),
	m_ui(new Ui::viewer)
{
	m_ui->setupUi(this);
    m_ui->graphicsView->setScene(&m_scene);
}

Viewer::~Viewer()
{
	delete m_ui;
}

Viewer::Viewer(const Viewer &) :
	QDialog(0)
{ }

void Viewer::operator=(const Viewer &)
{ }
