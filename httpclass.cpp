#include "httpclass.h"
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkCookieJar>
#include <QNetworkCookie>
#include <QNetworkReply>
#include <QEventLoop>
#include <QDebug>
HttpClass::HttpClass(QObject *parent) : QObject(parent)
{

}

QString HttpClass::GetString(QString &url){
    QNetworkAccessManager manager ;
    QNetworkRequest request ;
    request.setUrl(QUrl(url));
    QNetworkReply * reply = manager.get(request);
    QEventLoop loop ;
    connect(reply,SIGNAL(finished()),&loop,SLOT(quit()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),&loop,SLOT(quit()));
    loop.exec();
    if(reply->error()){
        return NULL ;
    }else{
        QString response = QString(reply->readAll()) ;
        reply->deleteLater();
        return response ;
    }
}
QVariant HttpClass::GetBytes(QString &url,QNetworkCookieJar *cookies){
    QNetworkAccessManager manager ;
    QNetworkRequest request ;
    if(cookies != nullptr)
        manager.setCookieJar(cookies);
    request.setUrl(QUrl(url));
    QNetworkReply * reply = manager.get(request);
    QEventLoop loop ;
    connect(reply,SIGNAL(finished()),&loop,SLOT(quit()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),&loop,SLOT(quit()));
    loop.exec();
    if(reply->error()){
        qDebug() << reply->errorString() ;
        return reply->errorString() ;
    }else{
        if(reply->header(QNetworkRequest::ContentTypeHeader).Bool){
           QVariant contentType =  reply->header(QNetworkRequest::ContentTypeHeader) ;
           QString content = contentType.toString();
           qDebug() << content;
           if(content == "application/octet-stream"){
               QByteArray tmp = reply->readAll();
               reply->deleteLater();
               return tmp ;
           }else{
               return QString("Invalid Response");
           }

        }else{
            return QString("Invalid Response Headers");
        }
    }
    return QString("Invalid State");
}
