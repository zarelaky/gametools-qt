#include "operationdockwidget.h"

OperationDockWidget::OperationDockWidget()
{
    setWindowTitle(tr("Operations"));
    setMinimumWidth(200);
    setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
    setFeatures(QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetFloatable);
}
