#ifndef EVENTLOGGER_H
#define EVENTLOGGER_H


#include <QDateTime>
#include <vector>

class EventLog;


class EventLogger
{
public:
    EventLogger();

    void addLog(QString text);
    void addLog(EventLog* log);

    const EventLog* logAtIndex(int index) const;
    const EventLog* latestLog() const;

    int count() const;

    void writeToFile();
    void writeToSubtitleFile();
private:
    std::vector<EventLog*> logs_;

    QString filename_;
};

#endif // EVENTLOGGER_H
