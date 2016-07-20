#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QDebug>

#include "qssStyle.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    QTranslator translator;
//    if (translator.load(
//                QLocale(QLocale::Russian, QLocale::Russia),
//                QLatin1String("translation"),
//                QLatin1String("."),
////                QLatin1String(":translations/translations")))
//                QLatin1String(".")))

//    if (translator.load("D:/build-ReportBuilder-Desktop_Qt_5_2_1_MinGW_32bit-Debug/debug/translation.en.qm"))
//    {
//        a.installTranslator(&translator);
//        qDebug() << "Translation file for russian lang loaded.";
//    } else {
//        qWarning() << "Translation file for russian lang not loaded!";
//    }

    MainWindow w;
    w.setStyleSheet( qss::style() );
    w.show();


    return a.exec();
}
