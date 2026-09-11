#ifndef FILECODER_H
#define FILECODER_H

#include <QObject>
#include <QMap>
#include <QList>
#include <QFile>
#include <QDir>

#include "settings.h"

#define CHANK_SIZE 1024


class FileCoder : public QObject
{
    Q_OBJECT
public:
    explicit FileCoder(QObject *parent = nullptr);

    void saveSettigs(const QString& file_mask, qint16 input_files_mode, const QDir& output_dir, const QDir& input_dir,
                     qint16 repeat_files_names_mode, bool repeat_coding_files, QTime repeat_timer, quint64 hex_code_mask); // готово
    void findFiles(QDir files_dir); // готово
    void startProcessing(); // готово
    void stopProcessing();
    void resumeProccesing();
    void processFile(QString path); // готово
    QByteArray processChank(QByteArray chank); // готово
    void scanDir(QDir files_dir); // готово

public slots:
    void process();

signals:
    void finished();
private:
    Settings coder_settings;
    QMap<QString ,quint64> files_offset;
    bool isPaused = false;
    QList<QString> files_to_code;



signals:
};

#endif // FILECODER_H
