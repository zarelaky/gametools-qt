#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class OperationDockWidget;
class OperationWidget;
class SettingsDockWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected slots:
    void onExit();
    void onExport();
    void onOpen();

private:
    OperationDockWidget*    _operationDockWidget;
    OperationWidget*        _operationWidget;
    SettingsDockWidget*     _settingsDockWidget;
};

#endif // MAINWINDOW_H
