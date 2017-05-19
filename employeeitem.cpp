#include "employeeitem.h"



// ----------------------------------------------------------------
EmployeeItem::EmployeeItem()
    : _chief(nullptr)
{

}


// ----------------------------------------------------------------
EmployeeItem::EmployeeItem(EmployeeItem* chief)
    : _chief(chief)
{
    _chief->appendSubordinate(this);
}



// ----------------------------------------------------------------
EmployeeItem::~EmployeeItem()
{
    for(auto subordinate : _subordinates)
    {
        delete subordinate;
    }
}



// ----------------------------------------------------------------
int EmployeeItem::rowForSubordinate(const EmployeeItem* employee) const
{
    for(int i = 0; i < _subordinates.size(); i++)
    {
        if(_subordinates.at(i) == employee)
            return i;
    }
    return -1;
}



// ----------------------------------------------------------------
EmployeeItem* EmployeeItem::subordinate(const int pos) const
{
    return nullptr;
}



// ----------------------------------------------------------------
void EmployeeItem::appendSubordinate(EmployeeItem* employee)
{
    insertSubordinate(_subordinates.size(), employee);
}



// ----------------------------------------------------------------
void EmployeeItem::insertSubordinate(const int pos, EmployeeItem* employee)
{
    _subordinates.append(employee);
}



// ----------------------------------------------------------------
EmployeeItem* EmployeeItem::removeSubordinate(const int pos)
{
    return nullptr;
}

QDebug operator<<(QDebug d, EmployeeItem* employee)
{
    if(employee)
    {
        d   << "name: " << employee->name()
            << "; surname: " << employee->surname()
            << "; patronymic: " << employee->patronymic()
            << "; appointment: " << employee->appointment()
            << "; birthdate: " << employee->birthDate();
    }
    else
    {
        d << "Employee is nullptr";
    }

    return d;
}
