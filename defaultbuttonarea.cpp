#include "defaultbuttonarea.h"
#include <algorithm>
#include "actionbutton.h"
#include "buttonparser.h"


const int kMaxButtonMargin = 0;

DefaultButtonArea::DefaultButtonArea(QWidget *parent) : QWidget(parent) {

    buttons_ = new std::vector<ActionButton*>();

    QPalette* palette = new QPalette();
    palette->setColor(QPalette::Background, Qt::black);

    this->setPalette(*palette);

    ButtonParser parser;
    std::vector<const ActionButtonData*> dataList = parser.parse();

    buttonCount_ = static_cast<int>(dataList.size());

    for (int i=0; i<buttonCount_; ++i) {
        const ActionButtonData* data = dataList.at(static_cast<unsigned int>(i));
        ActionButton* button = new ActionButton(data, this);
        buttons_->push_back(button);
        QObject::connect(button, &ActionButton::pressed, this, &DefaultButtonArea::onButtonPress);
    }

}

DefaultButtonArea::~DefaultButtonArea() {
    delete buttons_;
}


void DefaultButtonArea::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);

    QSize size = this->size();
    int buttonMargin = std::min(kMaxButtonMargin, size.width() / 20);

    int squareSide = static_cast<int>(optimal_size(size.width(), size.height(), buttonCount_));

    int itemsInRow = size.width() / squareSide;
    int rowCount = static_cast<int>(buttons_->size()) / itemsInRow;

    int buttonWidth =  std::max(squareSide, size.width() / itemsInRow);
    int buttonHeight = std::max(squareSide, size.height() / rowCount);

    int index = 0;

    for (std::vector<ActionButton*>::iterator it = buttons_->begin(); it != buttons_->end(); ++it) {
        ActionButton* button = *it;
        int xPos = index % itemsInRow * (buttonMargin + buttonWidth);
        int yPos = buttonMargin + (index/itemsInRow) * (buttonHeight + buttonMargin);
        button->move(xPos, yPos);
        button->resize(buttonWidth, buttonHeight);
        index++;
    }
}

double DefaultButtonArea::optimal_size (double W, double H, int N) {
    int i, j;
    for (i = static_cast<int>(round(sqrt(N*W/H))); i*floor(H*i/W) < N ; i++){}
    for (j = static_cast<int>(round(sqrt(N*H/W))) ; floor(W*j/H)*j < N ; j++){}
    return std::max (W/i, H/j) ;
}



/* * * * * *
 * SLOTS
 * * * * * */

void DefaultButtonArea::onButtonPress() {
    ActionButton* buttonSender = qobject_cast<ActionButton*>(sender());
    buttonPressed(buttonSender->data());
}
