#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

#include "turtle.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setTurtle(Turtle *turtle);
    std::pair<std::string, int> parseCommand(const std::string& input);

private slots:
    void on_lineEdit_returnPressed();

private:
    Ui::MainWindow *ui;
    Turtle* turtle_;
};
#endif // MAINWINDOW_H
