#include "MainWindow.h"

#include <QString>
#include <QVBoxLayout>
#include <QHBoxLayout>

MainWindow::MainWindow(
    double prediction,
    double historicalWinRate,
    int trophies,
    int opponentTrophies,
    double averageLevel,
    bool predictedWin,
    QWidget* parent
)
    : QMainWindow(parent)
{
    setWindowTitle("Clash Intel");
    resize(1100, 700);

    //creates the main widget and layout
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    //creates the application title
    QLabel* title = new QLabel("CLASH INTEL");
    title->setObjectName("title");

    QLabel* subtitle =
        new QLabel("Battle Analysis & Win Prediction");
    subtitle->setObjectName("subtitle");

    mainLayout->addWidget(title);
    mainLayout->addWidget(subtitle);

    //creates the current battle section
    QHBoxLayout* battleLayout = new QHBoxLayout();

    QVBoxLayout* playerLayout = new QVBoxLayout();

    QLabel* battleTitle = new QLabel("CURRENT BATTLE");
    battleTitle->setObjectName("sectionTitle");

    trophiesLabel = new QLabel(
        QString("My trophies: %1").arg(trophies)
    );

    opponentTrophiesLabel = new QLabel(
        QString("Opponent trophies: %1").arg(opponentTrophies)
    );

    levelLabel = new QLabel(
        QString("Average card level: %1")
            .arg(averageLevel, 0, 'f', 3)
    );

    playerLayout->addWidget(battleTitle);
    playerLayout->addWidget(trophiesLabel);
    playerLayout->addWidget(opponentTrophiesLabel);
    playerLayout->addWidget(levelLabel);

    battleLayout->addLayout(playerLayout);

    //creates the prediction section
    QVBoxLayout* predictionLayout = new QVBoxLayout();

    QLabel* predictionTitle =
        new QLabel("WIN PROBABILITY");
    predictionTitle->setObjectName("sectionTitle");

    predictionLabel = new QLabel(
        QString("%1%")
            .arg(prediction * 100.0, 0, 'f', 1)
    );

    predictionLabel->setObjectName("prediction");

    predictionBar = new QProgressBar();
    predictionBar->setRange(0, 100);
    predictionBar->setValue(
        static_cast<int>(prediction * 100.0)
    );
    predictionBar->setTextVisible(false);

    resultLabel = new QLabel(
        predictedWin
            ? "MODEL PREDICTION: WIN"
            : "MODEL PREDICTION: LOSS"
    );

    resultLabel->setObjectName("result");

    predictionLayout->addWidget(predictionTitle);
    predictionLayout->addWidget(predictionLabel);
    predictionLayout->addWidget(predictionBar);
    predictionLayout->addWidget(resultLabel);

    battleLayout->addLayout(predictionLayout);

    mainLayout->addLayout(battleLayout);

    //creates the historical performance section
    QVBoxLayout* historicalLayout = new QVBoxLayout();

    QLabel* historicalTitle =
        new QLabel("HISTORICAL PERFORMANCE");
    historicalTitle->setObjectName("sectionTitle");

    historicalLabel = new QLabel(
        QString("Historical win rate: %1%")
            .arg(historicalWinRate * 100.0, 0, '1')
    );

    historicalLabel->setObjectName("historical");

    historicalLayout->addWidget(historicalTitle);
    historicalLayout->addWidget(historicalLabel);

    mainLayout->addLayout(historicalLayout);

    //creates the refresh button
    QPushButton* refreshButton =
        new QPushButton("REFRESH ANALYSIS");

    refreshButton->setObjectName("refresh");

    mainLayout->addWidget(refreshButton);

    //sets the visual style for the dashboard
    setStyleSheet(
        "QMainWindow {"
        "background-color: #101827;"
        "}"

        "QWidget {"
        "color: white;"
        "font-family: Arial;"
        "}"

        "#title {"
        "font-size: 38px;"
        "font-weight: bold;"
        "color: #4cc9f0;"
        "padding-top: 20px;"
        "}"

        "#subtitle {"
        "font-size: 16px;"
        "color: #94a3b8;"
        "padding-bottom: 25px;"
        "}"

        "#sectionTitle {"
        "font-size: 15px;"
        "font-weight: bold;"
        "color: #94a3b8;"
        "}"

        "QLabel {"
        "font-size: 18px;"
        "}"

        "#prediction {"
        "font-size: 52px;"
        "font-weight: bold;"
        "color: #4ade80;"
        "}"

        "#result {"
        "font-size: 20px;"
        "font-weight: bold;"
        "color: #4ade80;"
        "}"

        "#historical {"
        "font-size: 28px;"
        "font-weight: bold;"
        "color: #fbbf24;"
        "}"

        "QProgressBar {"
        "height: 20px;"
        "border-radius: 10px;"
        "background-color: #1e293b;"
        "}"

        "QProgressBar::chunk {"
        "background-color: #4ade80;"
        "border-radius: 10px;"
        "}"

        "QPushButton {"
        "background-color: #2563eb;"
        "border: none;"
        "border-radius: 8px;"
        "padding: 14px;"
        "font-size: 16px;"
        "font-weight: bold;"
        "}"

        "QPushButton:hover {"
        "background-color: #3b82f6;"
        "}"
    );
}