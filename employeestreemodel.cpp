#include "employeestreemodel.h"



// ----------------------------------------------------------------
EmployeesTreeModel::EmployeesTreeModel(QObject* parent /*= nullptr*/)
    : QAbstractItemModel(parent)
{

}



// ----------------------------------------------------------------
int EmployeesTreeModel::rowCount(const QModelIndex& parent) const
{
    auto parentItem = _itemByIndex(parent);

    return ((parentItem) ? (parentItem->subordinates.size()) : (_roots.size()));
}



// ----------------------------------------------------------------
int EmployeesTreeModel::columnCount(const QModelIndex& parent) const
{
    return 1;
}



// ----------------------------------------------------------------
QModelIndex EmployeesTreeModel::index(int row, int column, const QModelIndex& parent) const
{
    if(!hasIndex(row, column, parent))
        return QModelIndex();

    auto parentItem = _itemByIndex(parent);


    return createIndex(row, column, ((parentItem) ? (parentItem->subordinates.at(row).data()) : (_roots.at(row).data())) );
}



// ----------------------------------------------------------------
QModelIndex EmployeesTreeModel::parent(const QModelIndex& child) const
{
    if(!child.isValid())
        return QModelIndex();

    auto currItem = static_cast<EmployeeTreeItem*>(child.internalPointer());
    auto chiefRef = currItem->chief.toStrongRef();

    if(!chiefRef)
        return QModelIndex();

    auto chiefsChiefRef = chiefRef->chief.toStrongRef();

    int parentRow = 0;

    if(chiefsChiefRef)
    {
        for(int i = 0; i < chiefsChiefRef->subordinates.size(); i++)
        {
            if(chiefsChiefRef->subordinates.at(i).data() == chiefRef.data())
            {
                parentRow = i;
                break;
            }
        }
    }

    return createIndex(parentRow, 0, chiefRef.data());
}



// ----------------------------------------------------------------
Qt::ItemFlags EmployeesTreeModel::flags(const QModelIndex& index) const
{
    if(!index.isValid())
        return Qt::ItemIsEnabled;

    return (Qt::ItemIsEnabled | Qt::ItemIsSelectable);
}



// ----------------------------------------------------------------
QVariant EmployeesTreeModel::data(const QModelIndex& index, int role /*= Qt::DisplayRole*/) const
{
    if(!index.isValid())
        return QVariant();

    auto item = static_cast<EmployeeTreeItem*>(index.internalPointer());

    if(role == Qt::DisplayRole)
    {
        return item->employee->name;
    }

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



// ----------------------------------------------------------------
EmployeeTreeItem* EmployeesTreeModel::_itemByIndex(const QModelIndex& index) const
{
    if(!index.isValid())
        return nullptr;

    return static_cast<EmployeeTreeItem*>(index.internalPointer());
}
