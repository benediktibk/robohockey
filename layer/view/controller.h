#ifndef ROBOHOCKEY_LAYER_VIEW_CONTROLLER_H
#define ROBOHOCKEY_LAYER_VIEW_CONTROLLER_H

#include <QtGui/QMainWindow>
#include "layer/autonomous/robot.h"
#include "layer/dataanalysis/dataanalyserimpl.h"
#include "layer/view/model.h"
#include "layer/view/graph.h"

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
            public QMainWindow
	{
		Q_OBJECT

	public:
		Controller(Model &model);
		~Controller();

	private slots:
        void on_turnAround_clicked();

        void on_turnToButton_clicked();

        void on_stop_clicked();

		void on_collectPuckInFront_clicked();

		void on_calibratePosition_clicked();

	public slots:
		void update();

    private:
		// forbid copies
		Controller(const Controller &viewer);
		void operator=(const Controller &viewer);

	private:
		Ui::View *m_ui;
		Model &m_model;
        Graph *m_graph;

	};
}
}
}

#endif
