#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QDateTime>
#include <QDebug>
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

class Log
{
public:
    void Read_codogram (QString codogram)
    {
        QStringList codogram_list = codogram.split(",");
        switch (codogram_list.at(0).toInt()) //определение типа кодограммы
        {
        case 1://Target
        {
            Target t;
            Log l;
            t.creationTime = l.string_to_DataTime(codogram_list.at(1));
            t.coordinate[0] = (codogram_list.at(2)).toInt();
            t.coordinate[1] = (codogram_list.at(3)).toInt();
            t.coordinate[2] = (codogram_list.at(4)).toInt();
            t.speed = (codogram_list.at(5)).toInt();
            t.object_type = (codogram_list.at(6)).toInt();
            break;
        }
        case 2://Antenna_Angle
        {
            Antenna_Angle t;
            Log l;
            t.creationTime = l.string_to_DataTime(codogram_list.at(1));
            t.angle_ZX = (codogram_list.at(2)).toInt();
            t.angle_ZY = (codogram_list.at(3)).toInt();
            break;
        }
        case 3://Power_Codogram
        {
            Power_Coodogram t;
            Log l;
            t.creationTime = l.string_to_DataTime(codogram_list.at(1));
            t.powerValue = codogram_list.at(2).toInt();
            break;
        }
        default://Mode
        {
            Mode t;
            Log l;
            t.creationTime = l.string_to_DataTime(codogram_list.at(1));
            t.modeValue = codogram_list.at(2).toInt();
            break;
        }
        }
    }

    void Write()
    {

    }
private:
    QVector<Target> codogram_1;
    QVector<Antenna_Angle> codogram_2;
    QVector<Power_Coodogram> codogram_3;
    QVector<Mode> codogram_4;


    QDateTime string_to_DataTime(QString str_DatTim)
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
};

#endif // MAINWINDOW_H
