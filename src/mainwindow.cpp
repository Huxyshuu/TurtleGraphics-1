#include "mainwindow.h"
#include "../ui/ui_mainwindow.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPixmap>
#include <QMessageBox>
#include <iostream>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene(this);

    QPixmap turtlePixmap(":/assets/turtle_mid.png"); // Path copied from the .qrc file. Mid picture seems like the best size as a default.

    if (!turtlePixmap.isNull()) {
        QGraphicsPixmapItem *turtleItem = new QGraphicsPixmapItem(turtlePixmap);

        // Add the item to the scene
        scene->addItem(turtleItem);

        ui->graphicsView->setScene(scene);
    } else {
        QMessageBox::warning(this, "Error", "Failed to load turtle image.");
        delete scene;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_lineEdit_returnPressed()
{
    QLineEdit *lineEdit = qobject_cast<QLineEdit*>(sender());

    if (lineEdit) {
        QString input = lineEdit->text();  // Get the entered text

        std::cout << input.toStdString() << std::endl;

        lineEdit->clear();
    }
}


