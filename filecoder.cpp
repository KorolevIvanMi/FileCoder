#include "filecoder.h"

#include "QFile"
#include <QThread>
#include <QRegularExpression>

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

    QFileInfoList files_dirs = files_dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot | QDir::NoSymLinks);
    QString dir = files_dir.absolutePath();

    for (const QFileInfo &info : std::as_const(files_dirs)){

        if (info.isFile()){
            if (!coder_settings.file_mask.isEmpty()) {
                QRegularExpression re(QRegularExpression::wildcardToRegularExpression(coder_settings.file_mask));
                if (!re.match(info.fileName()).hasMatch()) continue;
            }
            files_to_code.append(info.absoluteFilePath());
            files_offset[info.absoluteFilePath()] = 0;
            qDebug() << "Файл: " << info.fileName();
        } else {
            scanDir(info.absoluteFilePath());
        }
    }

}

void FileCoder::scanDir(QDir files_dir){
    QFileInfoList files_dirs = files_dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot | QDir::NoSymLinks);
    QString dir = files_dir.absolutePath();

    for (const QFileInfo &info : std::as_const(files_dirs)){

        if (info.isFile()){
            if (!coder_settings.file_mask.isEmpty()) {
                QRegularExpression re(QRegularExpression::wildcardToRegularExpression(coder_settings.file_mask));
                if (!re.match(info.fileName()).hasMatch()) continue;
            }
            files_to_code.append(info.absoluteFilePath());
            files_offset[info.absoluteFilePath()] = 0;
            qDebug() << "Файл: " << info.fileName();
        } else {
            scanDir(info.absoluteFilePath());
        }
    }
}

void FileCoder::startProcessing(){
    files_to_code.clear();
    files_offset.clear();
    isPaused = false;

    // QThread::msleep(5000);
    findFiles(coder_settings.input_dir);
    while (!files_to_code.isEmpty()) {
        const QString path = files_to_code.takeFirst();
        processFile(path);
        files_offset.remove(path);

    }
}

void FileCoder::processFile(QString path){
    QFile inputFile(path);
    if (!inputFile.open(QIODevice::ReadOnly)){
        qWarning() << "Не удалось открыть файл" << inputFile.errorString();
    }

    QFileInfo info(path);

    QString output_path = coder_settings.output_dir.absolutePath() + "/" + "codded_"+ info.fileName() ;
    qDebug() << "Выходная дерриктория: " << output_path;
    QFile outputFile(output_path);
    if(!outputFile.open(QIODevice::WriteOnly)){
        qWarning() << "Не создать выход:" << outputFile.errorString();
    }

    while (!inputFile.atEnd()){
        QByteArray chank = inputFile.read(CHANK_SIZE);
        QByteArray codded_chunk = processChank(chank);

        if(outputFile.write(codded_chunk) != codded_chunk.size()){
            qWarning() << "Ошибка записи:" << outputFile.errorString();
        }
    }
    inputFile.close();
    outputFile.close();
}

QByteArray FileCoder::processChank(QByteArray chank){
    const int n = chank.size();
    int i = 0;
    for (; i+8 <= n; i += 8){
        quint64 value = 0;
        memcpy(&value, chank.constData()+i, 8);
        value ^= coder_settings.hex_code_mask;
        memcpy(chank.data()+i, &value, 8);
    }
    if(i<n){
        const quint64 mask = coder_settings.hex_code_mask;
        const char *maskBytes = reinterpret_cast<const char*>(&mask);

        for (int k = 0; i < n; ++i, ++k) {
            chank[i] ^= maskBytes[k];
        }
    }
    return chank;
}