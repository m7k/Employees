#ifndef EMPLOYEESTREEMODEL_H
#define EMPLOYEESTREEMODEL_H

#include <QAbstractItemModel>

#include "employeeitem.h"

/**
 * @brief The EmployeesTreeModel class - EMPTY REALIZATION ATM!
 */

class EmployeesTreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    EmployeesTreeModel(QObject* parent = nullptr);

    // Implementations of QAbstractItemModel's class functions
    int rowCount(const QModelIndex& parent) const override;
    int columnCount(const QModelIndex& parent) const override;

    QModelIndex index(int row, int column, const QModelIndex& parent) const override;
    QModelIndex parent(const QModelIndex& child) const override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    bool insertRows(int row, int count, const QModelIndex& parent) override;
    bool removeRows(int row, int count, const QModelIndex& parent) override;

    // Custom functions
    void setRoots(const QList<QSharedPointer<EmployeeTreeItem>>& roots);

private:
    QList<QSharedPointer<EmployeeTreeItem>> _roots;

    EmployeeTreeItem* _itemByIndex(const QModelIndex& index) const;
//    int _rowForItem(EmployeeTreeItem* item, Employee)
};

#endif // EMPLOYEESTREEMODEL_H
