#include <QDebug>
#include "turtle.h"
#include <QGraphicsScene>
#include <QGraphicsPathItem>
#include <QPainterPath>
#include <QGraphicsView>
#include <QtMath> // For qDegreesToRadians
#include <QTimer>
#include "../ui/ui_mainwindow.h"


Turtle::Turtle(const QString& imagePath, QGraphicsScene* scene, Ui::MainWindow* ui)
{
    turtlePixmap_ = QPixmap(imagePath);
    scene_ = scene;
    ui_ = ui;

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

    steps_ = static_cast<int>(distance / 1); // step size
    dx_ = (delta_x / steps_); // these have to be double for non-axial movement to work... i'm crying
    dy_ = (delta_y / steps_);
    currentStep_ = 0;

    moveTimer_ = new QTimer(this);
    connect(moveTimer_, &QTimer::timeout, this, &Turtle::onMoveStep);
    moveTimer_->start(10); // move every given ms
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
    updateUI();
};

void Turtle::go(int x, int y) {
    setPos(x, y);

    // Draws a line
    if (drawing_) {
        QPainterPath path = pathItem_->path();
        path.lineTo(pos());
        pathItem_->setPath(path);
    }
    updateUI();
}

// Smoothly move
void Turtle::onMoveStep() {
    double nextX = x() + dx_;
    double nextY = y() + dy_;

    qDebug() << "nextX: ( " << x() << " + " << dx_ << " ) and nextY: (" << y() << " + " << dy_ << " )";

    QRectF visibleBounds = ui_->graphicsView->sceneRect();

    target_x_ = nextX;
    target_y_ = nextY;

    bool crossingBoundary = false;

    // Boundary check and crossing
    if (nextX > visibleBounds.right()) {
        target_x_ = visibleBounds.left();
        crossingBoundary = true;
    } else if (nextX < visibleBounds.left()) {
        target_x_ = visibleBounds.right();
        crossingBoundary = true;
    }

    if (nextY > visibleBounds.bottom()) {
        target_y_ = visibleBounds.top();
        crossingBoundary = true;
    } else if (nextY < visibleBounds.top()) {
        target_y_ = visibleBounds.bottom();
        crossingBoundary = true;
    }

    if (currentStep_ < steps_) {
        setPos(target_x_, target_y_);

        // Draw when not crossing the border
        if (drawing_) {
            QPainterPath path = pathItem_->path();

            if (crossingBoundary) {
                // Start a new path to avoid connecting across the boundary
                path.moveTo(pos());
            } else {
                // Continue the existing path
                path.lineTo(pos());
            }
            pathItem_->setPath(path);
        }

        currentStep_++;
    } else {
        moveTimer_->stop();
        moveTimer_->deleteLater();
        Turtle::go(target_x_, target_y_);
    }
    updateUI();
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
    return { x(), y() };
};

int Turtle::getRotation() const {
    return currentRotation_;
};

void Turtle::setBrushSize(int value){
    pensize_ = value;
    pathItem_->setPen(QPen(currentBrushColor_, value));
    // QPixmap scaledPixmap = turtlePixmap_.scaled(10*pensize_, 10*pensize_, Qt::KeepAspectRatio);
    // setPixmap(scaledPixmap);
    // setOffset(turtlePixmap_.width() / -2.0, turtlePixmap_.height() / -2.0);
}

void Turtle::updateBrushColor(QColor color){
    currentBrushColor_ = color;
    if (pensize_){
        pathItem_->setPen(QPen(currentBrushColor_, pensize_));
    }
    else {
        pathItem_->setPen(QPen(currentBrushColor_, 1));
    }
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

void Turtle::updateUI() {
    ui_->label->setText("Current position: (" + QString::number(x() ,'f', 1) + ", " + QString::number(y() ,'f', 1) + ")");
    ui_->label_2->setText("Current rotation: " + QString::number(-currentRotation_ % 360) + "°");
}
