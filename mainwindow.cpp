#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->statusbar->addWidget(new QLabel("Status: "));
    ui->statusbar->addWidget(new QLabel("Disconnected"));

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

MainWindow::~MainWindow()
{
    delete ui;
}
