#ifndef ACTIONBUTTONDATA_H
#define ACTIONBUTTONDATA_H

#include <QString>

class ActionButtonData
{
public:
    ActionButtonData(int index, QString label, QString logText);
    ActionButtonData(QStringList stringList);

    int buttonIndex() const;
    QString label() const;
    QString logText() const;

private:
    int buttonIndex_;
    QString label_;
    QString logText_;
};

#endif // ACTIONBUTTONDATA_H
