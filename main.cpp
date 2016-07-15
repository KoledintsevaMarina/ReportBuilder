#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QDebug>

#include "qssStyle.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    if (translator.load(
                QLocale(QLocale::English, QLocale::UnitedKingdom),
                QLatin1String("translation"),
                QLatin1String("."),
                QLatin1String(":translations/translations")))
    {
        a.installTranslator(&translator);
        qDebug() << "Translation file for english lang loaded.";
    } else {
        qWarning() << "Translation file for english lang not loaded!";
    }

    MainWindow w;
    w.setStyleSheet( qss::style() );
    w.show();


    return a.exec();
}
