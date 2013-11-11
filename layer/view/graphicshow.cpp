#include "layer/view/graphicshow.h"
#include <QWidget>
#include <QtGui>

GraphicShow::GraphicShow(QWidget *parent) :
    QWidget(parent)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}

void GraphicShow::paintEvent(QPaintEvent *)
{
    QRect rect(100,30,50,40);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setBrush(Qt::red);
    painter.drawEllipse(rect);
}
