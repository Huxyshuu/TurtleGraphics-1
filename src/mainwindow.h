#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "turtle.h"
#include "storage.h"
#include <QMainWindow>
#include <QGraphicsScene>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/**
 * @class MainWindow
 * @brief Represents the main window of the application, managing the UI and interactions with the turtle.
 */
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

    void setHouse(QGraphicsPixmapItem* house);

    /**
     * @brief Sets the house object in the scene.
     * @param house Pointer to the QGraphicsPixmapItem representing the house.
     */
    void setHouse(QGraphicsPixmapItem* house);

    /**
     * @brief Parses the input string into a pair <string, int>
     * @param input string as a std::string reference
     * @return a pair containing the command and the command value (e.g., distance, angle)
     */
    std::pair<std::string, std::string> parseCommand(const std::string& input);

    /**
     * @brief Updates the turtles position and rotation into the UI
     */
    void updateTurtleUI(Turtle& turtle);

    /**
     * @brief getUi returns the ui
     * @return ui
     */
    Ui::MainWindow* getUi() const;


private slots:
    void on_lineEdit_returnPressed();
    void on_uploadButton_clicked();

    void on_radioButton_toggled(bool checked);
    void updateBrushSize(int value);
    void openColorDialog();

    void on_pushButton_2_pressed();

private:
    Ui::MainWindow *ui;
    Turtle* turtle_;
    QGraphicsPixmapItem* house_ = nullptr;
    QStringList history;
    QStringList helplist;
    Storage *storage;
    bool updatingRadioButton_ = false;
    QWidget *colorWidget;
    QColor currentBrushColor;
    QGraphicsScene *scene_;
};
#endif // MAINWINDOW_H
