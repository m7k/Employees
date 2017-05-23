#include "mainwindow.h"
#include <QApplication>

#include "employeedatamanagerxml.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

#if 0  // Example of current testing
        // xml to read should placed in QApp working directory
    EmployeeDataManagerXml rdr;
    auto roots = rdr.readFromSource("xml.xml");

    rdr.writeToSource(roots, "xml2.xml");
#endif

    return a.exec();
}
