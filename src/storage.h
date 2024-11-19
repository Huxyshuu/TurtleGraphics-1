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

    void clearHistory();

    void saveImage(const QImage &image, const QString &fileName);

  private:
    QStringList history;
    QStringListModel *model;
    QStringList helplist = { "Here are all the available commands:"
                            , "help"
                            , "forward [number]"
                            , "turn [degrees]"
                            , "go [x] [y]"
                            , "pen up"
                            , "pen down"
                            , "reset"
                            , "More?" };
};

#endif // STORAGE_H
