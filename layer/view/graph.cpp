#include <QPointF>
#include <vector>
#include "layer/view/model.h"
#include "layer/view/graph.h"
#include "common/point.h"
#include <QtGui/QGraphicsEllipseItem>

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::View;

Graph::Graph(Model &model) :
    QGraphicsView(),
    m_model(model)
{
    m_scene = new QGraphicsScene();
   // this->setSceneRect(50,50,350,350);

    this->setScene(m_scene);
    this->setSceneRect(0,0,4,6);
    this->resize(900,600);
}

//Graph::~Graph()
//{
   // m_scene = 0;
    //delete m_scene;

    /* for (vector<QGraphicsEllipseItem*>::iterator i = m_targetPositions.begin(); i != m_targetPositions.end(); ++i)
    {
        delete *i;
        m_targetPositions.clear();
    }*/
//}

void Graph::mousePressEvent(QMouseEvent *ev)
{
    QPointF point= mapToScene(ev->pos());
    QGraphicsView::mousePressEvent(ev);
    vector<Point> target = m_model.getAllTargetPoints();
    target.push_back(Point(point.x(),point.y()));
    m_model.setData(target);
}

void Graph::updateTargets()
{
    vector<Point> target = m_model.getAllTargetPoints();
    size_t size_target = target.size();

    while (size_target < m_targetPositions.size())
    {
        m_targetPositions.erase(m_targetPositions.end());
        //delete m_targetPositions.back();
        //m_targetPositions.pop_back();
    }

    while(size_target > m_targetPositions.size())
    {
        QGraphicsEllipseItem* item = new QGraphicsEllipseItem();
        m_targetPositions.push_back(item);
    }

    for (size_t i = 0; i < m_targetPositions.size(); ++i)
    {
        //QGraphicsEllipseItem &currentItem = *(m_targetPositions[i]);
        target = m_model.getAllTargetPoints();
        //const Point &currentPoint = target[i];
        //double current_x_position = currentPoint.getX();
        //double current_y_posiiton = currentPoint.getY();

    }

}
