#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->PB_start_stop->setText("Старт");
    ui->PB_start_stop->setCheckable(true);
    ui->PB_Clear->setText("Очистить");
    ui->PB_circle->setText("Круг");
    ui->label_time->setText("0.0");
    stopwatch = new StopWatch(this);
    connect(stopwatch, &StopWatch::timeUpdated, this, [this](QString t){
        ui->label_time->setText(t);
    });
    connect(stopwatch, &StopWatch::timecircle, this, [this](QString t){
        ui->text_log->append(t);
    });
ui->PB_circle->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::on_PB_start_stop_clicked()
{
    if (ui->PB_start_stop->isChecked())
    {
        ui->PB_start_stop->setText("Стоп");
stopwatch->start();
        ui->PB_circle->setEnabled(true);
    }
    else
    {

       ui->PB_start_stop->setText("Старт");
         stopwatch->stop();
        ui->PB_circle->setEnabled(false);
    }



}


void MainWindow::on_PB_Clear_clicked()
{
    stopwatch->clear();
    ui->label_time->clear();
    ui->text_log->clear();
    ui->label_time->setText("0.0");

}


void MainWindow::on_PB_circle_clicked()
{

        stopwatch->circle();

}

