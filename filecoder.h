#ifndef FILECODER_H
#define FILECODER_H

#include <QObject>

class FileCoder : public QObject
{
    Q_OBJECT
public:
    explicit FileCoder(QObject *parent = nullptr);

signals:
};

#endif // FILECODER_H
