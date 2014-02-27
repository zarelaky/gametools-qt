#include "mainwindow.h"

#include "operationdockwidget.h"
#include "operationwidget.h"
#include "settingsdockwidget.h"
#include <QToolBar>
#include <QMenuBar>
#include <QMenu>
#include <QScrollArea>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QFile>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    _operationWidget = new OperationWidget();
    _operationDockWidget = new OperationDockWidget();
    _settingsDockWidget = new SettingsDockWidget();


    QScrollArea* scrollArea = new QScrollArea();
    QPalette pal = scrollArea->palette();
    pal.setBrush(QPalette::All, QPalette::Window, QBrush(qRgb(100,100,100)));
    scrollArea->setPalette(pal);
    scrollArea->setWidget(_operationWidget);
    _operationWidget->setFixedSize(1024,768);

    setCentralWidget(scrollArea);
    addDockWidget(Qt::LeftDockWidgetArea, _settingsDockWidget);
    addDockWidget(Qt::RightDockWidgetArea, _operationDockWidget);

    setMinimumSize(1024,768);

    // menu bar
    QMenuBar* menuBar = new QMenuBar();

    QMenu* fileMenu = new QMenu(tr("&File"));

    QAction* action = fileMenu->addAction(tr("&Open"));
    connect(action, SIGNAL(triggered()), SLOT(onOpen()));

    action = fileMenu->addAction(tr("&Export"));
    fileMenu->addSeparator();
    connect(action, SIGNAL(triggered()), SLOT(onExport()));

    action = fileMenu->addAction(tr("E&xit"));
    connect(action, SIGNAL(triggered()), SLOT(onExit()));

    menuBar->addMenu(fileMenu);
    this->setMenuBar(menuBar);
    // tool bar
    QToolBar* toolBar = addToolBar(tr("mainToolbar"));
    action = toolBar->addAction(tr("help"));


}

MainWindow::~MainWindow()
{

}


void MainWindow::onExit() {
    close();
}

void MainWindow::onExport() {

    const QList<QPoint*>& l = _operationWidget->getPoints();
    if (l.size() == 0) {
        return;
    }
    CoordSystem* cs = _settingsDockWidget->currentCoordSystem();
    QList<QPoint> out;
    QListIterator<QPoint*> itr(l);

    while (itr.hasNext()) {
        out.push_back(cs->translate(*(itr.next())));
    }

    QString path;

    path = QFileDialog::getSaveFileName();
    if (!path.isEmpty()) {
        QFile f(path);
        if (f.open(QFile::WriteOnly)){
            QTextStream ts(&f);
            QListIterator<QPoint> i(out);
            while (i.hasNext()) {
                const QPoint& pt = i.next();
                ts << pt.x() << "," << pt.y() << ",";
            }
           f.close();
        } else {
            QMessageBox::critical(this, tr("error"), tr("create file failed"), QMessageBox::Ok);
        }
   }

}


void MainWindow::onOpen() {
    QString f = QFileDialog::getOpenFileName(this, tr("open pictures"),"", tr("Images (*.png *.xpm *.jpg)"));
    if (f.isEmpty()) {
      return;
    }
    _operationWidget->setPixmap(QPixmap(f));
}
