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



    ui->setupUi(this);
    ui->startProcessBtn->setEnabled(false);

    connect(ui->startProcessBtn, &QPushButton::released, this, &MainWindow::StartWork);
    connect(ui->modificationValueLe, &QLineEdit::textChanged, this, &MainWindow::checkHexMusk);


}

MainWindow::~MainWindow()
{
    if (thread && thread->isRunning()) {
        thread->quit();
        thread->wait(3000);
    }
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

    file_coder = new FileCoder();
    thread     = new QThread();

    file_coder->saveSettigs(file_mask, input_files_mode, output_dir, input_dir,
                            repeat_files_names_mode, repeat_coding_files,
                            repeat_timer, hex_code_mask);

    file_coder->moveToThread(thread);

    connect(thread, &QThread::started, file_coder, &FileCoder::process);
    connect(file_coder, &FileCoder::finished, thread, &QThread::quit);


    connect(file_coder, &FileCoder::finished,file_coder, &QObject::deleteLater);
    connect(thread, &QThread::finished,thread, &QObject::deleteLater);

    connect(thread, &QThread::finished, this, [this]() {
        file_coder = nullptr;
        thread = nullptr;});

    thread->start();

}

void MainWindow::checkHexMusk(){
    QString mask = ui->modificationValueLe->text();
    const QString availableSimbols = "1234567890ABCDEFabcdef";
    bool is_okay = true;
    if (mask.size() == 16){
        for(QChar symbol : mask){
            if(availableSimbols.contains(symbol) == false ){
                is_okay = false;
                break;
            }
        }
    } else {
        is_okay = false;
    }
    if(is_okay){
        ui->startProcessBtn->setEnabled(true);
    }else{
        ui->startProcessBtn->setEnabled(false);
    }
}