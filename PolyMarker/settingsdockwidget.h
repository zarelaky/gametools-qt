#ifndef SETTINGSDOCKWIDGET_H
#define SETTINGSDOCKWIDGET_H

#include <QDockWidget>
#include <coordsystem.h>
#include <QComboBox>

class SettingsDockWidget : public QDockWidget
{
    Q_OBJECT
public:
    explicit SettingsDockWidget();
    
    CoordSystem* currentCoordSystem();

signals:
    
private:
    QComboBox* _coordSystemCmb;
};

#endif // SETTINGSDOCKWIDGET_H
