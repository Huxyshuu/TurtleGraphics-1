#ifndef STORAGE_H
#define STORAGE_H

#include <QStringList>
#include <QString>
#include <QStringListModel>

class Storage
{
  public:
    Storage();

    void addToHistory(const QString &line);
    QStringList getHistory() const;
    QStringListModel* getModel() const;

  private:
    QStringList history;
    QStringListModel *model;
};

#endif // STORAGE_H
