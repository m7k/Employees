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
    auto roots = rdr.readFromFile("xml.xml");

    rdr.writeToFile(roots, "xml2.xml");
    for(auto r : roots)
        delete r;
#endif

    return a.exec();
}
