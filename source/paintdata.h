#ifndef PAINTDATA_H
#define PAINTDATA_H

#include <QColor>
#include <QPoint>
#include <QVector>

class PaintData
{
public:
    friend class DrawBoardArea;

    int penWidth;
    QColor penColor;
    QPoint startPoint;
    QPoint endPoint;

    QVector<QPoint> shapeBuffer;
    int bufferSize;

    void addPoint(const QPoint &newPoint);
    void sendData();
    bool mouseReleasePoint;

};

#endif // PAINTDATA_H
