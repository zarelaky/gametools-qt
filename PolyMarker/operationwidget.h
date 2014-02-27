#ifndef OPERATIONWIDGET_H
#define OPERATIONWIDGET_H

#include <QWidget>
#include <QList>

class OperationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OperationWidget(QWidget *parent = 0);
    virtual ~OperationWidget();
protected:
    virtual void paintEvent(QPaintEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void keyPressEvent(QKeyEvent *);
signals:
    
public:
    void setPixmap(const QPixmap& px);

    const QList<QPoint*>& getPoints() const;
    void cleanPoints();
protected:
    QPoint* hitPoints(const QPoint& pt);
private:
    QPixmap _px;
    QList<QPoint*>  _points;
    QPoint*         _dragPoint;
    qint32          _controlsPointRadius;
};


#endif // OPERATIONWIDGET_H
