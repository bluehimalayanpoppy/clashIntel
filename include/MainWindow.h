#pragma once

#include <QMainWindow>
#include <QLabel>
#include <QProgressBar>
#include <QPushButton>

class MainWindow : public QMainWindow
{
public:
    MainWindow(
        double prediction,
        double historicalWinRate,
        int trophies,
        int opponentTrophies,
        double averageLevel,
        bool predictedWin,
        QWidget* parent = nullptr
    );

private:
    QLabel* trophiesLabel;
    QLabel* opponentTrophiesLabel;
    QLabel* levelLabel;

    QLabel* predictionLabel;
    QLabel* historicalLabel;
    QLabel* resultLabel;

    QProgressBar* predictionBar;
};