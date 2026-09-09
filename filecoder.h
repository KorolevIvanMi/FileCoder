#ifndef FILECODER_H
#define FILECODER_H

#include <QObject>
#include <QMap>
#include <QList>
#include <QFile>

#include "settings.h"

class FileCoder : public QObject
{
    Q_OBJECT
public:
    explicit FileCoder(QObject *parent = nullptr);

private:
    Settings coder_settings;
    QMap<QString ,quint64> files_offset;
    bool isPaused;
    QList<QFile> files_to_code;


signals:
};

#endif // FILECODER_H
