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
std::pair<std::string, std::string> MainWindow::parseCommand(const std::string& input) {
    std::istringstream stream(input);
    std::string command;
    std::string arguments;

    if (!(stream >> command)) {
        throw std::invalid_argument("Invalid input");
    }

    std::getline(stream, arguments); // Capture the rest of the line as arguments
    if (!arguments.empty() && arguments[0] == ' ') {
        arguments.erase(0, 1); // Remove leading space if present
    }

    return {command, arguments};
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
            std::pair<std::string, std::string> commandData = parseCommand(command);
            QString str = ( QString::fromStdString(commandData.first) + " " + QString::fromStdString(commandData.second) );

            if (commandData.first == "forward" || commandData.first == "turn") {
                int value = std::stoi(commandData.second);
                if (commandData.first == "forward") {
                    turtle_->forward(value);
                } else {
                    turtle_->turn(value);
                }
                storage->addToHistory(str);
            }

            else if (commandData.first == "go") {
                std::istringstream argsStream(commandData.second);
                int x, y;
                if (argsStream >> x >> y) {
                    turtle_->go(x, y);
                    storage->addToHistory(str);
                } else {
                    std::cerr << "Invalid arguments for 'go' command\n";
                }
            }

            else if (commandData.first == "pen") {
                if (commandData.second == "up" && turtle_->getDrawing()) {
                    updatingRadioButton_ = true;
                    turtle_->setDrawing(false);
                    ui->radioButton->setChecked(false);
                    updatingRadioButton_ = false;
                    storage->addToHistory(str);
                } else if (commandData.second == "down" && !turtle_->getDrawing()) {
                    updatingRadioButton_ = true;
                    turtle_->setDrawing(true);
                    ui->radioButton->setChecked(true);
                    updatingRadioButton_ = false;
                    storage->addToHistory(str);
                }
            }

            else if (commandData.first == "help") {
                storage->helpDisplay();
            }

        } catch (const std::invalid_argument& error) {
            std::cerr << "Invalid input! Error: " << error.what() << std::endl; // typing a string into int causes error
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
            std::pair<std::string, std::string> commandData = parseCommand(command);
            QString str = ( QString::fromStdString(commandData.first) + " " + QString::fromStdString(commandData.second) );

            if (commandData.first == "forward" || commandData.first == "turn") {
                int value = std::stoi(commandData.second);
                if (commandData.first == "forward") {
                    turtle_->forward(value);
                } else {
                    turtle_->turn(value);
                }
                storage->addToHistory(str);
            }

        } catch (const std::invalid_argument& error) {
            std::cerr << "Invalid input! Error: " << error.what() << std::endl; // typing a string into int causes error
        }
    }
    file.close();
}

void MainWindow::on_radioButton_toggled(bool checked)
{
    turtle_->setDrawing(checked);
    if (!updatingRadioButton_) {
        if (checked) {
            storage->addToHistory("pen down");
        } else {
            storage->addToHistory("pen up");
        }
    }

    ui->lineEdit->setFocus(); // Focus back on the input field
}

