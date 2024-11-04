#include <QDebug>
#include "turtle.h"

Turtle::Turtle(const QString& imagePath)
{
    turtlePixmap_ = QPixmap(imagePath);

    // Check if the image loaded successfully
    if (!turtlePixmap_.isNull()) {
        setPixmap(turtlePixmap_);

        // Move the origin of the pixmap to its center
        setOffset(turtlePixmap_.width() / -2.0, turtlePixmap_.height() / -2.0);

        qDebug() << "Turtle image loaded successfully from path:" << imagePath;
    } else {
        qDebug() << "Failed to load turtle image from path:" << imagePath;
    }
}

void Turtle::forward(int distance) {
    // Move in the current direction based on angle
    double radians = qDegreesToRadians((double)(currentRotation_));
    int dx = (int)(distance * std::cos(radians));
    int dy = (int)(distance * std::sin(radians));
    setPos(x() + dx, y() + dy);
};

void Turtle::turn(int angle) {
    currentRotation_ -= angle;
    setRotation(currentRotation_);

    // Mirror the pixmap if the angle is within 90° < angle < 270°
    if ((currentRotation_ % 360 > 90 && currentRotation_ % 360 < 270) ||
        (currentRotation_ % 360 < -90 && currentRotation_ % 360 > -270)) {

        setPixmap(turtlePixmap_.transformed(QTransform().scale(1, -1)));
    } else {
        setPixmap(turtlePixmap_);
    }
};

QPixmap Turtle::getPixmap() const {
    return turtlePixmap_;
}
