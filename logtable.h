#ifndef LOGTABLE_H
#define LOGTABLE_H

#include <QObject>
#include <QWidget>
#include <QTableWidget>

class EventLogger;
class EventLog;

class LogTable : public QTableWidget {
    Q_OBJECT
public:
    explicit LogTable(EventLogger* logger, QWidget *parent = nullptr);

    void setLogger(EventLogger *logger);
protected:
    void setLogToTableAtIndex(const EventLog *log, int index);

private:
    EventLogger* logger_;

    void updateTable();   
    void reloadTable();
signals:

public slots:
    void onLoggerUpdate();
};

#endif // LOGTABLE_H
