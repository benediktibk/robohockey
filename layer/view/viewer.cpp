#include "layer/view/viewer.h"
#include "ui_viewer.h"

using namespace RoboHockey::Layer::View;

Viewer::Viewer(QWidget *parent) :
	QDialog(parent  ),
	ui(new Ui::viewer)
{
	ui->setupUi(this);
}

Viewer::~Viewer()
{
	delete ui;
}
