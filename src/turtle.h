#ifndef TURTLE_H
#define TURTLE_H

#include <QGraphicsPixmapItem>
#include <QPixmap>

class Turtle : public QGraphicsPixmapItem
{
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

private:
    QPixmap turtlePixmap_;

    int currentRotation_ = 0; // [0° - 360°] -> 0° (facing right) and 90° (facing up)
    QGraphicsScene* scene_;
    QGraphicsPathItem* pathItem_;
};

#endif // TURTLE_H
