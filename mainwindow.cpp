#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QAction>
#include <QMenu>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>
#ifndef QT_NO_PRINTER
#include <QPrinter>
#include <QPrintDialog>
#endif

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->workField_xyButton, &QPushButton::toggled, this, [this](bool) {
        ui->workField_stackedWidget->setCurrentIndex(1);
    });

    connect(ui->workField_daButton, &QPushButton::toggled, this, [this](bool) {
        ui->workField_stackedWidget->setCurrentIndex(0);
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
        if (m_inter_state.interfase1.pos_units == Pos_units::KILOMETER)
        {
            ui->label_32->setText("Х [м]");
            ui->label_35->setText("Y [м]");
            ui->label_38->setText("Высота [м]");
            ui->label_3->setText("Высота [м]");
            ui->label_2->setText("Дальность [м]");
            foreach (QSpinBox * spinBox, listOfSpinBoxes)
            {
                spinBox->setValue(spinBox->value() * 1000);
            }
            foreach (QDoubleSpinBox * spinBox, listOfDoubleSpinBoxesForPace)
            {
                spinBox->setValue(spinBox->value() * 1000);
            }
        }
    });

    connect (ui->pushButton_kilometers, &QPushButton::toggled, this, [=] (bool){
        if (m_inter_state.interfase1.pos_units == Pos_units::METER)
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
        }
    });

    connect (ui->pushButton_meter_per_second, &QPushButton::toggled, this, [=] (bool){
        if (m_inter_state.interfase1.speed_units == Speed_units::KILOMETER_PER_HOUR)
        {
            ui->comboBox_speed->setCurrentIndex(0);
            ui->doubleSpinBox_speed_min->setValue(ui->doubleSpinBox_speed_min->value() * 0.278);
            ui->doubleSpinBox_speed_max->setValue(ui->doubleSpinBox_speed_max->value() * 0.278);
            m_inter_state.interfase1.speed_units = Speed_units::METER_PER_SECOND;
            m_inter_state.interfase1.speed_coeff = 0;
        }
    });

    connect (ui->pushButton_kilometer_per_hour, &QPushButton::toggled, this, [=] (bool){
        if (m_inter_state.interfase1.speed_units == Speed_units::METER_PER_SECOND)
        {
            ui->comboBox_speed->setCurrentIndex(1);
            ui->doubleSpinBox_speed_min->setValue(ui->doubleSpinBox_speed_min->value() * 3.6);
            ui->doubleSpinBox_speed_max->setValue(ui->doubleSpinBox_speed_max->value() * 3.6);
            m_inter_state.interfase1.speed_units = Speed_units::KILOMETER_PER_HOUR;
            m_inter_state.interfase1.speed_coeff = 1;
        }
        ui->spinBox_Xmin->setValue(ui->doubleSpinBox_speed_min->value() / 1000);
    });

    for (int i = 0 ; i < listOfPushButton.size(); i++){
        connect(listOfPushButton.at(i), &QPushButton::toggled, this, [this] (bool){
            _save_interface_state();
            QString text_report = m_log.create_report(m_inter_state);
            write_report(text_report);
        });
    }

    for(int i = 0; i < listOfCheckBox.size(); i++){
        connect(listOfCheckBox.at(i), &QCheckBox::clicked, this, [this] (bool){
            _save_interface_state();
            QString text_report = m_log.create_report(m_inter_state);
            write_report(text_report);
        });
    }

    for(int i = 0; i < listOfComboBox.size(); i++){
        connect(listOfComboBox.at(i), static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, [this] (bool){
            _save_interface_state();
            QString text_report = m_log.create_report(m_inter_state);
            write_report(text_report);
        });
    }

    for(int i = 0; i < listOfSpinBoxes.size(); i++){
        connect(listOfSpinBoxes.at(i), static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, [this] (bool){
            _save_interface_state();
            QString text_report = m_log.create_report(m_inter_state);
            write_report(text_report);
        });
    }

    for(int i = 0; i < listOfDoubleSpinBox.size(); i++){
        connect(listOfDoubleSpinBox.at(i), static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, [this] (bool){
            _save_interface_state();
            QString text_report = m_log.create_report(m_inter_state);
            write_report(text_report);
        });
    }

    for(int i = 0; i < listOfDateTimeEdit.size(); i++){
        connect(listOfDateTimeEdit.at(i), &QDateTimeEdit::dateTimeChanged, this, [this] (){
            _save_interface_state();
            QString text_report = m_log.create_report(m_inter_state);
            write_report(text_report);
        });
    }

    connect (ui->listWidget, &QListWidget::itemClicked, this, [this] (QListWidgetItem *){
        m_inter_state.report_type_index = ui->listWidget->currentRow();
        _save_interface_state();
        QString text_report = m_log.create_report(m_inter_state);
        write_report(text_report);
    });

    connect (ui->action_Open_log, &QAction::triggered, this, [this] () {
        QString file_name = QFileDialog::getOpenFileName(this, tr("Открыть файл"), "", "*.txt");
        if (file_name !="")
        {
            m_log.add_log(file_name);

            _save_interface_state();
            QString text_report = m_log.create_report(m_inter_state);
            write_report(text_report);
        }
    });

    connect (ui->action_Close_log, &QAction::triggered, this, [=] () {
        _clear_interfase_widgets();
    });

    connect (ui->action_Save, &QAction::triggered, this, [this](){
        QString fileName = QFileDialog::getSaveFileName(this, tr("Сохранить файл"), "", "Text Files (*.txt)");
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
        close();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::_save_interface_state()
{
    Interface_1 inter1;
    inter1.time_gen_Min = ui->dateTimeEdit_work_field_min->dateTime();
    inter1.time_gen_Max = ui->dateTimeEdit_work_field_max->dateTime();
    if (ui->workField_xyButton->isChecked())
    {
        inter1.coordinate_system = Coordinate_system::CARTESIAN;
        inter1.scope[0][0] = ui->spinBox_Xmin->value();
        inter1.scope[0][1] = ui->spinBox_Xmax->value();
        inter1.scope[1][0] = ui->spinBox_Ymin->value();
        inter1.scope[1][1] = ui->spinBox_Ymax->value();
        inter1.scope[2][0] = ui->spinBox_Hmin->value();
        inter1.scope[2][1] = ui->spinBox_Hmax->value();
        inter1.coordinate1 = tr("X");
        inter1.coordinate2 = tr("Y ");
    } else
        if (ui->workField_daButton->isChecked())
        {
            inter1.coordinate_system = Coordinate_system::POLAR;
            inter1.scope[0][0] = ui->doubleSpinBox_azimut_min->value();
            inter1.scope[0][1] = ui->doubleSpinBox_azimut_max->value();
            inter1.scope[1][0] = ui->doubleSpinBox_range_min->value();
            inter1.scope[1][1] = ui->doubleSpinBox_range_max->value();
            inter1.scope[2][0] = ui->doubleSpinBox_H_min->value();
            inter1.scope[2][1] = ui->doubleSpinBox_H_max->value();
            inter1.coordinate1 = tr("А");
            inter1.coordinate2 = tr("Д");
        }
    if (ui->pushButton_meters->isChecked())
    {
        inter1.pos_coeff = 0;
        inter1.pos_units = Pos_units::METER;
    }
    else if (ui->pushButton_kilometers->isChecked())
    {
        inter1.pos_coeff = 1;
        inter1.pos_units = Pos_units::KILOMETER;
    }
    if (ui->pushButton_meter_per_second->isChecked())
    {
        inter1.speed_coeff = 0;
        inter1.speed_units = Speed_units::METER_PER_SECOND;
    }
    else if (ui->pushButton_kilometer_per_hour->isChecked())
    {
        inter1.speed_coeff = 1;
        inter1.speed_units = Speed_units::KILOMETER_PER_HOUR;
    }
    inter1.pace[0] = ui->doubleSpinBox_speed_min->value();
    inter1.pace[1] = ui->doubleSpinBox_speed_max->value();
    inter1.object = ui->comboBox_object->currentIndex();
    inter1.select_x = ui->checkBox_select_X->checkState();
    inter1.select_y = ui->checkBox_select_Y->checkState();
    inter1.select_h = ui->checkBox_select_Height->checkState();
    inter1.select_azimut = ui->checkBox_select_Azimut->checkState();
    inter1.select_range = ui->checkBox_select_Range->checkState();
    inter1.select_h2 = ui->checkBox_select_Height_2->checkState();
    inter1.select_speed = ui->checkBox_select_Speed->checkState();
    inter1.select_time = ui->checkBox_select_Time_work_field->checkState();
    inter1.select_type = ui->checkBox_select_Type->checkState();
    inter1.units_pos = ui->label_35->text().right(4);
    inter1.units_speed = ui->comboBox_speed->currentText();
    inter1.units_h = ui->label_3->text();

    Interface_2 inter2;
    inter2.time_gen_Min = ui->dateTimeEdit_angle_min->dateTime();
    inter2.time_gen_Max = ui->dateTimeEdit_angle_max->dateTime();
    inter2.angleZX[0] = ui->doubleSpinBox_ZX_min->value();
    inter2.angleZX[1] = ui->doubleSpinBox_ZX_max->value();
    inter2.angleZY[0] = ui->doubleSpinBox_ZY_min->value();
    inter2.angleZY[1] = ui->doubleSpinBox_ZY_max->value();
    inter2.select_time = ui->checkBox_select_Time_angle->checkState();
    inter2.select_angleZX = ui->checkBox_select_AngleZX->checkState();
    inter2.select_angleZY = ui->checkBox_select_AngleZY->checkState();

    Interface_3 inter3;
    inter3.time_gen_Min = ui->dateTimeEdit_power_min->dateTime();
    inter3.time_gen_Max = ui->dateTimeEdit_power_max->dateTime();
    inter3.energy[0] = ui->doubleSpinBox_power_min->value();
    inter3.energy[1] = ui->doubleSpinBox_power_max->value();
    inter3.select_time = ui->checkBox_select_Time_power->checkState();
    inter3.select_power = ui->checkBox_select_Power->checkState();

    Interface_4 inter4;
    inter4.time_gen_Min = ui->dateTimeEdit_mode_min->dateTime();
    inter4.time_gen_Max = ui->dateTimeEdit_mode_max->dateTime();
    inter4.mode = ui->comboBox_mode->currentIndex();
    inter4.select_time = ui->checkBox_select_Time_mode->checkState();
    inter4.select_mode = ui->checkBox_select_Mode->checkState();

    m_inter_state.interfase1=inter1;
    m_inter_state.interfase2=inter2;
    m_inter_state.interfase3=inter3;
    m_inter_state.interfase4=inter4;

    m_inter_state.dt_max_value = ui->dateTimeEdit_work_field_min->minimumDateTime();
    m_inter_state.dt_min_value = ui->dateTimeEdit_work_field_min->maximumDateTime();
}

void MainWindow::_clear_interfase_widgets()
{
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

    QList<QDateTimeEdit *> listOfDateTimeEdit;
    listOfDateTimeEdit.append(ui->dateTimeEdit_work_field_min);
    listOfDateTimeEdit.append(ui->dateTimeEdit_work_field_max);
    listOfDateTimeEdit.append(ui->dateTimeEdit_angle_min);
    listOfDateTimeEdit.append(ui->dateTimeEdit_angle_max);
    listOfDateTimeEdit.append(ui->dateTimeEdit_power_min);
    listOfDateTimeEdit.append(ui->dateTimeEdit_power_max);
    listOfDateTimeEdit.append(ui->dateTimeEdit_mode_min);
    listOfDateTimeEdit.append(ui->dateTimeEdit_mode_max);

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
}

void MainWindow::write_report(QString text_report)
{
    ui->plainTextEdit->setPlainText(text_report);
}

QString Log::create_report(InterfaceState m_inter_state)
{
    QString report = "";
    if (m_inter_state.report_type_index == 0)
    {
        report += write_top_report_WorkField( m_inter_state);
        if (m_codogram_target.size() != 0)
        {
            QVector<Target> sorted_codogram_target = select_codogram_Target(m_inter_state);
            Statistics_target statistics_target = compilation_statistics_Target(sorted_codogram_target, m_inter_state);
            report += write_top_tableTarget(m_inter_state);
            report += append_codogram_to_tableTarget(sorted_codogram_target, m_inter_state);
            report += append_statistics_Target(statistics_target, m_inter_state);
        }
        report += write_bottom_report_WorkField();
    }
    else if (m_inter_state.report_type_index == 1)
    {
        report += write_top_report_ActionOperator(m_inter_state);
        if (m_codogram_angle.size() != 0)
        {
            QVector<Antenna_Angle> sorted_codogram_angle = select_codogram_AntennaAngle(m_inter_state);
            Statistics_angle statistics_angle = compilation_statistics_AntennaAngle(sorted_codogram_angle, m_inter_state);
            report += write_top_tableAntennaAngle();
            report += append_codogram_to_tableAntennaAngle(sorted_codogram_angle);
            report += append_statistics_AntennaAngle(statistics_angle);
        }
        if (m_codogram_power.size() != 0)
        {
            QVector<Power> sorted_codogram_power = select_codogram_Power(m_inter_state);
            Statistics_power statistics_power = compilation_statistics_Power(sorted_codogram_power, m_inter_state);
            report += write_top_tablePower();
            report += append_codogram_to_tablePower(sorted_codogram_power);
            report += append_statistics_Power(statistics_power);
        }
        if (m_codogram_mode.size() != 0)
        {
            QVector<Mode> sorted_codogram_mode = select_codogram_Mode(m_inter_state);
            Statistics_mode statistics_mode = compilation_statistics_Mode(sorted_codogram_mode, m_inter_state);
            report += write_top_tableMode();
            report += append_codogram_to_tableMode(sorted_codogram_mode);
            report += append_statistics_Mode(statistics_mode);
        }
        report += write_bottom_report_ActionOperator();
    }
    return report;
}

QString Log::write_top_report_WorkField(InterfaceState inter_state)
{
    QString part_report = "";
    part_report += QObject::tr("                                                                                     ОТЧЕТ\n\n");
    part_report += QObject::tr("                                                                               Рабочее поле\n\n\n");
    part_report += QObject::tr(" Время создания отчета: ") + QDateTime::currentDateTime().toString() + QObject::tr("\n\n2. Условия выбора данных для отчета:\n");
    if (inter_state.interfase1.select_x != 0 or inter_state.interfase1.select_azimut != 0 or
            inter_state.interfase1.select_y != 0 or inter_state.interfase1.select_range != 0 or
            inter_state.interfase1.select_h != 0 or inter_state.interfase1.select_h2 != 0)
    {
        part_report += QObject::tr("Отбор по области:\n");
        if (inter_state.interfase1.select_x != 0 or inter_state.interfase1.select_azimut != 0)
        {
            part_report += "                 " + inter_state.interfase1.coordinate1 + QObject::tr(" от ") +
                    QString::number(inter_state.interfase1.scope[0][0]) + QObject::tr(" до ") +
                    QString::number(inter_state.interfase1.scope[0][1]) + "\n";
        }
        if (inter_state.interfase1.select_y != 0 or inter_state.interfase1.select_range != 0)
        {
            part_report += "                   " + inter_state.interfase1.coordinate2 + QObject::tr(" от ") +
                    QString::number(inter_state.interfase1.scope[1][0]) + QObject::tr(" до ") +
                    QString::number(inter_state.interfase1.scope[1][1]) + "\n";
        }
        if (inter_state.interfase1.select_h != 0 or inter_state.interfase1.select_h2 != 0)
        {
            part_report += QObject::tr("                   Высота от ") + QString::number(inter_state.interfase1.scope[2][0]) + QObject::tr(" до ")
                    + QString::number(inter_state.interfase1.scope[2][1]) + "\n";
        }
    }
    if (inter_state.interfase1.select_speed != 0)
    {
        part_report += QObject::tr("  Отбор по скорости: от ") + QString::number(inter_state.interfase1.pace[0]) + QObject::tr(" до ")
                + QString::number(inter_state.interfase1.pace[1]) + "\n";
    }
    if (inter_state.interfase1.select_time != 0)
    {
        part_report += QObject::tr("  Отбор по времени: от ") + inter_state.interfase1.time_gen_Min.toString() + QObject::tr(" до ")
                + inter_state.interfase1.time_gen_Max.toString() + "\n";
    }
    if (inter_state.interfase1.select_type != 0)
    {
        part_report += QObject::tr("  Отбор по параметрам цели: ") + QString::number(inter_state.interfase1.object) + "\n";
    }
    return part_report;
}

QString Log::write_top_report_ActionOperator(InterfaceState inter_state)
{
    QString part_report = "";
    part_report += QObject::tr("                                                                                     ОТЧЕТ\n\n");
    part_report += QObject::tr("\n                                                                               Действия оператора\n\n\n");
    part_report += QObject::tr("1. Время создания отчета: ") + QDateTime::currentDateTime().toString() + "\n";
    part_report += QObject::tr("\n2. Условия выбора данных для отчета:\n");
    if (inter_state.interfase2.select_time != 0 or inter_state.interfase2.select_angleZX != 0 or inter_state.interfase2.select_angleZY != 0)
    {
        part_report += QObject::tr("  Отбор по углу поворота антенны:\n");
        if (inter_state.interfase2.select_time != 0)
        {
            part_report += QObject::tr("            Отбор по времени от ") + inter_state.interfase2.time_gen_Min.toString() +
                    QObject::tr(" до ") + inter_state.interfase2.time_gen_Max.toString() + "\n";
        }
        if (inter_state.interfase2.select_angleZX != 0)
        {
            part_report += QObject::tr("            Угол в плоскости Z-X от ") + QString::number(inter_state.interfase2.angleZX[0]) +
                    QObject::tr(" до ") + QString::number(inter_state.interfase2.angleZX[1]) + "\n";
        }
        if (inter_state.interfase2.select_angleZY != 0)
        {
            part_report += QObject::tr("            Угол в плоскости Z-Y от ") + QString::number(inter_state.interfase2.angleZY[0]) +
                    QObject::tr(" до ") + QString::number(inter_state.interfase2.angleZY[1]) + "\n";
        }
    }
    if (inter_state.interfase3.select_time != 0 or inter_state.interfase3.select_power != 0)
    {
        part_report += QObject::tr("  Отбор по мощности излучения:\n");
        if (inter_state.interfase3.select_time != 0)
        {
            part_report += QObject::tr("            Отбор по времени от ") + inter_state.interfase3.time_gen_Min.toString() + QObject::tr(" до ")
                    + inter_state.interfase3.time_gen_Max.toString() + "\n";
        }
        if (inter_state.interfase3.select_power != 0)
        {
            part_report += QObject::tr("            Мощность излучения от ") + QString::number(inter_state.interfase3.energy[0]) +
                    QObject::tr(" до ") + QString::number(inter_state.interfase3.energy[1]) + "\n";
        }
    }
    if (inter_state.interfase4.select_time != 0 or inter_state.interfase4.select_mode != 0)
    {
        part_report += QObject::tr("  Отбор по режиму:\n");
        if (inter_state.interfase4.select_time != 0)
        {
            part_report += QObject::tr("            Отбор по времени от ") + inter_state.interfase4.time_gen_Min.toString() +
                    QObject::tr(" до ") + inter_state.interfase4.time_gen_Max.toString() + "\n";
        }
        if (inter_state.interfase4.select_mode != 0)
        {
            part_report += QObject::tr("            Режим ") + QString::number(inter_state.interfase4.mode) + "\n";
        }
    }
    part_report += QObject::tr("3. Таблица кодограмм:\n\n");
    return part_report;
}

QVector<Target> Log::select_codogram_Target(InterfaceState inter_state)
{
    QVector<Target> sorted_m_codogram_target;
    for (Target & cdgr_target: m_codogram_target)
    {
        if ((cdgr_target.coordinate[0] >= inter_state.interfase1.scope[0][0] and cdgr_target.coordinate[0] <= inter_state.interfase1.scope[0][1])
                or inter_state.interfase1.select_x == 0)//X
        {
            if ((cdgr_target.coordinate[1] >= inter_state.interfase1.scope[1][0] and cdgr_target.coordinate[1] <= inter_state.interfase1.scope[1][1])
                    or inter_state.interfase1.select_y == 0)//Y
            {
                if ((cdgr_target.coordinate[2] >= inter_state.interfase1.scope[2][0] and cdgr_target.coordinate[2] <= inter_state.interfase1.scope[2][1])
                        or inter_state.interfase1.select_h == 0 or inter_state.interfase1.select_h2 == 0)//Высота
                {
                    if ((cdgr_target.creationTime <= inter_state.interfase1.time_gen_Max and cdgr_target.creationTime >= inter_state.interfase1.time_gen_Min)
                            or inter_state.interfase1.select_time == 0)//Время
                    {
                        if ((cdgr_target.speed >= inter_state.interfase1.pace[0] and cdgr_target.speed <= inter_state.interfase1.pace[1])
                                or inter_state.interfase1.select_speed == 0)//Скорость
                        {
                            if ((sqrt(pow(cdgr_target.coordinate[0], 2) + pow(cdgr_target.coordinate[1], 2)) >= inter_state.interfase1.scope[0][0]
                                 and sqrt(pow(cdgr_target.coordinate[0], 2) + pow(cdgr_target.coordinate[1], 2)) <= inter_state.interfase1.scope[0][1])
                                    or inter_state.interfase1.select_range == 0)//Дальность
                            {
                                if ((atan(cdgr_target.coordinate[1]/cdgr_target.coordinate[0]) >= inter_state.interfase1.scope[1][0]
                                     and atan(cdgr_target.coordinate[1]/cdgr_target.coordinate[0]) <= inter_state.interfase1.scope[1][1])
                                        or inter_state.interfase1.select_azimut == 0)//Азимут
                                {
                                    if (cdgr_target.object_type == inter_state.interfase1.object or inter_state.interfase1.select_type == 0)//Цель
                                    {
                                        sorted_m_codogram_target.append(cdgr_target);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return sorted_m_codogram_target;
}

QString Log::write_top_tableTarget(InterfaceState inter_state)
{
    QString part_report = "";
    part_report += QObject::tr("\n3. Таблица кодограмм:\n\n");
    part_report += QObject::tr("  ТК    Ввремя генерации кодограммы                 ") + inter_state.interfase1.coordinate1;
    if(inter_state.interfase1.coordinate_system == Coordinate_system::CARTESIAN)
    {
        part_report += inter_state.interfase1.units_pos;
    }
    else if (inter_state.interfase1.coordinate_system == Coordinate_system::POLAR)
    {
        part_report += QObject::tr("[град]");
    }
    part_report += "                  " + inter_state.interfase1.coordinate2 + inter_state.interfase1.units_pos + "              "
            + inter_state.interfase1.units_h + QObject::tr("    Скорость [") + inter_state.interfase1.units_speed + QObject::tr("]        Тип ВО\n");
    part_report += "_____________________________________________________________________________________________________\n";
    return part_report;
}

Log::Statistics_target Log::compilation_statistics_Target(QVector<Target> sorted_codogram_target, InterfaceState inter_state)
{
    Statistics_target statistics_target;

    statistics_target.dt_max = inter_state.dt_max_value;
    statistics_target.dt_min = inter_state.dt_min_value;
    for (int i = 0; i < 3; i++)
    {
        statistics_target.coord_max[i] = 0;//[X,Y,Z]
        statistics_target.coord_min[i] = 9999;//[X,Y,Z]
    }
    statistics_target.speed_max = 1;
    statistics_target.speed_min = 1000;
    statistics_target.number_sorted_cdgr_target = 0;

    for (Target & sorted_cdgr_target: sorted_codogram_target)
    {
        statistics_target.dt_max = qMax(statistics_target.dt_max, sorted_cdgr_target.creationTime);
        statistics_target.dt_min = qMin(statistics_target.dt_min, sorted_cdgr_target.creationTime);
        statistics_target.coord_max[0] = qMax(statistics_target.coord_max[0], sorted_cdgr_target.coordinate[0]);
        statistics_target.coord_min[0] = qMin(statistics_target.coord_min[0], sorted_cdgr_target.coordinate[0]);
        statistics_target.coord_max[1] = qMax(statistics_target.coord_max[1], sorted_cdgr_target.coordinate[1]);
        statistics_target.coord_min[1] = qMin(statistics_target.coord_min[1], sorted_cdgr_target.coordinate[1]);
        statistics_target.coord_max[2] = qMax(statistics_target.coord_max[2], sorted_cdgr_target.coordinate[2]);
        statistics_target.coord_min[2] = qMin(statistics_target.coord_min[2], sorted_cdgr_target.coordinate[2]);
        statistics_target.speed_max = qMax(statistics_target.speed_max, sorted_cdgr_target.speed);
        statistics_target.speed_min = qMin(statistics_target.speed_min, sorted_cdgr_target.speed);
        statistics_target.number_sorted_cdgr_target ++;
    }

    return statistics_target;
}

QString Log::append_codogram_to_tableTarget(QVector<Target> sorted_codogram_target, InterfaceState inter_state)
{
    QString part_report = "";
    for (Target & sorted_cdgr_target: sorted_codogram_target)
    {
        part_report += "   1          " + sorted_cdgr_target.creationTime.toString() + "                       ";
        if (inter_state.interfase1.coordinate_system == Coordinate_system::CARTESIAN)
        {
            part_report += QString("%1").arg(sorted_cdgr_target.coordinate[0] / pow(1000,inter_state.interfase1.pos_coeff),0,',',2);
            part_report += "            ";
            part_report += QString("%1").arg(sorted_cdgr_target.coordinate[1] / pow(1000,inter_state.interfase1.pos_coeff),0,',',2);
            part_report += "            ";
            part_report += QString("%1").arg(sorted_cdgr_target.coordinate[2] / pow(1000,inter_state.interfase1.pos_coeff),0,',',2);
        }
        else if (inter_state.interfase1.coordinate_system == Coordinate_system::POLAR)
        {
            part_report += QString("%1").arg(atan(sorted_cdgr_target.coordinate[1]/sorted_cdgr_target.coordinate[0]),0,',',2);
            part_report += "                    ";
            part_report += QString("%1").arg(sqrt(pow(sorted_cdgr_target.coordinate[0], 2) + pow(sorted_cdgr_target.coordinate[1], 2))
                    / pow(1000,inter_state.interfase1.pos_coeff),0,',',2);
            part_report += "                  ";
            part_report += QString("%1").arg(sorted_cdgr_target.coordinate[2] / pow(1000,inter_state.interfase1.pos_coeff),0,',',2);
        }
        part_report += "                    ";
        part_report += QString("%1").arg(sorted_cdgr_target.speed * pow(3.6, inter_state.interfase1.speed_coeff),0,',',2);
        part_report += "                      " + QString::number(sorted_cdgr_target.object_type) + "\n";
    }
    return part_report;
}

QString Log::append_statistics_Target(Statistics_target statistics_target, InterfaceState inter_state)
{
    QString part_report = "";
    if (statistics_target.number_sorted_cdgr_target != 0)
    {
        part_report += QObject::tr("\nКолличество кодограмм в логе: ") + QString::number(m_codogram_target.size() + m_codogram_angle.size()
                                                                                + m_codogram_power.size() + m_codogram_mode.size()) + "\n";
        part_report += QObject::tr("\nКолличество кодограмм прошедших выборку: ") + QString::number(statistics_target.number_sorted_cdgr_target) + "\n";
        part_report += QObject::tr("\nМаксимальные значения полей: \n");
        part_report += QObject::tr("    Время герерации кодограммы: ") + statistics_target.dt_max.toString() + "\n";
        if (inter_state.interfase1.coordinate_system == Coordinate_system::CARTESIAN)
        {
            part_report += "    " + inter_state.interfase1.coordinate1 + ": " + QString("%1").arg(statistics_target.coord_max[0]
                                                                                / pow(1000,inter_state.interfase1.pos_coeff),0,',',2);
            part_report += "\n    " + inter_state.interfase1.coordinate2 + ": " + QString("%1").arg(statistics_target.coord_max[1]
                                                                                / pow(1000,inter_state.interfase1.pos_coeff),0,',',2);
        }
        else if (inter_state.interfase1.coordinate_system == Coordinate_system::POLAR)
        {
            part_report += "\n    " + inter_state.interfase1.coordinate1 + ": " +
                                       QString("%1").arg(atan(statistics_target.coord_max[1]/statistics_target.coord_max[0]),0,',',2);
            part_report += "\n    " + inter_state.interfase1.coordinate2 + ": " +
                               QString("%1").arg(sqrt(pow(statistics_target.coord_max[0], 2) + pow(statistics_target.coord_max[1], 2))
                                                                                / pow(1000,inter_state.interfase1.pos_coeff),0,',',2);
        }
        part_report += QObject::tr("\n    Высота: ") + QString("%1").arg(statistics_target.coord_max[2]
                                                                           / pow(1000,inter_state.interfase1.pos_coeff),0,',',2);
        part_report += QObject::tr("\n    Скорость: ") + QString("%1").arg(statistics_target.speed_max
                                                                           * pow(3.6, inter_state.interfase1.speed_coeff),0,',',2);

        part_report += QObject::tr("\n\nМинимальные значения полей: \n");
        part_report += QObject::tr("    Время герерации кодограммы: ") + statistics_target.dt_min.toString() + "\n";
        if (inter_state.interfase1.coordinate_system == Coordinate_system::CARTESIAN)
        {
            part_report += "    " + inter_state.interfase1.coordinate1 + ": " + QString("%1").arg(statistics_target.coord_min[0]
                                                                                     / pow(1000,inter_state.interfase1.pos_coeff),0,',',2);
            part_report += "\n    " + inter_state.interfase1.coordinate2 + ": " + QString("%1").arg(statistics_target.coord_min[1]
                                                                                     / pow(1000,inter_state.interfase1.pos_coeff),0,',',2);
        }
        else if (inter_state.interfase1.coordinate_system == Coordinate_system::POLAR)
        {
            part_report += "\n    " + inter_state.interfase1.coordinate1 + ": " +
                                             QString("%1").arg(atan(statistics_target.coord_min[1]/statistics_target.coord_min[0]),0,',',2);
            part_report += "\n    " + inter_state.interfase1.coordinate2 + ": " +
                                     QString("%1").arg(sqrt(pow(statistics_target.coord_min[0], 2) + pow(statistics_target.coord_min[1], 2))
                                                                                      / pow(1000,inter_state.interfase1.pos_coeff),0,',',2);
        }
        part_report += QObject::tr("\n    Высота: ") + QString("%1").arg(statistics_target.coord_min[2]
                                                                                      / pow(1000,inter_state.interfase1.pos_coeff),0,',',2);
        part_report += QObject::tr("\n    Скорость: ") + QString("%1").arg(statistics_target.speed_min
                                                                           * pow(3.6, inter_state.interfase1.speed_coeff),0,',',2);
    }
    return part_report;
}

QVector<Antenna_Angle> Log::select_codogram_AntennaAngle(InterfaceState inter_state)
{
    QVector<Antenna_Angle> sorted_m_codogram_angle;
    for (Antenna_Angle & cdgr_angle: m_codogram_angle)
    {
        if ((cdgr_angle.creationTime <= inter_state.interfase2.time_gen_Max and cdgr_angle.creationTime >= inter_state.interfase2.time_gen_Min)
                or inter_state.interfase2.select_time == 0)
        {
            if ((cdgr_angle.angle_ZX >= inter_state.interfase2.angleZX[0] and cdgr_angle.angle_ZX <= inter_state.interfase2.angleZX[1])
                    or inter_state.interfase2.select_angleZX == 0)
            {
                if ((cdgr_angle.angle_ZY >= inter_state.interfase2.angleZY[0] and cdgr_angle.angle_ZY <= inter_state.interfase2.angleZY[1])
                        or inter_state.interfase2.select_angleZY == 0)
                {
                    sorted_m_codogram_angle.append(cdgr_angle);
                }
            }
        }
    }
    return sorted_m_codogram_angle;
}

QString Log::write_top_tableAntennaAngle()
{
    QString part_report = "";
    part_report += QObject::tr("  ТК    Время генерации кодограммы  Угол Z-X[град]   Угол Z-Y[град]\n");
    part_report += "_____________________________________________________________________________________________________\n";
    return part_report;
}

Log::Statistics_angle Log::compilation_statistics_AntennaAngle(QVector<Antenna_Angle> sorted_codogram2, InterfaceState inter_state)
{
    Statistics_angle statistics_angle;

    statistics_angle.dt_max = inter_state.dt_max_value;
    statistics_angle.dt_min = inter_state.dt_min_value;
    statistics_angle.angleZX_max = 0;
    statistics_angle.angleZX_min = 360;
    statistics_angle.angleZY_max = 0;
    statistics_angle.angleZY_min = 90;
    statistics_angle.number_sorted_cdgr_angle = 0;

    for (Antenna_Angle & cdgr_angle: sorted_codogram2)
    {
        statistics_angle.dt_max = qMax(statistics_angle.dt_max, cdgr_angle.creationTime);
        statistics_angle.dt_min = qMin(statistics_angle.dt_min, cdgr_angle.creationTime);
        statistics_angle.angleZX_max = qMax(statistics_angle.angleZX_max, cdgr_angle.angle_ZX);
        statistics_angle.angleZX_min = qMin(statistics_angle.angleZX_min, cdgr_angle.angle_ZX);
        statistics_angle.angleZY_max = qMax(statistics_angle.angleZY_max, cdgr_angle.angle_ZY);
        statistics_angle.angleZY_min = qMin(statistics_angle.angleZY_min, cdgr_angle.angle_ZY);
        statistics_angle.number_sorted_cdgr_angle ++;
    }
    return statistics_angle;
}

QString Log::append_codogram_to_tableAntennaAngle(QVector<Antenna_Angle> sorted_codogram_angle)
{
    QString part_report = "";
    for (Antenna_Angle & sorted_cdgr_angle: sorted_codogram_angle)
    {
        part_report += "   2          " + sorted_cdgr_angle.creationTime.toString() + "              " + QString::number(sorted_cdgr_angle.angle_ZX)
                + "                     " + QString::number(sorted_cdgr_angle.angle_ZY) + "\n";
    }
    return part_report;
}

QString Log::append_statistics_AntennaAngle(Statistics_angle statistics_angle)
{
    QString part_report = "";
    part_report += QObject::tr("\nКолличество кодограмм в логе: ") + QString::number(m_codogram_target.size() + m_codogram_angle.size()
                                                                        + m_codogram_power.size() + m_codogram_mode.size()) + "\n";
    part_report += QObject::tr("\nКолличество кодограмм прошедших выборку: ") + QString::number(statistics_angle.number_sorted_cdgr_angle) + "\n";
    if (statistics_angle.number_sorted_cdgr_angle != 0)
    {
        part_report += QObject::tr("\nМаксимальные значения полей: \n");
        part_report += QObject::tr("    Время герерации кодограммы: ") + statistics_angle.dt_max.toString() + "\n";
        part_report += QObject::tr("    Угол в плоскости Z-X: ") + QString::number(statistics_angle.angleZX_max) + "\n";
        part_report += QObject::tr("    Угол в плоскости Z-Y: ") + QString::number(statistics_angle.angleZY_max) + "\n";

        part_report += QObject::tr("\nМинимальные значения полей: \n");
        part_report += QObject::tr("    Время герерации кодограммы: ") + statistics_angle.dt_min.toString() + "\n";
        part_report += QObject::tr("    Угол в плоскости Z-X: ") + QString::number(statistics_angle.angleZX_min) + "\n";
        part_report += QObject::tr("    Угол в плоскости Z-Y: ") + QString::number(statistics_angle.angleZY_min) + "\n";
    }
    return part_report;
}

QVector<Power> Log::select_codogram_Power(InterfaceState inter_state)
{
    QVector<Power> sorted_m_codogram_power;
    for (Power & cdgr_power: m_codogram_power)
    {
        if ((cdgr_power.creationTime <= inter_state.interfase3.time_gen_Max and cdgr_power.creationTime >= inter_state.interfase3.time_gen_Min)
                or inter_state.interfase3.select_time == 0)
        {
            if ((cdgr_power.powerValue >= inter_state.interfase3.energy[0] and cdgr_power.powerValue <= inter_state.interfase3.energy[1])
                    or inter_state.interfase3.select_power == 0)
            {
                sorted_m_codogram_power.append(cdgr_power);
            }
        }
    }
    return sorted_m_codogram_power;
}

QString Log::write_top_tablePower()
{
    QString part_report = "";
    part_report += QObject::tr("  ТК    Ввремя генерации кодограммы    Мощность[Вт]\n");
    part_report += "_____________________________________________________________________________________________________\n";
    return part_report;
}

Log::Statistics_power Log::compilation_statistics_Power(QVector<Power> sorted_codogram3, InterfaceState inter_state)
{
    Statistics_power statistics_power;

    statistics_power.dt_max = inter_state.dt_max_value;
    statistics_power.dt_min = inter_state.dt_min_value;
    statistics_power.power_max = 1;
    statistics_power.power_min = 999;
    statistics_power.number_sorted_cdgr_power = 0;

    for (Power & cdgr_power: sorted_codogram3)
    {
        statistics_power.dt_max = qMax(statistics_power.dt_max, cdgr_power.creationTime);
        statistics_power.dt_min = qMin(statistics_power.dt_min, cdgr_power.creationTime);
        statistics_power.power_max = qMax(statistics_power.power_max, cdgr_power.powerValue);
        statistics_power.power_min = qMin(statistics_power.power_min, cdgr_power.powerValue);
        statistics_power.number_sorted_cdgr_power ++;
    }
    return statistics_power;
}

QString Log::append_codogram_to_tablePower(QVector<Power> sorted_codogram3)
{
    QString part_report = "";
    for (Power & cdgr_power: sorted_codogram3)
    {
        part_report += "   3          " + cdgr_power.creationTime.toString() + "                   " + QString::number(cdgr_power.powerValue)
                + "\n";
    }
    return part_report;
}

QString Log::append_statistics_Power(Statistics_power statistics_power)
{
    QString part_report = "";
    part_report += QObject::tr("\nКолличество кодограмм в логе: ") + QString::number(m_codogram_target.size() + m_codogram_angle.size()
                                                                        + m_codogram_power.size() + m_codogram_mode.size()) + "\n";
    part_report += QObject::tr("\nКолличество кодограмм прошедших выборку: ") + QString::number(statistics_power.number_sorted_cdgr_power) + "\n";
    if (statistics_power.number_sorted_cdgr_power != 0)
    {
        part_report += QObject::tr("\nМаксимальные значения полей: \n");
        part_report += QObject::tr("    Время герерации кодограммы: ") + statistics_power.dt_max.toString() + "\n";
        part_report += QObject::tr("    Мощность: ") + QString::number(statistics_power.power_max) + "\n";

        part_report += QObject::tr("\nМинимальные значения полей: \n");
        part_report += QObject::tr("    Время герерации кодограммы: ") + statistics_power.dt_min.toString() + "\n";
        part_report += QObject::tr("    Мощность: ") + QString::number(statistics_power.power_min) + "\n";
    }
    return part_report;
}

QVector<Mode> Log::select_codogram_Mode(InterfaceState inter_state)
{
    QVector<Mode> sorted_m_codogram_mode;
    for (Mode & cdgr_mode: m_codogram_mode)
    {
        if ((cdgr_mode.creationTime <= inter_state.interfase4.time_gen_Max and cdgr_mode.creationTime >= inter_state.interfase4.time_gen_Min)
                or inter_state.interfase4.select_time == 0)
        {
            if (cdgr_mode.modeValue == inter_state.interfase4.mode or inter_state.interfase4.select_mode == 0)
            {
                sorted_m_codogram_mode.append(cdgr_mode);
            }
        }
    }
    return sorted_m_codogram_mode;
}

QString Log::write_top_tableMode()
{
    QString part_report = "";
    part_report += QObject::tr("  ТК    Ввремя генерации кодограммы    Режим\n");
    part_report += "_____________________________________________________________________________________________________\n";
    return part_report;
}

Log::Statistics_mode Log::compilation_statistics_Mode(QVector<Mode> sorted_codogram4, InterfaceState inter_state)
{
    Statistics_mode statistics_mode;

    statistics_mode.dt_max = inter_state.dt_max_value;
    statistics_mode.dt_min = inter_state.dt_min_value;
    statistics_mode.mode_0 = 0;
    statistics_mode.mode_1 = 0;
    statistics_mode.number_sorted_cdgr_mode = 0;

    for (Mode & cdgr_mode: sorted_codogram4)
    {
        statistics_mode.number_sorted_cdgr_mode ++;
        statistics_mode.dt_max = qMax(statistics_mode.dt_max, cdgr_mode.creationTime);
        statistics_mode.dt_min = qMin(statistics_mode.dt_min, cdgr_mode.creationTime);
        if (cdgr_mode.modeValue == 0)
        {
            ++statistics_mode.mode_0;
        }
        if (cdgr_mode.modeValue == 1)
        {
            ++statistics_mode.mode_1;
        }
    }
    return statistics_mode;
}

QString Log::append_codogram_to_tableMode(QVector<Mode> sorted_codogram_mode)
{
    QString part_report = "";
    for (Mode & cdgr_mode: sorted_codogram_mode)
    {
        part_report += "   4          " + cdgr_mode.creationTime.toString() + "             " + QString::number(cdgr_mode.modeValue) + "\n";
    }
    return part_report;
}

QString Log::append_statistics_Mode(Statistics_mode statistics_mode)
{
    QString part_report = "";
    part_report += QObject::tr("\nКолличество кодограмм в логе: ") + QString::number(m_codogram_target.size()
                                                    + m_codogram_angle.size() + m_codogram_power.size() + m_codogram_mode.size()) + "\n";
    part_report += QObject::tr("\nКолличество кодограмм прошедших выборку: ") + QString::number(statistics_mode.number_sorted_cdgr_mode) + "\n";
    if (statistics_mode.number_sorted_cdgr_mode != 0)
    {
        part_report += QObject::tr("\nМаксимальные значения полей: \n");
        part_report += QObject::tr("    Время герерации кодограммы: ") + statistics_mode.dt_max.toString() + "\n";
        part_report += QObject::tr("\nМинимальные значения полей: \n");
        part_report += QObject::tr("    Время герерации кодограммы: ") + statistics_mode.dt_min.toString() + "\n\n";
        part_report += QObject::tr("Дежурный режим включен ") + QString::number(statistics_mode.mode_0) +
                               QObject::tr(" раз.\n Боевой режим включен ") + QString::number(statistics_mode.mode_1) + QObject::tr(" раз.\n");
    }
    return part_report;
}

QString Log::write_bottom_report_WorkField()
{
    QString part_report = "";
    part_report += QObject::tr("\nИспользуемые сокращения: \nТК - тип кодограммы;\nА - Азимут;\nД - Дальность\nТип ВО: ");
    part_report += QObject::tr("0 - Самолет\n              1 - Вертолет\n              2 - БПЛА\n              3 - Снаряд\n");
    return part_report;
}

QString Log::write_bottom_report_ActionOperator()
{
    QString part_report = "";
    part_report += QObject::tr("\nИспользуемые сокращения: \nТК - тип кодограммы\n\n");
    return part_report;
}

void Log::add_codogram(QString codogram)
{
    QStringList codogram_list = codogram.split(",");
    switch (codogram_list.at(0).toInt()) //определение типа кодограммы
    {
    case 1://Target
    {
        Target cdgr_target;
        cdgr_target.creationTime = Log::_string_to_DataTime(codogram_list.at(1));
        cdgr_target.coordinate[0] = (codogram_list.at(2)).toInt();
        cdgr_target.coordinate[1] = (codogram_list.at(3)).toInt();
        cdgr_target.coordinate[2] = (codogram_list.at(4)).toInt();
        cdgr_target.speed = (codogram_list.at(5)).toInt();
        cdgr_target.object_type = (codogram_list.at(6)).toInt();
        m_codogram_target.append(cdgr_target);
        break;
    }
    case 2://Antenna_Angle
    {
        Antenna_Angle cdgr_angle;
        cdgr_angle.creationTime = Log::_string_to_DataTime(codogram_list.at(1));
        cdgr_angle.angle_ZX = (codogram_list.at(2)).toInt();
        cdgr_angle.angle_ZY = (codogram_list.at(3)).toInt();
        m_codogram_angle.append(cdgr_angle);
        break;
    }
    case 3://Power_Codogram
    {
        Power cdgr_power;
        cdgr_power.creationTime = Log::_string_to_DataTime(codogram_list.at(1));
        cdgr_power.powerValue = codogram_list.at(2).toInt();
        m_codogram_power.append(cdgr_power);
        break;
    }
    case 4://Mode
    {
        Mode cdgr_mode;
        cdgr_mode.creationTime = Log::_string_to_DataTime(codogram_list.at(1));
        cdgr_mode.modeValue = codogram_list.at(2).toInt();
        m_codogram_mode.append(cdgr_mode);
        break;
    }
    default:
    {
        qWarning() << QObject::tr("Не известная кодограмма");
        break;
    }
    }
}

bool Log::add_log(QString path_to_file)
{
    QFile file(path_to_file);
    if (!file.open(QIODevice::ReadOnly))
    {
        //        QMessageBox::critical(this, "Error", "Could not open file");
        qWarning() << Q_FUNC_INFO << QObject::tr("Невозможно открыть файл");
        return false;
    }
    while(!file.atEnd())
    {
        QString codogram = file.readLine();
        add_codogram(codogram);
    }
    file.close();
    return true;
}
