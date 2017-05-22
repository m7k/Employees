#include "employeedatamanagerxml.h"

#include <QFile>
#include <QStack>

#include "defines.h"


// ----------------------------------------------------------------
QList<QSharedPointer<EmployeeTreeItem> > EmployeeDataManagerXml::readFromSource(const QString& address)
{
    QFile file(address);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return QList<QSharedPointer<EmployeeTreeItem>>();
    }

    QXmlStreamReader reader(&file);

    QSharedPointer<EmployeeTreeItem> currEmployeeItem;
    QList<QSharedPointer<EmployeeTreeItem>> roots;
    QStack<QSharedPointer<EmployeeTreeItem>> chiefsStack;

    while(!reader.atEnd() && !reader.hasError())
    {
        QXmlStreamReader::TokenType token = reader.readNext();
        if(token == QXmlStreamReader::StartDocument)
            continue;

        if(token == QXmlStreamReader::StartElement)
        {
            if(reader.name() == EMPLOYEES_BLOCK_TAG)
            {
                // we only start parsing, current employee should be empty, as well as chiefs stack
                Q_ASSERT(currEmployeeItem.isNull() && !chiefsStack.size() && "Current employee should be nullprt atm");
                continue;
            }

            if(reader.name() == EMPLOYEE_TAG)
            {
                /* new employee upcoming. need to create it usig approriate chief and
                     * parse it's attributes
                     */
                currEmployeeItem = QSharedPointer<EmployeeTreeItem>(new EmployeeTreeItem());
                if(chiefsStack.size())
                {
                    chiefsStack.top()->subordinates.append(currEmployeeItem);
                    currEmployeeItem->chief = chiefsStack.top();
                }
                else
                {
                    roots.append(currEmployeeItem);
                }

                QXmlStreamAttributes attrs = reader.attributes();
                if(attrs.hasAttribute(NAME_ATTR))
                {
                    currEmployeeItem->employee->name = attrs.value(NAME_ATTR).toString();
                }
                if(attrs.hasAttribute(SURNAME_ATTR))
                {
                    currEmployeeItem->employee->surname = attrs.value(SURNAME_ATTR).toString();
                }
                if(attrs.hasAttribute(PATRONYMIC_ATTR))
                {
                    currEmployeeItem->employee->patronymic = attrs.value(PATRONYMIC_ATTR).toString();
                }
                if(attrs.hasAttribute(APPOINTMENT_ATTR))
                {
                    currEmployeeItem->employee->appointment = attrs.value(APPOINTMENT_ATTR).toString();
                }
                if(attrs.hasAttribute(BIRTHDATE_ATTR))
                {
                    /// ToDo: when format will be selected, here should be written converting from string to date
                }
                continue;
            }


            if(reader.name() == SUBORDINATES_BLOCK_TAG)
            {
                /* If subordinate block is found, we need to cache current employee for future
                     * (we can't know for sure, if it's subordinates are regular employees or chiefs itself)
                    */
                Q_ASSERT(!currEmployeeItem.isNull() && "Current employee can't be nullptr atm");
                chiefsStack.push(currEmployeeItem);
                continue;
            }
        }
        if(token == QXmlStreamReader::EndElement)
        {
            if(reader.name() == EMPLOYEES_BLOCK_TAG)
            {
                // End of whole employees block parsing
                continue;
            }
            if(reader.name() == EMPLOYEE_TAG)
            {
                // End of parsing single employee
                continue;
            }
            if(reader.name() == SUBORDINATES_BLOCK_TAG)
            {
                /* Subordinates block finished, we can remove stack's top
                 */
                chiefsStack.pop();
                continue;
            }
        }

    }
    if(reader.hasError())
    {
        qDebug() << "Error: " << reader.errorString();
    }
    else
    {
        // if no errors occur while parsing, chiefs stack should be empty
        Q_ASSERT(!chiefsStack.size() && "parsing finished, stack should be empty");
    }
    return roots;
}




// ----------------------------------------------------------------
bool EmployeeDataManagerXml::writeToSource(const QList<QSharedPointer<EmployeeTreeItem> >& roots, const QString& address)
{
    QFile file(address);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
    {
        qDebug() << "Error openning/creating file for writing";
        return false;
    }

    QXmlStreamWriter writer(&file);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();

    writer.writeStartElement(EMPLOYEES_BLOCK_TAG);

    for(auto root : roots)
    {
        _writeEmployee(writer, root);
    }

    writer.writeEndElement();

    writer.writeEndDocument();
    return true;
}



// ----------------------------------------------------------------
void EmployeeDataManagerXml::_writeEmployee(QXmlStreamWriter& writer, QSharedPointer<EmployeeTreeItem> employeeItem)
{
    /// ToDo: think about: if employee is nullptr, should we dump empty employee or not?
    writer.writeStartElement(EMPLOYEE_TAG);
    if(employeeItem)
    {
        // if employee isn't nullptr, we can parse it's attributes and subordinates
        writer.writeAttribute(NAME_ATTR, employeeItem->employee->name);
        writer.writeAttribute(SURNAME_ATTR, employeeItem->employee->surname);
        writer.writeAttribute(PATRONYMIC_ATTR, employeeItem->employee->patronymic);
        writer.writeAttribute(APPOINTMENT_ATTR, employeeItem->employee->appointment);
        /// ToDo: atm format isn't chosen, so can't convert birthdate from QDate to QString, writing empty string atm
        writer.writeAttribute(BIRTHDATE_ATTR, QString("") /* employeeItem->employee->birthDate */);

        // Parsing employee's subordinates recursively
        if(employeeItem->subordinates.size())
        {
            writer.writeStartElement(SUBORDINATES_BLOCK_TAG);
            for(auto sub : employeeItem->subordinates)
            {
                _writeEmployee(writer, sub);
            }
            writer.writeEndElement();
        }
    }

    writer.writeEndElement();
}


