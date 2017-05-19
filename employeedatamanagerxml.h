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
    virtual QList<EmployeeItem*> readFromFile(const QString &fileName) override;

    /**
     * @brief writeToFile - implementation of interface's method
     * @param roots - list with elements to dump
     * @param fileName - if filename doesn't exist - it will be created. If exists - overriden
     * @return true on success, false otherwize
     */
    virtual bool writeToFile(QList<EmployeeItem*> roots, const QString &fileName) override;

private:
    /**
     * @brief _writeEmployee - used for recursive dump of employees, if it has any subordinates
     * @param writer - ref for currently used XmlStreamWriter
     * @param employee - employee we're need to dump
     */
    void _writeEmployee(QXmlStreamWriter& writer, EmployeeItem* employee);
};

#endif // EMPLOYEEDATAMANAGERXML_H
