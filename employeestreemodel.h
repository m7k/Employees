#ifndef EMPLOYEESTREEMODEL_H
#define EMPLOYEESTREEMODEL_H

#include <QAbstractItemModel>

#include "employeeitem.h"

/**
 * @brief The EmployeesTreeModel class - used for representing EmployeeTreeItems' hierarchy.
 * In model indexes (QModelIndex) in internal pointers are stored raw pointers to EmployeesTreeItems.
 * This is normal, because all QModelIndexes are regenerated after any operations, changing model.
 *
 * All new roots, passed to the model are stored under fake-root vertex. This is used for proper drag&drop or
 * insert operations. Fake root can't be deleted, dragged or no items can be inserted at it's level.
 *
 * @warning Drag&Drop support is made only for usage inside this model!
 */

class EmployeesTreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    enum class Column
    {
        Name = 0,
        Surname,
        Patronymic,
        Appointment,
        Birthdate
    };

    EmployeesTreeModel(QObject* parent = nullptr);

    // Implementations of QAbstractItemModel's class functions
    int rowCount(const QModelIndex& parent) const override;
    int columnCount(const QModelIndex& parent) const override;

    QModelIndex index(int row, int column, const QModelIndex& parent) const override;
    QModelIndex parent(const QModelIndex& child) const override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;
    Qt::DropActions supportedDropActions() const override;
    QStringList mimeTypes() const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QMimeData* mimeData(const QModelIndexList& indexes) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    bool insertRows(int row, int count, const QModelIndex& parent) override;
    bool removeRows(int row, int count, const QModelIndex& parent) override;
    bool moveRows(const QModelIndex &sourceParent, int sourceRow, int count, const QModelIndex &destinationParent, int destinationChild) override;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) override;

    // Custom functions
    /**
     * @brief getRoots - returning list of all real roots (items, underlying the fake-root element).
     * Mainly should be used for deserializing model.
     *
     * @return
     */
    const QList<QSharedPointer<EmployeeTreeItem>> getRoots() const;

    /**
     * @brief setRoots - setting new roots. All current roots will be dropped.
     * @param roots
     */
    void setRoots(const QList<QSharedPointer<EmployeeTreeItem>>& roots);

private:
    QSharedPointer<EmployeeTreeItem> _root;

    /**
     * @brief _getElementIndex - used for retrieving QModelIndex for provided EmployeeTreeItem
     * @param item - supposed not to be nullptr, but if so, will return QModelIndex()
     * @return
     */
    QModelIndex _getElementIndex(EmployeeTreeItem* item);

    /**
     * @brief _getSharedForItem - used for retrieving QSharedPointer, that originall manages provided EmployeeTreeItem
     * raw pointer
     * @param item
     * @return empty QSharedPointer, if passed EmployeeTreeItem is nullptr;
     */
    QSharedPointer<EmployeeTreeItem> _getSharedForItem(EmployeeTreeItem* item);

    static const QString EMPLOYEE_MIME_TYPE_NAME;
};

#endif // EMPLOYEESTREEMODEL_H
