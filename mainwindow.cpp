#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QAction>
#include <QMenu>
#include <QDebug>//===================     потом удалить    =====================================================
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

#ifndef QT_NO_PRINTER
#include <QPrinter>
#include <QPrintDialog>
#endif

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//=====================================================================================================================
    connect(ui->workField_xyButton, &QPushButton::toggled, this, [=](bool) {
        ui->workField_stackedWidget->setCurrentIndex(1);
    });

    connect(ui->workField_daButton, &QPushButton::toggled, this, [=](bool) {
        ui->workField_stackedWidget->setCurrentIndex(0);
    });

    connect(ui->operatorActions_xyButton, &QPushButton::toggled, this, [=](bool) {
        ui->operatorActions_stackedWidget->setCurrentIndex(1);
    });

    connect(ui->operatorActions_daButton, &QPushButton::toggled, this, [=](bool) {
        ui->operatorActions_stackedWidget->setCurrentIndex(0);
    });
//=======================================================================================================================


    connect (ui->action_Open_log, &QAction::triggered, this, [this] () {
        qDebug()<<"Open log";
        QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "*.txt");
        if (fileName !="")
        {
            QFile file(fileName);
            if (!file.open(QIODevice::ReadOnly))
            {
                QMessageBox::critical(this, "Error", "Could not open file");
                return;
            }
            while(!file.atEnd())
            {
                QString codogram = file.readLine(); //считывание кодограммы (одной строки)
                Log l;
                l.Read_codogram(codogram);
            }

            file.close();
        }
    });

    connect (ui->action_Close_log, &QAction::triggered, this, [this] () {//возможно доделать
        qDebug()<<"Close codogram";
        ui->plainTextEdit->clear();

        ui->workField_xyButton->setChecked(1);
        ui->workField_daButton->setChecked(0);
        ui->pushButton_5->setChecked(1);
        ui->pushButton_6->setChecked(0);

        ui->doubleSpinBox->setValue(0);
        ui->doubleSpinBox_2->setValue(0);
        ui->doubleSpinBox_3->setValue(0);
        ui->doubleSpinBox_4->setValue(0);
        ui->doubleSpinBox_5->setValue(0);
        ui->doubleSpinBox_6->setValue(0);
        ui->doubleSpinBox_7->setValue(0);
        ui->doubleSpinBox_8->setValue(0);
        ui->doubleSpinBox_15->setValue(0);
        ui->doubleSpinBox_16->setValue(0);
        ui->doubleSpinBox_17->setValue(0);

        ui->checkBox->setChecked(0);
        ui->checkBox_3->setChecked(0);
        ui->checkBox_2->setChecked(0);
        ui->checkBox_4->setChecked(0);
        ui->checkBox_5->setChecked(0);
        ui->checkBox_6->setChecked(0);
        ui->checkBox_7->setChecked(0);
        ui->checkBox_8->setChecked(0);
        ui->checkBox_12->setChecked(0);
        ui->checkBox_13->setChecked(0);
        ui->checkBox_14->setChecked(0);
        ui->checkBox_15->setChecked(0);
        ui->checkBox_16->setChecked(0);

        ui->comboBox->setCurrentIndex(0);
        ui->comboBox_4->setCurrentIndex(0);
        ui->comboBox_5->setCurrentIndex(0);

//        ui->dateTimeEdit->setDateTime(ui->dateTimeEdit->minimumDateTime());
        ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
        ui->dateTimeEdit_2->setDateTime(QDateTime::currentDateTime());
        ui->dateTimeEdit_3->setDateTime(QDateTime::currentDateTime());
        ui->dateTimeEdit_4->setDateTime(QDateTime::currentDateTime());
        ui->dateTimeEdit_5->setDateTime(QDateTime::currentDateTime());
        ui->dateTimeEdit_6->setDateTime(QDateTime::currentDateTime());
        ui->dateTimeEdit_7->setDateTime(QDateTime::currentDateTime());
        ui->dateTimeEdit_8->setDateTime(QDateTime::currentDateTime());

    });

    connect (ui->action_Save, &QAction::triggered, this, [this](){
        QString fileName = QFileDialog::getSaveFileName(this, "Save File", "", "Text Files (*.txt)");

        QFile file(fileName);
        file.open(QIODevice::WriteOnly);
        QTextStream stream(&file);
        stream << ui->plainTextEdit->toPlainText();
        stream.flush();
        file.close();
    });

    #if !defined(QT_NO_PRINTER) && !defined(QT_NO_PRINTDIALOG)
    connect (ui ->action_Print, &QAction::triggered, this, [this]() {//я не уверенна, что работает
        QPrinter printer;
        QPrintDialog* pPrintDialog = new QPrintDialog(&printer, this);
        if (pPrintDialog->exec())
        {
            ui->plainTextEdit->print(&printer);
        }
        delete pPrintDialog;
    });
    #endif // QT_NO_PRINTER

    connect(ui->action_Exit, &QAction::triggered, this, [this] (){//доделать +окно
        qDebug()<<"Exit";
        QMainWindow::close();
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}
