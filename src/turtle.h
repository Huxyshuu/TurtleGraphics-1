#ifndef TURTLE_H
#define TURTLE_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QObject>
#include <QTimer> // For time sleep


class Turtle : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Turtle(const QString& imagePath, QGraphicsScene* scene);

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

private slots:
    void onMoveStep();

private:
    QPixmap turtlePixmap_;

    int currentRotation_ = 0; // [0° - 360°] -> 0° (facing right) and 90° (facing up)
    std::pair<int, int> currentPosition_ = {0, 0}; // Turtle position as a pair of ints (x, y)

    bool drawing_ = true;

    QGraphicsScene* scene_;
    QGraphicsPathItem* pathItem_;

    int dx_;
    int dy_;
    int currentStep_;
    int steps_;
    double target_x_;
    double target_y_;
    QTimer *moveTimer_;
};

#endif // TURTLE_H
