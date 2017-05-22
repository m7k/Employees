#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "employeedatamanagerxml.h"




// ----------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow)
{
    _init();
}



// ----------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete _ui;
}



// ----------------------------------------------------------------
void MainWindow::_init()
{
    _ui->setupUi(this);
}
