#include "paintdata.h"

#include "request.h"

PaintData::PaintData()
{
    bufferSize = 10;
}

void PaintData::serializeData()
{
    QDataStream out(&serializeByteArray, QIODevice::WriteOnly);
    out << (qint32) 0 << (qint32) Shape.penWidth ;//<< Shape.penColor;
    //for(int i=0; i<Shape.shapeBuffer.size(); i++)
    //{
    //       out << Shape.shapeBuffer[i];
    //}

    //qDebug()<<"Serialized Byte Array: "<<serializeByteArray.size();

}

void PaintData::sendData(){

    serializeData();

    *reinterpret_cast <SREQUEST * > (serializeByteArray.data()) = SREQUEST::E_NEW_SHAPE;

    //qDebug()<<"Serialized Byte Array: "<<serializeByteArray;

    int bytes_to_send = serializeByteArray.size();

    //client_ptr->sendData(serializeByteArray, bytes_to_send);

    client_ptr->sendData("2", 2);
}

void PaintData::addPoint(const QPoint &newPoint)
{
    Shape.shapeBuffer << newPoint;

    static DWORD last_time = GetTickCount();

    if(GetTickCount() - last_time > 200){
        sendData();
        last_time = GetTickCount();
    }


    /*if(mouseReleasePoint) {
        //sendData();
        //Shape.shapeBuffer.clear();
    }
    else
        if(Shape.shapeBuffer.size() >= bufferSize) {
        qDebug()<<Shape.shapeBuffer.size();

        sendData();
        tempPoint = Shape.shapeBuffer.last();
        Shape.shapeBuffer.clear();
        Shape.shapeBuffer << tempPoint;
    }*/
}
