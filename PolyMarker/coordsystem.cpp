#include "coordsystem.h"
#include <QString>

CoordSystem::CoordSystem(const QString& name, const QMatrix& matrix)
    : _name(name)
    , _matrix(matrix)
{
}


QPoint CoordSystem::translate(const QPoint& pt) {
    return _matrix.map(pt);
}

const QString& CoordSystem::name() const {
    return _name;
}


class CoordSystemInitializer
{
public:
    CoordSystemInitializer()
    {

        QMatrix screenMatrix(
                    1.f,0.f,
                    0.f,1.f,
                    0.f,0.f);
        coordSystems.append(new CoordSystem(QObject::tr("Screen"), screenMatrix));
//        QMatrix openglBottomLeft(
//                    1.0f, 0.0f,
//                    0.0f, -1.0f,
//                    0.f, 0.f);
//        coordSystems.append(new CoordSystem(QObject::tr("OpenGL BottomLeft"), openglBottomLeft));

    }
    ~CoordSystemInitializer() {
        QListIterator<CoordSystem*> i(coordSystems);
        while (i.hasNext()) {
            delete i.next();
        }
        coordSystems.clear();;
    }

    QList<CoordSystem*> coordSystems;
};



QList<CoordSystem*>& CoordSystem::coordSystems()
{
    static CoordSystemInitializer inst;
    return inst.coordSystems;

}


