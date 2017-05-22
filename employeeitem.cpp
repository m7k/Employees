#include "employeeitem.h"



// ----------------------------------------------------------------
EmployeeTreeItem::EmployeeTreeItem()
    : employee(new Employee())
{

}



// ----------------------------------------------------------------
QDebug operator<<(QDebug d, EmployeeTreeItem* employeeItem)
{
    if(employeeItem)
    {
        d   << "name: " << employeeItem->employee->name
            << "; surname: " << employeeItem->employee->surname
            << "; patronymic: " << employeeItem->employee->patronymic
            << "; appointment: " << employeeItem->employee->appointment
            << "; birthdate: " << employeeItem->employee->birthdate
            << "; subordinates nums: " << employeeItem->subordinates.size()
            << "; chief: " << ((employeeItem->chief.toStrongRef()) ? ("valid") : ("not_valid")) ;
    }
    else
    {
        d << "Employee is nullptr";
    }

    return d;
}



