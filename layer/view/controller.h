#ifndef ROBOHOCKEY_LAYER_VIEW_CONTROLLER_H
#define ROBOHOCKEY_LAYER_VIEW_CONTROLLER_H

#include <QtGui/QDialog>

namespace Ui
{
	class View;
}

namespace RoboHockey
{
namespace Layer
{
namespace View
{
	class Controller :
			public QDialog
	{
		Q_OBJECT

	public:
		Controller();
		~Controller();

	private:
		// forbid copies
		Controller(const Controller &viewer);
		void operator=(const Controller &viewer);

	private:
		Ui::View *m_ui;
	};
}
}
}

#endif
