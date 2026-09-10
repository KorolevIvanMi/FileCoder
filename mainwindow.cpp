#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QDebug"
#include <QString>
#include <QDir>
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    file_coder = new FileCoder();

    ui->setupUi(this);

    connect(ui->startProcessBtn, &QPushButton::released, this, &MainWindow::StartWork);



}

MainWindow::~MainWindow()
{
    delete file_coder;
    delete ui;

}

void MainWindow::StartWork(){
    qDebug() << "начало работы";
    qDebug() << "считывание данных с формы";

    QString file_mask = ui->fileMaskLe->text();
    qint16 input_files_mode = ui->inputFileActionCmb->currentIndex();
    QDir output_dir = ui->outputPathLe->text();
    QDir input_dir = ui->inputPathLe->text();
    qint16 repeat_files_names_mode = ui->repeatingFileCmb->currentIndex();
    bool repeat_coding_files = ui->workFormatCmb->currentIndex();
    QTime repeat_timer = ui->repeatTimeTe->time();
    QString string_code_mask = ui->modificationValueLe->text();
    quint64 hex_code_mask = string_code_mask.toULongLong(nullptr, 16);

    qDebug() << "Маска файлов: " << file_mask
             << "\nДействие с входными файлами: " << input_files_mode
             << "\nДериктория результата: " << output_dir
             << "\nДериктория входных: " << input_dir
             << "\nДействие при повторяющихся названиях: " << repeat_files_names_mode
             << "\nПовторения кодинга: " << repeat_coding_files
             << "\nПериодичность повторений: " << repeat_timer
             << "\nМаска для кодирования файла: " << hex_code_mask;

    file_coder->saveSettigs(file_mask, input_files_mode, output_dir, input_dir,
        repeat_files_names_mode, repeat_coding_files, repeat_timer, hex_code_mask);
    // file_coder->findFiles(input_dir);



}