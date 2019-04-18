#ifndef ACTIONBUTTON_H
#define ACTIONBUTTON_H

#include <QPushButton>
#include "actionbuttondata.h"

class ActionButton : public QPushButton
{
    Q_OBJECT
public:
    explicit ActionButton(const ActionButtonData* data, QWidget *parent = nullptr);

    const ActionButtonData* data() const;

private:
    int index();
    const ActionButtonData* data_;

signals:

public slots:
};

#endif // ACTIONBUTTON_H
