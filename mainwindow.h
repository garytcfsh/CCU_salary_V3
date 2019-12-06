#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QNetworkCookieJar>
#include <QEventLoop>
#include <QTextCodec>
#include <QList>
#include <QUrlQuery>
#include <QCheckBox>
#include <QDateTime>
#include <QMessageBox>
#include <QDate>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void intoLogs();

    void createCheckBoxList();

    void appendSelectedDays(QStringList*);

    void appendSelectedWorks(QStringList*);

public slots:
    void markWeekend();

private slots:
    void on_loginButton_clicked();

    void on_createLogs_clicked();

    void on_createPrintButton_clicked();

    void on_logOutButton_clicked();

private:
    Ui::MainWindow *ui;

    QNetworkAccessManager *manager;
    QEventLoop eventLoop;
    QNetworkRequest homeRequest, logsRequest, attendRequest, main2Request, nextRequest, todbRequest
    , printRequest, checkRequest;
    int numberOfWorkDays;
    QList< QCheckBox*> workCheckBoxList, cbl;
    QMessageBox msg;
    QDate qd;
};

#endif // MAINWINDOW_H
