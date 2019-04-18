#ifndef MANUALINPUTFIELD_H
#define MANUALINPUTFIELD_H

#include <QLineEdit>

class ManualInputField : public QLineEdit {
    Q_OBJECT
public:
    explicit ManualInputField(QWidget *parent = nullptr);
    ~ManualInputField();

};

#endif // MANUALINPUTFIELD_H
