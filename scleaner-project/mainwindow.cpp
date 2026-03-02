#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>
#include <QDebug>
#include <QString>

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

void MainWindow::on_LoadButton_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Load schedule from file", NULL, "Spreadsheets (*.csv)");
    // why don't it work?
    qDebug() << "load file " + file_name;
}


void MainWindow::on_SaveButton_clicked()
{
    // should be using different function
    QString file_name = QFileDialog::getSaveFileName(this, "Save current configuration");
}


void MainWindow::on_RenderButton_clicked()
{
    QString file_name = QFileDialog::getSaveFileName(this, "Render schedule to picture", NULL, "PNG Image (*.png)");
}

