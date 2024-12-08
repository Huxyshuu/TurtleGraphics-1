#include "unittest.h"
#include "../src/storage.h"
#include <QGraphicsScene>
#include <iostream>
#include "../src/mainwindow.h"
#include "unittest.h"
#include <QApplication>
#include "../tests/unittest.h"
#include <iostream>


unittest::unittest() {}

void unittest::storageTest(){

    Storage storage;

    bool flag = false;

    storage.addToHistory("forward 10");
    storage.addToHistory("turn 90");
    storage.addToHistory("1294813yr13nfkansfsasc--<>Q€%/€%())=^^***^^ÂA-*22*'/n'   ff#%&/");

    int size = 3;

    if(storage.getModel()->stringList() != storage.getHistory()){
        std::cout << "Model fetching failed (history model)" << std::endl;
        flag = true;
    }

    //validate size
    if(storage.getHistory().size() != size){
        std::cout << "Adding failed" << std::endl;
        flag = true;

    }
    //validate order
    if(storage.getHistory().at(0) != "1294813yr13nfkansfsasc--<>Q€%/€%())=^^***^^ÂA-*22*'/n'   ff#%&/"
        && storage.getHistory().at(2) != "forward 10"){
        std::cout << "Wrong order in history" << std::endl;
        flag = true;
    }

    storage.clearHistory();
    //validate clearing
    if(storage.getHistory().size() != 0){
        std::cout << "Clear failed" << std::endl;
        flag = true;

    }

    storage.helpDisplay();
    //validates correct stringlist fetching
    if(storage.getModel()->stringList().isEmpty()){
        std::cout << "Model fetching failed (help display didn't change model)" << std::endl;
        flag = true;

    }

    storage.addToHistory("turn 90");
    //check if stringlist switched back to history from helplist
    if(storage.getModel()->stringList() != storage.getHistory()){
        std::cout << "Model fetching failed" << std::endl;
        flag = true;

    }

    if (flag == false) {
        std::cout << "Storage tests passed!" << std::endl;
    }
}

void unittest::turtleTest(MainWindow w){

    //this might cause some memory leaks so have to check this with valgrind...
    QGraphicsScene *scene = new QGraphicsScene(&w);
    Turtle *turtle = new Turtle(":/assets/turtle_mid.png", scene, w.getUi());
    scene->addItem(turtle);

    bool flag = false;

    //turtle testing
    std::pair<int, int> pos = turtle->getPosition();
    int rotation;

    if(pos.first != 0 && pos.second != 0){
        std::cout << "Starting position is not correctly displayed" << std::endl;
        flag = true;
    }

    //position testing
    turtle->go(10, 10);
    pos = turtle->getPosition();
    if(pos.first != 10 && pos.second != 10){
        std::cout << "Wrong positional data" << std::endl;
        flag = true;
    }

    //Rotation test
    turtle->turn(360+90);
    rotation = turtle->getRotation();

    if(rotation != -450){
        std::cout << "Overrotation interpeted as "<< rotation << std::endl;
        flag = true;
    }

    //position reset
    turtle->resetTurtle();

    if(turtle->getPosition().first != 0 && turtle->getPosition().second != 0){
        std::cout << "Position reset failed. Turtle location: "<< turtle->getPosition().first << " " << turtle->getPosition().second << std::endl;
        flag = true;
    }

    if(flag == false){
        std::cout << "Turtle tests passed!" << std::endl;
    }
}
