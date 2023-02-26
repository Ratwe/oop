#include "mainwindow.h"
#include "qmenubar.h"
#include "request.h"
#include "err.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QInputDialog>
#include <QPointF>
#include <QtMath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Создаем QAction для открытия изображения и связываем его со слотом openImage()
    openAction = new QAction(tr("&Open"), this);
    connect(openAction, &QAction::triggered, this, &MainWindow::openImage);

    // Создаем QAction для увеличения изображения и связываем его со слотом zoomIn()
    scaleAction = new QAction(tr("&Scale"), this);
    scaleAction->setEnabled(true);
    connect(scaleAction, &QAction::triggered, this, &MainWindow::scale);

//    // Создаем QAction для уменьшения изображения и связываем его со слотом zoomOut()
//    zoomOutAction = new QAction(tr("Zoom &Out"), this);
//    zoomOutAction->setEnabled(true);
//    connect(zoomOutAction, &QAction::triggered, this, &MainWindow::zoomOut);

//    // Создаем QAction для поворота изображения и связываем его со слотом rotate()
//    rotateAction = new QAction(tr("&Rotate"), this);
//    rotateAction->setEnabled(true);
//    connect(rotateAction, &QAction::triggered, this, &MainWindow::rotate);

//    // Создаем QAction для перемещения изображения и связываем его со слотом move()
//    moveAction = new QAction(tr("&Move"), this);
//    moveAction->setEnabled(true);
//    connect(moveAction, &QAction::triggered, this, &MainWindow::move);

    // Создаем меню File и добавляем туда QAction для открытия изображения
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAction);

    // Создаем меню Edit и добавляем туда QAction для увеличения, уменьшения, поворота и перемещения изображения
    QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(scaleAction);
//    editMenu->addAction(zoomOutAction);
//    editMenu->addAction(rotateAction);
//    editMenu->addAction(moveAction);

    // Создаем QGraphicsScene и QGraphicsView для отображения изображения
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    setCentralWidget(view);

    openImage();
}

canvas_t MainWindow::init_canvas()
{
    static canvas_t canvas;

    canvas.scene = MainWindow::scene;
    canvas.width = MainWindow::scene->width();
    canvas.height = MainWindow::scene->height();

    printf("%dx%d\n", canvas.width, canvas.height);

    return canvas;
}

void MainWindow::handle_rc(const err_t rc)
{
    printf("handling_rc = %d\n", rc);

    if (!rc)
    {
        canvas_t canvas = init_canvas();
        request_t draw_request = {.code = REQUEST_DRAW, .canvas = canvas};
        handle_request(draw_request);
    }
    else
        handle_error(rc);
}

void MainWindow::openImage()
{
    // Создание структуры request_t с указанием кода REQUEST_LOAD и имени файла "data.txt"
    request_t load_request = {.code = REQUEST_LOAD};

    // Обработка запроса на загрузку данных из файла
    err_t rc = handle_request(load_request);

    // Обработка ошибки при обработке запроса
    handle_rc(rc);
}

void MainWindow::scale()
{
    // Создание структуры request_t с указанием кода REQUEST_LOAD и имени файла "data.txt"
    request_t load_request = {.code = REQUEST_SCALE};

    // Обработка запроса на загрузку данных из файла
    err_t rc = handle_request(load_request);

    // Обработка ошибки при обработке запроса
    handle_rc(rc);
}

//void MainWindow::rotate()
//{
//    QGraphicsPixmapItem *item = dynamic_cast<QGraphicsPixmapItem*>(scene->items().first());
//    if (item) {
//        bool ok;
//        int angle = QInputDialog::getInt(this, tr("Rotate"), tr("Angle (degrees):"), 0, -359, 359, 1, &ok);
//        if (ok) {
//            item->setRotation(item->rotation() + angle);
//            QPointF center = item->boundingRect().center();
//            QPointF offset = center - item->mapToScene(center);
//            item->setPos(item->pos() + offset);
//        }
//    }
//}

//void MainWindow::move()
//{
//    QGraphicsPixmapItem *item = dynamic_cast<QGraphicsPixmapItem*>(scene->items().first());
//    if (item) {
//        bool ok;
//        int x = QInputDialog::getInt(this, tr("Move"), tr("X:"), 0, -10000, 10000, 1, &ok);
//        if (!ok)
//            return;
//        int y = QInputDialog::getInt(this, tr("Move"), tr("Y:"), 0, -10000, 10000, 1, &ok);
//        if (!ok)
//            return;
//        QPointF newPos = item->pos() + QPointF(x, y);
//        item->setPos(newPos);
//    }
//}


MainWindow::~MainWindow()
{
    delete scene;
    delete view;
    delete openAction;
//    delete zoomInAction;
//    delete zoomOutAction;
//    delete rotateAction;
//    delete moveAction;
}
