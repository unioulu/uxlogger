#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "defaultbuttonarea.h"
#include "manualinputfield.h"
#include "eventlogger.h"
#include <algorithm>
#include "logtable.h"
#include <QActionGroup>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>


const int manualInputHeight = 50;
const int manualInputMargin = 5;

const int topMargin = 50;
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

    createActions();
    createMenus();

    this->resize(1000, 800);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::createActions() {

    newAction = new QAction("New", this);
    newAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    newAction->setStatusTip("Start logging from beginnig");
    QObject::connect(newAction, &QAction::triggered, this, &MainWindow::onNewActionPress);

    openAction = new QAction("Open", this);
    openAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    openAction->setStatusTip("Continue previously saved log file");
    QObject::connect(openAction, &QAction::triggered, this, &MainWindow::onOpenActionPress);

    saveAction = new QAction("Save", this);
    saveAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    saveAction->setStatusTip("Save as .log file");
    QObject::connect(saveAction, &QAction::triggered, this, &MainWindow::onSaveActionPress);

    exportLogAction = new QAction("Export as LOG", this);
    exportLogAction->setStatusTip("Export as normal log file");
    QObject::connect(exportLogAction, &QAction::triggered, this, &MainWindow::onSaveActionPress);

    exportSrtAction = new QAction("Export as SRT", this);
    exportSrtAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_E));
    exportSrtAction->setStatusTip("Export as subtitle file");
    QObject::connect(exportSrtAction, &QAction::triggered, this, &MainWindow::onExportSrtActionPress);

    exportGroup = new QActionGroup(this);
    exportGroup->addAction(exportLogAction);
    exportGroup->addAction(exportSrtAction);
}

void MainWindow::createMenus() {

    fileMenu = menuBar()->addMenu("File");

    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);

    exportMenu = fileMenu->addMenu("Export");

    exportMenu->addAction(exportLogAction);
    exportMenu->addAction(exportSrtAction);

}

int MainWindow::logAreaWidth() {
    return std::min(maxLogAreaWidth, this->size().width() / 3);
}


bool MainWindow::unsavedChangesCheck() { //returns false if cancel pressed and thus caller should not continue, true otherwise
    if (logger_->isSaved() == false) {
        QMessageBox msgBox;
        msgBox.setText("You have unsaved changes.");
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();

        switch (ret) {
          case QMessageBox::Save:
              onSaveActionPress();
              return true;
          case QMessageBox::Discard:
              return true;
          case QMessageBox::Cancel:
              return false;
          default:
              break;
        }
    }

    return true;
}


/* * * * * *
 * EVENTS
 * * * * * */


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


void MainWindow::closeEvent(QCloseEvent *event) {
    if (unsavedChangesCheck()) {
        QMainWindow::closeEvent(event);
    }
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

void MainWindow::onNewActionPress() {
    if (unsavedChangesCheck()) {
        delete logger_;
        logger_ = new EventLogger();
        logTable_->setLogger(logger_);
    }
}

void MainWindow::onOpenActionPress() {
    if (unsavedChangesCheck()) {
        QString path = QFileDialog::getOpenFileName(this, "Open .log file", QDir::currentPath(), "Log (*.log)");
        delete logger_;
        logger_ = new EventLogger(path);
        logTable_->setLogger(logger_);
    }
}

void MainWindow::onSaveActionPress() {
    QString path = logger_->filename();
    if (path == nullptr) {
        path = QFileDialog::getSaveFileName(this, "Save as", QDir::currentPath(), "Log (*.log)");
    }
    logger_->setFilename(path);
    logger_->writeToFile(path);
}

void MainWindow::onExportSrtActionPress() {
    QString path = QFileDialog::getSaveFileName(this, "Export as SRT", QDir::currentPath(), "Subtitles (*.srt)");
    logger_->writeToSubtitleFile(path);
}

