#include "mainwindow.h"
#include "../ui/ui_mainwindow.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPixmap>
#include <QMessageBox>
#include <iostream>
#include <QDir>
#include "turtle.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene(this);

    // Create a Turtle object
    Turtle *turtle = new Turtle(":/assets/turtle_mid.png", scene);
    setTurtle(turtle);

    // Add the item to the scene
    scene->addItem(turtle);

    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Parses input commands from user
std::pair<std::string, int> MainWindow::parseCommand(const std::string& input) {
    std::istringstream stream(input);
    std::string command;
    int value;

    if (stream >> command >> value) {
        return {command, value};
    } else {
        throw std::invalid_argument("Invalid input");
    }
}

void MainWindow::setTurtle(Turtle *turtle) {
    turtle_ = turtle;
}


void MainWindow::on_lineEdit_returnPressed()
{
    QLineEdit *lineEdit = qobject_cast<QLineEdit*>(sender());

    if (lineEdit) {
        QString input = lineEdit->text();  // Get the entered text

        std::string command = input.toStdString();

        // Makes all commands lowercase, so user doesn't have to worry about
        // case-sensitivty
        for (auto& c : command) {
            c = tolower(c);
        }

        try {
            std::pair<std::string, int> commandData = parseCommand(command);
            std::cout << commandData.first << " " << commandData.second << std::endl;

            if (commandData.first == "forward") {
                turtle_->forward(commandData.second);
            }

            if (commandData.first == "turn") {
                turtle_->turn(commandData.second);
            }

        } catch (const std::invalid_argument& error) {
            std::cerr << error.what() << std::endl; // typing a string into int causes error
        }

        lineEdit->clear();


    }
}


