#include "eventlogger.h"
#include "time.h"
#include "eventlog.h"

#include <QFile>
#include <QTextStream>
#include <QStandardPaths>
#include <QDateTime>
#include <QCoreApplication>

EventLogger::EventLogger() {
    Time::startTime();
    backupFilename_ = QDateTime::currentDateTime().toString(Qt::ISODate);
    backupFilename_.replace(':', '-');
    filename_ = nullptr;
    timerStarted_ = false;
    isSaved_ = true;
}

EventLogger::EventLogger(QString path) {
    QFile file(path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream(&file);

    timerStarted_ = false;
    isSaved_ = true;

    while(!stream.atEnd()) {
        QString line = stream.readLine();
        QStringList list = line.split(';');
        QString time = list.at(0);
        QString text = list.at(1);
        EventLog* log = new EventLog(text, time.toInt());
        logs_.push_back(log);
    }

    file.close();
}

EventLogger::~EventLogger() {
    for (std::vector<EventLog*>::iterator it = logs_.begin(); it != logs_.end(); ++it) {
        delete *it;
    }
}

void EventLogger::addLog(QString text) {
    resetTimerIfNecessary();
    addLog(new EventLog(text));
}

void EventLogger::addLog(EventLog *log) {
    logs_.push_back(log);
    writeToFile(backupFilePath());
    writeToSubtitleFile(backupFilePath());
    isSaved_ = false;
}

void EventLogger::resetTimerIfNecessary() {
    if (timerStarted_ == false) {
        int offset = 0;
        if (logs_.size() > 0) {
            EventLog* log = logs_.at(logs_.size()-1);
            offset = -log->time();
        }
        Time::resetStartTime(offset);
        timerStarted_ = true;
    }
}

void EventLogger::setFilename(QString str) {
    filename_ = str;
}

const QString EventLogger::filename() const {
    return filename_;
}

bool EventLogger::isSaved() const {
    return isSaved_;
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

void EventLogger::writeToFile(QString path) {
    QFile file(path);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream stream(&file);

    for (EventLog* log : logs_) {
        stream << log->fileEntry() << endl;
    }

    file.close();
    isSaved_ = true;
}

void EventLogger::writeToSubtitleFile(QString path) {
    QFile file(path);
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


/* * * * *
 * PRIVATE
 * * * * */

QString EventLogger::backupFilePath() {
    QString appPath = QCoreApplication::applicationDirPath();
    appPath.append("/backups");
    appPath.append("/" + backupFilename_ + ".log");
    return appPath;
}
