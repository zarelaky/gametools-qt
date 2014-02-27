#ifndef COORDSYSTEM_H
#define COORDSYSTEM_H
#include <QMatrix>

class CoordSystem
{
    CoordSystem(const QString& name, const QMatrix& matrix);
public:
    static QList<CoordSystem*>& coordSystems();
    QPoint translate(const QPoint& pt);
    const QString& name() const;
private:
    QString     _name;
    QMatrix     _matrix;

    friend class CoordSystemInitializer;
};

#endif // COORDSYSTEM_H
