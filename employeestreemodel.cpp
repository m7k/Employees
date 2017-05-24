#include "employeestreemodel.h"

#include <QMimeData>
#include <QDataStream>


const QString EmployeesTreeModel::EMPLOYEE_MIME_TYPE_NAME("EmployeesMimeType");


// ----------------------------------------------------------------
EmployeesTreeModel::EmployeesTreeModel(QObject* parent /*= nullptr*/)
    : QAbstractItemModel(parent)
    , _root(new EmployeeTreeItem())
{
    _root->employee->name = tr("[root_element]");
}



// ----------------------------------------------------------------
int EmployeesTreeModel::rowCount(const QModelIndex& parent) const
{
    // parent invalid -> we have root element, row count is 1
    if(!parent.isValid())
        return 1;

    return static_cast<EmployeeTreeItem*>(parent.internalPointer())->subordinates.size();
}



// ----------------------------------------------------------------
int EmployeesTreeModel::columnCount(const QModelIndex& parent) const
{
    return 5;
}



// ----------------------------------------------------------------
QModelIndex EmployeesTreeModel::index(int row, int column, const QModelIndex& parent) const
{
    if(!hasIndex(row, column, parent))
        return QModelIndex();

    return createIndex(row, column,  ((parent.isValid()) ? (static_cast<EmployeeTreeItem*>(parent.internalPointer())->subordinates.at(row).data()) : (_root.data())));
}



// ----------------------------------------------------------------
QModelIndex EmployeesTreeModel::parent(const QModelIndex& child) const
{
    if(!child.isValid())
        return QModelIndex();

    auto currItem = static_cast<EmployeeTreeItem*>(child.internalPointer());
    auto chiefRef = currItem->chief.toStrongRef();

    // if !chiefRef - child is root element, and it's parent index is invalid index
    if(!chiefRef)
        return QModelIndex();

    auto chiefsChiefRef = chiefRef->chief.toStrongRef();

    // defining parent row to create index
    int parentRow = 0;

    // if !chiefsChiefRef - we got root element and it's row is 0
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

    // Root is not editable or dragable, but drop is enabled
    if(static_cast<EmployeeTreeItem*>(index.internalPointer()) == _root.data())
        return (Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDropEnabled);

    return (Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled);
}



// ----------------------------------------------------------------
Qt::DropActions EmployeesTreeModel::supportedDropActions() const
{
    return Qt::MoveAction;
}



// ----------------------------------------------------------------
QStringList EmployeesTreeModel::mimeTypes() const
{
    QStringList types;
    types << EMPLOYEE_MIME_TYPE_NAME;
    return types;
}



// ----------------------------------------------------------------
QVariant EmployeesTreeModel::headerData(int section, Qt::Orientation orientation, int role /*= Qt::DisplayRole*/) const
{
    if(role != Qt::DisplayRole)
        return QVariant();

    if(orientation == Qt::Horizontal)
    {
        switch(section)
        {
            case Column::Name:
                return tr("[name]");
                break;
            case Column::Surname:
                return tr("[surname]");
                break;
            case Column::Patronymic:
                return tr("[patronymic]");
                break;
            case Column::Appointment:
                return tr("[appointment]");
                break;
            case Column::Birthdate:
                return tr("[birthdate]");
                break;
            default:
                return QVariant();
                break;
        }
    }

    return QVariant();
}



// ----------------------------------------------------------------
QVariant EmployeesTreeModel::data(const QModelIndex& index, int role /*= Qt::DisplayRole*/) const
{
    if(!index.isValid())
        return QVariant();

    auto item = static_cast<EmployeeTreeItem*>(index.internalPointer());

    if(role == Qt::DisplayRole || role == Qt::EditRole)
    {
        if(item == _root.data())
        {
            if(index.column() == (int)Column::Name)
                return item->employee->name;
            else
                return QVariant();
        }
        else
        {
            switch(index.column())
            {
            case Column::Name:
                return item->employee->name;
                break;
            case Column::Surname:
                return item->employee->surname;
                break;
            case Column::Patronymic:
                return item->employee->patronymic;
                break;
            case Column::Appointment:
                return item->employee->appointment;
                break;
            case Column::Birthdate:
                return item->employee->birthdate;
                break;
            default:
                return QVariant();
                break;
            }
        }
    }

    return QVariant();
}



// ----------------------------------------------------------------
QMimeData* EmployeesTreeModel::mimeData(const QModelIndexList& indexes) const
{
    if(indexes.isEmpty() || !indexes.at(0).isValid())
        return nullptr;

    auto elemAddr = (quintptr)(indexes.at(0).internalPointer());

    QByteArray encodedData(QString::number(elemAddr).toUtf8());

    auto mimeData = new QMimeData();
    mimeData->setData(EMPLOYEE_MIME_TYPE_NAME, encodedData);
    return mimeData;
}



// ----------------------------------------------------------------
bool EmployeesTreeModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if(!index.isValid())
        return false;

    auto item = static_cast<EmployeeTreeItem*>(index.internalPointer());

    if(role == Qt::EditRole)
    {
        switch(index.column())
        {
        case Column::Name:
            item->employee->name = value.toString();
            break;
        case Column::Surname:
            item->employee->surname = value.toString();
            break;
        case Column::Patronymic:
            item->employee->patronymic = value.toString();
            break;
        case Column::Appointment:
            item->employee->appointment = value.toString();
            break;
        case Column::Birthdate:
            item->employee->birthdate = value.toDate();
            break;
        default:
            return false;
            break;
        }

        emit dataChanged(index, index);
        return true;
    }

    return true;
}



// ----------------------------------------------------------------
bool EmployeesTreeModel::insertRows(int row, int count, const QModelIndex& parent)
{
    // It's not supposed to have any elements on fake root element level
    if(!parent.isValid())
        return false;

    const int last = row + count - 1;

    auto chiefItem = static_cast<EmployeeTreeItem*>(parent.internalPointer());
    const auto chiefShared = _getSharedForItem(chiefItem);

    beginInsertRows(parent, row, last);


    for(int i = row; i <= last; i++)
    {
        chiefItem->subordinates.insert(i, QSharedPointer<EmployeeTreeItem>::create());
        chiefItem->subordinates.at(i)->chief = chiefShared;
    }

    endInsertRows();

    return true;
}



// ----------------------------------------------------------------
bool EmployeesTreeModel::removeRows(int row, int count, const QModelIndex& parent)
{
    // It's not supposed you can delete fake root
    if(!parent.isValid())
        return false;

    const int last = row + count - 1;

    auto chiefItem = static_cast<EmployeeTreeItem*>(parent.internalPointer());

    beginRemoveRows(parent, row, last);

    for(int i = last; i <= row; i++)
    {
        chiefItem->subordinates.takeAt(i);
    }

    endRemoveRows();

    return true;
}



// ----------------------------------------------------------------
bool EmployeesTreeModel::moveRows(const QModelIndex& sourceParent, int sourceRow, int count, const QModelIndex& destinationParent, int destinationChild)
{
    // It's not supposed to move any elements on one level with fake-root or move fake-root itself
    if(!destinationParent.isValid() || !sourceParent.isValid())
        return false;

    const int lastSourceR = sourceRow + count - 1;


    const auto sourceParentItem = static_cast<EmployeeTreeItem*>(sourceParent.internalPointer());
    const auto destinationParentItem = static_cast<EmployeeTreeItem*>(destinationParent.internalPointer());
    const auto destinationParentShared = _getSharedForItem(destinationParentItem);

    beginMoveRows(sourceParent, sourceRow, lastSourceR, destinationParent, destinationChild);

    for(int i = destinationChild + 1; i <= destinationChild + count; i++)
    {
        auto pointerToMove = sourceParentItem->subordinates.takeAt(sourceRow);
        pointerToMove->chief = destinationParentShared;
        destinationParentItem->subordinates.insert(i, pointerToMove);
    }

    endMoveRows();

    return true;
}



// ----------------------------------------------------------------
bool EmployeesTreeModel::dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent)
{
    if(action == Qt::IgnoreAction || !data)
        return false;

    if(!data->hasFormat(EMPLOYEE_MIME_TYPE_NAME))
        return false;

    if(!parent.isValid())
        return false;

    QByteArray encodedData = data->data(EMPLOYEE_MIME_TYPE_NAME);
    auto elemAddr = (EmployeeTreeItem*)encodedData.toULongLong();
    if(!elemAddr)
        return false;
    if(elemAddr == _root.data())
        return false;

    auto oldChiefIndex = _getElementIndex(elemAddr->chief.toStrongRef().data());
    auto newChiefIndex = _getElementIndex(static_cast<EmployeeTreeItem*>(parent.internalPointer()));
    // if oldChiefIndex is the same as newChiefIndex, don't need to do anything
    if(oldChiefIndex == newChiefIndex)
        return false;
    auto oldElementsIndex = _getElementIndex(elemAddr);

    moveRows(oldChiefIndex, oldElementsIndex.row(), 1, newChiefIndex, 0);

    // returning false to prevent deletion of row, that was transferred
    return false;
}



// ----------------------------------------------------------------
const QList<QSharedPointer<EmployeeTreeItem>> EmployeesTreeModel::getRoots() const
{
    return _root->subordinates;
}



// ----------------------------------------------------------------
void EmployeesTreeModel::setRoots(const QList<QSharedPointer<EmployeeTreeItem> >& roots)
{
    beginResetModel();

    _root->subordinates.clear();
    _root->subordinates.append(roots);

    for(auto subroot : _root->subordinates)
    {
        subroot->chief = _root;
    }

    endResetModel();
}



// ----------------------------------------------------------------
QModelIndex EmployeesTreeModel::_getElementIndex(EmployeeTreeItem* item)
{
    if(!item)
        return QModelIndex();

    auto chiefRef = item->chief.toStrongRef();
    if(chiefRef)
    {
        for(int i = 0; i < chiefRef->subordinates.size(); i++)
        {
            if(chiefRef->subordinates.at(i).data() == item)
                return createIndex(i, 0, item);
        }
    }
    else
    {
        // we have root element
        return createIndex(0, 0, item);
    }

    return QModelIndex();
}



// ----------------------------------------------------------------
QSharedPointer<EmployeeTreeItem> EmployeesTreeModel::_getSharedForItem(EmployeeTreeItem* item)
{
    if(!item)
        return QSharedPointer<EmployeeTreeItem>();

    auto chiefRef = item->chief.toStrongRef();

    if(chiefRef)
    {
        for(int i = 0; i < chiefRef->subordinates.size(); i++)
        {
            if(chiefRef->subordinates.at(i).data() == item)
                return QSharedPointer<EmployeeTreeItem>(chiefRef->subordinates.at(i));
        }
    }
    else
    {
        // we got root element
        return QSharedPointer<EmployeeTreeItem>(_root);
    }

    return QSharedPointer<EmployeeTreeItem>();
}
