#ifndef ROBOHOCKEY_LAYER_VIEW_CONTROLLER_H
#define ROBOHOCKEY_LAYER_VIEW_CONTROLLER_H

#include <QtGui/QMainWindow>
#include "common/fieldobjectcolor.h"

class QGraphicsScene;
class QGraphicsEllipseItem;
class QGraphicsPolygonItem;

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
	class Graph;

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
		void on_leavePuckInFront_clicked();
		void on_pushButton_clicked();

	private slots:
		void update();
		void updateTargets();
		void updateObjects();
		void mouseClickInGraph(QPointF);

	private:
		// forbid copies
		Controller(const Controller &viewer);
		void operator=(const Controller &viewer);

	private:
		QString convertIntoString(bool value) const;
		QString convertIntoString(double value) const;
		Common::FieldObjectColor getSeletectedPuckColor() const;

	private:
		Ui::View *m_ui;
		Model &m_model;
		Graph *m_graph;
		QGraphicsScene *m_scene;
		std::vector<QGraphicsEllipseItem*> m_targetPositions;
		std::vector<QGraphicsEllipseItem*> m_objectPositions;
		QGraphicsPolygonItem *m_triangle;
		int m_pixelPerMeter;
		double m_robotDiameter;
		double m_targetSpotDiameter;
		QString m_trueString;
		QString m_falseString;
		unsigned int m_numberOfDigitsRightOfComma;
	};
}
}
}

#endif
