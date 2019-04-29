#include "logtable.h"
#include "eventlogger.h"
#include "eventlog.h"

#include <QTableWidgetItem>
#include <QHeaderView>
#include <QDebug>


LogTable::LogTable(EventLogger* logger, QWidget *parent) : QTableWidget(0, 2, parent) {
    logger_ = logger;

    this->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    this->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
}


void LogTable::updateTable() {
    int logCount = logger_->count();
    const EventLog* log = logger_->latestLog();

    setLogToTableAtIndex(log, logCount-1);

    this->scrollToBottom();
}

void LogTable::reloadTable() {

    this->clearContents();
    this->setRowCount(0);

    for (int i=0; i<logger_->count(); ++i) {
        const EventLog* log = logger_->logAtIndex(i);
        qDebug() << "Reload log: " << log->fileEntry();
        setLogToTableAtIndex(log, i);
    }

    this->scrollToBottom();

}

void LogTable::setLogToTableAtIndex(const EventLog* log, int index) {
    if (this->rowCount() < index+1) {
        this->setRowCount(index+1);
    }

    int logCount = logger_->count();

    this->setItem(index, 0, new QTableWidgetItem(QString::number(log->time())));
    this->setItem(index, 1, new QTableWidgetItem(log->text()));

    this->scrollToBottom();

}

void LogTable::setLogger(EventLogger* logger) {
    logger_ = logger;
    reloadTable();
}


/* * * * * *
 * SLOTS
 * * * * * */

void LogTable::onLoggerUpdate() {
    updateTable();
}
