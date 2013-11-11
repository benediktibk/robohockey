#include "layer/view/window.h"
#include "layer/view/graphicshow.h"
#include <QtGui>

Window::Window()
{
        view=new GraphicShow;
        QGridLayout *mainLayout = new QGridLayout;

        mainLayout->setColumnStretch(0,1);
        mainLayout->setColumnStretch(1,1);

        mainLayout->addWidget(view,0,0,0,0);
        setLayout(mainLayout);

        setWindowTitle("Robot_Control");

    }

