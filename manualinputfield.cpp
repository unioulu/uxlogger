#include "manualinputfield.h"

ManualInputField::ManualInputField(QWidget* parent) : QLineEdit (parent)
{
    QWidget::grabKeyboard();
}

ManualInputField::~ManualInputField() {

}
