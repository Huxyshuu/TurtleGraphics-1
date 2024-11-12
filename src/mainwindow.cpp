#include "mainwindow.h"
#include "../ui/ui_mainwindow.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPixmap>
#include <QMessageBox>
#include <iostream>
#include <QDir>
#include <sstream>
#include <QFile>
#include <QTextStream>
#include "turtle.h"
#include "storage.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , storage(new Storage())
{
    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene(this);

    // Create a Turtle object
    Turtle *turtle = new Turtle(":/assets/turtle_mid.png", scene);
    setTurtle(turtle);

    // Add the item to the scene
    scene->addItem(turtle);

    // Draws a red circle in the center of the screen
    QGraphicsEllipseItem *dot = scene->addEllipse(-5, -5, 10, 10, QPen(Qt::red), QBrush(Qt::red));
    scene->addItem(dot);

    ui->graphicsView->setScene(scene);

    // Keep the view from moving or adjusting when the turtle moves
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setSceneRect(-200, -165, 400, 330);

    //create new storage object
    if (storage->getModel()) {
        ui->listView->setModel(storage->getModel());  // Set the storage model to display history
    } else {
        std::cerr << "Error: Storage model is not initialized!\n";
    }

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_uploadButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setTurtle(Turtle *turtle) {
    turtle_ = turtle;
}

// Parses input commands from user
std::pair<std::string, int> MainWindow::parseCommand(const std::string& input) {
    std::istringstream stream(input);
    std::string command;
    int value = 0;

    if (!(stream >> command)) {
         throw std::invalid_argument("Invalid input");
    }
    if (stream >> value) {
        return {command, value};
    }

    return {command, value}; // returns just the command without a real value
}

void MainWindow::updateTurtleUI(Turtle& turtle) {
    ui->label->setText("Current position: (" + QString::number(turtle.getPosition().first) + ", " + QString::number(turtle.getPosition().second) + ")");
    ui->label_2->setText("Current rotation: " + QString::number(-turtle.getRotation() % 360) + "°");
}


// Input text bar
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
            QString str = ( QString::fromStdString(commandData.first) + " " + QString::number(commandData.second) );

            if (commandData.first == "forward") {
                turtle_->forward(commandData.second);
                storage->addToHistory(str);
            }

            if (commandData.first == "go") {
                std::cout << "This go function needs a better parsing to work :(" << std::endl;
            }

            if (commandData.first == "pen") {
                std::cout << "Pen function" << std::endl;
            }

            if (commandData.first == "pen") {
                std::cout << "Pen function" << std::endl;
            }

            if (commandData.first == "help") {
                storage->helpDisplay();
            }

            if (commandData.first == "turn") {
                turtle_->turn(commandData.second);
                storage->addToHistory(str);
            }

        } catch (const std::invalid_argument& error) {
            std::cerr << error.what() << std::endl; // typing a string into int causes error
        }

        lineEdit->clear();
        updateTurtleUI(*turtle_);
    }
}

// Upload file
void MainWindow::on_uploadButton_clicked()
{
    // This whole function should probably be moved to the storage.cpp/h according to the initial plan?
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Command File"), "", tr("Text Files (*.txt)"));
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Error"), tr("Unable to open file"));
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        std::string command = line.toStdString();

        // Makes all commands lowercase, so user doesn't have to worry about
        // case-sensitivty
        for (auto& c : command) {
            c = tolower(c);
        }

        try {
            std::pair<std::string, int> commandData = parseCommand(command);
            std::cout << commandData.first << " " << commandData.second << std::endl;
            QString str = ( QString::fromStdString(commandData.first) + " " + QString::number(commandData.second) );

            if (commandData.first == "forward") {
                turtle_->forward(commandData.second);
                storage->addToHistory(str);
            }

            if (commandData.first == "turn") {
                turtle_->turn(commandData.second);
                storage->addToHistory(str);
            }

        } catch (const std::invalid_argument& error) {
            std::cerr << error.what() << std::endl; // typing a string into int causes error
        }
    }
    file.close();
}

void MainWindow::on_radioButton_toggled(bool checked)
{
    turtle_->setDrawing(checked);
    if (checked) {
        storage->addToHistory("pen down");
    } else {
        storage->addToHistory("pen up");
    }
}

