#ifndef EMPLOYEEITEM_H
#define EMPLOYEEITEM_H

#include <QString>
#include <QList>
#include <QDate>
#include <QDebug>
#include <QSharedPointer>
#include <QWeakPointer>


/**
 * @brief The Employee struct - contains all info about employee. POD class.
 */
struct Employee
{
    QString name = QObject::tr("[not_set]");
    QString surname = QObject::tr("[not_set]");
    QString patronymic = QObject::tr("[not_set]");
    QString appointment = QObject::tr("[not_set]");
    QDate   birthdate = QDate(2000, 01, 01);
};



/**
 * @brief The EmployeeTreeItem class.
 * Contains pointer to Employee struct (unique to prevent copying) and additional info, used in hierarchy tree:
 * list of subordinates (can be empty) and a weak pointer to employee's chief.
 */
class EmployeeTreeItem
{
public:
    EmployeeTreeItem();

    QScopedPointer<Employee> employee;

    QWeakPointer<EmployeeTreeItem> chief;
    QList<QSharedPointer<EmployeeTreeItem>> subordinates;

    EmployeeTreeItem(const EmployeeTreeItem&) = delete;
    EmployeeTreeItem& operator=(const EmployeeTreeItem&) = delete;
};

QDebug operator<<(QDebug d, EmployeeTreeItem* employeeItem);

#endif // EMPLOYEEITEM_H
