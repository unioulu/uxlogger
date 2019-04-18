#include "actionbutton.h"

ActionButton::ActionButton(const ActionButtonData* data, QWidget *parent) : QPushButton(data->label(), parent) {
    data_ = data;
}

const ActionButtonData* ActionButton::data() const {
    return data_;
}

int ActionButton::index() {
    return data_->buttonIndex();
}
