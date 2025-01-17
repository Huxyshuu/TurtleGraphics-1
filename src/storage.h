#ifndef STORAGE_H
#define STORAGE_H

#include <QStringList>
#include <QString>
#include <QStringListModel>

class Storage
{
  public:
    Storage();
    ~Storage();

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

  private:
    QStringList history;
    QStringListModel *model;
    QStringList helplist = {
        "General Commands:",
        "  help",
        "  reset",
        "  gameify",
        "  pen up",
        "  pen down",

        "\nMovement Commands:",
        "  forward [number]",
        "  turn [degrees]",
        "  go [x] [y]",

        "\nDrawing Commands:",
        "  house"
        "  triangle",
        "  square",
        "  rectangle",
        "  circle",
        "  star",
        "  cyclohexane",
        "  random",
        "  spinning [number]",
    };

};

#endif // STORAGE_H
