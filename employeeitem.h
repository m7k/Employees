#ifndef EMPLOYEEITEM_H
#define EMPLOYEEITEM_H

#include <QString>
#include <QList>
#include <QDate>
#include <QDebug>


/**
 * @brief The EmployeeItem class. Contains info about emplyee: name, surname, patronymic, appointment and birthdate.
 * Also contains info about employee's chief and subordinates (used for building employees hierarchy tree)
 */
class EmployeeItem
{
public:
    explicit EmployeeItem();
    explicit EmployeeItem(EmployeeItem* chief);
    ~EmployeeItem();

    // Getters and setters block
    QString name() const { return _name; }
    QString surname() const { return _surname; }
    QString patronymic() const { return _patronymic; }
    QString appointment() const { return _appointment; }
    QDate   birthDate() const { return _birthdate; }

    void setName(const QString& name) { _name = name; }
    void setSurname(const QString& surname) { _surname = surname; }
    void setPatronymic(const QString& patronymic) { _patronymic = patronymic; }
    void setAppointment(const QString& appointment) { _appointment = appointment; }
    void setBirthDate(const QDate& birthdate) { _birthdate = birthdate; }

    const EmployeeItem* chief() const { return _chief; }
    QList<EmployeeItem*> subordinates() const { return _subordinates; }

    // Custom functions. Will be used in model for employees
    int rowForSubordinate(const EmployeeItem* employee) const;
    EmployeeItem* subordinate(const int pos) const;


    void appendSubordinate(EmployeeItem* employee);
    void insertSubordinate(const int pos, EmployeeItem* employee);
    EmployeeItem* removeSubordinate(const int pos);

private:
    QString _name;
    QString _surname;
    QString _patronymic;
    QString _appointment;
    QDate   _birthdate;

    EmployeeItem*           _chief;
    QList<EmployeeItem*>    _subordinates;
};

QDebug operator<<(QDebug d, EmployeeItem* employee);

#endif // EMPLOYEEITEM_H
