#ifndef TIME_H
#define TIME_H

#include <QDateTime>

class Time {
public:
    static int deltaTime();
    static QDateTime startTime();
    static void resetStartTime(int offset = 0);

    static QString timeStringFromMs(int inputMs);

protected:
    static Time& instance();

private:
    Time();

    QDateTime startTime_;

};

#endif // TIME_H
