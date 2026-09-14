#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "filecoder.h"
#include "settings.h"


#include <QMainWindow>
#include <QThread>
#include <QTimer>

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
public slots:
    void checkHexMusk();
    void writeSettings();
    void checkAppMod();

private:
    Ui::MainWindow *ui;
    FileCoder* file_coder = nullptr;
    QThread* thread     = nullptr;

    QTimer* repeat_timer = nullptr;
    Settings settings;
    // MyDialog* mydlg;
};
#endif // MAINWINDOW_H
