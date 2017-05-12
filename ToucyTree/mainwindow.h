#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

#include "winclient.h"
#include "request.h"

#include <QMainWindow>
#include <QModelIndex>
#include <QList>
#include <QTimer>

class DrawBoardArea;

class MainWindow : public QMainWindow, private Ui::MainWindow {
    Q_OBJECT

    WinSocket client;

public:
    MainWindow(QWidget *parent = 0);

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    /// drawboard
    void open();
    void save();
    void penColor();
    void penWidth();
    void about();

private:
    void createActions();
    void createMenus();
    bool maybeSave();
    bool saveFile(const QByteArray &fileFormat);

    QTimer timer;
    DrawBoardArea *drawboardArea;

    QMenu *saveAsMenu;
    QMenu *fileMenu;
    QMenu *optionMenu;
    QMenu *helpMenu;

    QAction *newImageAct;
    QAction *openAct;
    QList <QAction *> saveAsActs;
    QAction *exitAct;
    QAction *penColorAct;
    QAction *penWidthAct;
    QAction *printAct;
    QAction *clearScreenAct;
    QAction *aboutAct;

public slots:
    void updateActions();
    void updateFrame();

private slots:

    /// tree
    void insertChild(const QString &filename);
    bool insertColumn();
    void insertRow(const QString &filename);
    bool removeColumn();
    void removeRow();

signals:
    void test();

};

#endif // MAINWINDOW_H
