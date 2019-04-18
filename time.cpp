#include "time.h"


static Time* instance_ = nullptr;

Time& Time::instance() {
    if (instance_ == nullptr) {
        instance_ = new Time();
    }
    return *instance_;
}



int Time::deltaTime() {
    QDateTime now = QDateTime::currentDateTime();
    return static_cast<int>(instance().startTime_.msecsTo(now));
}

QDateTime Time::startTime() {
    return instance().startTime_;
}

void Time::resetStartTime() {
    instance().startTime_ = QDateTime::currentDateTime();
}


Time::Time() {
    startTime_ = QDateTime::currentDateTime();
}


QString Time::timeStringFromMs(int inputMs) {
    int ms = inputMs % 1000;
    inputMs /= 1000;
    int s = inputMs % 60;
    inputMs /= 60;
    int m = inputMs % 60;
    inputMs /= 60;
    int h = inputMs;

    return QString::asprintf("%02d:%02d:%02d.%03d", h, m, s, ms);
}
