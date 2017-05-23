#ifndef EMPLOYEEDATAMANAGERXML_H
#define EMPLOYEEDATAMANAGERXML_H

#include <QXmlStreamReader>
#include <QXmlStreamWriter>

#include "employeedatamanagerinterface.h"



class EmployeeDataManagerXml : public EmployeeDataManagerInterface
{
public:
    EmployeeDataManagerXml(){}

    /**
     * @brief readFromFile - implementation of interface's method
     * @param fileName - if file doesn't exist, empty list will be returned
     * @return - if any errors occur while parsing, list might be incomplete
     */
    QList<QSharedPointer<EmployeeTreeItem>> readFromSource(const QString& address) override;

    /**
     * @brief writeToFile - implementation of interface's method
     * @param roots - list with elements to dump
     * @param fileName - if filename doesn't exist - it will be created. If exists - overriden
     * @return true on success, false otherwize
     */
    bool writeToSource(const QList<QSharedPointer<EmployeeTreeItem>>& roots, const QString& address) override;

private:
    /**
     * @brief _writeEmployee - used for recursive dump of employees, if it has any subordinates
     * @param writer - ref for currently used XmlStreamWriter
     * @param employee - employee we're need to dump
     */
    void _writeEmployee(QXmlStreamWriter& writer, QSharedPointer<EmployeeTreeItem> employeeItem);
};

#endif // EMPLOYEEDATAMANAGERXML_H
