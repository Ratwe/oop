#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "draw.h"
#include "err.h"

#include <stdio.h>
#include <QMainWindow>
#include <QAction>
#include <QGraphicsScene>
#include <QGraphicsView>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openImage();
    void scale();
//    void zoomOut();
//    void rotate();
//    void move();

    void handle_rc(const err_t rc);
    canvas_t init_canvas();

private:
    QAction *openAction;
    QAction *scaleAction;
    QAction *rotateAction;
    QAction *moveAction;
    QGraphicsScene *scene;
    QGraphicsView *view;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
