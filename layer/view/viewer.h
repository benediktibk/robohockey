#ifndef ROBOHOCKEY_LAYER_VIEW_VIEWER_H
#define ROBOHOCKEY_LAYER_VIEW_VIEWER_H

#include <QtGui/QDialog>

namespace Ui
{
	class viewer;
}

namespace RoboHockey
{
namespace Layer
{
namespace View
{
	class Viewer : public QDialog
	{
		Q_OBJECT

	public:
		explicit Viewer(QWidget *parent = 0);
		~Viewer();

	private:
		Ui::viewer *ui;
	};
}
}
}

#endif
