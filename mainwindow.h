#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QDateTime>
#include <QDebug>//====================================      потом удалить    ===================================================================
#include <QVariant>

namespace Ui {
class MainWindow;
}

struct Target
{
    uint type = 1;
    QDateTime creationTime;
    int coordinate[3];
    uint speed;
    uint object_type;
};

struct Antenna_Angle
{
    uint type = 2;
    QDateTime creationTime;
    int angle_ZX;
    int angle_ZY;
};

struct Power_Coodogram
{
    uint type = 3;
    QDateTime creationTime;
    uint powerValue;
};

struct Mode
{
    uint type = 4;
    QDateTime creationTime;
    bool modeValue;
};


struct Interface_1
{
    QDateTime time_gen_Min;
    QDateTime time_gen_Max;
    QString coordinate1;
    QString coordinate2;
    double scope[3][2];
    uint pace[2];
    uint object;
};

struct Interface_2
{
    QDateTime time_gen_Min;
    QDateTime time_gen_Max;
    int angleZX[2];
    int angleZY[2];
};
struct Interface_3
{
    QDateTime time_gen_Min;
    QDateTime time_gen_Max;
    uint energy[2];
};
struct Interface_4
{
    QDateTime time_gen_Min;
    QDateTime time_gen_Max;
    bool mode;
};

struct InterfaceState
{
Interface_1 interfase1;
Interface_2 interfase2;
Interface_3 interfase3;
Interface_4 interfase4;
bool workField = 1;
bool speedButton_index = 0;
bool posButton_index = 0;
bool listWidget_index = 0;
};

class Log
{
public:
    void read_codogram (QString codogram);

    QVector<Target> codogram_1;
    QVector<Antenna_Angle> codogram_2;
    QVector<Power_Coodogram> codogram_3;
    QVector<Mode> codogram_4;

    static QDateTime string_to_DataTime(QString str_DatTim)
    {
        int day = (str_DatTim.mid(0,2)).toInt();
        int mounth = (str_DatTim.mid(3,2)).toInt();
        int year = (str_DatTim.mid(6,4)).toInt();
        QDate date(year, mounth, day);

        int hour = (str_DatTim.mid(11,2)).toInt();
        int minute = (str_DatTim.mid(14,2)).toInt();
        int second = (str_DatTim.mid(17,2)).toInt();
        QTime time(hour, minute, second);

        QDateTime  dat_tim = QDateTime(date, time);
        return dat_tim;
    }

};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:

    Ui::MainWindow *ui;
    Log m_l;
    InterfaceState inter_state;

    struct Min_Max_value_target
    {
        QDateTime dt_max;
        QDateTime dt_min;
        int coord_max[3];
        int coord_min[3];
        uint speed_max;
        uint speed_min;
    };

    struct Min_Max_value_angle
    {
        QDateTime dt_max;
        QDateTime dt_min;
        int angleZX_max;
        int angleZY_max;
        int angleZX_min;
        int angleZY_min;

    };

    struct Min_Max_value_power
    {
        QDateTime dt_max;
        QDateTime dt_min;
        uint power_max, power_min;
    };

    struct Min_Max_value_mode
    {
        QDateTime dt_max;
        QDateTime dt_min;
        uint mode_0, mode_1;
    };

    Min_Max_value_target min_max_value1;
    Min_Max_value_angle min_max_value2;
    Min_Max_value_power min_max_value3;
    Min_Max_value_mode min_max_value4;

    void appendLineToReport(QString);

    void read_interface();

    void write_report();

    void write_top_report_WorkField();
    void write_top_report_ActionOperator();

    QVector<Target> select_codogram_Target();
    void write_top_tableTarget();
    void search_min_max_value_Target(QVector<Target> sorted_codogram1);
    void append_codogram_to_tableTarget(QVector<Target> sorted_codogram1);
    void append_statistics_Target(int number_sorted_cdgr1);

    QVector<Antenna_Angle> select_codogram_AntennaAngle();
    void write_top_tableAntennaAngle();
    void search_min_max_value_AntennaAngle(QVector<Antenna_Angle> sorted_codogram2);
    void append_codogram_to_tableAntennaAngle(QVector<Antenna_Angle> sorted_codogram2);
    void append_statistics_AntennaAngle(int number_sorted_cdgr2);

    QVector<Power_Coodogram> select_codogram_Power();
    void write_top_tablePower();
    void search_min_max_value_Power(QVector<Power_Coodogram> sorted_codogram3);
    void append_codogram_to_tablePower(QVector<Power_Coodogram> sorted_codogram3);
    void append_statistics_Power(int number_sorted_cdgr3);

    QVector<Mode> select_codogram_Mode();
    void write_top_tableMode();
    void search_min_max_value_Mode(QVector<Mode> sorted_codogram4);
    void append_codogram_to_tableMode(QVector<Mode> sorted_codogram4);
    void append_statistics_Mode(int number_sorted_cdgr4);

    void write_bottom_report_WorkField();
    void write_bottom_report_ActionOperator();


};

#endif // MAINWINDOW_H
