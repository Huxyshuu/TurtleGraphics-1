#include <QDebug>
#include "turtle.h"
#include <QGraphicsScene>
#include <QGraphicsPathItem>
#include <QPainterPath>
#include <QtMath> // For qDegreesToRadians
#include <QTimer>

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
    double delta_x = distance * std::cos(radians);
    double delta_y = distance * std::sin(radians);

    target_x_ = currentPosition_.first + delta_x;
    target_y_ = currentPosition_.second + delta_y;

    steps_ = static_cast<int>(distance / 1.5); // each move step size is 1.5
    dx_ = delta_x / steps_;
    dy_ = delta_y / steps_;
    currentStep_ = 0;

    moveTimer_ = new QTimer(this);
    connect(moveTimer_, &QTimer::timeout, this, &Turtle::onMoveStep);
    moveTimer_->start(100); // move every 80 ms
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

// Smoothly move
void Turtle::onMoveStep() {
    if (currentStep_ < steps_) {
        setPos(x() + dx_, y() + dy_);
        currentPosition_.first += dx_;
        currentPosition_.second += dy_;

        if (drawing_) {
            QPainterPath path = pathItem_->path();
            path.lineTo(pos());
            pathItem_->setPath(path);
        }

        currentStep_++;
    } else {
        moveTimer_->stop();
        moveTimer_->deleteLater();
        Turtle::go(target_x_, target_y_);
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

void Turtle::setBrushSize(int value){
    pensize_ = value;
    pathItem_->setPen(QPen(Qt::black, value));
    // QPixmap scaledPixmap = turtlePixmap_.scaled(10*pensize_, 10*pensize_, Qt::KeepAspectRatio);
    // setPixmap(scaledPixmap);
    // setOffset(turtlePixmap_.width() / -2.0, turtlePixmap_.height() / -2.0);
}

void Turtle::resetTurtle() {
    // Clears all turtle paths
    QPainterPath newPath;
    pathItem_->setPath(newPath);
    qDebug() << "Turtle reset!";

    // Reset the rotation and position of turtle
    go(0, 0);
    turn(currentRotation_);
    currentPosition_ = {0, 0};
    currentRotation_ = 0;
}
