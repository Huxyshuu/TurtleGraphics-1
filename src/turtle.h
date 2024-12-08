#ifndef TURTLE_H
#define TURTLE_H

#include "../ui/ui_mainwindow.h"
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QObject>
#include <queue>
#include <QTimer>

/**
 * @class Turtle
 * @brief Represents a turtle object that can move and draw paths in a graphics scene.
 */
class Turtle : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    /**
     * @brief Constructs a Turtle object with the given image path and scene.
     * @param imagePath Path to the turtle image.
     * @param scene Pointer to the QGraphicsScene where the turtle is displayed.
     * @param ui Pointer to the user interface
     */
    Turtle(const QString& imagePath, QGraphicsScene* scene, Ui::MainWindow* ui);
    ~Turtle();

    /**
     * @brief Moves the turtle forward by the specified distance.
     * @param distance Distance to move.
     */
    void forward(int distance);

    /**
     * @brief Rotates the turtle counter-clockwise by the specified angle.
     * @param angle Angle to turn in degrees.
     */
    void turn(int angle);

    /**
     * @brief Moves the turtle to the given position
     * @param x coordinate given as int
     * @param y coordinate given as int
     */
    void go(int x, int y);

    /**
     * @brief Sets whether the turtle is drawing as it moves.
     * @param drawing True to enable drawing, false to disable.
     */
    void setDrawing(bool drawing);

    /**
     * @brief Checks whether the turtle is currently drawing.
     * @return True if drawing is enabled, false otherwise.
     */
    bool getDrawing() const;

    /**
     * @brief Gets the current position of the turtle.
     * @return The current position as a pair of (x, y) coordinates.
     */
    std::pair<int, int> getPosition() const;

    /**
     * @brief Gets the current rotation of the turtle.
     * @return The rotation in degrees.
     */
    int getRotation() const;

    /**
     * @brief Sets the brush size for drawing.
     * @param value The size of the brush.
     */
    void setBrushSize(int value);

    /**
     * @brief Updates the brush color for drawing.
     * @param color The new brush color.
     */
    void updateBrushColor(QColor color);

    /**
     * @brief Resets the turtle and clears all drawn paths.
     */
    void resetTurtle();

    /**
     * @brief Adds a command to the command queue for sequential execution.
     * @param command The command to enqueue as a std::function.
     */
    void enqueueCommand(const std::function<void()>& command);

    /**
     * @brief Processes the next command in the queue, if available.
     */
    void processNextCommand();

    // Shape drawing functions
    void star();
    void triangle();
    void square();
    void rectangle();
    void circle();
    void cyclohexane();
    void house();
    void spinning(int sides);
    void random();

    std::pair<int, int> getGamePos();

    /**
     * @brief Gets the game-specific random position.
     * @return The random position as a pair of (x, y) coordinates.
     */
    std::pair<int, int> getGamePos();

    /**
     * @brief Updates the user interface with the turtle's current position and rotation.
     */
    void updateUI();

    /**
     * @brief Turns the turtle graphics into a game mode.
     */
    void gameify();

    void setHouse(QGraphicsPixmapItem* house);

    /**
     * @brief Sets the house object for the game mode.
     * @param house Pointer to the QGraphicsPixmapItem representing the house.
     */
    void setHouse(QGraphicsPixmapItem* house);

    /**
     * @brief Checks whether the game has been won by reaching the target area.
     * @return True if the game is won, false otherwise.
     */
    bool gameWon() const;

private slots:
    void onMoveStep();

private:
    QPixmap turtlePixmap_;

    int currentRotation_ = 0; // [0° - 360°] -> 0° (facing right) and 90° (facing up)
    std::pair<int, int> currentPosition_ = {0, 0};
    std::pair<int, int> randomPos_ = {0, 0};

    std::queue<std::function<void()>> commandQueue_;
    bool isProcessingCommand_ = false;

    QGraphicsScene* scene_;
    Ui::MainWindow* ui_;
    QGraphicsPathItem* pathItem_;
    QGraphicsPixmapItem* house_;

    QGraphicsPixmapItem* house_;

    double dx_;
    double dy_;
    int currentStep_;
    int steps_;
    double target_x_;
    double target_y_;
    QTimer *moveTimer_;

    int pensize_ = 1;
    QColor currentBrushColor_;
    bool drawing_ = true;
};

#endif // TURTLE_H
