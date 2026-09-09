#include "filecoder.h"

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