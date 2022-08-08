#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_btnShow_clicked()
{
    QString site_url="http://localhost:3000/car";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    //BASIC AUTENTIKOINTI ALKU
    QString credentials="netuser:netpass";
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader( "Authorization", headerData.toLocal8Bit() );
    //BASIC AUTENTIKOINTI LOPPU

    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished (QNetworkReply*)),this, SLOT(getBookSlot(QNetworkReply*)));
    reply = manager->get(request);
}

void MainWindow::getCarSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
       QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
       QJsonArray json_array = json_doc.array();
       QString car;
       foreach (const QJsonValue &value, json_array) {
           QJsonObject json_obj = value.toObject();
           car+=QString::number(json_obj["idcar"].toInt())+","+json_obj["branch"].toString()+","+json_obj["model"].toString()+"\r";
       }

       qDebug()<<car;

       ui->TxtCar->setText(car);

       reply->deleteLater();
       manager->deleteLater();
}


