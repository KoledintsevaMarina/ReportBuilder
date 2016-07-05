#include "qssStyle.h"

QString qss::style(QString path, bool update)
{
    static QMap<QString, QString> styles;

    if (!styles.contains(path) || update)
    {
        QFile f(path);
        if (f.open(QFile::ReadOnly | QFile::Text))
        {
            QTextStream in(&f);
            styles.insert(path, in.readAll());
        }

    }

    return styles.value(path);
}

