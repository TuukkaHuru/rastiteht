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

void MainWindow::myAsyncFunction()
{
    QThread::msleep(3000);
       valueFromAsync="Data from AsyncFunction";
       emit mySignal();
       qDebug()<< "Async function finish";
}


void MainWindow::on_btnShow_clicked()
{
    connect(this, SIGNAL(mySignal()), this, SLOT(mySlot()));
    myAsyncFunction();
}

void MainWindow::mySlot()
{
    ui->labelInfo->setText(valueFromAsync);
}

