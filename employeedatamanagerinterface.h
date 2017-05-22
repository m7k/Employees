#ifndef EMPLOYEEDATAMANAGERINTERFACE_H
#define EMPLOYEEDATAMANAGERINTERFACE_H

#include "employeeitem.h"



class EmployeeDataManagerInterface
{
public:
    virtual ~EmployeeDataManagerInterface(){}

    /**
     * @brief readFromFile - used to read employees info from file with expected format.
     * @param fileName - name of the file to read. It should exist, otherwize empty list will be returned
     * @return QList<EmployeeItem*> - list with items. If any errors occur, list can be incomplete
     */
    virtual QList<QSharedPointer<EmployeeTreeItem>> readFromSource(const QString& address) = 0;

    /**
     * @brief writeToFile - used to dump list of employees to file with format, specified in child classes
     * @param roots - list with items to dump
     * @param fileName - name of the file, where dump should be stored.
     * @return true, if writing was successfull, otherwize - false
     */
    virtual bool writeToSource(const QList<QSharedPointer<EmployeeTreeItem>>& roots, const QString& address) = 0;
};

#endif // EMPLOYEEDATAMANAGERINTERFACE_H
