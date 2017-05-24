#ifndef EMPLOYEEDATAMANAGERINTERFACE_H
#define EMPLOYEEDATAMANAGERINTERFACE_H

#include "employeeitem.h"



class EmployeeDataManagerInterface
{
public:
    virtual ~EmployeeDataManagerInterface(){}

    /**
     * @brief readFromSource - used to read employees info from source, accessed by address.
     * @param address - address to access the source. In case of DB, it can be connection string.
     * @return QList<EmployeeItem*> - list with items. If any errors occur, list can be incomplete
     */
    virtual QList<QSharedPointer<EmployeeTreeItem>> readFromSource(const QString& address) = 0;

    /**
     * @brief writeToSource - used to dump list of employees to source.
     * @param roots - list with items to dump
     * @param address - address of the source, where dump should be stored.
     * @return true, if writing was successfull, otherwize - false
     */
    virtual bool writeToSource(const QList<QSharedPointer<EmployeeTreeItem>>& roots, const QString& address) = 0;
};

#endif // EMPLOYEEDATAMANAGERINTERFACE_H
