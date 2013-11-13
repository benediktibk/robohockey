#ifndef ROBOHOCKEY_LAYER_VIEW_GRAPH_H
#define ROBOHOCKEY_LAYER_VIEW_GRAPH_H

#include <QtGui/QMouseEvent>
#include <QtGui/QGraphicsView>
#include <QtGui/QGraphicsScene>

class QGraph : public QGraphicsView
{
    Q_OBJECT
public:
    explicit QGraph(QWidget *parent = 0);
    
signals:
    
public slots:
    void mousePressEvent(QMouseEvent *ev);

private:
    QGraphicsScene *scene;
    
};

#endif // QGRAPH_H
