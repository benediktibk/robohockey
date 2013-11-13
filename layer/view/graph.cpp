#include "layer/view/graph.h"
#include <QPointF>


QGraph::QGraph(QWidget *parent) :
    QGraphicsView(parent)
{

    scene = new QGraphicsScene();
   // this->setSceneRect(50,50,350,350);

    this->setScene(scene);
    this->setSceneRect(0,0,4,6);
    this->resize(900,600);
}

void QGraph::mousePressEvent(QMouseEvent *ev)
{
    double rad=10;
    QPointF point= mapToScene(ev->pos());
    scene->addEllipse(point.x()-rad, point.y()-rad,rad*2.0,rad*2.0,QPen(),QBrush(Qt::SolidPattern));
    QGraphicsView::mousePressEvent(ev);
}
