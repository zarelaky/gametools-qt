#include "settingsdockwidget.h"
#include <QFormLayout>

#include <QLabel>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>


SettingsDockWidget::SettingsDockWidget() :
    QDockWidget()
{
    setWindowTitle(tr("Settings"));
    setMinimumWidth(200);
    setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
    setFeatures(QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetFloatable);

    QGridLayout* gridLayout = new QGridLayout();
    _coordSystemCmb = new QComboBox();
    QLabel* lbl = new QLabel(tr("CoordSys:"));
    lbl->setAlignment(Qt::AlignRight);
    gridLayout->addWidget(lbl,0,0);
    gridLayout->addWidget(_coordSystemCmb, 0, 1);
    QListIterator<CoordSystem*> itr(CoordSystem::coordSystems());
    while (itr.hasNext()) {
        CoordSystem* p = itr.next();
        _coordSystemCmb->addItem(p->name());
    }

    lbl = new QLabel(tr("Save To:"));
    lbl->setAlignment(Qt::AlignRight);
    gridLayout->addWidget(lbl, 1,0);
    QLineEdit* savePathEdt = new QLineEdit();
    gridLayout->addWidget(savePathEdt, 1,1);
    QPushButton* browsnBtn = new QPushButton(tr("..."));
    browsnBtn->setFixedWidth(40);
    gridLayout->addWidget(browsnBtn, 1,2);


    QVBoxLayout* layout = new QVBoxLayout();
    layout->addLayout(gridLayout);
    layout->addStretch(1);
    QWidget* widget = new QWidget();
    widget->setLayout(layout);


//    layout->addSpacing(10);
//    layout->setStretch(0, 10);
//    layout->setStretch(1, 90);

    //setLayout(formlayout);
    setWidget(widget);
}


CoordSystem* SettingsDockWidget::currentCoordSystem() {
    if (-1 == _coordSystemCmb->currentIndex()) {
        return NULL;
    }
    QListIterator<CoordSystem*> itr(CoordSystem::coordSystems());
    QString txt = _coordSystemCmb->currentText();
    while (itr.hasNext()) {
        CoordSystem* p = itr.next();
        if (p->name().compare(txt) == 0) {
            return p;
        }
    }
    Q_ASSERT(false);
    return NULL;
}

