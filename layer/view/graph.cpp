#include "layer/view/graph.h"
#include <QtCore/QPointF>

using namespace RoboHockey::Layer::View;

void Graph::mousePressEvent(QMouseEvent *ev)
{
	QPointF point = mapToScene(ev->pos());
	QGraphicsView::mousePressEvent(ev);
	emit clicked(point);
}