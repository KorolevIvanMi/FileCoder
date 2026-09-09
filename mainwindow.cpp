#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QDebug"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->startProcessBtn, &QPushButton::released, this, &MainWindow::StartWork);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::StartWork(){
    qDebug() << "начало работы";
}