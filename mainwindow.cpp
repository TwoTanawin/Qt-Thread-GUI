#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_stopThread(false) // initialize stop flag to false
    , m_running(false) // initialize running flag to false
    , m_thread(nullptr) // initialize thread pointer to nullptr
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    m_stopThread = false; // reset stop flag
    QThread* thread = new QThread(this);
    QObject::connect(thread, &QThread::started, [=]() {
        int i = 0;
        while (!m_stopThread) { // check stop flag in loop condition
            ui->label->setText(QString::number(i));
            i++;
            QThread::msleep(10);
        }
    });
    thread->start();
}

void MainWindow::on_pushButton_2_clicked()
{
    m_stopThread = true; // set stop flag to true

    if (m_running) {
        m_running = false;
        if (m_thread) {
            m_thread->quit();
            m_thread->wait();
            m_thread->deleteLater(); // release memory used by QThread object
            m_thread = nullptr;
        }
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    QThread* thread = new QThread(this); // create new thread
    QObject::connect(thread, &QThread::started, this, [=]() {
        ui->label_2->setText("Hello World");
    });
    thread->start();
}


void MainWindow::on_pushButton_4_clicked()
{
    QThread* thread = new QThread(this); // create new thread
    QObject::connect(thread, &QThread::started, this, [=]() {
        ui->label_2->setText("Toyota");
    });
    thread->start();
}

