#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , blueNote("://LowNote.wav")
    , redNote("://HighNote.wav")
{
    ui->setupUi(this);

    ui->redButton->setStyleSheet( QString("QPushButton {background-color: rgb(200,0,0);} QPushButton:pressed {background-color: rgb(200,100,100);}"));
    ui->blueButton->setStyleSheet( QString("QPushButton {background-color: rgb(0,0,200);} QPushButton:pressed {background-color: rgb(100,100,200);}"));
    ui->redButton->update();
    ui->blueButton->update();
    QFont font("Times", 74, QFont::Bold);
    ui->title->setFont(font);
    iterations = 0;
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
    ui->progressLabel->setText(QString::number(0) + "%");
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
    redNote.stop();
    blueNote.stop();
    if (game.sequenceDone())
    {
        ui->redButton->setEnabled(true);
        ui->blueButton->setEnabled(true);
        ui->progressBar->setValue(0);
        return;
    }
    if(iterations < 8)
    {
        timer.singleShot(1000 - (iterations * 100), this, &MainWindow::delayTimerHit);
    }
    else
    {
        timer.singleShot(1000 - (800), this, &MainWindow::delayTimerHit);
    }
}

void MainWindow::delayTimerHit()
{
    if (game.getNext())
    {
        ui->redButton->setStyleSheet(QString("QPushButton {background-color: rgb(200,100,100);}"));
        ui->redButton->update();
        redNote.play();
    }
    else
    {
        ui->blueButton->setStyleSheet(QString("QPushButton {background-color: rgb(100,100,200);}"));
        ui->blueButton->update();
        blueNote.play();
    }
    if(iterations < 8)
    {
        timer.singleShot(1000 - (iterations * 100), this, &MainWindow::flashTimerHit);
    }
    else
    {
        timer.singleShot(1000 - (800), this, &MainWindow::flashTimerHit);
    }
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
        ui->title->setText("You Lose: Your score was " + QString::number(game.getSize() - 1));
        iterations = 0;
        ui->start->setEnabled(true);
        return;
    }
    ui->progressBar->setValue(percent);
    ui->progressLabel->setText(QString::number(percent) + "%");
    if (percent == 100)
    {
        ui->redButton->setEnabled(false);
        ui->blueButton->setEnabled(false);
        game.addToSequence();
        iterations++;
        timer.singleShot(1000, this, &MainWindow::delayTimerHit);
    }
}

void MainWindow::on_blueButton_pressed()
{
    blueNote.play();
}

void MainWindow::on_blueButton_released()
{
    blueNote.stop();
}

void MainWindow::on_redButton_pressed()
{
    redNote.play();
}

void MainWindow::on_redButton_released()
{
    redNote.stop();
}
