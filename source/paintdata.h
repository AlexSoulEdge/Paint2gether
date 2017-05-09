#ifndef PAINTDATA_H
#define PAINTDATA_H

#include <QColor>
#include <QPoint>

class PaintData
{
public:
    int penWidth;
    QColor penColor;
    QPoint startPoint;
    QPoint endPoint;
    /*
     * bitset <T> get_drawing
     * char *get_drawing = new int [buffer];
     *
     * To be added:
     * serialization of the class
     */


};

#endif // PAINTDATA_H
