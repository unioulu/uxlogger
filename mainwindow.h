#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class DefaultButtonArea;
class ManualInputField;
class LogTable;
class EventLogger;

namespace Ui {
class MainWindow;
}

class ActionButtonData;




class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent* event);

private:
    Ui::MainWindow *ui;
    DefaultButtonArea* buttonArea_;
    ManualInputField* manualInput_;
    LogTable* logTable_;
    EventLogger* logger_;

    int logAreaWidth();

signals:
    void loggerUpdated();


 public slots:
    void onActionButtonPress(const ActionButtonData* data);
    void onManualLogEnter();

};

#endif // MAINWINDOW_H
