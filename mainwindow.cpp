#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->textBrowser->setText("Version 3\n");
    ui->textBrowser->append("Tips:");
    ui->textBrowser->append("1. Automatically set system time");
    ui->textBrowser->append("2. Days will change with the month");
    ui->textBrowser->append("3. The words for the weekend is red");
    ui->textBrowser->append("4. Now will show message if you forget to enter something\n");
    ui->textBrowser->append("Fix:");
    ui->textBrowser->append("1. Logout function");
    ui->textBrowser->append("2. Now if you login fail it will show correct message");

    manager = new QNetworkAccessManager(this);
    QObject::connect(manager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
    connect(ui->month,  SIGNAL(currentIndexChanged(int)), this, SLOT(markWeekend()));
    connect(ui->year,  SIGNAL(textChanged(QString)), this, SLOT(markWeekend()));
//bug
    ui->identity->insertItem(0, "計畫主持人", "1");
    ui->identity->insertItem(1, "專任助理", "2");
    ui->identity->insertItem(2, "兼任助理", "3");
    ui->identity->insertItem(3, "臨時工", "4");

    workCheckBoxList.append( new QCheckBox(tr("整理數據"), this));
    workCheckBoxList.append( new QCheckBox(tr("操作實驗"), this));
    workCheckBoxList.append( new QCheckBox(tr("實驗前處理"), this));
    workCheckBoxList.append( new QCheckBox(tr("實驗儀器整理"), this));
    workCheckBoxList[0]->move(48, 260);
    workCheckBoxList[1]->move(148, 260);
    workCheckBoxList[2]->move(248, 260);
    workCheckBoxList[3]->move(348, 260);

    createCheckBoxList();

    QString homeUrl = "https://miswww1.ccu.edu.tw/pt_proj/control.php";
    homeRequest.setUrl(QUrl(homeUrl));
    homeRequest.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    QString logsUrl = "https://miswww1.ccu.edu.tw/pt_proj/control2.php";
    logsRequest.setUrl(QUrl(logsUrl));
    logsRequest.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    //use attend to confirn successful login by search user name
    QString attendUrl = "https://miswww1.ccu.edu.tw/pt_proj/attend.php";
    attendRequest.setUrl(QUrl(attendUrl));
    attendRequest.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    QString main2Url = "https://miswww1.ccu.edu.tw/pt_proj/main2.php";
    main2Request.setUrl(QUrl(main2Url));
    main2Request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    QString nextUrl = "https://miswww1.ccu.edu.tw/pt_proj/next.php";
    nextRequest.setUrl(QUrl(nextUrl));
    nextRequest.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    QString todbUrl = "https://miswww1.ccu.edu.tw/pt_proj/todb.php";
    todbRequest.setUrl(QUrl(todbUrl));
    todbRequest.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    QString printUrl = "https://miswww1.ccu.edu.tw/pt_proj/print_row.php";
    printRequest.setUrl(QUrl(printUrl));
    printRequest.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    QString checkUrl = "https://miswww1.ccu.edu.tw/pt_proj/print_check.php";
    checkRequest.setUrl(QUrl(checkUrl));
    checkRequest.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");


//    QTextCodec *codec0 = QTextCodec::codecForName("UTF-8");
//    QString homeReplyUTF8 = codec0->toUnicode(homeReply->readAll());
//    QTextCodec *codec1 = QTextCodec::codecForName("utf8");
//    QString logsReplyUTF8 = codec1->toUnicode(logsReply->readAll());

//    QTextCodec *codec2 = QTextCodec::codecForName("utf8");
//    QString nextReplyUTF8 = codec2->toUnicode(nextReply->readAll());
//    QTextCodec *codec3 = QTextCodec::codecForName("utf8");
//    QString todbReplyUTF8 = codec3->toUnicode(todbReply->readAll());

//    ui->textBrowser->setText(todbReplyUTF8);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createCheckBoxList()
{
    cbl.append(ui->checkBox);
    cbl.append(ui->checkBox_2);
    cbl.append(ui->checkBox_3);
    cbl.append(ui->checkBox_4);
    cbl.append(ui->checkBox_5);
    cbl.append(ui->checkBox_6);
    cbl.append(ui->checkBox_7);
    cbl.append(ui->checkBox_8);
    cbl.append(ui->checkBox_9);
    cbl.append(ui->checkBox_10);
    cbl.append(ui->checkBox_11);
    cbl.append(ui->checkBox_12);
    cbl.append(ui->checkBox_13);
    cbl.append(ui->checkBox_14);
    cbl.append(ui->checkBox_15);
    cbl.append(ui->checkBox_16);
    cbl.append(ui->checkBox_17);
    cbl.append(ui->checkBox_18);
    cbl.append(ui->checkBox_19);
    cbl.append(ui->checkBox_20);
    cbl.append(ui->checkBox_21);
    cbl.append(ui->checkBox_22);
    cbl.append(ui->checkBox_23);
    cbl.append(ui->checkBox_24);
    cbl.append(ui->checkBox_25);
    cbl.append(ui->checkBox_26);
    cbl.append(ui->checkBox_27);
    cbl.append(ui->checkBox_28);
    cbl.append(ui->checkBox_29);
    cbl.append(ui->checkBox_30);
    cbl.append(ui->checkBox_31);
}

void MainWindow::on_loginButton_clicked()
{
    QUrlQuery homeDataArray;
    homeDataArray.addQueryItem("staff_cd", ui->account->text());
    homeDataArray.addQueryItem("passwd", ui->password->text());
    homeDataArray.addQueryItem("proj_type", ui->identity->currentData().toString());

    QNetworkReply *homeReply = manager->post(homeRequest, homeDataArray.toString(QUrl::FullyEncoded).toUtf8());
    eventLoop.exec();

    QNetworkReply *attendReply = manager->get(attendRequest);
    eventLoop.exec();

    QTextCodec *codec3 = QTextCodec::codecForName("utf8");
    QString homeReplyUTF8 = codec3->toUnicode(homeReply->readAll());
    QTextCodec *codec4 = QTextCodec::codecForName("utf8");
    QString attendReplyUTF8 = codec4->toUnicode(attendReply->readAll());
    ui->textBrowser->clear();

    QStringList ql = attendReplyUTF8.split("<b>");
    QString userName = ql[1];
    ql = userName.split("</b>");
    userName = ql[0];

    if (userName == "")
    {
        ui->textBrowser->setText(homeReplyUTF8);
    }
    else
    {
        ui->textBrowser->setText(userName + " 登入成功");
        intoLogs();
    }
}

void MainWindow::intoLogs()
{
    QNetworkReply *logsReply = manager->get(logsRequest);
    eventLoop.exec();

    QNetworkReply *main2Reply = manager->get(main2Request);
    eventLoop.exec();
//qDebug()<<"logsReply";
//qDebug()<<logsReply;
//qDebug()<<"main2Reply";
//qDebug()<<main2Reply;

    QTextCodec *codec4 = QTextCodec::codecForName("UTF-8");
    QString main2ReplyUTF8 = codec4->toUnicode(main2Reply->readAll());
    QStringList main2HTML, planList;
    QString planName, planNum;
    main2HTML = main2ReplyUTF8.split('\n');
    for (int i=0; i<main2HTML.count(); i++)
    {
        if (main2HTML[i].contains("<option value="))
        {
            planName = main2HTML[i].remove(0, 26);
            planList.append(planName);
        }
    }
    for (int i=0; i<planList.count(); i++)
    {
        planNum = planList[i];
        planNum.remove(9, planNum.count()-1);
        ui->planNumComboBox->insertItem(i, planList[i], planNum);
    }
//qDebug()<<"main2HTML";
//qDebug()<<main2HTML;

    //set year and month of the worklogs
    QDateTime time;
    int QDT_year;
    QString yyyy;
    QDT_year = time.currentDateTime().toString("yyyy").toInt() - 1911;
    yyyy = QString::number(QDT_year);
    ui->year->setText(yyyy);
    ui->month->setCurrentText(time.currentDateTime().toString("MM"));
    ui->workHours->setText("4");

    markWeekend();
}

void MainWindow::markWeekend()
{
    for (int i=0; i<31; i++)
    {
        cbl[i]->setStyleSheet("QChechBox { color: black}");
        cbl[i]->setVisible(true);
    }
    for (int i=0; i<31; i++)
    {
        int dayOfWeek;
        qd.setDate(ui->year->text().toInt()+1911, ui->month->currentText().toInt(), i+1);
        dayOfWeek = qd.dayOfWeek();
        if (dayOfWeek == 6 || dayOfWeek == 7)
        {
            cbl[i]->setStyleSheet("QCheckBox { color: red; font: bold}");
           // cbl[i]->setStyleSheet("QCheckBox { font: bold}");
        }
        if (dayOfWeek == 0)
            cbl[i]->setVisible(false);
    }
}

void MainWindow::on_createLogs_clicked()
{
    QStringList workInList, dateList;

    appendSelectedWorks(&workInList);
    appendSelectedDays(&dateList);

    if (ui->year->text().isEmpty())
    {
        msg.setText("Please enter the year.");
        msg.exec();
    }
    else if (ui->workHours->text().isEmpty())
    {
        msg.setText("Please enter work hours");
        msg.exec();
    }
    else if (workInList.isEmpty())
    {
        msg.setText("Please enter the work");
        msg.exec();
    }
    else
    {
        qsrand(QDateTime::currentDateTime ().toTime_t ());
        int n,m;
        m = workInList.count();

        QNetworkReply *nextReply;
        QUrlQuery nextDataArray;
        numberOfWorkDays = dateList.count();

        for (int i=0; i<numberOfWorkDays; i++)
        {
            nextDataArray.clear();
            nextDataArray.addQueryItem("type", ui->planNumComboBox->currentData().toString());
            nextDataArray.addQueryItem("yy", ui->year->text());
            nextDataArray.addQueryItem("mm", ui->month->currentText());
            nextDataArray.addQueryItem("dd", dateList[i]);
            nextDataArray.addQueryItem("hrs", ui->workHours->text());
            n = qrand()%m;
            nextDataArray.addQueryItem("workin", workInList[n]);
            nextReply = manager->post(nextRequest, nextDataArray.toString(QUrl::FullyEncoded).toUtf8());
            eventLoop.exec();

            QNetworkReply *todbReply = manager->get(todbRequest);
            eventLoop.exec();

            QTextCodec *codec3 = QTextCodec::codecForName("utf8");
            QString nextReplyUTF8 = codec3->toUnicode(nextReply->readAll());
            ui->textBrowser->clear();
            QString success="  <form action=\"control2.php\" method = \"post\" name=\"go\" target=\"_top\">\n  </form>\n  <script>\n  \tdocument.all[\"go\"].submit();\n  </script>\n";
            if (nextReplyUTF8 == success)
                ui->textBrowser->setText("日誌登錄成功\n(尚未產生批號)");
            else
                ui->textBrowser->setText(nextReplyUTF8);
        }
    }
}

void MainWindow::appendSelectedWorks(QStringList* workInList)
{
    if (ui->workIn->text() != "" && ui->workIn->text() != "非必填")
        workInList->append(ui->workIn->text());
    for (int i=0; i<workCheckBoxList.count(); i++)
    {
        if (workCheckBoxList[i]->isChecked())
            workInList->append(workCheckBoxList[i]->text());
    }
}

void MainWindow::appendSelectedDays(QStringList* dateList)
{

    if (ui->checkBox->isChecked())
        dateList->append("01");
    if (ui->checkBox_2->isChecked())
        dateList->append("02");
    if (ui->checkBox_3->isChecked())
        dateList->append("03");
    if (ui->checkBox_4->isChecked())
        dateList->append("04");
    if (ui->checkBox_5->isChecked())
        dateList->append("05");
    if (ui->checkBox_6->isChecked())
        dateList->append("06");
    if (ui->checkBox_7->isChecked())
        dateList->append("07");
    if (ui->checkBox_8->isChecked())
        dateList->append("08");
    if (ui->checkBox_9->isChecked())
        dateList->append("09");
    if (ui->checkBox_10->isChecked())
        dateList->append("10");
    if (ui->checkBox_11->isChecked())
        dateList->append("11");
    if (ui->checkBox_12->isChecked())
        dateList->append("12");
    if (ui->checkBox_13->isChecked())
        dateList->append("13");
    if (ui->checkBox_14->isChecked())
        dateList->append("14");
    if (ui->checkBox_15->isChecked())
        dateList->append("15");
    if (ui->checkBox_16->isChecked())
        dateList->append("16");
    if (ui->checkBox_17->isChecked())
        dateList->append("17");
    if (ui->checkBox_18->isChecked())
        dateList->append("18");
    if (ui->checkBox_19->isChecked())
        dateList->append("19");
    if (ui->checkBox_20->isChecked())
        dateList->append("20");
    if (ui->checkBox_21->isChecked())
        dateList->append("21");
    if (ui->checkBox_22->isChecked())
        dateList->append("22");
    if (ui->checkBox_23->isChecked())
        dateList->append("23");
    if (ui->checkBox_24->isChecked())
        dateList->append("24");
    if (ui->checkBox_25->isChecked())
        dateList->append("25");
    if (ui->checkBox_26->isChecked())
        dateList->append("26");
    if (ui->checkBox_27->isChecked())
        dateList->append("27");
    if (ui->checkBox_28->isChecked())
        dateList->append("28");
    if (ui->checkBox_29->isChecked())
        dateList->append("29");
    if (ui->checkBox_30->isChecked())
        dateList->append("30");
    if (ui->checkBox_31->isChecked())
        dateList->append("31");
}

void MainWindow::on_createPrintButton_clicked()
{
    QNetworkReply *printReply;
    QUrlQuery printDataArray;
    printDataArray.addQueryItem("unit_cd1", ui->planNumComboBox->currentData().toString());
    printDataArray.addQueryItem("sy", ui->year->text());
    printDataArray.addQueryItem("sm", ui->month->currentText());
    printDataArray.addQueryItem("sd", "01");
    printDataArray.addQueryItem("ey", ui->year->text());
    printDataArray.addQueryItem("em", "12");
    printDataArray.addQueryItem("ed", "31");
    printDataArray.addQueryItem("go", "%E4%BE%9D%E6%A2%9D%E4%BB%B6%E9%81%B8%E5%87%BA%E8%B3%87%E6%96%99");
    printReply = manager->post(printRequest, printDataArray.toString(QUrl::FullyEncoded).toUtf8());
    eventLoop.exec();

    QNetworkReply *checkReply;
    QUrlQuery checkDataArray;
    checkDataArray.addQueryItem("chka", "on");
    QString name1="cb_", name2="ssno_", num;
    for (int i=0; i<numberOfWorkDays; i++)
    {
        num.setNum(i);
        checkDataArray.addQueryItem(name1+num, "1");
        num.setNum(i+1);
        checkDataArray.addQueryItem(name2+num, "1");
    }
    checkDataArray.addQueryItem("go_check", "%E7%A2%BA%E5%AE%9A%E9%80%81%E5%87%BA%E4%B8%A6%E5%88%97%E5%8D%B0");
    checkReply = manager->post(checkRequest, checkDataArray.toString(QUrl::FullyEncoded).toUtf8());
    eventLoop.exec();

    QTextCodec *codec3 = QTextCodec::codecForName("utf8");
    QString checkReplyUTF8 = codec3->toUnicode(checkReply->readAll());
    ui->textBrowser->clear();
    ui->textBrowser->setText(checkReplyUTF8);
}

void MainWindow::on_logOutButton_clicked()
{
    ui->account->clear();
    ui->password->clear();
    ui->identity->setCurrentIndex(0);

    ui->planNumComboBox->clear();
    ui->year->clear();
    ui->month->setCurrentText("01");
    ui->workHours->clear();
    ui->workIn->clear();
    for (int i=0; i<workCheckBoxList.count(); i++)
        workCheckBoxList[i]->setChecked(false);
    ui->checkBox->setChecked(false);
    ui->checkBox_2->setChecked(false);
    ui->checkBox_3->setChecked(false);
    ui->checkBox_4->setChecked(false);
    ui->checkBox_5->setChecked(false);
    ui->checkBox_6->setChecked(false);
    ui->checkBox_7->setChecked(false);
    ui->checkBox_8->setChecked(false);
    ui->checkBox_9->setChecked(false);
    ui->checkBox_10->setChecked(false);
    ui->checkBox_11->setChecked(false);
    ui->checkBox_12->setChecked(false);
    ui->checkBox_13->setChecked(false);
    ui->checkBox_14->setChecked(false);
    ui->checkBox_15->setChecked(false);
    ui->checkBox_16->setChecked(false);
    ui->checkBox_17->setChecked(false);
    ui->checkBox_18->setChecked(false);
    ui->checkBox_19->setChecked(false);
    ui->checkBox_20->setChecked(false);
    ui->checkBox_21->setChecked(false);
    ui->checkBox_22->setChecked(false);
    ui->checkBox_23->setChecked(false);
    ui->checkBox_24->setChecked(false);
    ui->checkBox_25->setChecked(false);
    ui->checkBox_26->setChecked(false);
    ui->checkBox_27->setChecked(false);
    ui->checkBox_28->setChecked(false);
    ui->checkBox_29->setChecked(false);
    ui->checkBox_30->setChecked(false);
    ui->checkBox_31->setChecked(false);
    ui->textBrowser->clear();

    //delete the older manager and create the new one
    delete manager;
    manager = new QNetworkAccessManager(this);
    QObject::connect(manager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
}
