#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ConnectButton_clicked(bool checked);
    void on_devicesList_activated(const QString &arg1);
    void onSerialDataReceived(); // 👈 New slot for incoming data

    void on_red_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort *serial = nullptr;
    bool isConnected = false; // ✅ Track connection state

};

#endif // MAINWINDOW_H
