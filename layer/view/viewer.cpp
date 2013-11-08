#include "layer/view/viewer.h"
#include "ui_viewer.h"

using namespace RoboHockey::Layer::View;

Viewer::Viewer() :
	QDialog(0),
	ui(new Ui::viewer)
{
	ui->setupUi(this);
}

Viewer::~Viewer()
{
	delete ui;
}

Viewer::Viewer(const Viewer &) :
	QDialog(0)
{ }

void Viewer::operator=(const Viewer &)
{ }
