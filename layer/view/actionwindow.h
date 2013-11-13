#ifndef ROBOHOCKEY_LAYER_VIEW_ACTIONWINDOW_H
#define ROBOHOCKEY_LAYER_VIEW_ACTIONWINDOW_H

#include <QtGui/QDialog>

namespace Ui
{
	class ActionWindow;
}

namespace RoboHockey
{
namespace Layer
{
namespace View
{
	class ActionWindow :
			public QDialog
	{
		Q_OBJECT

	public:
		ActionWindow();
		~ActionWindow();

	private:
		// forbid copies
		ActionWindow(const ActionWindow &viewer);
		void operator=(const ActionWindow &viewer);

	private:
		Ui::ActionWindow *m_ui;
	};
}
}
}

#endif
