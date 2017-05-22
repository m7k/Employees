#include "employeestreemodel.h"



// ----------------------------------------------------------------
EmployeesTreeModel::EmployeesTreeModel(QObject* parent /*= nullptr*/)
    : QAbstractItemModel(parent)
{

}



// ----------------------------------------------------------------
int EmployeesTreeModel::rowCount(const QModelIndex& parent) const
{
    return 0;
}



// ----------------------------------------------------------------
int EmployeesTreeModel::columnCount(const QModelIndex& parent) const
{
    return 0;
}



// ----------------------------------------------------------------
QModelIndex EmployeesTreeModel::index(int row, int column, const QModelIndex& parent) const
{
    return QModelIndex();
}



// ----------------------------------------------------------------
QModelIndex EmployeesTreeModel::parent(const QModelIndex& child) const
{
    return QModelIndex();
}



// ----------------------------------------------------------------
Qt::ItemFlags EmployeesTreeModel::flags(const QModelIndex& index) const
{
    return Qt::ItemIsEnabled;
}



// ----------------------------------------------------------------
QVariant EmployeesTreeModel::data(const QModelIndex& index, int role) const
{
    return QVariant();
}



// ----------------------------------------------------------------
bool EmployeesTreeModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    return false;
}



// ----------------------------------------------------------------
bool EmployeesTreeModel::insertRows(int row, int count, const QModelIndex& parent)
{
    return false;
}



// ----------------------------------------------------------------
bool EmployeesTreeModel::removeRows(int row, int count, const QModelIndex& parent)
{
    return false;
}



// ----------------------------------------------------------------
void EmployeesTreeModel::setRoots(const QList<QSharedPointer<EmployeeTreeItem> >& roots)
{
    beginResetModel();
    _roots = roots;
    endResetModel();
}
