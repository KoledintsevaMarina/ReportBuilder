#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "ReportDialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    connect(ui->openReportDialogButton, &QPushButton::clicked, this, [=]() {
//        ReportDialog rd;
//        rd.exec();
//    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
