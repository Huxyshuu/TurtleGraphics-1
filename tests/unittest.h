#ifndef UNITTEST_H
#define UNITTEST_H
#include <QApplication>
#include "../src/mainwindow.h"

class unittest
{
public:
    unittest();
    /**
     * @brief storageTest tests functions from storage.h
     */
    void storageTest();

    /**
     * @brief turtleTest tests functions from turtle.h
     * @param w is the mainwindow parameter so the test can create a new turtle that works as a testing turtle.
     */
    void turtleTest(MainWindow w);
};

#endif // UNITTEST_H
