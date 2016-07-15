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

    void appendLineToReport(QString);

    void read_interface();

    void write_report();

    void write_top_report_WorkField();
    void write_top_report_ActionOperators();

    void tableTarget_generation();
    void write_top_tableTarget();
    void entry_codogram_to_tableTarget(Target codograma_targer);

    void tableAntennaAngle_generation();
    void write_top_tableAntennaAngle();

    void tablePower_generation();
    void write_top_tablePower();

    void tableMode_generation();
    void write_top_tableMode();

public slots:

private:
    Ui::MainWindow *ui;
    Log m_l;
    InterfaceState inter_state;

};

#endif // MAINWINDOW_H
