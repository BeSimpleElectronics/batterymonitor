#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDir>
//#include <Qtex
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->widget->addGraph();
    ui->widget->graph(0);
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        ui->devicesList->addItem(info.portName());
    }

    // Fill baudrates
    ui->baudrateList->addItem("9600");
    ui->baudrateList->addItem("19200");
    ui->baudrateList->addItem("38400");
    ui->baudrateList->addItem("57600");
    ui->baudrateList->addItem("115200");
    ui->red->setEnabled(0);
    // Set default selections
    ui->devicesList->setCurrentIndex(0);
    ui->baudrateList->setCurrentText("9600");

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_ConnectButton_clicked(bool checked)
{
    if (!isConnected) {
        if (serial == nullptr) {
            serial = new QSerialPort(this);
        }

        QString portName = "/dev/" + (ui->devicesList->currentText());
        int baudRate = ui->baudrateList->currentText().toInt();

        serial->setPortName(portName);
        serial->setBaudRate(baudRate);
        serial->setDataBits(QSerialPort::Data8);
        serial->setParity(QSerialPort::NoParity);
        serial->setStopBits(QSerialPort::OneStop);
        serial->setFlowControl(QSerialPort::NoFlowControl);

        if (serial->open(QIODevice::ReadWrite)) {
            connect(serial, &QSerialPort::readyRead, this, &MainWindow::onSerialDataReceived);
            qDebug() << "Connected to" << portName << "at" << baudRate << "baud.";
            isConnected = true;
            ui->ConnectButton->setText("Disconnect");
            ui->red->setEnabled(1);
        } else {
            qDebug() << "Failed to connect:" << serial->errorString();
        }
    }
    else {
        serial->close();
        qDebug() << "Disconnected.";
        isConnected = false;
        ui->ConnectButton->setText("Connect");
    }
}

void MainWindow::onSerialDataReceived()
{
    QByteArray data = serial->readAll();
    ui->textEdit->append(QString::fromUtf8(data));
}

void MainWindow::on_devicesList_activated(const QString &arg1)
{
    return;
}


void MainWindow::on_red_clicked()
{
    serial->write("R");

}

