#include <QDebug>
#include "turtle.h"
#include <QGraphicsScene>
#include <QGraphicsPathItem>
#include <QPainterPath>
#include <QGraphicsView>
#include <QtMath> // For qDegreesToRadians
#include <QTimer>
#include "../ui/ui_mainwindow.h"
#include <QMessageBox>
#include <cstdlib>
#include <iostream>

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
    } else {
        qDebug() << "Failed to load turtle image from path:" << imagePath;
    }

    pathItem_ = new QGraphicsPathItem(this);
    pathItem_->setPen(QPen(Qt::black, 1));
    scene_->addItem(pathItem_);
}

Turtle::~Turtle() {
};

void Turtle::forward(int distance) {
    enqueueCommand([=]() {
        double radians = qDegreesToRadians((double)(currentRotation_));
        double delta_x = distance * std::cos(radians);
        double delta_y = distance * std::sin(radians);

        double step_size = 1;
        steps_ = fmax(1, fmin(10, static_cast<int>(abs(distance) / step_size)));
        dx_ = (delta_x / steps_);
        dy_ = (delta_y / steps_);
        currentStep_ = 0;

        moveTimer_ = new QTimer(this);
        connect(moveTimer_, &QTimer::timeout, this, &Turtle::onMoveStep);
        moveTimer_->start(10); // ms
    });

    qDebug() << "Done now!";
}

void Turtle::turn(int angle) {
    enqueueCommand([=]() {
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

        processNextCommand();
    });
};

void Turtle::go(int x, int y) {
    enqueueCommand([=]() {
        setPos(x, y);

        if (drawing_) {
            QPainterPath path = pathItem_->path();
            path.lineTo(pos());
            pathItem_->setPath(path);
        }
        updateUI();

        processNextCommand();
    });
}

void Turtle::onMoveStep() {
    double nextX = x() + dx_;
    double nextY = y() + dy_;

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

    }
    currentStep_++;
    if (currentStep_ >= steps_) { // is last step
        moveTimer_->stop();
        moveTimer_->deleteLater();
        moveTimer_ = nullptr;
        setPos(target_x_, target_y_);

        if(gameWon()){
            house_->setVisible(false);
        }

        processNextCommand();
    }
    updateUI();
}

void Turtle::setDrawing(bool drawing) {
    drawing_ = drawing;

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

void Turtle::setHouse(QGraphicsPixmapItem* house) {
    house_ = house;
};

void Turtle::resetTurtle() {
    QPainterPath newPath;
    pathItem_->setPath(newPath);

    go(0, 0);
    turn(currentRotation_);
    currentPosition_ = {0, 0};
    currentRotation_ = 0;
}

void Turtle::updateUI() {
    ui_->label->setText("Current position: (" + QString::number(x() ,'f', 1) + ", " + QString::number(y() ,'f', 1) + ")");
    ui_->label_2->setText("Current rotation: " + QString::number(-currentRotation_ % 360) + "°");
}

void Turtle::enqueueCommand(const std::function<void()>& command) {
    commandQueue_.push(command);
    if (!isProcessingCommand_) {
        processNextCommand();
    }
}

void Turtle::processNextCommand() {
    if (!commandQueue_.empty()) {
        isProcessingCommand_ = true;
        auto nextCommand = commandQueue_.front();
        commandQueue_.pop();
        nextCommand();
    } else {
        isProcessingCommand_ = false;
    }
}

void Turtle::star() {
    forward(100);
    turn(144);
    forward(100);
    turn(144);
    forward(100);
    turn(144);
    forward(100);
    turn(144);
    forward(100);
    turn(144);
}

void Turtle::triangle() {
    forward(100);
    turn(120);
    forward(100);
    turn(120);
    forward(100);
    turn(120);
}

void Turtle::square() {
    forward(100);
    turn(90);
    forward(100);
    turn(90);
    forward(100);
    turn(90);
    forward(100);
    turn(90);
}

void Turtle::rectangle() {
    forward(150);
    turn(90);
    forward(100);
    turn(90);
    forward(150);
    turn(90);
    forward(100);
    turn(90);
}

void Turtle::circle() {
    for (int i = 0; i < 180; ++i) {
        forward(1);
        turn(2);
    }
}

void Turtle::cyclohexane() {
    for (int i = 0; i < 6; ++i) {
        forward(50); // Length of each side
        turn(60);    // Turn angle to create a hexagon
    }
}

void Turtle::house() {
    // Rectangular base
    for (int i = 0; i < 2; ++i) {
        forward(100);
        turn(90);
        forward(70);
        turn(90);
    }

    forward(100);
    turn(90);
    forward(70);
    turn(45);

    // Triangular roof
    forward(50 * sqrt(2));
    turn(90);
    forward(50 * sqrt(2));
}

void Turtle::spinning(int sides) { 
    const int steps = 50;  // Number of squares
    const double edgeFactor = 2.5;
    for (int step = 1; step <= steps; ++step) {
        for (int j = 0; j < sides; ++j) {
            forward(step * edgeFactor);
            turn(360 / sides);
        }
        turn(360.0 / steps); // Slight rotation for spiral effect
    }
}

double randomDouble(double l, double r) {
    return l + (r - l) * (std::rand() % 10000) / 10000.0;
}

int randomInt(int l, int r) {
    return l + (r - l) * (std::rand() % 10000) / 10000;
}

void Turtle::random() {
    std::vector<std::pair<int, double>> commands(0);
    const int FORWARD = 1;
    const int TURN = 2;

    const double angle = randomDouble(90, 180);
    const int count = randomInt(50, 150);
    for (int i = 0; i < count; i++) {
        commands.push_back({FORWARD, 1});
        commands.push_back({TURN, angle});
    }

    // Simulate movement to calculate bounds and scaling ratio
    double currentAngle = 0;
    double minX = INFINITY, maxX = -INFINITY, minY = INFINITY, maxY = -INFINITY;
    double centerX = 0, centerY = 0;
    int pointCount = 0;
    double tempX = 0, tempY = 0;
    for (int i = 0; i < commands.size(); i++) {
        if (commands[i].first == FORWARD) {
            double dx = commands[i].second * cos(currentAngle * M_PI / 180.0);
            double dy = commands[i].second * sin(currentAngle * M_PI / 180.0);
            tempX += dx;
            tempY += dy;
            minX = std::min(minX, tempX);
            maxX = std::max(maxX, tempX);
            minY = std::min(minY, tempY);
            maxY = std::max(maxY, tempY);
            centerX += tempX;
            centerY += tempY;
            pointCount++;
        } else if (commands[i].first == TURN) {
            currentAngle -= commands[i].second;
        }
    }
    centerX /= pointCount;
    centerY /= pointCount;

    // Calculate scaling ratio
    double patternWidth = maxX - minX;
    double patternHeight = maxY - minY;
    QRectF visibleBounds = ui_->graphicsView->sceneRect();
    double screenWidth = visibleBounds.right() - visibleBounds.left();
    double screenHeight = visibleBounds.bottom() - visibleBounds.top();
    double ratio = std::min(screenWidth / patternWidth, screenHeight / patternHeight) * 0.8; // 80% of screen
    
    // Move to offset center
    turn(-90);
    forward(-centerY * ratio);
    turn(90);
    forward(-centerX * ratio);
    
    // Execute commands
    for (const auto& cmd : commands) {
        if (cmd.first == FORWARD) {
            forward(cmd.second * ratio);
        } else if (cmd.first == TURN) {        
            turn(cmd.second);
        }
    }
}

std::pair<int, int> Turtle::getGamePos() {
    return randomPos_;
};

void Turtle::gameify() {

    resetTurtle();

    QRectF visibleBounds = ui_->graphicsView->sceneRect();

    int sw = visibleBounds.width() - 10;
    int sh = visibleBounds.height() - 15;

    int w = std::rand() % sw;
    int h = std::rand() % sh;

    w -= sw/2;
    h -= sh/2;

    randomPos_ = {w, h};

    std::cout << "target:"<<randomPos_.first << " " << randomPos_.second << " current: " << x() << " " << y() << std::endl;
}

bool Turtle::gameWon() const{

    int tolerance = 15;

    if( (std::abs(randomPos_.first - getPosition().first) <= tolerance) &&
        (std::abs(randomPos_.second - getPosition().second) <= tolerance) ){
        QMessageBox::information(nullptr,"", "The turtle made it back home!");
        return true;
    }
    return false;
}
