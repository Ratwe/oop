#include "mainwindow.h"
#include "qmenubar.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QFileDialog>
#include <QInputDialog>
#include <QPointF>
#include <QtMath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Создаем QAction для открытия изображения и связываем его со слотом openImage()
    moveAction = new QAction(tr("&Open"), this);
    connect(openAction, &QAction::triggered, this, &MainWindow::openImage);

    // Создаем QAction для увеличения изображения и связываем его со слотом zoomIn()
    zoomInAction = new QAction(tr("Zoom &In"), this);
    zoomInAction->setEnabled(false);
    connect(zoomInAction, &QAction::triggered, this, &MainWindow::zoomIn);

    // Создаем QAction для уменьшения изображения и связываем его со слотом zoomOut()
    zoomOutAction = new QAction(tr("Zoom &Out"), this);
    zoomOutAction->setEnabled(false);
    connect(zoomOutAction, &QAction::triggered, this, &MainWindow::zoomOut);

    // Создаем QAction для поворота изображения и связываем его со слотом rotate()
    rotateAction = new QAction(tr("&Rotate"), this);
    rotateAction->setEnabled(false);
    connect(rotateAction, &QAction::triggered, this, &MainWindow::rotate);

    // Создаем QAction для перемещения изображения и связываем его со слотом move()
    moveAction = new QAction(tr("&Move"), this);
    moveAction->setEnabled(false);
    connect(moveAction, &QAction::triggered, this, &MainWindow::move);

    // Создаем меню File и добавляем туда QAction для открытия изображения
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAction);

    // Создаем меню Edit и добавляем туда QAction для увеличения, уменьшения, поворота и перемещения изображения
    QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(zoomInAction);
    editMenu->addAction(zoomOutAction);
    editMenu->addAction(rotateAction);
    editMenu->addAction(moveAction);

    // Создаем QGraphicsScene и QGraphicsView для отображения изображения
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    setCentralWidget(view);
}

void MainWindow::openImage()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files (*.png *.jpg *.bmp)"));
    if (fileName.isEmpty())
        return;
    QPixmap pixmap(fileName);
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap);
    scene->clear();
    scene->addItem(item);
    view->fitInView(item, Qt::KeepAspectRatio);
}

void MainWindow::zoomIn()
{
    QGraphicsPixmapItem *item = dynamic_cast<QGraphicsPixmapItem*>(scene->focusItem());
    if (item)
        item->setScale(item->scale() * 1.2);
}

void MainWindow::zoomOut()
{
    QGraphicsPixmapItem *item = dynamic_cast<QGraphicsPixmapItem*>(scene->focusItem());
    if (item)
        item->setScale(item->scale() / 1.2);
}

void MainWindow::rotate()
{
    QGraphicsPixmapItem *item = dynamic_cast<QGraphicsPixmapItem*>(scene->focusItem());
    if (item) {
        bool ok;
        int angle = QInputDialog::getInt(this, tr("Rotate"), tr("Angle (degrees):"), 0, -359, 359, 1, &ok);
        if (ok) {
            item->setRotation(item->rotation() + angle);
            QPointF center = item->boundingRect().center();
            QPointF offset = center - item->mapToScene(center);
            item->setPos(item->pos() + offset);
        }
    }
}

void MainWindow::move()
{
    QGraphicsPixmapItem *item = dynamic_cast<QGraphicsPixmapItem*>(scene->focusItem());
    if (item) {
        bool ok;
        int x = QInputDialog::getInt(this, tr("Move"), tr("X:"), 0, -10000, 10000, 1, &ok);
        if (!ok)
            return;
        int y = QInputDialog::getInt(this, tr("Move"), tr("Y:"), 0, -10000, 10000, 1, &ok);
        if (!ok)
            return;
        QPointF newPos = item->pos() + QPointF(x, y);
        item->setPos(newPos);
    }
}


MainWindow::~MainWindow()
{
    delete scene;
    delete view;
    delete openAction;
    delete zoomInAction;
    delete zoomOutAction;
    delete rotateAction;
    delete moveAction;
}
