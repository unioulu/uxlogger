#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class DefaultButtonArea;
class ManualInputField;
class LogTable;
class EventLogger;
class QActionGroup;
class QFileDialog;

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
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    DefaultButtonArea* buttonArea_;
    ManualInputField* manualInput_;
    LogTable* logTable_;
    EventLogger* logger_;

    bool unsavedChangesCheck();

    int logAreaWidth();

    void createActions();
    void createMenus();

    QMenu* fileMenu;
    QMenu* exportMenu;
    QAction* newAction;
    QAction* openAction;
    QAction* saveAction;
    QActionGroup* exportGroup;
    QAction* exportLogAction;
    QAction* exportSrtAction;

    QFileDialog* openDialog;
    QFileDialog* saveDialog;
    QFileDialog* exportDialog;
signals:
    void loggerUpdated();


 public slots:
    void onActionButtonPress(const ActionButtonData* data);
    void onManualLogEnter();

private slots:
    void onNewActionPress();
    void onOpenActionPress();
    void onSaveActionPress();
    void onExportSrtActionPress();
};

#endif // MAINWINDOW_H
