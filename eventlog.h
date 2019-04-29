#ifndef EVENTLOG_H
#define EVENTLOG_H

#include <QString>
#include <QDateTime>

class EventLog
{
public:
    EventLog(QString text);

    QString text() const;
    int time() const;

    QString fileEntry() const;

    EventLog(QString text, int time);
private:
    QString text_;
    int time_;
};

#endif // EVENTLOG_H
