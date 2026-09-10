#include "filecoder.h"

#include "QFile"

FileCoder::FileCoder(QObject *parent)
    : QObject{parent}
{}

void FileCoder::saveSettigs(const QString& file_mask, qint16 input_files_mode, const QDir& output_dir,const QDir& input_dir, qint16 repeat_files_names_mode,
                       bool repeat_coding_files, QTime repeat_timer, quint64 hex_code_mask){
    this->coder_settings.file_mask = file_mask;
    this->coder_settings.input_files_mode = input_files_mode;
    this->coder_settings.output_dir = output_dir;
    this->coder_settings.input_dir = input_dir;
    this->coder_settings.repeat_files_names_mode = repeat_files_names_mode;
    this->coder_settings.repeat_timer = repeat_timer;
    this->coder_settings.hex_code_mask = hex_code_mask;
}

void FileCoder::findFiles(QDir files_dir){

    if (coder_settings.file_mask != ""){
        QStringList filter;
        filter << coder_settings.file_mask;
        files_dir.setNameFilters(filter);
    }
    QFileInfoList files_dirs = files_dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot);
    QString dir = files_dir.absolutePath();

    for (const QFileInfo &info : std::as_const(files_dirs)){

        if (info.isFile()){
            files_to_code.append(info.absoluteFilePath());
            qDebug() << "Файл: " << info.fileName();
        } else {
            scanDir(info.absoluteFilePath());
        }
    }

}

void FileCoder::scanDir(QDir path){
    if (coder_settings.file_mask != ""){
        QStringList filter;
        filter << coder_settings.file_mask;
        path.setNameFilters(filter);
    }
    QFileInfoList files_dirs = path.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot);
    QString dir = path.absolutePath();

    for (const QFileInfo &info : std::as_const(files_dirs)){

        if (info.isFile()){
            files_to_code.append(info.absoluteFilePath());
            qDebug() << "Файл: " << info.fileName();
        } else {
            scanDir(info.absoluteFilePath());
        }
    }
}