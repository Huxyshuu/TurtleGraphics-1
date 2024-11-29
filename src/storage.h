#ifndef STORAGE_H
#define STORAGE_H

#include <QStringList>
#include <QString>
#include <QStringListModel>


class Storage
{
  public:
    Storage();

      /**
     * @brief addToHistory adds user typed commands to a list
     * @param line is the user given string that gets added to history
     */
    void addToHistory(const QString &line);

    /**
     * @brief getHistory
     * @return returns a QStringList where all the commands are stored as a list
     */
    QStringList getHistory() const;

    /**
     * @brief getModel
     * @return returns the currently used model
     */
    QStringListModel* getModel() const;

    /**
     * @brief helpDisplay shows all the commands that the user can type as a list in the historyView window
     */
    void helpDisplay();

    /**
     * @brief clearHistory clears the user input list/history
     */
    void clearHistory();

    /**
     * @brief saveImage saves the image that the turtle has drawn
     * @param image is the image that we want to save
     * @param fileName is user given name for the image
     */
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
                            , "star"
                            , "triangle"
                            , "square"
                            , "rectangle"
                            , "circle"
                            , "cyclohexane"
                            , "house"
                            , "spinning"
                            , "random"
                            , "gameify"
                            , "More?" };
};

#endif // STORAGE_H
