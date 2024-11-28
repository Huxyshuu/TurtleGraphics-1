#ifndef TURTLE_H
#define TURTLE_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QObject>
#include <queue>
#include <QTimer> // For time sleep
#include "../ui/ui_mainwindow.h"


class Turtle : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Turtle(const QString& imagePath, QGraphicsScene* scene, Ui::MainWindow* ui);

    /**
     * @brief Moves the turtle in the facing direction a distance given
     * @param distance to be moved as a int
     */
    void forward(int distance);

    /**
     * @brief Rotates the turtle counter-clockwise the amount specified in angle
     * @param angle to be turned as a int
     */
    void turn(int angle);

    /**
     * @brief Moves the turtle to the given position
     * @param x coordinate given as int
     * @param y coordinate given as int
     */
    void go(int x, int y);

    void setDrawing(bool drawing);
    bool getDrawing() const;

    std::pair<int, int> getPosition() const;
    int getRotation() const;

    void setBrushSize(int value);
    void updateBrushColor(QColor color);

    /**
     * @brief Resets the turtle and clears all drawn paths
     */
    void resetTurtle();

    /**
     * @brief Updates the user interface with the turtle's current position and rotation.
     */
    void updateUI();

    /**
     * @brief Adds a command to the command queue for sequential execution.
     * @param a command function representing the command to enqueue.
     */
    void enqueueCommand(const std::function<void()>& command);

    /**
     * @brief Processes the next command in the queue, if available.
     */
    void processNextCommand();
    void star();
    void triangle();
    void square();
    void rectangle();
    void circle();
    void cyclohexane();
    void house();
    /**
     * @brief gameify turns the turtle graphics to a game. Turtle needs to move to the designated area to win.
     */
    void gameify();

    /**
     * @brief gameWon checks wether the turtle is in the designated area to display a win message.
     * @return return true if the turtle is in the correct location and false if not.
     */
    bool gameWon() const;

private slots:
    void onMoveStep();

private:
    QPixmap turtlePixmap_;

    int currentRotation_ = 0; // [0° - 360°] -> 0° (facing right) and 90° (facing up)
    std::pair<int, int> currentPosition_ = {0, 0}; // Turtle position as a pair of ints (x, y)
    std::pair<int, int> randomPos_ = {0, 0};
    bool drawing_ = true;

    std::queue<std::function<void()>> commandQueue_;
    bool isProcessingCommand_ = false;

    QGraphicsScene* scene_;
    Ui::MainWindow* ui_;
    QGraphicsPathItem* pathItem_;

    double dx_;
    double dy_;
    int currentStep_;
    int steps_;
    double target_x_;
    double target_y_;
    QTimer *moveTimer_;

    int pensize_;
    QColor currentBrushColor_;
};

#endif // TURTLE_H
