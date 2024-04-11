#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSerialPort>
#include <QSerialPortInfo>

#include <QMessageBox>

#include <QDebug>

static const char blankString[] = QT_TRANSLATE_NOOP("SettingsDialog", "N/A");

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_serial(new QSerialPort(this))
{
    ui->setupUi(this);

    custom_status_bar_style();
    custom_stack_widget_style();


    connect(m_serial, &QSerialPort::readyRead, this, &MainWindow::readData);
    connect(m_serial, &QSerialPort::errorOccurred, this, &MainWindow::handleError);

    ui->serialPortInfoListBox->installEventFilter(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::custom_status_bar_style()
{
    ui->statusbar->addWidget(new QLabel("Status: "));
    ui->statusbar->addWidget(new QLabel("Disconnected"));
}

void MainWindow::custom_stack_widget_style()
{
    QTabWidget *tabw = ui->tabWidget;
    tabw->setTabText(0, "");
    tabw->setTabText(1, "");
    tabw->setTabText(2, "");
    tabw->setTabText(3, "");
    QTabBar *tabbar = tabw->tabBar();

    QLabel *lbl1 = new QLabel();
    lbl1->setText("Capture");
    tabbar->setTabButton(0, QTabBar::LeftSide, lbl1);

    QLabel *lbl2 = new QLabel();
    lbl2->setText("Enroll");
    tabbar->setTabButton(1, QTabBar::LeftSide, lbl2);

    QLabel *lbl3 = new QLabel();
    lbl3->setText("Authentication");
    tabbar->setTabButton(2, QTabBar::LeftSide, lbl3);

    QLabel *lbl4 = new QLabel();
    lbl4->setText("Vertification");
    tabbar->setTabButton(3, QTabBar::LeftSide, lbl4);
}

void MainWindow::Reset_serialPortInfoListBox()
{
    ui->serialPortInfoListBox->setCurrentIndex(0);
}

void MainWindow::readData()
{

    QByteArray data = m_serial->readAll();
    qDebug() << data;

}

void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), m_serial->errorString());
        m_serial->close();
    }
}

void MainWindow::on_connectButton_clicked()
{
    switch (ui->serialPortInfoListBox->currentIndex()) {
    case 0:
        qDebug() << "Devices Selected";
        QMessageBox::warning(this, "Error", "Select a device.", QMessageBox::Ok);
        break;
    case 1:
        qDebug() << "Fap30";
        QMessageBox::warning(this, "Error", "No devices found.", QMessageBox::Ok);
        break;
    case 2:
        qDebug() << "Fap90";
        QMessageBox::warning(this, "Error", "No devices found.", QMessageBox::Ok);
        break;
    default:
        qDebug() << "Error";
        break;
    };
}



void MainWindow::on_disconnectButton_clicked()
{

    m_serial->close();

    ui->connectButton->setEnabled(1);
    ui->disconnectButton->setEnabled(0);

}

void MainWindow::fillPortsInfo()
{
    const auto infos = QSerialPortInfo::availablePorts();


    for (const QSerialPortInfo &info : infos) {
        QStringList list;
        const QString description = info.description();
        const QString manufacturer = info.manufacturer();
        const QString serialNumber = info.serialNumber();
        const auto vendorId = info.vendorIdentifier();
        const auto productId = info.productIdentifier();

        qDebug() << info.portName() << description << manufacturer << serialNumber << vendorId << productId;

    }

}
