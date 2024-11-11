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
    void helpDisplay();

  private:
    QStringList history;
    QStringListModel *model;
    QStringList helplist = { "Here are all the available commands:"
                            , "help"
                            , "forward [number]"
                            , "turn [degrees]"
                            , "More features coming soon!" };
};

#endif // STORAGE_H
