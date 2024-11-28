#include "mainwindow.h"
#include <QApplication>
#include "../tests/unittest.h"

int main(int argc, char *argv[])
{
    //testing functions
    unittest tester;
    tester.storageTest();

    QApplication a(argc, argv);
    MainWindow w;

    MainWindow test;
    tester.turtleTest(&test);

    w.show();
    return a.exec();
}
