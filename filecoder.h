#ifndef FILECODER_H
#define FILECODER_H

#include <QObject>
#include <QMap>
#include <QList>
#include <QFile>
#include <QDir>

#include "settings.h"

class FileCoder : public QObject
{
    Q_OBJECT
public:
    explicit FileCoder(QObject *parent = nullptr);

    void saveSettigs();
    void findFiles(QDir files_dir);
    void startProcessing();
    void stopProcessing();
    void resumeProccesing();
    void proccesFile();


private:
    Settings coder_settings;
    QMap<QString ,quint64> files_offset;
    bool isPaused;
    QList<QFile> files_to_code;


signals:
};

#endif // FILECODER_H
