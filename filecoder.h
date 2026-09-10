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

    void saveSettigs(const QString& file_mask, qint16 input_files_mode, const QDir& output_dir, const QDir& input_dir,
                     qint16 repeat_files_names_mode, bool repeat_coding_files, QTime repeat_timer, quint64 hex_code_mask);
    void findFiles(QDir files_dir);
    void startProcessing();
    void stopProcessing();
    void resumeProccesing();
    void proccesFile();
    void scanDir(QDir path);


private:
    Settings coder_settings;
    QMap<QString ,quint64> files_offset;
    bool isPaused = false;
    QList<QString> files_to_code;



signals:
};

#endif // FILECODER_H
