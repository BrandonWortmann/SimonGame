#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->redButton->setStyleSheet( QString("QPushButton {background-color: rgb(200,0,0);} QPushButton:pressed {background-color: rgb(200,100,100);}"));
    ui->blueButton->setStyleSheet( QString("QPushButton {background-color: rgb(0,0,200);} QPushButton:pressed {background-color: rgb(100,100,200);}"));
    ui->redButton->update();
    ui->blueButton->update();
    QFont font("Times", 74, QFont::Bold);
    ui->title->setFont(font);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_start_clicked()
{
    QFont font("Times", 74, QFont::Bold);
    ui->title->setFont(font);
    ui->title->setText("Simon");
    ui->progressBar->setValue(0);
    ui->start->setEnabled(false);
    game.startGame();
    timer.singleShot(1000, this, &MainWindow::delayTimerHit);
}

void MainWindow::flashTimerHit()
{
    ui->redButton->setStyleSheet( QString("QPushButton {background-color: rgb(200,0,0);} QPushButton:pressed {background-color: rgb(200,100,100);}"));
    ui->blueButton->setStyleSheet( QString("QPushButton {background-color: rgb(0,0,200);} QPushButton:pressed {background-color: rgb(100,100,200);}"));
    ui->redButton->update();
    ui->blueButton->update();
    if (game.sequenceDone())
    {
        ui->redButton->setEnabled(true);
        ui->blueButton->setEnabled(true);
        ui->progressBar->setValue(0);
        return;
    }
    timer.singleShot(1000, this, &MainWindow::delayTimerHit);
}

void MainWindow::delayTimerHit()
{
    if (game.getNext())
    {
        ui->redButton->setStyleSheet(QString("QPushButton {background-color: rgb(200,100,100);}"));
        ui->redButton->update();
    }
    else
    {
        ui->blueButton->setStyleSheet(QString("QPushButton {background-color: rgb(100,100,200);}"));
        ui->blueButton->update();
    }
    timer.singleShot(1000, this, &MainWindow::flashTimerHit);
}

void MainWindow::on_redButton_clicked()
{
    buttonClick(true);
}

void MainWindow::on_blueButton_clicked()
{
    buttonClick(false);
}

void MainWindow::buttonClick(bool color)
{
    int percent = game.isCorrect(color);
    if (percent == -1)
    {
        ui->redButton->setEnabled(false);
        ui->blueButton->setEnabled(false);
        QFont font("Times", 40, QFont::Bold);
        ui->title->setFont(font);
        ui->title->setText("You Lose: Your score was " + QString::number(game.getSize()));
        ui->start->setEnabled(true);
    }
    ui->progressBar->setValue(percent);
    if (percent == 100)
    {
        ui->redButton->setEnabled(false);
        ui->blueButton->setEnabled(false);
        game.addToSequence();
        timer.singleShot(1000, this, &MainWindow::delayTimerHit);
    }
}
