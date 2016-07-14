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
        inter_state.workField = 1;
        read_interface();
        write_report();
    });

    connect(ui->workField_daButton, &QPushButton::toggled, this, [=](bool) {
        ui->workField_stackedWidget->setCurrentIndex(0);
        inter_state.workField = 0;
        read_interface();
        write_report();
    });

    connect(ui->workField_xyButton, &QPushButton::toggled, this, [=](bool) {
        ui->workField_stackedWidget->setCurrentIndex(1);
        inter_state.workField = 1;
        read_interface();
        write_report();
    });

    connect(ui->workField_daButton, &QPushButton::toggled, this, [=](bool) {
        ui->workField_stackedWidget->setCurrentIndex(0);
        inter_state.workField = 0;
        read_interface();
        write_report();
    });

    connect (ui->pushButton, &QPushButton::toggled, this, [=] (bool){
        if (inter_state.posButton_index == 1)
        {
            ui->label_32->setText("Х [м]");
            ui->label_35->setText("Y [м]");
            ui->label_38->setText("Высота [м]");
            ui->label_3->setText("Высота [м]");
            ui->label_2->setText("Дальность [м]");
            ui->spinBox->setValue(ui->spinBox->value() * 1000);
            ui->spinBox_2->setValue(ui->spinBox_2->value() * 1000);
            ui->spinBox_3->setValue(ui->spinBox_3->value() * 1000);
            ui->spinBox_4->setValue(ui->spinBox_4->value() * 1000);
            ui->spinBox_5->setValue(ui->spinBox_5->value() * 1000);
            ui->spinBox_6->setValue(ui->spinBox_6->value() * 1000);
            ui->doubleSpinBox_3->setValue(ui->doubleSpinBox_3->value() * 1000);
            ui->doubleSpinBox_4->setValue(ui->doubleSpinBox_4->value() * 1000);
            ui->doubleSpinBox_5->setValue(ui->doubleSpinBox_5->value() * 1000);
            ui->doubleSpinBox_6->setValue(ui->doubleSpinBox_6->value() * 1000);
            inter_state.posButton_index = 0;
        }
        read_interface();
        write_report();
    });

    connect (ui->pushButton_2, &QPushButton::toggled, this, [=] (bool){
        if (inter_state.posButton_index == 0)
        {
            ui->label_32->setText("Х [км]");
            ui->label_35->setText("Y [км]");
            ui->label_38->setText("Высота [км]");
            ui->label_3->setText("Высота [км]");
            ui->label_2->setText("Дальность [км]");
            ui->spinBox->setValue(ui->spinBox->value() / 1000);
            ui->spinBox_2->setValue(ui->spinBox_2->value() / 1000);
            ui->spinBox_3->setValue(ui->spinBox_3->value() / 1000);
            ui->spinBox_4->setValue(ui->spinBox_4->value() / 1000);
            ui->spinBox_5->setValue(ui->spinBox_5->value() / 1000);
            ui->spinBox_6->setValue(ui->spinBox_6->value() / 1000);
            ui->doubleSpinBox_3->setValue(ui->doubleSpinBox_3->value() / 1000);
            ui->doubleSpinBox_4->setValue(ui->doubleSpinBox_4->value() / 1000);
            ui->doubleSpinBox_5->setValue(ui->doubleSpinBox_5->value() / 1000);
            ui->doubleSpinBox_6->setValue(ui->doubleSpinBox_6->value() / 1000);
            inter_state.posButton_index = 1;
        }
        read_interface();
        write_report();
    });

    connect (ui->pushButton_5, &QPushButton::toggled, this, [=] (bool){
        if (inter_state.speedButton_index == 1)
        {
            ui->comboBox_4->setCurrentIndex(0);
            ui->doubleSpinBox_7->setValue(ui->doubleSpinBox_7->value() * 0.278);
            ui->doubleSpinBox_8->setValue(ui->doubleSpinBox_8->value() * 0.278);
            inter_state.speedButton_index = 0;
        }
        read_interface();
        write_report();
    });

    connect (ui->pushButton_6, &QPushButton::toggled, this, [=] (bool){
        if (inter_state.speedButton_index == 0)
        {
            ui->comboBox_4->setCurrentIndex(1);
            ui->doubleSpinBox_7->setValue(ui->doubleSpinBox_7->value() * 3.6);
            ui->doubleSpinBox_8->setValue(ui->doubleSpinBox_8->value() * 3.6);
            inter_state.speedButton_index = 1;
        }
        ui->spinBox->setValue(ui->doubleSpinBox_7->value() / 1000);
        read_interface();
        write_report();
    });

    connect (ui->checkBox_20, &QCheckBox::clicked, this, [=] (bool){
        read_interface();
        write_report();
    });

    connect (ui->checkBox_21, &QCheckBox::clicked, this, [=] (bool){
        read_interface();
        write_report();
    });

    connect (ui->checkBox_22, &QCheckBox::clicked, this, [=] (bool){
        read_interface();
        write_report();
    });

    connect (ui->checkBox_3, &QCheckBox::clicked, this, [=] (bool){
        read_interface();
        write_report();
    });

    connect (ui->checkBox, &QCheckBox::clicked, this, [=] (bool){
        read_interface();
        write_report();
    });

    connect (ui->checkBox_4, &QCheckBox::clicked, this, [=] (bool){
        read_interface();
        write_report();
    });

    connect (ui->checkBox_5, &QCheckBox::clicked, this, [=] (bool){
        read_interface();
        write_report();
    });

    connect (ui->checkBox_6, &QCheckBox::clicked, this, [=] (bool){
        read_interface();
        write_report();
    });

    connect (ui->checkBox_7, &QCheckBox::clicked, this, [=] (bool){
        read_interface();
        write_report();
    });

    connect (ui->checkBox_2, &QCheckBox::clicked, this, [=] (bool){
        MainWindow::read_interface();
        MainWindow::write_report();
    });

    connect (ui->checkBox_8, &QCheckBox::clicked, this, [=] (bool){
        read_interface();
        write_report();
    });

    connect (ui->checkBox_12, &QCheckBox::clicked, this, [=] (bool){
        read_interface();
        write_report();
    });

    connect (ui->checkBox_13, &QCheckBox::clicked, this, [=] (bool){
        read_interface();
        write_report();
    });

    connect (ui->checkBox_15, &QCheckBox::clicked, this, [=] (bool){
        read_interface();
        write_report();
    });

    connect (ui->checkBox_16, &QCheckBox::clicked, this, [=] (bool){
        read_interface();
        write_report();
    });

    connect (ui->checkBox_14, &QCheckBox::clicked, this, [=] (bool){
        read_interface();
        write_report();
    });

    connect (ui->comboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, [=] (int){
        read_interface();
        write_report();
    });

    connect (ui->comboBox_4, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, [=] (int){
        read_interface();
        write_report();
    });

    connect (ui->comboBox_5, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, [=] (int){
        read_interface();
        write_report();
    });

    connect (ui->spinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, [=] (int){
        read_interface();
        write_report();
    });

    connect (ui->spinBox_2, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, [=] (int){
        read_interface();
        write_report();
    });

    connect (ui->spinBox_3, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, [=] (int){
        read_interface();
        write_report();
    });

    connect (ui->spinBox_4, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, [=] (int){
        read_interface();
        write_report();
    });

    connect (ui->spinBox_5, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, [=] (int){
        read_interface();
        write_report();
    });

    connect (ui->spinBox_6, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, [=] (int){
        read_interface();
        write_report();
    });

    connect (ui->doubleSpinBox, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, [=] (double){
        read_interface();
        write_report();
    });

    connect (ui->doubleSpinBox_2, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, [=] (double){
        read_interface();
        write_report();
    });

    connect (ui->doubleSpinBox_3, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, [=] (double){
        read_interface();
        write_report();
    });

    connect (ui->doubleSpinBox_4, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, [=] (double){
        read_interface();
        write_report();
    });

    connect (ui->doubleSpinBox_5, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, [=] (double){
        read_interface();
        write_report();
    });

    connect (ui->doubleSpinBox_6, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, [=] (double){
        read_interface();
        write_report();
    });

    connect (ui->doubleSpinBox_7, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, [=] (double){
        read_interface();
        write_report();
    });

    connect (ui->doubleSpinBox_8, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, [=] (double){
        read_interface();
        write_report();
    });

    connect (ui->doubleSpinBox_35, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, [=] (double){
        read_interface();
        write_report();
    });

    connect (ui->doubleSpinBox_36, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, [=] (double){
        read_interface();
        write_report();
    });

    connect (ui->doubleSpinBox_37, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, [=] (double){
        read_interface();
        write_report();
    });

    connect (ui->doubleSpinBox_38, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, [=] (double){
        read_interface();
        write_report();
    });

    connect (ui->doubleSpinBox_39, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, [=] (double){
        read_interface();
        write_report();
    });

    connect (ui->doubleSpinBox_40, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, [=] (double){
        read_interface();
        write_report();
    });

    connect (ui->dateTimeEdit, &QDateTimeEdit::dateTimeChanged, this, [=] (const QDateTime &){
        read_interface();
        write_report();
    });

    connect (ui->dateTimeEdit_2, &QDateTimeEdit::dateTimeChanged, this, [=] (const QDateTime &){
        read_interface();
        write_report();
    });

    connect (ui->dateTimeEdit_3, &QDateTimeEdit::dateTimeChanged, this, [=] (const QDateTime &){
        read_interface();
        write_report();
    });

    connect (ui->dateTimeEdit_4, &QDateTimeEdit::dateTimeChanged, this, [=] (const QDateTime &){
        read_interface();
        write_report();
    });

    connect (ui->dateTimeEdit_5, &QDateTimeEdit::dateTimeChanged, this, [=] (const QDateTime &){
        read_interface();
        write_report();
    });

    connect (ui->dateTimeEdit_6, &QDateTimeEdit::dateTimeChanged, this, [=] (const QDateTime &){
        read_interface();
        write_report();
    });

    connect (ui->dateTimeEdit_7, &QDateTimeEdit::dateTimeChanged, this, [=] (const QDateTime &){
        read_interface();
        write_report();
    });

    connect (ui->dateTimeEdit_8, &QDateTimeEdit::dateTimeChanged, this, [=] (const QDateTime &){
        read_interface();
        write_report();
    });

    connect (ui->listWidget, &QListWidget::itemClicked, this, [=] (QListWidgetItem *){
        read_interface();
        write_report();
    });
    //=======================================================================================================================

    connect (ui->action_Open_log, &QAction::triggered, this, [this] () {
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
                    QString codogram = file.readLine();
                    m_l.Read_codogram(codogram);
                }
                file.close();
                MainWindow::read_interface();
                MainWindow::write_report();
            }
        });

        connect (ui->action_Close_log, &QAction::triggered, this, [this] () {//доделать
            qDebug()<<"Close log";

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

            ui->comboBox->setCurrentIndex(0);
            ui->comboBox_4->setCurrentIndex(0);
            ui->comboBox_5->setCurrentIndex(0);

            ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
            ui->dateTimeEdit_2->setDateTime(QDateTime::currentDateTime());
            ui->dateTimeEdit_3->setDateTime(QDateTime::currentDateTime());
            ui->dateTimeEdit_4->setDateTime(QDateTime::currentDateTime());

            ui->plainTextEdit->clear();
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
        connect (ui ->action_Print, &QAction::triggered, this, [this]() {
            QPrinter printer;
            QPrintDialog* pPrintDialog = new QPrintDialog(&printer, this);
            if (pPrintDialog->exec())
            {
                ui->plainTextEdit->print(&printer);
            }
            delete pPrintDialog;
        });
        #endif // QT_NO_PRINTER

        connect(ui->action_Exit, &QAction::triggered, this, [this] (){
            qDebug()<<"Exit";
            QMainWindow::close();
        });
    }

    MainWindow::~MainWindow()
    {
        delete ui;
    }

    void MainWindow::read_interface()
    {
        Interface_1 inter1;
        inter1.time_gen_Min = ui->dateTimeEdit->dateTime();
        inter1.time_gen_Max = ui->dateTimeEdit_2->dateTime();
        if (inter_state.workField == 1)
        {
            inter1.scope[0][0] = ui->spinBox->value();
            inter1.scope[0][1] = ui->spinBox_2->value();
            inter1.scope[1][0] = ui->spinBox_3->value();
            inter1.scope[1][1] = ui->spinBox_4->value();
            inter1.scope[2][0] = ui->spinBox_5->value();
            inter1.scope[2][1] = ui->spinBox_6->value();
            inter1.coordinate1 = "X";
            inter1.coordinate2 = "Y ";
        }
        else if (inter_state.workField ==0)
        {
            inter1.scope[0][0] = ui->doubleSpinBox->value();
            inter1.scope[0][1] = ui->doubleSpinBox_2->value();
            inter1.scope[1][0] = ui->doubleSpinBox_3->value();
            inter1.scope[1][1] = ui->doubleSpinBox_4->value();
            inter1.scope[2][0] = ui->doubleSpinBox_5->value();
            inter1.scope[2][1] = ui->doubleSpinBox_6->value();
            inter1.coordinate1 = "А";
            inter1.coordinate2 = "Д";
        }
        inter1.pace[0] = ui->doubleSpinBox_7->value();
        inter1.pace[1] = ui->doubleSpinBox_8->value();
        inter1.object = ui->comboBox->currentIndex();

        Interface_2 inter2;
        inter2.time_gen_Min = ui->dateTimeEdit_3->dateTime();
        inter2.time_gen_Max = ui->dateTimeEdit_4->dateTime();
        inter2.angleZX[0] = ui->doubleSpinBox_35->value();
        inter2.angleZX[1] = ui->doubleSpinBox_36->value();
        inter2.angleZY[0] = ui->doubleSpinBox_37->value();
        inter2.angleZY[1] = ui->doubleSpinBox_38->value();

        Interface_3 inter3;
        inter3.time_gen_Min = ui->dateTimeEdit_5->dateTime();
        inter3.time_gen_Max = ui->dateTimeEdit_6->dateTime();
        inter3.energy[0] = ui->doubleSpinBox_39->value();
        inter3.energy[1] = ui->doubleSpinBox_40->value();

        Interface_4 inter4;
        inter4.time_gen_Min = ui->dateTimeEdit_7->dateTime();
        inter4.time_gen_Max = ui->dateTimeEdit_8->dateTime();
        inter4.mode = ui->comboBox_5->currentIndex();
        inter_state.interfase1=inter1;
        inter_state.interfase2=inter2;
        inter_state.interfase3=inter3;
        inter_state.interfase4=inter4;
    }

    void MainWindow::write_report()
    {
        ui->plainTextEdit->setPlainText("                                                                                       ОТЧЕТ\n");
        if (ui->listWidget->currentRow() ==0)
        {
            MainWindow::write_top_report_1();
            MainWindow::table_generation_1();
            ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() +
                                            "\n\nИспользуемые сокращения: \nТК - тип кодограммы;\nА - Азимут;\nД - Дальность\nТип ВО: " +
                                            "0 - Самолет\n              1 - Вертолет\n              2 - БПЛА\n              3 - Снаряд\n");
        }
        else if (ui->listWidget->currentRow() == 1)
        {
            MainWindow::write_top_report_2();
            ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "\n3. Таблица кодограмм:\n");
            if (m_l.codogram_2.size() != 0)
            {
                MainWindow::table_generation_2();
            }
            if (m_l.codogram_3.size() != 0)
            {
                MainWindow::table_generation_3();
            }
            if (m_l.codogram_4.size() != 0)
            {
                MainWindow::table_generation_4();
            }
            ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "\n\nИспользуемые сокращения: \nТК - тип кодограммы\n\n");
        }
    }

    void MainWindow::write_top_report_1()
    {
        ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "\n" +
           "                                                                                 Рабочее поле\n" + "\n\n");
        ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "1. Время создания отчета: " +
                                        QDateTime::currentDateTime().toString() + "\n\n2. Условия выбора данных для отчета:\n");
        if (ui->checkBox_20->checkState() != 0 or ui->checkBox_5->checkState() != 0 or
                ui->checkBox_21->checkState() != 0 or ui->checkBox_6->checkState() != 0 or
                ui->checkBox_22->checkState() != 0 or ui->checkBox_7->checkState() != 0)
        {
            ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() +
                          "                                                                    Отбор по области:\n");
            if (ui->checkBox_20->checkState() != 0 or ui->checkBox_5->checkState() != 0)
            {
                ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() +
                   "                                                                                                     " +
                    inter_state.interfase1.coordinate1 + " от " + QString::number(inter_state.interfase1.scope[0][0]) + " до " +
                        QString::number(inter_state.interfase1.scope[0][1]) + "\n");
            }
            if (ui->checkBox_21->checkState() != 0 or ui->checkBox_6->checkState() != 0)
            {
                ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() +
                    "                                                                                                     " +
                     inter_state.interfase1.coordinate2 + " от " + QString::number(inter_state.interfase1.scope[1][0]) + " до " +
                        QString::number(inter_state.interfase1.scope[1][1]) + "\n");
            }
            if (ui->checkBox_22->checkState() != 0 or ui->checkBox_7->checkState() != 0)
            {
                ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() +
                   "                                                                                                     Высота от " +
                    QString::number(inter_state.interfase1.scope[2][0]) + " до " +
                        QString::number(inter_state.interfase1.scope[2][1]) + "\n");
            }
        }
        if (ui->checkBox_3->checkState() != 0)
        {
            ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() +
                "                                                                     Отбор по скорости: от " +
                                            QString::number(inter_state.interfase1.pace[0]) + " до " +
                    QString::number(inter_state.interfase1.pace[1]) + "\n");
        }
        if (ui->checkBox->checkState() != 0)
        {
            ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() +
                  "                                                                     Отбор по времени: от " +
                                            inter_state.interfase1.time_gen_Min.toString() + " до " +
                    inter_state.interfase1.time_gen_Max.toString() + "\n");
        }
        if (ui->checkBox_4->checkState() != 0)
        {
            ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() +
                  "                                                                     Отбор по параметрам цели: "+
                    QString::number(inter_state.interfase1.object) + "\n");
        }
    }

    void MainWindow::write_top_report_2()
    {
        ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "\n" +
           "                                                                                 Действия оператора\n" + "\n\n");
        ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() +
                                        "1. Время создания отчета: " + QDateTime::currentDateTime().toString() + "\n");
        ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "\n2. Условия выбора данных для отчета:\n");
        if (ui->checkBox_2->checkState() != 0 or ui->checkBox_8->checkState() != 0 or ui->checkBox_12->checkState() != 0)
        {
            ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() +
                          "                                                                    Отбор по углу поворота антенны:\n");
            if (ui->checkBox_2->checkState() != 0)
            {
                ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() +
                          "                                                                                Отбор по времени от " +
                    inter_state.interfase2.time_gen_Min.toString() + " до " + inter_state.interfase2.time_gen_Max.toString() + "\n");
            }
            if (ui->checkBox_8->checkState() != 0)
            {
                ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() +
                          "                                                                                Угол в плоскости Z-X от " +
                    QString::number(inter_state.interfase2.angleZX[0]) + " до " + QString::number(inter_state.interfase2.angleZX[1]) + "\n");
            }
            if (ui->checkBox_12->checkState() != 0)
            {
                ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() +
                          "                                                                                Угол в плоскости Z-Y от " +
                    QString::number(inter_state.interfase2.angleZY[0]) + " до " + QString::number(inter_state.interfase2.angleZY[1]) + "\n");
            }
        }
        if (ui->checkBox_15->checkState() != 0 or ui->checkBox_13->checkState() != 0)
        {
            ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() +
                          "                                                                    Отбор по мощности излучения:\n");
            if (ui->checkBox_15->checkState() != 0)
            {
                ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() +
                          "                                                                                Отбор по времени от " +
                    inter_state.interfase3.time_gen_Min.toString() + " до " + inter_state.interfase3.time_gen_Max.toString() + "\n");
            }
            if (ui->checkBox_13->checkState() != 0)
            {
                ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() +
                          "                                                                                Мощность излучения от " +
                    QString::number(inter_state.interfase3.energy[0]) + " до " + QString::number(inter_state.interfase3.energy[1]) + "\n");
            }
        }
        if (ui->checkBox_16->checkState() != 0 or ui->checkBox_14->checkState() != 0)
        {
            ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() +
                          "                                                                    Отбор по режиму:\n");
            if (ui->checkBox_16->checkState() != 0)
            {
                ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() +
                          "                                                                                Отбор по времени от " +
                    inter_state.interfase4.time_gen_Min.toString() + " до " + inter_state.interfase4.time_gen_Max.toString() + "\n");
            }
            if (ui->checkBox_14->checkState() != 0)
            {
                ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() +
                          "                                                                                Режим " +
                    QString::number(inter_state.interfase4.mode) + "\n");
            }
        }
    }

    void MainWindow::table_generation_1()
    {
        ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "\n3. Таблица кодограмм:\n");
        ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "  ТК    Ввремя генерации кодограммы                 "
                                        + inter_state.interfase1.coordinate1);
        if(inter_state.workField == 1)
        {
            ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + ui->label_35->text().right(4));
        }
        else
        {
            ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "[град]");
        }
        ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "                  " + inter_state.interfase1.coordinate2 +
                                        ui->label_35->text().right(4) + "              " + ui->label_3->text() +
                                        "    Скорость [" + ui->comboBox_4->currentText() + "]   Тип ВО\n");
        ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() +
                                        "_____________________________________________________________________________________________________\n");

        QDateTime dt_max = ui->dateTimeEdit->minimumDateTime();//------------------------------------------------{
        QDateTime dt_min = ui->dateTimeEdit->maximumDateTime();
        int coord_max[3] = {0,0,0};//[X,Y,Z]
        int coord_min[3] = {9999,9999,9999};//[X,Y,Z]
        uint speed_max = 1;  //                                      переменные для поиска min и max значений полей
        uint speed_min = 1000;
        uint number_c = 0;
        for (Target & c: m_l.codogram_1)//------------------------------------------------------------------------}
        {
            //------------------------------      отбор кодограмм{       -------------------------------------------------------------------------
            if ((c.coordinate[0] >= inter_state.interfase1.scope[0][0] and c.coordinate[0] <= inter_state.interfase1.scope[0][1])
                    or ui->checkBox_20->checkState() == 0)//X
            {
                if ((c.coordinate[1] >= inter_state.interfase1.scope[1][0] and c.coordinate[1] <= inter_state.interfase1.scope[1][1])
                        or ui->checkBox_21->checkState() == 0)//Y
                {
                    if ((c.coordinate[2] >= inter_state.interfase1.scope[2][0] and c.coordinate[2] <= inter_state.interfase1.scope[2][1])
                            or ui->checkBox_22->checkState() == 0 or ui->checkBox_7->checkState() == 0)//Высота
                    {
                        if ((atan(c.coordinate[1]/c.coordinate[0]) >= inter_state.interfase1.scope[1][0]
                             and atan(c.coordinate[1]/c.coordinate[0]) <= inter_state.interfase1.scope[1][1])
                                or ui->checkBox_5->checkState() == 0)//Азимут
                        {
                            if((sqrt(pow(c.coordinate[0], 2) + pow(c.coordinate[1], 2)) >= inter_state.interfase1.scope[0][0]
                                and sqrt(pow(c.coordinate[0], 2) + pow(c.coordinate[1], 2)) <= inter_state.interfase1.scope[0][1])
                                or ui->checkBox_6->checkState() == 0)//Дальность
                            {
                                if ((c.speed >= inter_state.interfase1.pace[0] and c.speed <= inter_state.interfase1.pace[1])
                                        or ui->checkBox_3->checkState() == 0)//Скорость
                                {
                                    if ((c.creationTime <= inter_state.interfase1.time_gen_Max and c.creationTime >= inter_state.interfase1.time_gen_Min)
                                            or ui->checkBox->checkState() == 0)//Время
                                    {
                                        if (c.object_type == inter_state.interfase1.object or ui->checkBox_4->checkState() == 0)//Цель
                                        {
                                            ++number_c;
                                            ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "   1          " + c.creationTime.toString() +
                                                                            "                       ");
                                            if (inter_state.workField == 1)
                                            {
                                                ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() +
                                                        QString::number(round(c.coordinate[0] / pow(1000, inter_state.posButton_index) * 100) / 100) + "                    " +
                                                        QString::number(round(c.coordinate[1] / pow(1000, inter_state.posButton_index) * 100) / 100) + "                   " +
                                                        QString::number(round(c.coordinate[2] / pow(1000, inter_state.posButton_index) * 100) / 100));
                                            }
                                            else if (inter_state.workField == 0)
                                            {
                                                ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() +
                                                        QString::number(round(atan(c.coordinate[1]/c.coordinate[0]) * 100) / 100) + "                    " +
                                                        QString::number(round(sqrt(pow(c.coordinate[0], 2) + pow(c.coordinate[1], 2)) / pow(1000, inter_state.posButton_index) * 100) / 100)
                                                         + "                  " + QString::number(round(c.coordinate[2] / pow(1000, inter_state.posButton_index) * 100) / 100));
                                            }
                                            ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "                    " +
                                                 QString::number(round(c.speed * pow(3.6, inter_state.speedButton_index) * 100) / 100) + "                      "
                                                                            + QString::number(c.object_type) + "\n");
                                            //                                                         //------------------------------      }отбор кодограмм       -----------------------------------------------------------------

                                            // =============================================   поиск min max значений полей      ================================

                                            dt_max = qMax(dt_max, c.creationTime);
                                            dt_min = qMin(dt_min, c.creationTime);
                                            coord_max[0] = qMax(coord_max[0], c.coordinate[0]);
                                            coord_min[0] = qMin(coord_min[0], c.coordinate[0]);
                                            coord_max[1] = qMax(coord_max[1], c.coordinate[0]);
                                            coord_min[1] = qMin(coord_min[1], c.coordinate[0]);
                                            coord_max[2] = qMax(coord_max[2], c.coordinate[0]);
                                            coord_min[2] = qMin(coord_min[2], c.coordinate[0]);
                                            speed_max = qMax(speed_max, c.speed);
                                            speed_min = qMin(speed_min, c.speed);

                                            // =============================================   поиск min и max значений полей      ================================
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "\nКолличество кодограмм в логе: " +
            QString::number(m_l.codogram_1.size() + m_l.codogram_2.size() + m_l.codogram_3.size() + m_l.codogram_4.size()) + "\n");
        ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "\nКолличество кодограмм прошедших выборку: " + QString::number(number_c) + "\n");
        if (number_c != 0)
        {
            ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "\nМаксимальные значения полей: \n");
            ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "    Время герерации кодограммы: " + dt_max.toString() + "\n");
            ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "    " + inter_state.interfase1.coordinate1
                                            + ": " + QString::number(coord_max[0]) + "\n");
            ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "    " + inter_state.interfase1.coordinate2
                                            + ": " + QString::number(coord_max[1]) + "\n");
            ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "    Высота: " + QString::number(coord_max[2]) + "\n");
            ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "    Скорость: " + QString::number(speed_max) + "\n");

            ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "\nМинимальные значения полей: \n");
            ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "    Время герерации кодограммы: " + dt_min.toString() + "\n");
            ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "    " + inter_state.interfase1.coordinate1
                                            + ": " + QString::number(coord_min[0]) + "\n");
            ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "    " + inter_state.interfase1.coordinate2
                                            + ": " + QString::number(coord_min[1]) + "\n");
            ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "    Высота: " + QString::number(coord_min[2]) + "\n");
            ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "    Скорость: " + QString::number(speed_min) + "\n");
            //====================================================================================================================================     }вывод min и max значений полей
        }
    }

    void MainWindow::table_generation_2()
    {
        ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "  ТК    Время генерации кодограммы    Угол Z-X     Угол Z-Y\n");
        ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() +
                                        "_____________________________________________________________________________________________________\n");
        QDateTime dt_max = ui->dateTimeEdit_3->minimumDateTime();
        QDateTime dt_min = ui->dateTimeEdit_3->maximumDateTime();
        int angleZX_max = 0, angleZX_min = 360;
        int angleZY_max = 0, angleZY_min = 90;
        uint number_c = 0;
        for (Antenna_Angle & c: m_l.codogram_2)
        {
            //------------------------------      отбор кодограмм{       --------------------------------------------------------------------------------
            if ((c.creationTime <= inter_state.interfase2.time_gen_Max and c.creationTime >= inter_state.interfase2.time_gen_Min)
                    or ui->checkBox_2->checkState() == 0)
            {
                if ((c.angle_ZX >= inter_state.interfase2.angleZX[0] and c.angle_ZX <= inter_state.interfase2.angleZX[1])
                        or ui->checkBox_8->checkState() == 0)
                {
                    if ((c.angle_ZY >= inter_state.interfase2.angleZY[0] and c.angle_ZY <= inter_state.interfase2.angleZY[1])
                            or ui->checkBox_12->checkState() == 0)
                    {
                        ++number_c;
                        ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "   2          " + c.creationTime.toString() +
                           "              " + QString::number(c.angle_ZX) + "                " + QString::number(c.angle_ZY) + "\n");
                        //------------------------------      }отбор кодограмм       -----------------------------------------------------------------

                        // =============================================   поиск min max значений полей      ================================

                        dt_max = qMax(dt_max, c.creationTime);
                        dt_min = qMin(dt_min, c.creationTime);
                        angleZX_max = qMax(angleZX_max, c.angle_ZX);
                        angleZX_min = qMin(angleZX_min, c.angle_ZX);
                        angleZY_max = qMax(angleZY_max, c.angle_ZY);
                        angleZY_min = qMin(angleZY_min, c.angle_ZY);

                        // =============================================   поиск min и max значений полей      ================================
                    }
                }
            }
        }
        ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "\nКолличество кодограмм в логе: " +
            QString::number(m_l.codogram_1.size() + m_l.codogram_2.size() + m_l.codogram_3.size() + m_l.codogram_4.size()) + "\n");
        ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "\nКолличество кодограмм прошедших выборку: " + QString::number(number_c) + "\n");
        if (number_c != 0)
        {
            ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "\nМаксимальные значения полей: \n");
            ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "    Время герерации кодограммы: " + dt_max.toString() + "\n");
            ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "    Угол в плоскости Z-X: " + QString::number(angleZX_max) + "\n");
            ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "    Угол в плоскости Z-Y: " + QString::number(angleZY_max) + "\n");

            ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "\nМинимальные значения полей: \n");
            ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "    Время герерации кодограммы: " + dt_min.toString() + "\n");
            ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "    Угол в плоскости Z-X: " + QString::number(angleZX_min) + "\n");
            ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "    Угол в плоскости Z-Y: " + QString::number(angleZY_min) + "\n");
            //====================================================================================================================================     }вывод min и max значений полей
        }
    }

    void MainWindow::table_generation_3()
    {
        ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "  ТК    Ввремя генерации кодограммы    Мощность\n");
        ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() +
                                        "_____________________________________________________________________________________________________\n");
        QDateTime dt_max = ui->dateTimeEdit_3->minimumDateTime();
        QDateTime dt_min = ui->dateTimeEdit_3->maximumDateTime();
        uint power_max = 1, power_min = 999;
        uint number_c = 0;
        for (Power_Coodogram & c: m_l.codogram_3)
        {
            //------------------------------      отбор кодограмм{       --------------------------------------------------------------------------------
            if ((c.creationTime <= inter_state.interfase3.time_gen_Max and c.creationTime >= inter_state.interfase3.time_gen_Min)
                    or ui->checkBox_15->checkState() == 0)
            {
                if ((c.powerValue >= inter_state.interfase3.energy[0] and c.powerValue <= inter_state.interfase3.energy[1])
                        or ui->checkBox_13->checkState() == 0)
                {
                    ++number_c;
                    ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "   3          " + c.creationTime.toString() +
                                                    "              " + QString::number(c.powerValue) + "\n");

                    dt_max = qMax(dt_max, c.creationTime);
                    dt_min = qMin(dt_min, c.creationTime);
                    power_max = qMax(power_max, c.powerValue);
                    power_min = qMin(power_min, c.powerValue);
                }
            }
        }
        ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "\nКолличество кодограмм в логе: " +
                                        QString::number(m_l.codogram_1.size() + m_l.codogram_2.size() + m_l.codogram_3.size() + m_l.codogram_4.size()) + "\n");
        ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "\nКолличество кодограмм прошедших выборку: " + QString::number(number_c) + "\n");
        if (number_c != 0)
        {
            ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "\nМаксимальные значения полей: \n");
            ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "    Время герерации кодограммы: " + dt_max.toString() + "\n");
            ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "    Мощность: " + QString::number(power_max) + "\n");

            ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "\nМинимальные значения полей: \n");
            ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "    Время герерации кодограммы: " + dt_min.toString() + "\n");
            ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "    Мощность: " + QString::number(power_min) + "\n");
            //====================================================================================================================================     }вывод min и max значений полей
        }
    }

    void MainWindow::table_generation_4()
    {
        ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "  ТК    Ввремя генерации кодограммы    Режим\n");
        ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() +
                                        "_____________________________________________________________________________________________________\n");
        QDateTime dt_max = ui->dateTimeEdit_3->minimumDateTime();
        QDateTime dt_min = ui->dateTimeEdit_3->maximumDateTime();
        uint number_c = 0, mode_0 = 0, mode_1 = 0;
        for (Mode & c: m_l.codogram_4)
        {
            //------------------------------      отбор кодограмм{       --------------------------------------------------------------------------------
            if ((c.creationTime <= inter_state.interfase4.time_gen_Max and c.creationTime >= inter_state.interfase4.time_gen_Min)
                    or ui->checkBox_16->checkState() == 0)
            {
                if (c.modeValue == inter_state.interfase4.mode or ui->checkBox_14->checkState() == 0)
                {
                    ++number_c;
                    ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "   4          " + c.creationTime.toString() +
                                                    "              " + QString::number(c.modeValue) + "\n");
                    dt_max = qMax(dt_max, c.creationTime);
                    dt_min = qMin(dt_min, c.creationTime);
                    if (c.modeValue == 0)
                    {
                        ++mode_0;
                    }
                    if (c.modeValue == 1)
                    {
                        ++mode_1;
                    }
                }
            }
        }
        ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "\nКолличество кодограмм в логе: " +
                                        QString::number(m_l.codogram_1.size() + m_l.codogram_2.size() + m_l.codogram_3.size() + m_l.codogram_4.size()) + "\n");
        ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "\nКолличество кодограмм прошедших выборку: " + QString::number(number_c) + "\n");
        if (number_c != 0)
        {
            ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "\nМаксимальные значения полей: \n");
            ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "    Время герерации кодограммы: " + dt_max.toString() + "\n");
            ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "\nМинимальные значения полей: \n");
            ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "    Время герерации кодограммы: " + dt_min.toString() + "\n\n");
            ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "Дежурный режим включен " + QString::number(mode_0) +
                                            " раз.\n Боевой режим включен " + QString::number(mode_1) + " раз.\n");
        }
    }

    void Log::Read_codogram(QString codogram)
    {
        QStringList codogram_list = codogram.split(",");
        switch (codogram_list.at(0).toInt()) //определение типа кодограммы
        {
        case 1://Target
        {
            Target c;
            c.creationTime = Log::string_to_DataTime(codogram_list.at(1));
            c.coordinate[0] = (codogram_list.at(2)).toInt();
            c.coordinate[1] = (codogram_list.at(3)).toInt();
            c.coordinate[2] = (codogram_list.at(4)).toInt();
            c.speed = (codogram_list.at(5)).toInt();
            c.object_type = (codogram_list.at(6)).toInt();
            codogram_1.append(c);
            break;
        }
        case 2://Antenna_Angle
        {
            Antenna_Angle c;
            c.creationTime = Log::string_to_DataTime(codogram_list.at(1));
            c.angle_ZX = (codogram_list.at(2)).toInt();
            c.angle_ZY = (codogram_list.at(3)).toInt();
            codogram_2.append(c);
            break;
        }
        case 3://Power_Codogram
        {
            Power_Coodogram c;
            c.creationTime = Log::string_to_DataTime(codogram_list.at(1));
            c.powerValue = codogram_list.at(2).toInt();
            codogram_3.append(c);
            break;
        }
        case 4://Mode
        {
            Mode c;
            c.creationTime = Log::string_to_DataTime(codogram_list.at(1));
            c.modeValue = codogram_list.at(2).toInt();
            codogram_4.append(c);
            break;
        }
        default:
        {
            qWarning() << "Не известная кодограмма";
            break;
        }
        }
    }
