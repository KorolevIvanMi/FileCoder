#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "filecoder.h"

#include <QMainWindow>
#include <QThread>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    void StartWork();

private:
    Ui::MainWindow *ui;
    FileCoder *file_coder = nullptr;
    QThread   *thread     = nullptr;
};
#endif // MAINWINDOW_H
