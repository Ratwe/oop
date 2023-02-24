#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QGraphicsScene>
#include <QGraphicsView>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openImage();
    void zoomIn();
    void zoomOut();
    void rotate();
    void move();

private:
    QAction *openAction;
    QAction *zoomInAction;
    QAction *zoomOutAction;
    QAction *rotateAction;
    QAction *moveAction;
    QGraphicsScene *scene;
    QGraphicsView *view;
};

#endif // MAINWINDOW_H
