#include "processenddialog.h"
#include "ui_processenddialog.h"

ProcessEndDialog::ProcessEndDialog(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ProcessEndDialog)
{
    ui->setupUi(this);
    connect(ui->pushButton1, &QPushButton::clicked, this, &QWidget::close);
}

ProcessEndDialog::~ProcessEndDialog()
{
    delete ui;
}
