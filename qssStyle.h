#ifndef QSSSTYLE
#define QSSSTYLE

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMap>

namespace qss {

QString style(QString path = ":/qssStyles/qssStyles/main.qss", bool update = false);

}

#endif // QSSSTYLE
