#include <QPointF>
#include <vector>
#include "layer/view/model.h"
#include "layer/view/graph.h"
#include "common/point.h"
#include <QtGui/QGraphicsEllipseItem>
#include "layer/autonomous/fieldobject.h"

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::View;
using namespace RoboHockey::Layer::Autonomous;

Graph::Graph(Model &model) :
    QGraphicsView(),
    m_model(model),
    m_robot(new QGraphicsEllipseItem)
{
    m_scene = new QGraphicsScene();
    m_scene->addItem(m_robot);
   // this->setSceneRect(50,50,350,350);

    connect(&model, SIGNAL(targetPositionsChanged()), this, SLOT(updateTargets()));
    connect(&model, SIGNAL(robotDataChanged()), this, SLOT(updateObjects()));
    this->setScene(m_scene);
    this->setSceneRect(0,0,4,6);
    this->resize(900,600);
}

Graph::~Graph()
{
    m_scene = 0;
    delete m_scene;

     for (vector<QGraphicsEllipseItem*>::iterator i = m_targetPositions.begin(); i != m_targetPositions.end(); ++i)
    {
        delete *i;
        m_targetPositions.clear();
    }
}

void Graph::mousePressEvent(QMouseEvent *ev)
{
    QPointF point= mapToScene(ev->pos());
    QGraphicsView::mousePressEvent(ev);
    vector<Point> target = m_model.getAllTargetPoints();
    target.push_back(Point(point.x() / 15.0, point.y() / 15.0));
    m_model.setData(target);
}

void Graph::updateTargets()
{
    vector<Point> target = m_model.getAllTargetPoints();
    size_t size_target = target.size();

    while (size_target < m_targetPositions.size())
    {
        m_targetPositions.erase(m_targetPositions.end());
        m_scene->removeItem(*m_targetPositions.end());
        //delete m_targetPositions.back();
        //m_targetPositions.pop_back();
    }

    while(size_target > m_targetPositions.size())
    {
        QGraphicsEllipseItem* item = new QGraphicsEllipseItem();
        m_targetPositions.push_back(item);
        m_scene->addItem(item);
    }

    for (size_t i = 0; i < m_targetPositions.size(); ++i)
    {
        QGraphicsEllipseItem &currentItem = *(m_targetPositions[i]);
        const Point &currentPoint = target[i];
        double current_x_position = currentPoint.getX();
        double current_y_position = currentPoint.getY();
        current_x_position = current_x_position * 15.0;
        current_y_position = current_y_position * 15.0;
        currentItem.setRect(current_x_position - 5,current_y_position - 5,10,10);


    }

}

void Graph::updateObjects()
{
    vector<FieldObject> object = m_model.getAllFieldObjects();
    size_t size_object = object.size();

    while (size_object < m_objectPositions.size())
    {
        m_objectPositions.erase(m_objectPositions.end());
        m_scene->removeItem(*m_objectPositions.end());
        //delete m_targetPositions.back();
        //m_targetPositions.pop_back();
    }

    while(size_object > m_objectPositions.size())
    {
        QGraphicsEllipseItem* item = new QGraphicsEllipseItem();
        m_objectPositions.push_back(item);
        m_scene->addItem(item);
    }

    for (size_t i = 0; i < m_objectPositions.size(); ++i)
    {
        QGraphicsEllipseItem &currentItem = *(m_objectPositions[i]);
        const FieldObject &currentObject = object[i];
        const Circle &currentCircle = currentObject.getCircle();
        double diameter = currentCircle.getDiameter();
        Point center = currentCircle.getCenter();
        diameter = diameter * 15;
        center = center * 15;
        double centerX = center.getX();
        double centerY = center.getY();
        currentItem.setRect(centerX - 0.5 * diameter, centerY - 0.5 * diameter, diameter, diameter);


    }

    const Point robotPosition = m_model.getCurrentPosition();
    double positionX = robotPosition.getX();
    double positionY = robotPosition.getY();
    m_robot->setRect(positionX - 7,positionY - 7, 14, 14);
}
