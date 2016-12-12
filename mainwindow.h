#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "httpclass.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setStatusText(const QString &status, int Timeout =0);
private slots:
    void on_btnCheck_clicked();


    void on_btnFile_clicked();

    void on_txtPassword_returnPressed();

private:
    Ui::MainWindow *ui;
    HttpClass *web ;
};

#endif // MAINWINDOW_H
