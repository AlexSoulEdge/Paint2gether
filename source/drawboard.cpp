#include <QtWidgets>
#ifndef QT_NO_PRINTER
#include <QPrinter>
#include <QPrintDialog>
#endif

#include "drawboard.h"

DrawBoardArea::DrawBoardArea(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    modified = false;
    scribbling = false;
    myPenWidth = 1;
    myPenColor = Qt::black;
}


bool DrawBoardArea::openImage(const QString &fileName)
{
    QImage loadedImage;
    if (!loadedImage.load(fileName))
        return false;

    QSize newSize = loadedImage.size().expandedTo(size());
    resizeImage(&loadedImage, newSize);
    image = loadedImage;
    modified = false;
    update();
    return true;
}

/*
 * In the openImage() function, we load the given image then we resize it to be
 * at least as large as the widget.
 * At the end, we call QWidget::update() to schedule a repaint.
 */




bool DrawBoardArea::saveImage(const QString &fileName, const char *fileFormat)
{
    QImage visibleImage = image;
    resizeImage(&visibleImage, size());

    if (visibleImage.save(fileName, fileFormat))
    {
        modified = false;
        return true;
    } else
    {
        return false;
    }
}

/*
 * saveImage() creates a QImage object that covers only the visible section of the
 * actual image and saves it using QImage::save().
 */




void DrawBoardArea::setPenColor(const QColor &newColor)
{
    myPenColor = newColor;
}

void DrawBoardArea::setPenWidth(int newWidth)
{
    myPenWidth = newWidth;
}



void DrawBoardArea::clearImage()
{
    image.fill(qRgb(255, 255, 255));
    modified = true;
    update();
}

/*
 * clearImage() clears the image displayed.
 * We simply fill the entire image with white - RGB value (255, 255, 255).
 */



void DrawBoardArea::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        lastPoint = event->pos();       //lastPoint is the point from where we begin scribbling
        scribbling = true;
    }
}

void DrawBoardArea::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && scribbling)
        drawLineTo(event->pos());       //event->pos() returns a Qpoint of the current mouse position
}

void DrawBoardArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && scribbling)
    {
        drawLineTo(event->pos());
        scribbling = false;
    }
}


/*
 * If the users press the left mouse button, we store the position of the mouse cursor in lastPoint.
 * We also make a note that the user is currently scribbling.
 */



void DrawBoardArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, image, dirtyRect);
}



void DrawBoardArea::resizeEvent(QResizeEvent *event)
{
    if (width() > image.width() || height() > image.height())
    {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}


void DrawBoardArea::drawLineTo(const QPoint &endPoint)
{
    QPainter painter(&image);
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawLine(lastPoint, endPoint);
    modified = true;

    int rad = (myPenWidth / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized()
                                     .adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
}

/*
 * drawLineTo() draws a line from the point where the mouse was located when the last mouse press
 * or mouse move occurred
 *
 * Optimization:
 * Instead of calling update() with no parameter, we pass a QRect that specifies the rectangle
 * inside the drawboard are needs updating, to avoid a complete repaint of the widget.
 *
 *
 * To be added:
 * serialization of:
 * -lastPoint, endPoint,myPenWidth, myPenColor
 */



void DrawBoardArea::resizeImage(QImage *image, const QSize &newSize)
{
    if (image->size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}


void DrawBoardArea::print()
{
#if !defined(QT_NO_PRINTER) && !defined(QT_NO_PRINTDIALOG)
    QPrinter printer(QPrinter::HighResolution);


    QPrintDialog printDialog(&printer, this);
    if (printDialog.exec() == QDialog::Accepted)
    {
        QPainter painter(&printer);
        QRect rect = painter.viewport();
        QSize size = image.size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.setWindow(image.rect());
        painter.drawImage(0, 0, image);

        /*
         * We scale the image to fit within the available space
         * on the page before painting it onto the paint device.
         */
    }
#endif // QT_NO_PRINTER
}
