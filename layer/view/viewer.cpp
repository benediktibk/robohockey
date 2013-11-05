#include "layer/view/viewer.h"
#include "layer/view/ui_viewer.h"


viewer::viewer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::viewer)
{
    ui->setupUi(this);
}

viewer::~viewer()
{
    delete ui;
}
