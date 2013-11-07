#include <QtGui/QApplication>
#include "layer/view/viewer.h"
//#include "layer/view/model.h"

using namespace RoboHockey::Layer::View;

int main(int argc, char **argv)
{
	QApplication application(argc, argv);
	Viewer view;

	view.show();
	return application.exec();
}
