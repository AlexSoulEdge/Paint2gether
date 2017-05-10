#include <QVector>
#include <QPoint>

#include "paintdata.h"

void PaintData::sendData()
{

    /*
     *  !!!!!!!!!!!!!!!!! TO CODE !!!!!!!!!!!!!!!!!!!!!
     * Here we need to send the buffer to the server(QVector type) and
     * also the width(myPenWidth) and the color(myPenColor) of the pen
     */


}

void PaintData::addPoint(const QPoint &newPoint)
{
    shapeBuffer << newPoint;

    if(mouseReleasePoint)
    {
        sendData();
        shapeBuffer.clear();
    } else if(shapeBuffer.size() >= bufferSize)
    {
        sendData();
        shapeBuffer.clear();
    }
}

