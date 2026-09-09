#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>
#include <QDir>
#include <QTime>

struct Settings{
    QString file_mask;
    qint16 input_files_mode;
    QDir output_dir;
    QDir input_dir;
    qint16 repeat_files_names_mode;
    bool repeat_coding_files;
    QTime repeat_timer;
    quint64 hex_code_mask;

};

#endif // SETTINGS_H
