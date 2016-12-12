#ifndef HTTPCLASS_H
#define HTTPCLASS_H

#include <QObject>
#include <QNetworkCookieJar>
class HttpClass : public QObject
{
    Q_OBJECT
public:
    explicit HttpClass(QObject *parent = 0);

    QString GetString(QString &url);
    QVariant GetBytes(QString &url, QNetworkCookieJar *cookies = nullptr);
signals:

public slots:
};

#endif // HTTPCLASS_H
