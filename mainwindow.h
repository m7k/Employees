#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>

class EmployeeDataManagerXml;
class EmployeesTreeModel;
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void _onCurrentRowChanged(const QModelIndex& current, const QModelIndex& previous);
    void _onAddEmployeeBtnClicked();
    void _onRemoveEmployeeBtnClicked();

private:
    Ui::MainWindow* _ui;
    EmployeesTreeModel* _model;
    EmployeeDataManagerXml* _xmlManager;
    QString _lastOpennedFile;

    void _init();
    void _showFileDialog(QFileDialog::AcceptMode dialogAcceptRole = QFileDialog::AcceptOpen);
};

#endif // MAINWINDOW_H
