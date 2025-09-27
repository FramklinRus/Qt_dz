#include "mainwindow.h"
#include "./ui_mainwindow.h"
int value = 0;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    int value = 0;
    ui->setupUi(this);
    ui->RB_no->setText("Да");
      ui->RB_yes->setText("Нет");
    ui->PB_start->setText("Старт");
      ui->PBAR_progressBar->setMaximum(10);
    ui->PBAR_progressBar->setMinimum(0);

  ui->PB_start->setCheckable(true);

    ui->groupBox->setTitle("Добавление слов ДА и НЕТ в лог");
ui->PB_start->setEnabled(false);



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
value++;
            ui->LW_listWidget->addItem("Да");
            ui->PBAR_progressBar->setValue(value);

    }
    else if (ui->RB_yes->isChecked())
    {

        value++;
        ui->LW_listWidget->addItem("Нет");
        ui->PBAR_progressBar->setValue(value);

    }
    else
    {
        ui->LW_listWidget->clear();
    }

    }
    if (value==11)
    {
        ui->PBAR_progressBar->setValue(0);
        value = 0;
        ui->LW_listWidget->clear();
        if (ui->RB_no->isChecked())
        {
            value++;
            ui->LW_listWidget->addItem("Да");
            ui->PBAR_progressBar->setValue(value);

        }
        else if (ui->RB_yes->isChecked())
        {

            value++;
            ui->LW_listWidget->addItem("Нет");
            ui->PBAR_progressBar->setValue(value);

        }
        else
        {
            ui->LW_listWidget->clear();
        }
    }


}


void MainWindow::on_RB_yes_clicked()
{
    ui->PB_start->setEnabled(true);
}


void MainWindow::on_RB_no_clicked()
{
    ui->PB_start->setEnabled(true);
}

