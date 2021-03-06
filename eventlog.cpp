#include "eventlog.h"
#include "time.h"


EventLog::EventLog(QString text) {
    text_ = text;
    time_ = Time::deltaTime();
}

EventLog::EventLog(QString text, int time) {
    text_ = text;
    time_ = time;
}

QString EventLog::text() const {
    return text_;
}

int EventLog::time() const {
    return time_;
}

QString EventLog::fileEntry() const {
    return QString::number(time()) + ";" + text();
}
