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
     * @brief readFromSource - implementation of interface's method
     * @param address - if file, accessible by path=address, doesn't exist, empty list will be returned
     * @return - if any errors occur while parsing, list might be incomplete
     */
    QList<QSharedPointer<EmployeeTreeItem>> readFromSource(const QString& address) override;

    /**
     * @brief writeToSource - implementation of interface's method
     * @param roots - list with elements to dump
     * @param address - if filename, accessible by path=address,  doesn't exist - it will be created. If exists - overriden
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

    // Static Constants, used for parsing. Can be moved to public, if will be needed outside this class
    static const QString EMPLOYEES_BLOCK_TAG;
    static const QString EMPLOYEE_TAG;
    static const QString SUBORDINATES_BLOCK_TAG;

    static const QString NAME_ATTR;
    static const QString SURNAME_ATTR;
    static const QString PATRONYMIC_ATTR;
    static const QString APPOINTMENT_ATTR;
    static const QString BIRTHDATE_ATTR;
    static const QString DATE_FORMAT;
};

#endif // EMPLOYEEDATAMANAGERXML_H
