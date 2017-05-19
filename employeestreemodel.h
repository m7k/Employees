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
    virtual int rowCount(const QModelIndex& parent) const override;
    virtual int columnCount(const QModelIndex& parent) const override;

    virtual QModelIndex index(int row, int column, const QModelIndex& parent) const override;
    virtual QModelIndex parent(const QModelIndex& child) const override;

    virtual Qt::ItemFlags flags(const QModelIndex& index) const override;
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    virtual bool insertRows(int row, int count, const QModelIndex& parent) override;
    virtual bool removeRows(int row, int count, const QModelIndex& parent) override;

    // Custom functions
    void setRoots(QList<EmployeeItem*> roots);

private:
    QList<EmployeeItem*> _roots;
};

#endif // EMPLOYEESTREEMODEL_H
