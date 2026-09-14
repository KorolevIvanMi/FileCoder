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
    repeat_timer = new QTimer(this);
    ui->startProcessBtn->setEnabled(false);
    ui->pauseBtn->setEnabled(false);
    ui->resumeBtn->setEnabled(false);

    ui->repeatTimeTe->setEnabled(false);

    connect(ui->startProcessBtn, &QPushButton::released, this, &MainWindow::writeSettings);

    connect(ui->modificationValueLe, &QLineEdit::textChanged, this, &MainWindow::checkHexMusk);
    connect(ui->workFormatCmb, &QComboBox::currentIndexChanged, this , &MainWindow::checkAppMod);

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

    if (thread && thread->isRunning()) {
        qDebug() << "Уже идёт, пропускаю";
        return;
    }

    if (repeat_timer->isActive()) {
        repeat_timer->stop();
    }
    qDebug() << "начало работы";


    file_coder = new FileCoder();
    thread = new QThread();

    file_coder->saveSettigs(settings.file_mask, settings.input_files_mode, settings.output_dir, settings.input_dir,
                            settings.repeat_files_names_mode, settings.repeat_coding_files,
                            settings.repeat_time, settings.hex_code_mask);

    connect(ui->pauseBtn, &QPushButton::released,file_coder, &FileCoder::pause, Qt::DirectConnection);
    connect(ui->resumeBtn, &QPushButton::released, file_coder, &FileCoder::resume, Qt::DirectConnection);

    file_coder->moveToThread(thread);

    connect(thread, &QThread::started, file_coder, &FileCoder::process);
    connect(file_coder, &FileCoder::finished, thread, &QThread::quit);


    connect(file_coder, &FileCoder::finished,file_coder, &QObject::deleteLater);
    connect(thread, &QThread::finished,thread, &QObject::deleteLater);

    connect(thread, &QThread::finished, this, [this]() {
        file_coder = nullptr;
        thread = nullptr;
        ui->startProcessBtn->setEnabled(true);
        ui->pauseBtn->setEnabled(false);
        ui->resumeBtn->setEnabled(false);});

    ui->startProcessBtn->setEnabled(false);
    ui->pauseBtn->setEnabled(true);
    ui->resumeBtn->setEnabled(true);
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

void MainWindow::writeSettings(){
    qDebug() << "считывание данных с формы";

    QString file_mask = ui->fileMaskLe->text();
    qint16 input_files_mode = ui->inputFileActionCmb->currentIndex();
    QDir output_dir = ui->outputPathLe->text();
    QDir input_dir = ui->inputPathLe->text();
    qint16 repeat_files_names_mode = ui->repeatingFileCmb->currentIndex();
    bool repeat_coding_files = ui->workFormatCmb->currentIndex();
    QTime repeat_time = ui->repeatTimeTe->time();
    QString string_code_mask = ui->modificationValueLe->text();
    quint64 hex_code_mask = string_code_mask.toULongLong(nullptr, 16);

    qDebug() << "Маска файлов: " << file_mask
             << "\nДействие с входными файлами: " << input_files_mode
             << "\nДериктория результата: " << output_dir
             << "\nДериктория входных: " << input_dir
             << "\nДействие при повторяющихся названиях: " << repeat_files_names_mode
             << "\nПовторения кодинга: " << repeat_coding_files
             << "\nПериодичность повторений: " << repeat_time
             << "\nМаска для кодирования файла: " << hex_code_mask;

    this->settings.file_mask = file_mask;
    this->settings.input_files_mode = input_files_mode;
    this->settings.output_dir = output_dir;
    this->settings.input_dir = input_dir;
    this->settings.repeat_files_names_mode = repeat_files_names_mode;
    this->settings.repeat_time = repeat_time;
    this->settings.hex_code_mask = hex_code_mask;

    int ms = QTime(0,0).msecsTo(repeat_time);
    if (ms > 0){
        repeat_timer->setInterval(ms);

        connect(repeat_timer, &QTimer::timeout, this, &MainWindow::StartWork);
        StartWork();
        repeat_timer->start();
    } else{
        StartWork();
    }


}

void MainWindow::checkAppMod(){
    if (ui->workFormatCmb->currentIndex() == 0){
        ui->repeatTimeTe->setEnabled(false);
    } else {
         ui->repeatTimeTe->setEnabled(true);
    }
}