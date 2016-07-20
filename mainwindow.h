#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QDateTime>
#include <QVariant>
#include <QMessageBox>
#include <QTranslator>
#include <QEvent>

namespace Ui {
class MainWindow;
}

enum Coordinate_system
{
   CARTESIAN,
   POLAR
 };

enum Speed_units
{
    METER_PER_SECOND,
    KILOMETER_PER_HOUR
};

enum Pos_units
{
    METER,
    KILOMETER
};

struct Target
{
    QDateTime creationTime;
    int coordinate[3];
    uint speed;
    uint object_type;
};

struct Antenna_Angle
{
    QDateTime creationTime;
    int angle_ZX;
    int angle_ZY;
};

struct Power
{
    QDateTime creationTime;
    uint powerValue;
};

struct Mode
{
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
    bool select_x, select_y, select_h, select_azimut, select_range, select_h2, select_speed, select_time, select_type;
    QString units_pos, units_speed, units_h;

    Speed_units speed_units = Speed_units::METER_PER_SECOND;
    int speed_coeff;

    Pos_units pos_units = Pos_units::METER;
    int pos_coeff;

    Coordinate_system coordinate_system = Coordinate_system::CARTESIAN;

};

struct Interface_2
{
    QDateTime time_gen_Min;
    QDateTime time_gen_Max;
    int angleZX[2];
    int angleZY[2];
    bool select_time, select_angleZX, select_angleZY;
};
struct Interface_3
{
    QDateTime time_gen_Min;
    QDateTime time_gen_Max;
    uint energy[2];
    bool select_time, select_power;
};
struct Interface_4
{
    QDateTime time_gen_Min;
    QDateTime time_gen_Max;
    bool mode;
    bool select_time, select_mode;
};

struct InterfaceState
{
Interface_1 interfase1;
Interface_2 interfase2;
Interface_3 interfase3;
Interface_4 interfase4;
int report_type_index = 0;
QDateTime dt_min_value, dt_max_value;
};

class Log
{
private:
    struct Statistics_target
    {
        QDateTime dt_max;
        QDateTime dt_min;
        int coord_max[3];
        int coord_min[3];
        uint speed_max;
        uint speed_min;
        uint number_sorted_cdgr_target;
    };

    struct Statistics_angle
    {
        QDateTime dt_max;
        QDateTime dt_min;
        int angleZX_max;
        int angleZY_max;
        int angleZX_min;
        int angleZY_min;
        uint number_sorted_cdgr_angle;
    };

    struct Statistics_power
    {
        QDateTime dt_max;
        QDateTime dt_min;
        uint power_max, power_min;
        uint number_sorted_cdgr_power;
    };

    struct Statistics_mode
    {
        QDateTime dt_max;
        QDateTime dt_min;
        uint mode_0, mode_1;
        uint number_sorted_cdgr_mode;
    };

    Statistics_target statistics_target;
    Statistics_angle statistics_angle;
    Statistics_power statistics_power;
    Statistics_mode statistics_mode;

public:
    bool add_log(QString pathToFile);
    void add_codogram(QString codogram);

    QString create_report(InterfaceState inter_state);

    QString write_top_report_WorkField(InterfaceState inter_state);
    QString write_top_report_ActionOperator(InterfaceState inter_state);

    QVector<Target> select_codogram_Target(InterfaceState inter_state);
    QString write_top_tableTarget(InterfaceState inter_state);
    Statistics_target compilation_statistics_Target(QVector<Target> sorted_codogram1, InterfaceState inter_state);
    QString append_codogram_to_tableTarget(QVector<Target> sorted_codogram1, InterfaceState inter_state);
    QString append_statistics_Target(Statistics_target statistics_target, InterfaceState inter_state);

    QVector<Antenna_Angle> select_codogram_AntennaAngle(InterfaceState inter_state);
    QString write_top_tableAntennaAngle();
    Statistics_angle compilation_statistics_AntennaAngle(QVector<Antenna_Angle> sorted_codogram2, InterfaceState inter_state);
    QString append_codogram_to_tableAntennaAngle(QVector<Antenna_Angle> sorted_codogram2);
    QString append_statistics_AntennaAngle(Statistics_angle statistics_angle);

    QVector<Power> select_codogram_Power(InterfaceState inter_state);
    QString write_top_tablePower();
    Statistics_power compilation_statistics_Power(QVector<Power> sorted_codogram3, InterfaceState inter_state);
    QString append_codogram_to_tablePower(QVector<Power> sorted_codogram3);
    QString append_statistics_Power(Statistics_power statistics_power);

    QVector<Mode> select_codogram_Mode(InterfaceState inter_state);
    QString write_top_tableMode();
    Statistics_mode compilation_statistics_Mode(QVector<Mode> sorted_codogram4, InterfaceState inter_state);
    QString append_codogram_to_tableMode(QVector<Mode> sorted_codogram4);
    QString append_statistics_Mode(Statistics_mode statistics_mode);

    QString write_bottom_report_WorkField();
    QString write_bottom_report_ActionOperator();

private:
    QVector<Target> m_codogram_target;
    QVector<Antenna_Angle> m_codogram_angle;
    QVector<Power> m_codogram_power;
    QVector<Mode> m_codogram_mode;

    static QDateTime _string_to_DataTime(QString str_DatTim)
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

    InterfaceState inter_state;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent * event) override;

private:

    Ui::MainWindow *ui;
    Log m_log;
    InterfaceState m_inter_state;

    void _save_interface_state();
    void _clear_interfase_widgets();

    void write_report(QString text_report);

    QTranslator qtLanguageTranslator;


};

#endif // MAINWINDOW_H
