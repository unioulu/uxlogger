#include "logtable.h"
#include "eventlogger.h"
#include "eventlog.h"

#include <QTableWidgetItem>
#include <QHeaderView>


LogTable::LogTable(EventLogger* logger, QWidget *parent) : QTableWidget(0, 2, parent) {
    logger_ = logger;

    this->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    this->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
}


void LogTable::updateTable() {
    int logCount = logger_->count();
    const EventLog* log = logger_->latestLog();

    this->setRowCount(logCount);
    this->setItem(logCount-1, 0, new QTableWidgetItem(QString::number(log->time())));
    this->setItem(logCount-1, 1, new QTableWidgetItem(log->text()));

    this->scrollToBottom();
}


void LogTable::onLoggerUpdate() {
    updateTable();
}
