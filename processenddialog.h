#ifndef PROCESSENDDIALOG_H
#define PROCESSENDDIALOG_H

#include <QWidget>

namespace Ui {
class ProcessEndDialog;
}

class ProcessEndDialog : public QWidget
{
    Q_OBJECT

public:
    explicit ProcessEndDialog(QWidget *parent = nullptr);
    ~ProcessEndDialog();

private:
    Ui::ProcessEndDialog *ui;
};

#endif // PROCESSENDDIALOG_H
