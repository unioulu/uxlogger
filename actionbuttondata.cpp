#include "actionbuttondata.h"

#include <QStringList>

ActionButtonData::ActionButtonData(int index, QString label, QString logText) {
    label_ = label;
    logText_ = logText;
    buttonIndex_ = index;
}

ActionButtonData::ActionButtonData(QStringList stringList) {
    buttonIndex_ = stringList.at(0).toInt();
    label_       = stringList.at(1);
    logText_     = stringList.at(2);
}


QString ActionButtonData::label() const {
    return label_;
}

QString ActionButtonData::logText() const {
    return logText_;
}

int ActionButtonData::buttonIndex() const {
    return buttonIndex_;
}
