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
    //labels used to display battle information
    QLabel* trophiesLabel;
    QLabel* opponentTrophiesLabel;
    QLabel* levelLabel;

    //labels used to display prediction results
    QLabel* predictionLabel;
    QLabel* historicalLabel;
    QLabel* resultLabel;

    //shows the prediction as a progress bar
    QProgressBar* predictionBar;
};