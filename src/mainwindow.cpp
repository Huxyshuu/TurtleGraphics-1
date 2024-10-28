#include "mainwindow.h"
#include "../ui/ui_mainwindow.h"
#include <QMessageBox>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

