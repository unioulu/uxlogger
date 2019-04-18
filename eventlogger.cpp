#include "eventlogger.h"
#include "time.h"
#include "eventlog.h"

#include <QFile>
#include <QTextStream>
#include <QStandardPaths>
#include <QDateTime>

EventLogger::EventLogger() {
    Time::startTime();
    filename_ = QDateTime::currentDateTime().toString(Qt::ISODate);
    filename_.replace(':', '-');
}

void EventLogger::addLog(QString text) {
    addLog(new EventLog(text));
}

void EventLogger::addLog(EventLog *log) {
    logs_.push_back(log);
    writeToFile();
    writeToSubtitleFile();
}

int EventLogger::count() const {
    return static_cast<int>(logs_.size());
}

const EventLog* EventLogger::logAtIndex(int index) const {
    return logs_.at(static_cast<unsigned int>(index));
}

const EventLog* EventLogger::latestLog() const {
    return count() > 0 ? logAtIndex(count()-1) : nullptr;
}

void EventLogger::writeToFile() {
    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    desktopPath.append("/" + filename_ + ".log");
    qDebug("piip" + desktopPath.toLatin1() + "");
    QFile file(desktopPath);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream stream(&file);

    for (EventLog* log : logs_) {
        stream << log->fileEntry();
    }

    file.close();
}

void EventLogger::writeToSubtitleFile() {
    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    desktopPath.append("/" + filename_ + ".srt");
    qDebug("piip" + desktopPath.toLatin1() + "");
    QFile file(desktopPath);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream stream(&file);

    int tally = 0;
    for (EventLog* log : logs_) {
        QString startTime = Time::timeStringFromMs(log->time());
        QString endTime = Time::timeStringFromMs(log->time()+1000);


        stream << tally << endl << startTime << " --> " << endTime << endl << log->text() << endl << endl;
        tally++;
    }

    file.close();
}
