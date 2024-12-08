#include "storage.h"
#include <QStringListModel>
#include <QImage>
#include <QFileDialog>
#include <QMessageBox>

Storage::Storage() : model(new QStringListModel(history)){
    model->setStringList(history); // Initialize the model
}

Storage::~Storage() {
    delete model;
};

void Storage::addToHistory(const QString &line) {
    history.prepend(line);
    model->setStringList(history);
}

QStringListModel *Storage::getModel() const {
    return model;
}

QStringList Storage::getHistory() const{
    return history;
}

void Storage::helpDisplay() {
    model->setStringList(helplist);
}

void Storage::clearHistory() {
    history.clear();
    model->setStringList(history);
}
