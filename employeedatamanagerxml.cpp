#include "employeedatamanagerxml.h"

#include <QFile>
#include <QStack>

#include "defines.h"


// ----------------------------------------------------------------
QList<EmployeeItem*> EmployeeDataManagerXml::readFromFile(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return QList<EmployeeItem*>();
    }

    QXmlStreamReader reader(&file);

    EmployeeItem* currentEmployee = nullptr;
    QList<EmployeeItem*> roots;
    QStack<EmployeeItem*> chiefsStack;

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
                Q_ASSERT(!currentEmployee && !chiefsStack.size() && "Current employee should be nullprt atm");
                continue;
            }

            if(reader.name() == EMPLOYEE_TAG)
            {
                /* new employee upcoming. need to create it usig approriate chief and
                     * parse it's attributes
                     */
                if(chiefsStack.size())
                    currentEmployee = new EmployeeItem(chiefsStack.top());
                else
                {
                    currentEmployee = new EmployeeItem();
                    roots.append(currentEmployee);
                }

                QXmlStreamAttributes attrs = reader.attributes();
                if(attrs.hasAttribute(NAME_ATTR))
                {
                    currentEmployee->setName(attrs.value(NAME_ATTR).toString());
                }
                if(attrs.hasAttribute(SURNAME_ATTR))
                {
                    currentEmployee->setSurname(attrs.value(SURNAME_ATTR).toString());
                }
                if(attrs.hasAttribute(PATRONYMIC_ATTR))
                {
                    currentEmployee->setPatronymic(attrs.value(PATRONYMIC_ATTR).toString());
                }
                if(attrs.hasAttribute(APPOINTMENT_ATTR))
                {
                    currentEmployee->setAppointment(attrs.value(APPOINTMENT_ATTR).toString());
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
                Q_ASSERT(currentEmployee && "Current employee can't be nullptr atm");
                chiefsStack.push(currentEmployee);
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
bool EmployeeDataManagerXml::writeToFile(QList<EmployeeItem*> roots, const QString &fileName)
{
    QFile file(fileName);
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
void EmployeeDataManagerXml::_writeEmployee(QXmlStreamWriter& writer, EmployeeItem* employee)
{
    /// ToDo: think about: if employee is nullptr, should we dump empty employee or not?
    writer.writeStartElement(EMPLOYEE_TAG);
    if(employee)
    {
        // if employee isn't nullptr, we can parse it's attributes and subordinates
        writer.writeAttribute(NAME_ATTR, employee->name());
        writer.writeAttribute(SURNAME_ATTR, employee->surname());
        writer.writeAttribute(PATRONYMIC_ATTR, employee->patronymic());
        writer.writeAttribute(APPOINTMENT_ATTR, employee->appointment());
        /// ToDo: atm format isn't chosen, so can't convert birthdate from QDate to QString, writing empty string atm
        writer.writeAttribute(BIRTHDATE_ATTR, QString(""));

        // Parsing employee's subordinates recursively
        if(employee->subordinates().size())
        {
            writer.writeStartElement(SUBORDINATES_BLOCK_TAG);
            for(auto sub : employee->subordinates())
            {
                _writeEmployee(writer, sub);
            }
            writer.writeEndElement();
        }
    }

    writer.writeEndElement();
}
