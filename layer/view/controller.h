#ifndef ROBOHOCKEY_LAYER_VIEW_CONTROLLER_H
#define ROBOHOCKEY_LAYER_VIEW_CONTROLLER_H

#include <QtGui/QDialog>
#include "layer/autonomous/robot.h"
#include "layer/dataanalysis/dataanalyserimpl.h"
#include "layer/view/model.h"


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
    class Model;

	class Controller :
			public QDialog
	{
		Q_OBJECT

	public:
        Controller(Model &model);
		~Controller();

    private slots:
        void on_turnAround_clicked();

    public slots:
        void update();

    private:
		// forbid copies
		Controller(const Controller &viewer);
		void operator=(const Controller &viewer);

	private:
		Ui::View *m_ui;
        Model &m_model;
	};
}
}
}

#endif
