#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "defaultbuttonarea.h"
#include "manualinputfield.h"
#include "eventlogger.h"
#include <algorithm>
#include "logtable.h"


const int manualInputHeight = 50;
const int manualInputMargin = 5;

const int topMargin = 15;
const int bottomMargin = 10;
const int sideMargin = 10;
const int middleMargin = 10;

const int maxLogAreaWidth = 400;


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    qDebug("constructor");

    this->buttonArea_ = new DefaultButtonArea(this);
    this->manualInput_ = new ManualInputField(this);
    this->logger_ = new EventLogger();

    this->logTable_ = new LogTable(logger_, this);

    QObject::connect(manualInput_, &ManualInputField::returnPressed, this, &MainWindow::onManualLogEnter);
    QObject::connect(buttonArea_, &DefaultButtonArea::buttonPressed, this, &MainWindow::onActionButtonPress);
    QObject::connect(this, &MainWindow::loggerUpdated, logTable_, &LogTable::onLoggerUpdate);

    this->resize(1000, 800);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);

    int rightAreaXPos = logAreaWidth() + 2*middleMargin;

    logTable_->move(sideMargin, topMargin);
    logTable_->resize(logAreaWidth(), size().height() - topMargin - bottomMargin);

    buttonArea_->move(rightAreaXPos, topMargin);
    buttonArea_->resize(this->size().width() - rightAreaXPos - sideMargin,
                        this->size().height() - manualInputHeight - manualInputMargin*2 - topMargin);

    manualInput_->move(rightAreaXPos, buttonArea_->pos().y() + buttonArea_->size().height());
    manualInput_->resize(this->size().width() - rightAreaXPos - sideMargin, manualInputHeight);

}

int MainWindow::logAreaWidth() {
    return std::min(maxLogAreaWidth, this->size().width() / 3);
}




/* * * * * *
 * SLOTS
 * * * * * */

void MainWindow::onManualLogEnter() {
    if (logger_->count() == 0) {
        Time::resetStartTime();
    }
    logger_->addLog(manualInput_->text());
    loggerUpdated();
    manualInput_->clear();
}

void MainWindow::onActionButtonPress(const ActionButtonData* data) {
    if (logger_->count() == 0) {
        Time::resetStartTime();
    }
    logger_->addLog(data->logText());
    loggerUpdated();
}

