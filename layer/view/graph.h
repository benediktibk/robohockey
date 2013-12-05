#ifndef ROBOHOCKEY_LAYER_VIEW_GRAPH_H
#define ROBOHOCKEY_LAYER_VIEW_GRAPH_H

#include <QtGui/QMouseEvent>
#include <QtGui/QGraphicsView>

namespace RoboHockey
{
namespace Layer
{
namespace View
{
	class Graph :
			public QGraphicsView
	{
		Q_OBJECT

	signals:
		void clicked(QPointF);

	public slots:
		void mousePressEvent(QMouseEvent *ev);
	};
}
}
}

#endif
