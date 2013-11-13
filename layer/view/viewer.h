#ifndef ROBOHOCKEY_LAYER_VIEW_VIEWER_H
#define ROBOHOCKEY_LAYER_VIEW_VIEWER_H

#include <QtGui/QDialog>
#include <QtGui/QGraphicsScene>

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
	class Viewer :
			public QDialog
	{
		Q_OBJECT

	public:
        Viewer();
		~Viewer();

	private:
		// forbid copies
		Viewer(const Viewer &viewer);
		void operator=(const Viewer &viewer);

	private:
        Ui::viewer *m_ui;
        QGraphicsScene m_scene;
	};
}
}
}

#endif
