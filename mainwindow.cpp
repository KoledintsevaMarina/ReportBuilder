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

    connect(ui->workField_xyButton, &QPushButton::toggled, this, [=](bool) {
        ui->workField_stackedWidget->setCurrentIndex(1);
        inter_state.workField = 1;
    });

    connect(ui->workField_daButton, &QPushButton::toggled, this, [=](bool) {
        ui->workField_stackedWidget->setCurrentIndex(0);
        inter_state.workField = 0;
    });

    QList<QSpinBox *> listOfSpinBoxes;
    listOfSpinBoxes.append(ui->spinBox_Xmin);
    listOfSpinBoxes.append(ui->spinBox_Xmax);
    listOfSpinBoxes.append(ui->spinBox_Ymin);
    listOfSpinBoxes.append(ui->spinBox_Ymax);
    listOfSpinBoxes.append(ui->spinBox_Hmin);
    listOfSpinBoxes.append(ui->spinBox_Hmax);

    QList<QDoubleSpinBox *> listOfDoubleSpinBoxesForPace;
    listOfDoubleSpinBoxesForPace.append(ui->doubleSpinBox_azimut_min);
    listOfDoubleSpinBoxesForPace.append(ui->doubleSpinBox_azimut_max);
    listOfDoubleSpinBoxesForPace.append(ui->doubleSpinBox_range_max);
    listOfDoubleSpinBoxesForPace.append(ui->doubleSpinBox_range_max);
    listOfDoubleSpinBoxesForPace.append(ui->doubleSpinBox_H_min);
    listOfDoubleSpinBoxesForPace.append(ui->doubleSpinBox_H_max);

    QList<QPushButton*> listOfPushButton;
    listOfPushButton.append(ui->workField_daButton);
    listOfPushButton.append(ui->workField_xyButton);
    listOfPushButton.append(ui->pushButton_meters);
    listOfPushButton.append(ui->pushButton_kilometers);
    listOfPushButton.append(ui->pushButton_meter_per_second);
    listOfPushButton.append(ui->pushButton_kilometer_per_hour);

    QList<QCheckBox*> listOfCheckBox;
    listOfCheckBox.append(ui->checkBox_select_X);
    listOfCheckBox.append(ui->checkBox_select_Y);
    listOfCheckBox.append(ui->checkBox_select_Height);
    listOfCheckBox.append(ui->checkBox_select_Azimut);
    listOfCheckBox.append(ui->checkBox_select_Range);
    listOfCheckBox.append(ui->checkBox_select_Height_2);
    listOfCheckBox.append(ui->checkBox_select_Time_work_field);
    listOfCheckBox.append(ui->checkBox_select_Type);
    listOfCheckBox.append(ui->checkBox_select_Time_angle);
    listOfCheckBox.append(ui->checkBox_select_AngleZX);
    listOfCheckBox.append(ui->checkBox_select_AngleZY);
    listOfCheckBox.append(ui->checkBox_select_Time_power);
    listOfCheckBox.append(ui->checkBox_select_Power);
    listOfCheckBox.append(ui->checkBox_select_Time_mode);
    listOfCheckBox.append(ui->checkBox_select_Mode);

    QList <QComboBox*> listOfComboBox;
    listOfComboBox.append(ui->comboBox_speed);
    listOfComboBox.append(ui->comboBox_object);
    listOfComboBox.append(ui->comboBox_mode);

    QList<QDoubleSpinBox *> listOfDoubleSpinBox;
    listOfDoubleSpinBox.append(ui->doubleSpinBox_azimut_min);
    listOfDoubleSpinBox.append(ui->doubleSpinBox_azimut_max);
    listOfDoubleSpinBox.append(ui->doubleSpinBox_range_max);
    listOfDoubleSpinBox.append(ui->doubleSpinBox_range_max);
    listOfDoubleSpinBox.append(ui->doubleSpinBox_H_min);
    listOfDoubleSpinBox.append(ui->doubleSpinBox_speed_min);
    listOfDoubleSpinBox.append(ui->doubleSpinBox_speed_max);
    listOfDoubleSpinBox.append(ui->doubleSpinBox_ZX_max);
    listOfDoubleSpinBox.append(ui->doubleSpinBox_ZX_min);
    listOfDoubleSpinBox.append(ui->doubleSpinBox_ZY_max);
    listOfDoubleSpinBox.append(ui->doubleSpinBox_ZY_min);
    listOfDoubleSpinBox.append(ui->doubleSpinBox_power_max);
    listOfDoubleSpinBox.append(ui->doubleSpinBox_power_min);

    QList<QDateTimeEdit *> listOfDateTimeEdit;
    listOfDateTimeEdit.append(ui->dateTimeEdit_work_field_min);
    listOfDateTimeEdit.append(ui->dateTimeEdit_work_field_max);
    listOfDateTimeEdit.append(ui->dateTimeEdit_angle_min);
    listOfDateTimeEdit.append(ui->dateTimeEdit_angle_max);
    listOfDateTimeEdit.append(ui->dateTimeEdit_power_min);
    listOfDateTimeEdit.append(ui->dateTimeEdit_power_max);
    listOfDateTimeEdit.append(ui->dateTimeEdit_mode_min);
    listOfDateTimeEdit.append(ui->dateTimeEdit_mode_max);

    connect (ui->pushButton_meters, &QPushButton::toggled, this, [=] (bool){
        if (inter_state.posButton_index == 1)
        {
            ui->label_32->setText("Х [м]"); //
            ui->label_35->setText("Y [м]");
            ui->label_38->setText("Высота [м]");
            ui->label_3->setText("Высота [м]");
            ui->label_2->setText("Дальность [м]");
            foreach (QSpinBox * spinBox, listOfSpinBoxes) {
                spinBox->setValue(spinBox->value() * 1000);
            }
            foreach (QDoubleSpinBox * spinBox, listOfDoubleSpinBoxesForPace) {
                spinBox->setValue(spinBox->value() * 1000);
            }
            inter_state.posButton_index = 0;
        }
    });

    connect (ui->pushButton_kilometers, &QPushButton::toggled, this, [=] (bool){
        if (inter_state.posButton_index == 0)
        {
            ui->label_32->setText("Х [км]");
            ui->label_35->setText("Y [км]");
            ui->label_38->setText("Высота [км]");
            ui->label_3->setText("Высота [км]");
            ui->label_2->setText("Дальность [км]");
            foreach (QSpinBox * spinBox, listOfSpinBoxes) {
                spinBox->setValue(spinBox->value()/1000);
            }
            foreach (QDoubleSpinBox * spinBox, listOfDoubleSpinBoxesForPace) {
                spinBox->setValue(spinBox->value()/1000);
            }
            inter_state.posButton_index = 1;
        }
    });

    connect (ui->pushButton_meter_per_second, &QPushButton::toggled, this, [=] (bool){
        if (inter_state.speedButton_index == 1)
        {
            ui->comboBox_speed->setCurrentIndex(0);
            ui->doubleSpinBox_speed_min->setValue(ui->doubleSpinBox_speed_min->value() * 0.278);
            ui->doubleSpinBox_speed_max->setValue(ui->doubleSpinBox_speed_max->value() * 0.278);
            inter_state.speedButton_index = 0;
        }
    });

    connect (ui->pushButton_kilometer_per_hour, &QPushButton::toggled, this, [=] (bool){
        if (inter_state.speedButton_index == 0)
        {
            ui->comboBox_speed->setCurrentIndex(1);
            ui->doubleSpinBox_speed_min->setValue(ui->doubleSpinBox_speed_min->value() * 3.6);
            ui->doubleSpinBox_speed_max->setValue(ui->doubleSpinBox_speed_max->value() * 3.6);
            inter_state.speedButton_index = 1;
        }
        ui->spinBox_Xmin->setValue(ui->doubleSpinBox_speed_min->value() / 1000);
    });

    for (int i = 0 ; i < listOfPushButton.size(); i++){
        connect(listOfPushButton.at(i), &QPushButton::toggled, this, [=] (bool){
            read_interface();
            write_report();
        });
    }

    for(int i = 0; i < listOfCheckBox.size(); i++){
        connect(listOfCheckBox.at(i), &QCheckBox::clicked, this, [=] (bool){
            read_interface();
            write_report();
        });
    }

    for(int i = 0; i < listOfComboBox.size(); i++){
        connect(listOfComboBox.at(i), static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, [=] (bool){
            read_interface();
            write_report();
        });
    }

    for(int i = 0; i < listOfSpinBoxes.size(); i++){
        connect(listOfSpinBoxes.at(i), static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, [=] (bool){
            read_interface();
            write_report();
        });
    }

    for(int i = 0; i < listOfDoubleSpinBox.size(); i++){
        connect(listOfDoubleSpinBox.at(i), static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, [=] (bool){
            read_interface();
            write_report();
        });
    }

    for(int i = 0; i < listOfDateTimeEdit.size(); i++){
        connect(listOfDateTimeEdit.at(i), &QDateTimeEdit::dateTimeChanged, this, [=] (){
            read_interface();
            write_report();
        });
    }

    connect (ui->listWidget, &QListWidget::itemClicked, this, [=] (QListWidgetItem *){
        read_interface();
        write_report();
    });

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
                m_l.read_codogram(codogram);
            }
            file.close();
            MainWindow::read_interface();
            MainWindow::write_report();
        }
    });

    connect (ui->action_Close_log, &QAction::triggered, this, [=] () {
        ui->workField_xyButton->setChecked(1);
        ui->workField_daButton->setChecked(0);
        ui->pushButton_meter_per_second->setChecked(1);
        ui->pushButton_kilometer_per_hour->setChecked(0);
        ui->pushButton_meters->setChecked(1);
        ui->pushButton_kilometers->setChecked(0);
        ui->doubleSpinBox_azimut_min->setValue(0);
        ui->doubleSpinBox_azimut_max->setValue(360);
        ui->doubleSpinBox_range_min->setValue(0);
        ui->doubleSpinBox_range_max->setValue(9999);
        ui->doubleSpinBox_H_min->setValue(0);
        ui->doubleSpinBox_H_max->setValue(9999);
        ui->doubleSpinBox_speed_min->setValue(0);
        ui->doubleSpinBox_speed_max->setValue(0);
        ui->doubleSpinBox_ZX_min->setValue(0);
        ui->doubleSpinBox_ZX_max->setValue(360);
        ui->doubleSpinBox_ZY_min->setValue(0);
        ui->doubleSpinBox_ZY_max->setValue(90);
        ui->doubleSpinBox_power_min->setValue(0);
        ui->doubleSpinBox_power_max->setValue(999);
        ui->spinBox_Xmin->setValue(0);
        ui->spinBox_Xmax->setValue(9999);
        ui->spinBox_Ymin->setValue(0);
        ui->spinBox_Ymax->setValue(9999);
        ui->spinBox_Hmin->setValue(0);
        ui->spinBox_Hmax->setValue(9999);

        foreach (QCheckBox * checkBox, listOfCheckBox) {
            checkBox->setChecked(0);
        }
        foreach (QComboBox * comboBox, listOfComboBox) {
            comboBox->setCurrentIndex(0);
        }
        foreach (QDateTimeEdit * dateTimeEdit, listOfDateTimeEdit) {
            dateTimeEdit->setDateTime(QDateTime::currentDateTime());
        }
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
    inter1.time_gen_Min = ui->dateTimeEdit_work_field_min->dateTime();
    inter1.time_gen_Max = ui->dateTimeEdit_work_field_max->dateTime();
    if (inter_state.workField == 1)
    {
        inter1.scope[0][0] = ui->spinBox_Xmin->value();
        inter1.scope[0][1] = ui->spinBox_Xmax->value();
        inter1.scope[1][0] = ui->spinBox_Ymin->value();
        inter1.scope[1][1] = ui->spinBox_Ymax->value();
        inter1.scope[2][0] = ui->spinBox_Hmin->value();
        inter1.scope[2][1] = ui->spinBox_Hmax->value();
        inter1.coordinate1 = "X";
        inter1.coordinate2 = "Y ";
    }
    else if (inter_state.workField ==0)
    {
        inter1.scope[0][0] = ui->doubleSpinBox_azimut_min->value();
        inter1.scope[0][1] = ui->doubleSpinBox_azimut_max->value();
        inter1.scope[1][0] = ui->doubleSpinBox_range_min->value();
        inter1.scope[1][1] = ui->doubleSpinBox_range_max->value();
        inter1.scope[2][0] = ui->doubleSpinBox_H_min->value();
        inter1.scope[2][1] = ui->doubleSpinBox_H_max->value();
        inter1.coordinate1 = "А";
        inter1.coordinate2 = "Д";
    }
    inter1.pace[0] = ui->doubleSpinBox_speed_min->value();
    inter1.pace[1] = ui->doubleSpinBox_speed_max->value();
    inter1.object = ui->comboBox_object->currentIndex();

    Interface_2 inter2;
    inter2.time_gen_Min = ui->dateTimeEdit_angle_min->dateTime();
    inter2.time_gen_Max = ui->dateTimeEdit_angle_max->dateTime();
    inter2.angleZX[0] = ui->doubleSpinBox_ZX_min->value();
    inter2.angleZX[1] = ui->doubleSpinBox_ZX_max->value();
    inter2.angleZY[0] = ui->doubleSpinBox_ZY_min->value();
    inter2.angleZY[1] = ui->doubleSpinBox_ZY_max->value();

    Interface_3 inter3;
    inter3.time_gen_Min = ui->dateTimeEdit_power_min->dateTime();
    inter3.time_gen_Max = ui->dateTimeEdit_power_max->dateTime();
    inter3.energy[0] = ui->doubleSpinBox_power_min->value();
    inter3.energy[1] = ui->doubleSpinBox_power_max->value();

    Interface_4 inter4;
    inter4.time_gen_Min = ui->dateTimeEdit_mode_min->dateTime();
    inter4.time_gen_Max = ui->dateTimeEdit_mode_max->dateTime();
    inter4.mode = ui->comboBox_mode->currentIndex();
    inter_state.interfase1=inter1;
    inter_state.interfase2=inter2;
    inter_state.interfase3=inter3;
    inter_state.interfase4=inter4;
}

void MainWindow::appendLineToReport(QString text)
{
    ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + text);
}

void MainWindow::write_report()
{

    ui->plainTextEdit->setPlainText("                                                                                     ОТЧЕТ\n\n");
    if (ui->listWidget->currentRow() == 0)
    {
        write_top_report_1();
        write_top_table1();
        table_generation_1();
        appendLineToReport("\nИспользуемые сокращения: \nТК - тип кодограммы;\nА - Азимут;\nД - Дальность\nТип ВО: ");
        appendLineToReport("0 - Самолет\n              1 - Вертолет\n              2 - БПЛА\n              3 - Снаряд\n");
    }
    else if (ui->listWidget->currentRow() == 1)
    {
        write_top_report_2();
        appendLineToReport("3. Таблица кодограмм:\n");
        if (m_l.codogram_2.size() != 0)
        {
            table_generation_2();
        }
        if (m_l.codogram_3.size() != 0)
        {
            table_generation_3();
        }
        if (m_l.codogram_4.size() != 0)
        {
            table_generation_4();
        }
        appendLineToReport("\nИспользуемые сокращения: \nТК - тип кодограммы\n\n");
    }
}

void MainWindow::write_top_report_1()
{
    appendLineToReport("                                                                               Рабочее поле\n\n\n");
    appendLineToReport(" Время создания отчета: " + QDateTime::currentDateTime().toString()
                   + "\n\n2. Условия выбора данных для отчета:\n");
    if (ui->checkBox_select_X->checkState() != 0 or ui->checkBox_select_Azimut->checkState() != 0 or
            ui->checkBox_select_Y->checkState() != 0 or ui->checkBox_select_Range->checkState() != 0 or
            ui->checkBox_select_Height->checkState() != 0 or ui->checkBox_select_Height_2->checkState() != 0)
    {
        appendLineToReport("Отбор по области:\n");
        if (ui->checkBox_select_X->checkState() != 0 or ui->checkBox_select_Azimut->checkState() != 0)
        {
            appendLineToReport("                 " + inter_state.interfase1.coordinate1 + " от " +
                           QString::number(inter_state.interfase1.scope[0][0]) + " до " +
                    QString::number(inter_state.interfase1.scope[0][1]) + "\n");
        }
        if (ui->checkBox_select_Y->checkState() != 0 or ui->checkBox_select_Range->checkState() != 0)
        {
            appendLineToReport("                   " + inter_state.interfase1.coordinate2 + " от " +
                           QString::number(inter_state.interfase1.scope[1][0]) + " до " +
                    QString::number(inter_state.interfase1.scope[1][1]) + "\n");
        }
        if (ui->checkBox_select_Height->checkState() != 0 or ui->checkBox_select_Height_2->checkState() != 0)
        {
            appendLineToReport("                   Высота от " + QString::number(inter_state.interfase1.scope[2][0]) + " до "
                    + QString::number(inter_state.interfase1.scope[2][1]) + "\n");
        }
    }
    if (ui->checkBox_select_Speed->checkState() != 0)
    {
        appendLineToReport("  Отбор по скорости: от " + QString::number(inter_state.interfase1.pace[0]) + " до "
                + QString::number(inter_state.interfase1.pace[1]) + "\n");
    }
    if (ui->checkBox_select_Time_work_field->checkState() != 0)
    {
        appendLineToReport("  Отбор по времени: от " + inter_state.interfase1.time_gen_Min.toString() + " до "
                       + inter_state.interfase1.time_gen_Max.toString() + "\n");
    }
    if (ui->checkBox_select_Type->checkState() != 0)
    {
        appendLineToReport("  Отбор по параметрам цели: " + QString::number(inter_state.interfase1.object) + "\n");
    }
}

void MainWindow::write_top_report_2()
{
    appendLineToReport("\n                                                                                 Действия оператора\n\n\n");
    appendLineToReport("1. Время создания отчета: " + QDateTime::currentDateTime().toString() + "\n");
    appendLineToReport("\n2. Условия выбора данных для отчета:\n");
    if (ui->checkBox_select_Time_angle->checkState() != 0 or ui->checkBox_select_AngleZX->checkState() != 0
            or ui->checkBox_select_AngleZY->checkState() != 0)
    {
        appendLineToReport("  Отбор по углу поворота антенны:\n");
        if (ui->checkBox_select_Time_angle->checkState() != 0)
        {
            appendLineToReport("            Отбор по времени от " + inter_state.interfase2.time_gen_Min.toString() +
                           " до " + inter_state.interfase2.time_gen_Max.toString() + "\n");
        }
        if (ui->checkBox_select_AngleZX->checkState() != 0)
        {
            appendLineToReport("            Угол в плоскости Z-X от " + QString::number(inter_state.interfase2.angleZX[0]) +
                    " до " + QString::number(inter_state.interfase2.angleZX[1]) + "\n");
        }
        if (ui->checkBox_select_AngleZY->checkState() != 0)
        {
            appendLineToReport("            Угол в плоскости Z-Y от " + QString::number(inter_state.interfase2.angleZY[0]) +
                    " до " + QString::number(inter_state.interfase2.angleZY[1]) + "\n");
        }
    }
    if (ui->checkBox_select_Time_power->checkState() != 0 or ui->checkBox_select_Power->checkState() != 0)
    {
        appendLineToReport("  Отбор по мощности излучения:\n");
        if (ui->checkBox_select_Time_power->checkState() != 0)
        {
            appendLineToReport("            Отбор по времени от " + inter_state.interfase3.time_gen_Min.toString() + " до "
                           + inter_state.interfase3.time_gen_Max.toString() + "\n");
        }
        if (ui->checkBox_select_Power->checkState() != 0)
        {
            appendLineToReport("            Мощность излучения от " + QString::number(inter_state.interfase3.energy[0]) +
                    " до " + QString::number(inter_state.interfase3.energy[1]) + "\n");
        }
    }
    if (ui->checkBox_select_Time_mode->checkState() != 0 or ui->checkBox_select_Mode->checkState() != 0)
    {
        appendLineToReport("  Отбор по режиму:\n");
        if (ui->checkBox_select_Time_mode->checkState() != 0)
        {
            appendLineToReport("            Отбор по времени от " + inter_state.interfase4.time_gen_Min.toString() +
                           " до " + inter_state.interfase4.time_gen_Max.toString() + "\n");
        }
        if (ui->checkBox_select_Mode->checkState() != 0)
        {
            appendLineToReport("            Режим " + QString::number(inter_state.interfase4.mode) + "\n");
        }
    }
}

void MainWindow::table_generation_1()
{
    QDateTime dt_max = ui->dateTimeEdit_work_field_min->minimumDateTime();
    QDateTime dt_min = ui->dateTimeEdit_work_field_min->maximumDateTime();
    int coord_max[3] = {0,0,0};//[X,Y,Z]
    int coord_min[3] = {9999,9999,9999};//[X,Y,Z]
    uint speed_max = 1;  //
    uint speed_min = 1000;
    uint number_c = 0;
    for (Target & cdgr_target: m_l.codogram_1)
    {
        if ((cdgr_target.coordinate[0] >= inter_state.interfase1.scope[0][0] and cdgr_target.coordinate[0] <= inter_state.interfase1.scope[0][1])
                or ui->checkBox_select_X->checkState() == 0)//X
        {
            if ((cdgr_target.coordinate[1] >= inter_state.interfase1.scope[1][0] and cdgr_target.coordinate[1] <= inter_state.interfase1.scope[1][1])
                    or ui->checkBox_select_Y->checkState() == 0)//Y
            {
                if ((cdgr_target.coordinate[2] >= inter_state.interfase1.scope[2][0] and cdgr_target.coordinate[2] <= inter_state.interfase1.scope[2][1])
                        or ui->checkBox_select_Height->checkState() == 0 or ui->checkBox_select_Height_2->checkState() == 0)//Высота
                {
                    if ((cdgr_target.creationTime <= inter_state.interfase1.time_gen_Max and cdgr_target.creationTime >= inter_state.interfase1.time_gen_Min)
                            or ui->checkBox_select_Time_work_field->checkState() == 0)//Время
                    {
                        if ((cdgr_target.speed >= inter_state.interfase1.pace[0] and cdgr_target.speed <= inter_state.interfase1.pace[1])
                                or ui->checkBox_select_Speed->checkState() == 0)//Скорость
                        {
                            if ((sqrt(pow(cdgr_target.coordinate[0], 2) + pow(cdgr_target.coordinate[1], 2)) >= inter_state.interfase1.scope[0][0]
                                 and sqrt(pow(cdgr_target.coordinate[0], 2) + pow(cdgr_target.coordinate[1], 2)) <= inter_state.interfase1.scope[0][1])
                                    or ui->checkBox_select_Range->checkState() == 0)//Дальность
                            {
                                if ((atan(cdgr_target.coordinate[1]/cdgr_target.coordinate[0]) >= inter_state.interfase1.scope[1][0]
                                     and atan(cdgr_target.coordinate[1]/cdgr_target.coordinate[0]) <= inter_state.interfase1.scope[1][1])
                                        or ui->checkBox_select_Azimut->checkState() == 0)//Азимут
                                {
                                    if (cdgr_target.object_type == inter_state.interfase1.object or ui->checkBox_select_Type->checkState() == 0)//Цель
                                    {
                                        ++number_c;
                                        entry_codogram_to_table1(cdgr_target);

                                        dt_max = qMax(dt_max, cdgr_target.creationTime);
                                        dt_min = qMin(dt_min, cdgr_target.creationTime);
                                        coord_max[0] = qMax(coord_max[0], cdgr_target.coordinate[0]);
                                        coord_min[0] = qMin(coord_min[0], cdgr_target.coordinate[0]);
                                        coord_max[1] = qMax(coord_max[1], cdgr_target.coordinate[0]);
                                        coord_min[1] = qMin(coord_min[1], cdgr_target.coordinate[0]);
                                        coord_max[2] = qMax(coord_max[2], cdgr_target.coordinate[0]);
                                        coord_min[2] = qMin(coord_min[2], cdgr_target.coordinate[0]);
                                        speed_max = qMax(speed_max, cdgr_target.speed);
                                        speed_min = qMin(speed_min, cdgr_target.speed);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    appendLineToReport("\nКолличество кодограмм в логе: " + QString::number(m_l.codogram_1.size() + m_l.codogram_2.size()
                                                                        + m_l.codogram_3.size() + m_l.codogram_4.size()) + "\n");
    appendLineToReport("\nКолличество кодограмм прошедших выборку: " + QString::number(number_c) + "\n");
    if (number_c != 0)
    {
        appendLineToReport("\nМаксимальные значения полей: \n");
        appendLineToReport("    Время герерации кодограммы: " + dt_max.toString() + "\n");
        appendLineToReport("    " + inter_state.interfase1.coordinate1 + ": " + QString::number(coord_max[0]) + "\n");
        appendLineToReport("    " + inter_state.interfase1.coordinate2 + ": " + QString::number(coord_max[1]) + "\n");
        appendLineToReport("    Высота: " + QString::number(coord_max[2]) + "\n");
        appendLineToReport("    Скорость: " + QString::number(speed_max) + "\n");
        appendLineToReport("\nМинимальные значения полей: \n");
        appendLineToReport("    Время герерации кодограммы: " + dt_min.toString() + "\n");
        appendLineToReport("    " + inter_state.interfase1.coordinate1 + ": " + QString::number(coord_min[0]) + "\n");
        appendLineToReport("    " + inter_state.interfase1.coordinate2 + ": " + QString::number(coord_min[1]) + "\n");
        appendLineToReport("    Высота: " + QString::number(coord_min[2]) + "\n");
        appendLineToReport("    Скорость: " + QString::number(speed_min) + "\n");
    }
}

void MainWindow::write_top_table1()
{
    appendLineToReport("\n3. Таблица кодограмм:\n");
    appendLineToReport("  ТК    Ввремя генерации кодограммы                 " + inter_state.interfase1.coordinate1);
    if(inter_state.workField == 1)
    {
        appendLineToReport(ui->label_35->text().right(4));
    }
    else
    {
        appendLineToReport("[град]");
    }
    appendLineToReport("                  " + inter_state.interfase1.coordinate2 + ui->label_35->text().right(4)
                   + "              " + ui->label_3->text() + "    Скорость [" + ui->comboBox_speed->currentText()
                   + "]        Тип ВО\n");
    appendLineToReport("_____________________________________________________________________________________________________\n");
}

void MainWindow::entry_codogram_to_table1(Target cdgr_target)
{
    appendLineToReport("   1          " + cdgr_target.creationTime.toString() + "                       ");
    if (inter_state.workField == 1)
    {
        appendLineToReport(QString::number(round(cdgr_target.coordinate[0] / pow(1000, inter_state.posButton_index) * 100) / 100) + "                    " +
                QString::number(round(cdgr_target.coordinate[1] / pow(1000, inter_state.posButton_index) * 100) / 100) + "                   " +
                QString::number(round(cdgr_target.coordinate[2] / pow(1000, inter_state.posButton_index) * 100) / 100));
    }
    else if (inter_state.workField == 0)
    {
        appendLineToReport(QString::number(round(atan(cdgr_target.coordinate[1]/cdgr_target.coordinate[0]) * 100) / 100) + "                    " +
                QString::number(round(sqrt(pow(cdgr_target.coordinate[0], 2) + pow(cdgr_target.coordinate[1], 2)) / pow(1000, inter_state.posButton_index) * 100) / 100)
                + "                  " + QString::number(round(cdgr_target.coordinate[2] / pow(1000, inter_state.posButton_index) * 100) / 100));
    }
    appendLineToReport("                    " +
                   QString::number(round(cdgr_target.speed * pow(3.6, inter_state.speedButton_index) * 100) / 100) + "                      "
                   + QString::number(cdgr_target.object_type) + "\n");

}

void MainWindow::table_generation_2()
{
    appendLineToReport("  ТК    Время генерации кодограммы    Угол Z-X     Угол Z-Y\n");
    appendLineToReport("_____________________________________________________________________________________________________\n");
    QDateTime dt_max = ui->dateTimeEdit_angle_min->minimumDateTime();
    QDateTime dt_min = ui->dateTimeEdit_angle_min->maximumDateTime();
    int angleZX_max = 0, angleZX_min = 360;
    int angleZY_max = 0, angleZY_min = 90;
    uint number_c = 0;
    for (Antenna_Angle & cdgr_angle: m_l.codogram_2)
    {
        if ((cdgr_angle.creationTime <= inter_state.interfase2.time_gen_Max and cdgr_angle.creationTime >= inter_state.interfase2.time_gen_Min)
                or ui->checkBox_select_Time_angle->checkState() == 0)
        {
            if ((cdgr_angle.angle_ZX >= inter_state.interfase2.angleZX[0] and cdgr_angle.angle_ZX <= inter_state.interfase2.angleZX[1])
                    or ui->checkBox_select_AngleZX->checkState() == 0)
            {
                if ((cdgr_angle.angle_ZY >= inter_state.interfase2.angleZY[0] and cdgr_angle.angle_ZY <= inter_state.interfase2.angleZY[1])
                        or ui->checkBox_select_AngleZY->checkState() == 0)
                {
                    ++number_c;
                    appendLineToReport("   2          " + cdgr_angle.creationTime.toString() + "              " + QString::number(cdgr_angle.angle_ZX)
                                   + "                " + QString::number(cdgr_angle.angle_ZY) + "\n");
                    dt_max = qMax(dt_max, cdgr_angle.creationTime);
                    dt_min = qMin(dt_min, cdgr_angle.creationTime);
                    angleZX_max = qMax(angleZX_max, cdgr_angle.angle_ZX);
                    angleZX_min = qMin(angleZX_min, cdgr_angle.angle_ZX);
                    angleZY_max = qMax(angleZY_max, cdgr_angle.angle_ZY);
                    angleZY_min = qMin(angleZY_min, cdgr_angle.angle_ZY);
                }
            }
        }
    }
    appendLineToReport("\nКолличество кодограмм в логе: " + QString::number(m_l.codogram_1.size() + m_l.codogram_2.size()
                                                                        + m_l.codogram_3.size() + m_l.codogram_4.size()) + "\n");
    appendLineToReport("\nКолличество кодограмм прошедших выборку: " + QString::number(number_c) + "\n");
    if (number_c != 0)
    {
        appendLineToReport("\nМаксимальные значения полей: \n");
        appendLineToReport("    Время герерации кодограммы: " + dt_max.toString() + "\n");
        appendLineToReport("    Угол в плоскости Z-X: " + QString::number(angleZX_max) + "\n");
        appendLineToReport("    Угол в плоскости Z-Y: " + QString::number(angleZY_max) + "\n");

        appendLineToReport("\nМинимальные значения полей: \n");
        appendLineToReport("    Время герерации кодограммы: " + dt_min.toString() + "\n");
        appendLineToReport("    Угол в плоскости Z-X: " + QString::number(angleZX_min) + "\n");
        appendLineToReport("    Угол в плоскости Z-Y: " + QString::number(angleZY_min) + "\n");
    }
}

void MainWindow::table_generation_3()
{
    appendLineToReport("  ТК    Ввремя генерации кодограммы    Мощность\n");
    appendLineToReport("_____________________________________________________________________________________________________\n");
    QDateTime dt_max = ui->dateTimeEdit_angle_min->minimumDateTime();
    QDateTime dt_min = ui->dateTimeEdit_angle_min->maximumDateTime();
    uint power_max = 1, power_min = 999;
    uint number_c = 0;
    for (Power_Coodogram & cdgr_power: m_l.codogram_3)
    {
        if ((cdgr_power.creationTime <= inter_state.interfase3.time_gen_Max and cdgr_power.creationTime >= inter_state.interfase3.time_gen_Min)
                or ui->checkBox_select_Time_power->checkState() == 0)
        {
            if ((cdgr_power.powerValue >= inter_state.interfase3.energy[0] and cdgr_power.powerValue <= inter_state.interfase3.energy[1])
                    or ui->checkBox_select_Power->checkState() == 0)
            {
                ++number_c;
                appendLineToReport("   3          " + cdgr_power.creationTime.toString() + "              " + QString::number(cdgr_power.powerValue) + "\n");
                dt_max = qMax(dt_max, cdgr_power.creationTime);
                dt_min = qMin(dt_min, cdgr_power.creationTime);
                power_max = qMax(power_max, cdgr_power.powerValue);
                power_min = qMin(power_min, cdgr_power.powerValue);
            }
        }
    }
    appendLineToReport("\nКолличество кодограмм в логе: " + QString::number(m_l.codogram_1.size() + m_l.codogram_2.size()
                                                                        + m_l.codogram_3.size() + m_l.codogram_4.size()) + "\n");
    appendLineToReport("\nКолличество кодограмм прошедших выборку: " + QString::number(number_c) + "\n");
    if (number_c != 0)
    {
        appendLineToReport("\nМаксимальные значения полей: \n");
        appendLineToReport("    Время герерации кодограммы: " + dt_max.toString() + "\n");
        appendLineToReport("    Мощность: " + QString::number(power_max) + "\n");

        appendLineToReport("\nМинимальные значения полей: \n");
        appendLineToReport("    Время герерации кодограммы: " + dt_min.toString() + "\n");
        appendLineToReport("    Мощность: " + QString::number(power_min) + "\n");
    }
}

void MainWindow::table_generation_4()
{
    appendLineToReport("  ТК    Ввремя генерации кодограммы    Режим\n");
    appendLineToReport("_____________________________________________________________________________________________________\n");
    QDateTime dt_max = ui->dateTimeEdit_angle_min->minimumDateTime();
    QDateTime dt_min = ui->dateTimeEdit_angle_min->maximumDateTime();
    uint number_c = 0, mode_0 = 0, mode_1 = 0;
    for (Mode & cdgr_mode: m_l.codogram_4)
    {
        if ((cdgr_mode.creationTime <= inter_state.interfase4.time_gen_Max and cdgr_mode.creationTime >= inter_state.interfase4.time_gen_Min)
                or ui->checkBox_select_Time_mode->checkState() == 0)
        {
            if (cdgr_mode.modeValue == inter_state.interfase4.mode or ui->checkBox_select_Mode->checkState() == 0)
            {
                ++number_c;
                appendLineToReport("   4          " + cdgr_mode.creationTime.toString() + "              " + QString::number(cdgr_mode.modeValue) + "\n");
                dt_max = qMax(dt_max, cdgr_mode.creationTime);
                dt_min = qMin(dt_min, cdgr_mode.creationTime);
                if (cdgr_mode.modeValue == 0)
                {
                    ++mode_0;
                }
                if (cdgr_mode.modeValue == 1)
                {
                    ++mode_1;
                }
            }
        }
    }
    appendLineToReport("\nКолличество кодограмм в логе: " + QString::number(m_l.codogram_1.size() + m_l.codogram_2.size()
                                                                        + m_l.codogram_3.size() + m_l.codogram_4.size()) + "\n");
    appendLineToReport("\nКолличество кодограмм прошедших выборку: " + QString::number(number_c) + "\n");
    if (number_c != 0)
    {
        appendLineToReport("\nМаксимальные значения полей: \n");
        appendLineToReport("    Время герерации кодограммы: " + dt_max.toString() + "\n");
        appendLineToReport("\nМинимальные значения полей: \n");
        appendLineToReport("    Время герерации кодограммы: " + dt_min.toString() + "\n\n");
        appendLineToReport("Дежурный режим включен " + QString::number(mode_0) + " раз.\n Боевой режим включен "
                       + QString::number(mode_1) + " раз.\n");
    }
}

void Log::read_codogram(QString codogram)
{
    QStringList codogram_list = codogram.split(",");
    switch (codogram_list.at(0).toInt()) //определение типа кодограммы
    {
    case 1://Target
    {
        Target cdgr_target;
        cdgr_target.creationTime = Log::string_to_DataTime(codogram_list.at(1));
        cdgr_target.coordinate[0] = (codogram_list.at(2)).toInt();
        cdgr_target.coordinate[1] = (codogram_list.at(3)).toInt();
        cdgr_target.coordinate[2] = (codogram_list.at(4)).toInt();
        cdgr_target.speed = (codogram_list.at(5)).toInt();
        cdgr_target.object_type = (codogram_list.at(6)).toInt();
        codogram_1.append(cdgr_target);
        break;
    }
    case 2://Antenna_Angle
    {
        Antenna_Angle cdgr_angle;
        cdgr_angle.creationTime = Log::string_to_DataTime(codogram_list.at(1));
        cdgr_angle.angle_ZX = (codogram_list.at(2)).toInt();
        cdgr_angle.angle_ZY = (codogram_list.at(3)).toInt();
        codogram_2.append(cdgr_angle);
        break;
    }
    case 3://Power_Codogram
    {
        Power_Coodogram cdgr_power;
        cdgr_power.creationTime = Log::string_to_DataTime(codogram_list.at(1));
        cdgr_power.powerValue = codogram_list.at(2).toInt();
        codogram_3.append(cdgr_power);
        break;
    }
    case 4://Mode
    {
        Mode cdgr_mode;
        cdgr_mode.creationTime = Log::string_to_DataTime(codogram_list.at(1));
        cdgr_mode.modeValue = codogram_list.at(2).toInt();
        codogram_4.append(cdgr_mode);
        break;
    }
    default:
    {
        qWarning() << "Не известная кодограмма";
        break;
    }
    }


}
