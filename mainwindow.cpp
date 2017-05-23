#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "employeedatamanagerxml.h"
#include "employeestreemodel.h"




// ----------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow),
    _model(new EmployeesTreeModel(this))
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


    _ui->employeesTreeView->setModel(_model);
}
