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
    QString name;
    QString surname;
    QString patronymic;
    QString appointment;
    QDate   birthdate;
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
    EmployeeTreeItem(const EmployeeTreeItem&) = delete;
    ~EmployeeTreeItem(){ qDebug() << "~Item"; }

    QScopedPointer<Employee> employee;

    QWeakPointer<EmployeeTreeItem> chief;
    QList<QSharedPointer<EmployeeTreeItem>> subordinates;

private:
    EmployeeTreeItem& operator=(const EmployeeTreeItem&);
};

QDebug operator<<(QDebug d, EmployeeTreeItem* employeeItem);

#endif // EMPLOYEEITEM_H
