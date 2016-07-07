#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QDateTime>
#include <QDebug>

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
        switch ((codogram.left(1)).toInt()) //определение типа кодограммы
        {
        case 1://Target
        {
            QDate date(((codogram.mid(2,2)).toInt()),((codogram.mid(5,2)).toInt()),((codogram.mid(8,4)).toInt()));
            QTime time(((codogram.mid(13,2)).toInt()),((codogram.mid(17,2)).toInt()),((codogram.mid(19,2)).toInt()));
            Target t;
            t.creationTime = QDateTime(date, time);
            t.coordinate[0] = (codogram.mid(22,4)).toInt();
            t.coordinate[1] = (codogram.mid(27,4)).toInt();
            t.coordinate[2] = (codogram.mid(32,4)).toInt();
            t.object_type = (codogram.mid(36,1)).toInt();
            break;
        }
        case 2://Antenna_Angle
        {
            QDate date(((codogram.mid(2,2)).toInt()),((codogram.mid(5,2)).toInt()),((codogram.mid(8,4)).toInt()));
            QTime time(((codogram.mid(13,2)).toInt()),((codogram.mid(17,2)).toInt()),((codogram.mid(19,2)).toInt()));
            Antenna_Angle t;
            t.creationTime = QDateTime(date, time);
            t.angle_ZX = (codogram.mid(22,3)).toInt();
            t.angle_ZY = (codogram.mid(26,2)).toInt();
            break;
        }
        case 3://Power_Codogram
        {
            QDate date(((codogram.mid(2,2)).toInt()),((codogram.mid(5,2)).toInt()),((codogram.mid(8,4)).toInt()));
            QTime time(((codogram.mid(13,2)).toInt()),((codogram.mid(17,2)).toInt()),((codogram.mid(19,2)).toInt()));
            Power_Coodogram t;
            t.creationTime = QDateTime(date, time);
            t.powerValue = (codogram.mid(22,3)).toInt();
            break;
        }
        default://Mode
        {
            QDate date(((codogram.mid(2,2)).toInt()),((codogram.mid(5,2)).toInt()),((codogram.mid(8,4)).toInt()));
            QTime time(((codogram.mid(13,2)).toInt()),((codogram.mid(17,2)).toInt()),((codogram.mid(19,2)).toInt()));
            Mode t;
            t.creationTime = QDateTime(date, time);
            t.modeValue = (codogram.mid(22,1)).toInt();
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
