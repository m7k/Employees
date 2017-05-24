#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

#include "employeedatamanagerxml.h"
#include "employeestreemodel.h"




// ----------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow),
    _model(new EmployeesTreeModel(this)),
    _xmlManager(new EmployeeDataManagerXml())
{
    _init();
}



// ----------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete _ui;
    delete _xmlManager;
}



// ----------------------------------------------------------------
void MainWindow::_onCurrentRowChanged(const QModelIndex& current, const QModelIndex& previous)
{

    if(current.isValid())
    {
        // current item is valid -> we can add new employee anyway
        _ui->addEmployeeBtn->setEnabled(true);

        if(current.parent().isValid())
        {
            // but we can delete only elements under fake-root
            _ui->removeEmployeeBtn->setEnabled(true);
        }
        else
        {
            _ui->removeEmployeeBtn->setEnabled(false);
        }
    }
    else
    {
        // we can't delete not existing element or add any element after it
        _ui->removeEmployeeBtn->setEnabled(false);
        _ui->addEmployeeBtn->setEnabled(false);
    }
}



// ----------------------------------------------------------------
void MainWindow::_onAddEmployeeBtnClicked()
{
    auto currRowIndex = _ui->employeesTreeView->selectionModel()->currentIndex();
    _model->insertRows(_model->rowCount(currRowIndex), 1, currRowIndex);
}



// ----------------------------------------------------------------
void MainWindow::_onRemoveEmployeeBtnClicked()
{
    auto currRowIndex = _ui->employeesTreeView->selectionModel()->currentIndex();
    if(currRowIndex.isValid())
    {
        auto result = QMessageBox::warning(this, tr("[deletion_warning]"), tr("[current_item_will_be_deleted.Proceed?]"), QMessageBox::Ok, QMessageBox::Cancel);
        if(result == QMessageBox::Ok)
            _model->removeRows(currRowIndex.row(), 1, currRowIndex.parent());
    }
}



// ----------------------------------------------------------------
void MainWindow::_init()
{
    _ui->setupUi(this);

    _ui->employeesTreeView->setAcceptDrops(true);
    _ui->employeesTreeView->setModel(_model);

    Q_ASSERT(connect(_ui->employeesTreeView->selectionModel(), &QItemSelectionModel::currentRowChanged, this, &MainWindow::_onCurrentRowChanged));
    Q_ASSERT(connect(_ui->addEmployeeBtn, &QPushButton::clicked, this, &MainWindow::_onAddEmployeeBtnClicked));
    Q_ASSERT(connect(_ui->removeEmployeeBtn, &QPushButton::clicked, this, &MainWindow::_onRemoveEmployeeBtnClicked));
    Q_ASSERT(connect(_ui->openBtn, &QPushButton::clicked, this, [this]()
    {
        _showFileDialog();
    }));
    Q_ASSERT(connect(_ui->saveAsBtn, &QPushButton::clicked, this, [this]()
    {
        _showFileDialog(QFileDialog::AcceptSave);
    }));
    Q_ASSERT(connect(_ui->saveBtn, &QPushButton::clicked, this, [this]()
    {
        if(_lastOpennedFile.isEmpty())
            return;
        _xmlManager->writeToSource(_model->getRoots(), _lastOpennedFile);
    }));
}



// ----------------------------------------------------------------
void MainWindow::_showFileDialog(QFileDialog::AcceptMode dialogAcceptRole)
{
    QFileDialog dial(this);
    dial.setAcceptMode(dialogAcceptRole);
    dial.setDefaultSuffix(".xml");
    dial.setNameFilters(QStringList() << QString("%1 \(*.xml\)").arg(tr("[xml_document]")));
    if(dialogAcceptRole == QFileDialog::AcceptOpen)
    {
        dial.setWindowTitle(tr("[open_xml_with_employyes]"));
        dial.setFileMode(QFileDialog::ExistingFile);
    }
    if(dialogAcceptRole == QFileDialog::AcceptSave)
    {
        dial.setWindowTitle(tr("[save_xml_with_employees]"));
        dial.setFileMode(QFileDialog::AnyFile);
    }

    if(dial.exec() == QDialog::Accepted)
    {
        auto fileName = dial.selectedFiles().at(0);
        if(dialogAcceptRole == QFileDialog::AcceptOpen)
        {
            _model->setRoots(_xmlManager->readFromSource(fileName));
            _lastOpennedFile=fileName;
        }
        if(dialogAcceptRole == QFileDialog::AcceptSave)
        {
            _xmlManager->writeToSource(_model->getRoots(), fileName);
            _lastOpennedFile = fileName;
        }
    }

}
