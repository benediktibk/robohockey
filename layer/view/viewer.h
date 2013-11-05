#ifndef ROBOHOCKEY_LAYER_VIEW_VIEWER_H
#define ROBOHOCKEY_LAYER_VIEW_VIEWER_H

#include <QtGui/QDialog>

namespace Ui {
class viewer;
}

class viewer : public QDialog
{
    Q_OBJECT
    
public:
    explicit viewer(QWidget *parent = 0);
    ~viewer();
    
private:
    Ui::viewer *ui;
};

#endif // VIEWER_H
