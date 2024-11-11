#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QFileDialog>

#include "turtle.h"
#include "storage.h"

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

    /**
     * @brief Sets the given turtle object as the main turtle of the app
     * @param turtle object as a pointer
     */
    void setTurtle(Turtle *turtle);

    /**
     * @brief Parses the input string into a pair <string, int>
     * @param input string as a std::string reference
     * @return a pair containing the command and the command value (e.g., distance, angle)
     */
    std::pair<std::string, int> parseCommand(const std::string& input);

    /**
     * @brief Updates the turtles position and rotation into the UI
     */
    void updateTurtleUI(Turtle& turtle);

private slots:
    void on_lineEdit_returnPressed();
    void on_uploadButton_clicked();

    void on_radioButton_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    Turtle* turtle_;
    QStringList history;
    QStringList helplist;
    Storage *storage;
};
#endif // MAINWINDOW_H
