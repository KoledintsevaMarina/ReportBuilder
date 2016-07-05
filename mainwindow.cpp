#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include "ReportDialog.h"

#include <QAction>
#include <QMenu>
#include <QDebug>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    connect(ui->openReportDialogButton, &QPushButton::clicked, this, [=]() {
//        ReportDialog rd;
//        rd.exec();
//    });

    connect (ui->action_Save, &QAction::triggered, this, [this](){
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Text Files (*.txt)"));

        QFile file(fileName);
        file.open(QIODevice::WriteOnly);
        QTextStream stream(&file);
        stream << ui->plainTextEdit->toPlainText();
        stream.flush();
        file.close();
    });

    connect (ui ->action_Print, &QAction::triggered, this, [this]() {
        qDebug()<<"Print";

    });

    connect(ui->action_Exit, &QAction::triggered, this, [this] (){
        QMainWindow::close();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
