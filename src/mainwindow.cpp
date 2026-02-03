#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore/QtCore>
#include <QtGui/QtGui>
#include <QtCharts/QtCharts>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
