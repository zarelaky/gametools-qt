#include "operationwidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QVector2D>

OperationWidget::OperationWidget(QWidget *parent) :
    QWidget(parent)
  , _dragPoint(NULL)
  , _controlsPointRadius(5)
{
    setFocusPolicy(Qt::ClickFocus);
}


OperationWidget::~OperationWidget()
{
    cleanPoints();
}


void OperationWidget::paintEvent(QPaintEvent * /*evt*/)
{
    QPainter p(this);
    p.drawPixmap(0, 0, _px);
    QListIterator<QPoint*> itr(_points);
    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setColor(QColor(255,0,0));
    const QPoint* lastPoint = NULL;
    while (itr.hasNext()) {
        QPoint* pt = itr.next();
        if (lastPoint) {
            p.drawLine(*lastPoint, *pt);
        }
        p.setPen(pen);
        p.drawEllipse(*pt, _controlsPointRadius,_controlsPointRadius);
        lastPoint = pt;
    }
}


void OperationWidget::setPixmap(const QPixmap &px)
{
    _px = px;
    cleanPoints();
    setFixedSize(px.width(), px.height());
    update();
}

void OperationWidget::mouseMoveEvent(QMouseEvent *evt) {
    QRect r(0,0, _px.width(), _px.height());

    if (_dragPoint && r.contains(evt->pos())) {
        _dragPoint->setX(evt->pos().x());
        _dragPoint->setY(evt->pos().y());
        update();
    }
}

void OperationWidget::mousePressEvent(QMouseEvent *evt) {
    if (_px.isNull()) {
        return;
    }

    if (QPoint* p = hitPoints(evt->pos())) {
        _dragPoint = p;
    } else {
        _points.append(new QPoint(evt->pos()));
        update();
    }

}

void OperationWidget::mouseReleaseEvent(QMouseEvent */*evt*/)
{
    _dragPoint = NULL;
}

void OperationWidget::keyPressEvent(QKeyEvent *evt) {

    if (evt->key() == Qt::Key_Escape) {
        if (_points.size() > 0) {
            delete _points.last();
            _points.removeLast();
            update();
        }
    }
}

QPoint* OperationWidget::hitPoints(const QPoint& pt){
    QListIterator<QPoint*> itr(_points);
    while (itr.hasNext()) {
        QPoint* p = itr.next();
        QVector2D v(*p - pt);
        if (v.length() < _controlsPointRadius) {
            return p;
        }
    }
    return NULL;
}

void OperationWidget::cleanPoints()
{
    QListIterator<QPoint*> itr(_points);
    while (itr.hasNext()) {
        delete itr.next();
    }
    _points.clear();
}

const QList<QPoint*>& OperationWidget::getPoints() const {
    return _points;
}
