#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    int value = 0;
    ui->setupUi(this);
    ui->RB_no->setText("Да");
      ui->RB_yes->setText("Нет");
    ui->PB_start->setText("Старт");
      ui->PBAR_progressBar->setMaximum(9);
    ui->PBAR_progressBar->setMinimum(0);

  ui->PB_start->setCheckable(true);

    ui->groupBox->setTitle("Добавление слов ДА и НЕТ в лог");




}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_PB_start_clicked()
{
    if (ui->PB_start->isChecked())
    {
    if (ui->RB_no->isChecked())
    {
        for (int i = 0; i<10; i++)
        {
            ui->LW_listWidget->addItem("Да");
            ui->PBAR_progressBar->setValue(i);
        }
    }

    else if (ui->RB_yes->isChecked())
    {

        for (int i = 0; i<10; i++)
        {
            ui->LW_listWidget->addItem("Нет");
            ui->PBAR_progressBar->setValue(i);
        }

    }
    else
    {
        ui->LW_listWidget->clear();
        ui->PBAR_progressBar->setValue(0);
    }

    }
    else
    {
        ui->LW_listWidget->clear();
        ui->PBAR_progressBar->setValue(0);

    }

}

