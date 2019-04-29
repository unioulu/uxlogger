#ifndef EVENTLOGGER_H
#define EVENTLOGGER_H


#include <QDateTime>
#include <vector>

class EventLog;


class EventLogger
{
public:
    EventLogger();
    EventLogger(QString filepath);
    virtual ~EventLogger();

    void addLog(QString text);
    void addLog(EventLog* log);

    const EventLog* logAtIndex(int index) const;
    const EventLog* latestLog() const;

    int count() const;

    void writeToFile(QString path);
    void writeToSubtitleFile(QString path);

    void setFilename(QString str);
    const QString filename() const;
    bool isSaved() const;

protected:
    QString backupFilePath();

private:
    std::vector<EventLog*> logs_;

    bool timerStarted_;
    bool isSaved_;

    QString filename_;
    QString backupFilename_;

    void resetTimerIfNecessary();
};

#endif // EVENTLOGGER_H
