#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>

#include <QDebug>
#include <QEvent>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void readData();
    void handleError(QSerialPort::SerialPortError error);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_connectButton_clicked();

    void on_disconnectButton_clicked();

private:

    bool eventFilter(QObject *obj, QEvent *event) override
    {

        if (event->type() == QEvent::MouseButtonPress) {
            Reset_serialPortInfoListBox();
        }
        return QWidget::eventFilter(obj, event);
    }

private:
    void custom_status_bar_style();
    void custom_stack_widget_style();

    void Reset_serialPortInfoListBox();
    void fillPortsInfo();

private:
    Ui::MainWindow *ui;

    QSerialPort *m_serial = nullptr;
};
#endif // MAINWINDOW_H
