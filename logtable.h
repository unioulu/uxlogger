#ifndef LOGTABLE_H
#define LOGTABLE_H

#include <QObject>
#include <QWidget>
#include <QTableWidget>

class EventLogger;

class LogTable : public QTableWidget {
    Q_OBJECT
public:
    explicit LogTable(EventLogger* logger, QWidget *parent = nullptr);

private:
    EventLogger* logger_;

    void updateTable();

signals:

public slots:
    void onLoggerUpdate();

};

#endif // LOGTABLE_H
