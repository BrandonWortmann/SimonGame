#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QSound>
#include "Game.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_start_clicked();

    void on_blueButton_clicked();

    void on_redButton_clicked();

    void on_blueButton_pressed();

    void on_blueButton_released();

    void on_redButton_pressed();

    void on_redButton_released();

private:
    Ui::MainWindow *ui;
    Game game;
    QTimer timer;
    QSound blueNote;
    QSound redNote;
    int iterations;
    void flashTimerHit();
    void delayTimerHit();
    void buttonClick(bool color);
};
#endif // MAINWINDOW_H
