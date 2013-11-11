#ifndef ROBOHOCKEY_LAYER_VIEW_WINDOW_H
#define ROBOHOCKEY_LAYER_VIEW_WINDOW_H

#include <QWidget>

class GraphicShow;

class Window : public QWidget
{
    Q_OBJECT
public:
    Window();
    
signals:
    
public slots:

private:
    GraphicShow *view;
    
};

#endif // WINDOW_H
