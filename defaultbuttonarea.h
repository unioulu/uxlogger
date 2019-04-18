#ifndef DEFAULTBUTTONS_H
#define DEFAULTBUTTONS_H

#include <QWidget>
#include <QPushButton>
#include "actionbuttondata.h"

class ActionButton;


class DefaultButtonArea : public QWidget {
    Q_OBJECT
public:
    explicit DefaultButtonArea(QWidget *parent = nullptr);
    ~DefaultButtonArea();

protected:
    void resizeEvent(QResizeEvent* event);

private:
    std::vector<ActionButton*>* buttons_;
    double optimal_size (double W, double H, int N);

    int buttonCount_;

signals:
    void buttonPressed(const ActionButtonData* data);

public slots:
    void onButtonPress();
};

#endif // DEFAULTBUTTONS_H
