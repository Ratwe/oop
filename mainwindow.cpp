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
#include <QFile>

// Копирование содержимого файла sourceFileName в файл destinationFileName
bool copyFile(const QString& sourceFileName, const QString& destinationFileName)
{
    QFile sourceFile(sourceFileName);
    QFile destinationFile(destinationFileName);

    if (!sourceFile.open(QIODevice::ReadOnly) || !destinationFile.open(QIODevice::WriteOnly))
        return false;

    QByteArray buffer;
    while (!sourceFile.atEnd()) {
        buffer = sourceFile.read(8192);
        if (destinationFile.write(buffer) == -1)
            return false;
    }

    return true;
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    copyFile("D:/Code/QT/lab_01/data_o.txt", "D:/Code/QT/lab_01/data.txt");

    // Создаем QAction для открытия изображения и связываем его со слотом openImage()
    openAction = new QAction(tr("&Open"), this);
    connect(openAction, &QAction::triggered, this, &MainWindow::openImage);

    // Создаем QAction для увеличения изображения и связываем его со слотом zoomIn()
    scaleAction = new QAction(tr("&Scale"), this);
    scaleAction->setEnabled(true);
    connect(scaleAction, &QAction::triggered, this, &MainWindow::scale);

    // Создаем QAction для поворота изображения и связываем его со слотом rotate()
    rotateAction = new QAction(tr("&Rotate"), this);
    rotateAction->setEnabled(true);
    connect(rotateAction, &QAction::triggered, this, &MainWindow::rotate);

    // Создаем QAction для перемещения изображения и связываем его со слотом move()
    moveAction = new QAction(tr("&Move"), this);
    moveAction->setEnabled(true);
    connect(moveAction, &QAction::triggered, this, &MainWindow::move);

    // Создаем меню File и добавляем туда QAction для открытия изображения
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAction);

    // Создаем меню Edit и добавляем туда QAction для увеличения, уменьшения, поворота и перемещения изображения
    QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(scaleAction);
    editMenu->addAction(rotateAction);
    editMenu->addAction(moveAction);

    // Создаем QGraphicsScene и QGraphicsView для отображения изображения
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    setCentralWidget(view);

    setFixedSize(800, 600);
    scene->setSceneRect(0, 0, 700, 500);
//    openImage();
}

canvas_t MainWindow::init_canvas()
{
    static canvas_t canvas;

    canvas.scene = scene;
    canvas.width = scene->width();
    canvas.height = scene->height();

    return canvas;
}

void MainWindow::handle_rc(const err_t rc)
{
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
    err_t rc = OK;
    bool ok;
    double coeff = QInputDialog::getDouble(this, tr("Scale"), tr("Scale coeff:"), 0, 0, 100, 1, &ok);

    if (ok) {
        // Создание структуры request_t с указанием кода REQUEST_LOAD и имени файла "data.txt"
        request_t scale_request = {.code = REQUEST_SCALE, .scale = {coeff, coeff, coeff}};

        // Обработка запроса на загрузку данных из файла
        rc = handle_request(scale_request);
    } else
        rc = INT_ERR;


    // Обработка ошибки при обработке запроса
    handle_rc(rc);
}

void MainWindow::rotate()
{
    err_t rc = OK;
    bool ok;
    double angle1 = QInputDialog::getInt(this, tr("Rotate"), tr("Angle 1 (degrees):"), 0, -359, 359, 1, &ok);
    if (ok) {
        double angle2 = QInputDialog::getInt(this, tr("Rotate"), tr("Angle 2 (degrees):"), 0, -359, 359, 1, &ok);
        if (ok) {
            double angle3 = QInputDialog::getInt(this, tr("Rotate"), tr("Angle 3 (degrees):"), 0, -359, 359, 1, &ok);
            if (ok) {
                // Создание структуры request_t с указанием кода REQUEST_ROTATE и углов поворота
                request_t turn_request = {
                    .code = REQUEST_TURN,
                    .turn = { angle1, angle2, angle3 }
                };

                // Обработка запроса на поворот
                rc = handle_request(turn_request);
            } else {
                rc = INT_ERR;
            }
        } else {
            rc = INT_ERR;
        }
    } else {
        rc = INT_ERR;
    }

    handle_rc(rc);
}



void MainWindow::move()
{
    err_t rc = OK;
    bool ok;
    double x = QInputDialog::getInt(this, tr("Move"), tr("X:"), 0, -10000, 10000, 1, &ok);
    if (ok) {
        double y = QInputDialog::getInt(this, tr("Move"), tr("Y:"), 0, -10000, 10000, 1, &ok);
        if (ok) {
            double z = QInputDialog::getInt(this, tr("Move"), tr("Z:"), 0, -10000, 10000, 1, &ok);
            if (ok) {
                // Создание структуры request_t с указанием кода REQUEST_ROTATE и углов поворота
                request_t turn_request = {
                    .code = REQUEST_MOVE,
                    .move = { x, y, z }
                };

                // Обработка запроса на поворот
                rc = handle_request(turn_request);
            } else {
                rc = INT_ERR;
            }
        } else {
            rc = INT_ERR;
        }
    } else {
        rc = INT_ERR;
    }


    handle_rc(rc);
}


MainWindow::~MainWindow()
{
    delete scene;
    delete view;
    delete openAction;
    delete rotateAction;
    delete moveAction;
}
