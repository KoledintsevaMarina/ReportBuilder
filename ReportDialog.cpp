#include "ReportDialog.h"
#include "ui_ReportDialog.h"

#include "qssStyle.h"

#include <QDebug>
#include <QFileDialog>

ReportDialog::ReportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReportDialog)
{
    ui->setupUi(this);
    setStyleSheet(qss::style());

    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::CustomizeWindowHint);

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

    connect(ui->closeButton, &QPushButton::clicked, this, [this]() {
        this->close();
    });
//------------------------------------------------------------------------------------------------------------------
    connect (ui->saveButton, &QPushButton::clicked, this, [this](){
        qDebug()<<"Save";
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Text Files (*.txt)"));

        QFile file(fileName);
        file.open(QIODevice::WriteOnly);
        QTextStream stream(&file);
        stream << ui->plainTextEdit->toPlainText();
        stream.flush();
        file.close();
    });

//------------------------------------------------------------------------------------------------------------------

}

ReportDialog::~ReportDialog()
{
    delete ui;
}
