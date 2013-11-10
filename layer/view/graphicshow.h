#ifndef ROBOHOCKEY_LAYER_VIEW_GRAPHICSHOW_H
#define ROBOHOCKEY_LAYER_VIEW_GRAPHICSHOW_H


#include <QWidget>

class GraphicShow : public QWidget
{
    Q_OBJECT
public:
    explicit GraphicShow(QWidget *parent = 0);
    
signals:
    
public slots:
protected:
    void paintEvent(QPaintEvent *);
    
};

#endif // GRAPHICSHOW_H
