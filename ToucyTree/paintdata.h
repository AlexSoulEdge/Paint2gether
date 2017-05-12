#ifndef PAINTDATA_H
#define PAINTDATA_H

#include <QByteArray>
#include <QColor>
#include <QDataStream>
#include <QPoint>
#include <QVector>

class PaintData {
public:
    class ShapeModel
    {
    public:
        int penWidth;
        QColor penColor;
        QVector <QPoint> shapeBuffer;
    }Shape;

    int bufferSize;

    QByteArray serializeByteArray;
    QPoint startPoint;
    QPoint finishPoint;
    QPoint tempPoint;

    void addPoint(const QPoint &newPoint);
    void serializeData();
    void sendData(); //to be coded by Matei
    void receiveData();
    bool mouseReleasePoint;

};

#endif // PAINTDATA_H
