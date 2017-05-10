#include "paintdata.h"

void PaintData::serializeData()
{
    QDataStream out(&serializeByteArray, QIODevice::WriteOnly);
    out << (qint32) Shape.penWidth << Shape.penColor << Shape.shapeBuffer;
}

void PaintData::sendData()
{

    /*
     *  !!!!!!!!!!!!!!!!! TO BE CODED BY MATEI !!!!!!!!!!!!!!!!!!!!!
     * Here we need to send the buffer to the server -> serializeByteArray
     */

}

void PaintData::receiveData()
{
    /*
     * Here we should recieve the serialized buffer from the server
    */

    QDataStream in(serializeByteArray);
    in >> Shape.penWidth >> Shape.penColor >> Shape.shapeBuffer;
}

void PaintData::addPoint(const QPoint &newPoint)
{
    Shape.shapeBuffer << newPoint;

    if(mouseReleasePoint)
    {
        sendData();
        Shape.shapeBuffer.clear();
    } else if(Shape.shapeBuffer.size() >= bufferSize)
    {
        sendData();
        tempPoint = Shape.shapeBuffer.last();
        Shape.shapeBuffer.clear();
        Shape.shapeBuffer << tempPoint;
    }
}

