#ifndef ROBOHOCKEY_LAYER_VIEW_GRAPH_H
#define ROBOHOCKEY_LAYER_VIEW_GRAPH_H

#include <QtGui/QMouseEvent>
#include <QtGui/QGraphicsView>
#include <QtGui/QGraphicsScene>
#include <vector>

namespace RoboHockey
{
namespace Layer
{
namespace View
{
    class Model;

    class Graph :
            public QGraphicsView
    {
        Q_OBJECT
    public:
        Graph(Model &model);
        ~Graph();

    public slots:
        void mousePressEvent(QMouseEvent *ev);
        void updateTargets();
        void updateObjects();

    private:
        QGraphicsScene *m_scene;
        Model &m_model;
        std::vector<QGraphicsEllipseItem*> m_targetPositions;
        std::vector<QGraphicsEllipseItem*> m_objectPositions;



    };

}
}
}
#endif
