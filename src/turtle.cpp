#include <QDebug>
#include "turtle.h"
#include <QGraphicsScene>
#include <QGraphicsPathItem>
#include <QPainterPath>
#include <QtMath> // For qDegreesToRadians

Turtle::Turtle(const QString& imagePath, QGraphicsScene* scene)
{
    turtlePixmap_ = QPixmap(imagePath);
    scene_ = scene;

    // Check if the image loaded successfully
    if (!turtlePixmap_.isNull()) {
        setPixmap(turtlePixmap_);
        qDebug() << "Turtle image loaded successfully from path:" << imagePath;

    } else {
        qDebug() << "Failed to load turtle image from path:" << imagePath;
    }

    pathItem_ = new QGraphicsPathItem();
    pathItem_->setPen(QPen(Qt::black, 2));
    scene_->addItem(pathItem_);
}

void Turtle::forward(int distance) {
    // Record current point
    QPointF startPoint = pos();
    // Move in the current direction based on angle
    double radians = qDegreesToRadians((double)(currentRotation_));
    int dx = (int)(distance * std::cos(radians));
    int dy = (int)(distance * std::sin(radians));
    setPos(x() + dx, y() + dy);

    // Paint to the new target point
    QPainterPath path = pathItem_->path();
    if (path.isEmpty())
        path.moveTo(startPoint);
    path.lineTo(pos());
    pathItem_->setPath(path);
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
