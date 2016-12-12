#ifndef FILEUTIL_H
#define FILEUTIL_H

#include <QObject>
#include <QFile>
class FileUtil : public QObject
{
    Q_OBJECT
public:
    explicit FileUtil(QObject *parent = 0);

    static QByteArray *getLZASection(QFile *RomFile);
    static QString getPassword(const QString &decoded);
    static QByteArray *getLZASection(QByteArray *RomFile);
signals:

public slots:
};

#endif // FILEUTIL_H
