#ifndef TURTLE_H
#define TURTLE_H

#include <QGraphicsPixmapItem>
#include <QPixmap>

class Turtle : public QGraphicsPixmapItem
{
public:
    Turtle(const QString& imagePath, QGraphicsScene* scene);

    void forward(int distance);
    void turn(int angle);

    QPixmap getPixmap() const;

private:
    QPixmap turtlePixmap_;

    int currentRotation_ = 0; // [0° - 360°] -> 0° (facing right) and 90° (facing up)
    QGraphicsScene* scene_;
    QGraphicsPathItem* pathItem_;
};

#endif // TURTLE_H
