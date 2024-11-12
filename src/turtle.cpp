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

        // Move the origin of the pixmap to its center
        setOffset(turtlePixmap_.width() / -2.0, turtlePixmap_.height() / -2.0);

        qDebug() << "Turtle image loaded successfully from path:" << imagePath;
    } else {
        qDebug() << "Failed to load turtle image from path:" << imagePath;
    }

    pathItem_ = new QGraphicsPathItem();
    pathItem_->setPen(QPen(Qt::black, 2));
    scene_->addItem(pathItem_);
}

void Turtle::forward(int distance) {
    // Move in the current direction based on angle
    double radians = qDegreesToRadians((double)(currentRotation_));
    int dx = (int)(distance * std::cos(radians));
    int dy = (int)(distance * std::sin(radians));
    setPos(x() + dx, y() + dy);
    currentPosition_.first += dx;
    currentPosition_.second += dy;

    // Draws a line
    if (drawing_) {
        QPainterPath path = pathItem_->path();
        path.lineTo(pos());
        pathItem_->setPath(path);
    }
};

void Turtle::turn(int angle) {
    currentRotation_ -= angle;
    setRotation(currentRotation_);

    // Mirror the pixmap if the angle is within 90° < angle < 270° (counter-clockwise)
    if ((currentRotation_ % 360 > 90 && currentRotation_ % 360 < 270) ||
        (currentRotation_ % 360 < -90 && currentRotation_ % 360 > -270)) {

        setPixmap(turtlePixmap_.transformed(QTransform().scale(1, -1)));
    } else {
        setPixmap(turtlePixmap_);
    }
};

void Turtle::go(int x, int y) {
    setPos(x, y);
    currentPosition_.first = x;
    currentPosition_.second = y;

    // Draws a line
    if (drawing_) {
        QPainterPath path = pathItem_->path();
        path.lineTo(pos());
        pathItem_->setPath(path);
    }
}

void Turtle::setDrawing(bool drawing) {
    drawing_ = drawing;

    // Draws a line
    if (drawing_) {
        QPainterPath path = pathItem_->path();
        path.moveTo(pos());
        pathItem_->setPath(path);
    }
}

bool Turtle::getDrawing() const {
    return drawing_;
}

std::pair<int, int> Turtle::getPosition() const {
    return currentPosition_;
};

int Turtle::getRotation() const {
    return currentRotation_;
};
