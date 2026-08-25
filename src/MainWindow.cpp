#include "MainWindow.h"

#include <QString>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QPixmap>
#include <QPalette>

// main application window
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

    // create the central widget and apply the clash royale background
    //this is qt parent (main window),  create new qwidget object
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QPixmap backgroundPixmap("assets/5HxZHBxQCd2ZLcEWnGJr.png.webp");
    QPalette palette;

    if (!backgroundPixmap.isNull()) {
        backgroundPixmap = backgroundPixmap.scaled(size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
        palette.setBrush(QPalette::Window, backgroundPixmap);
    }

    centralWidget->setAutoFillBackground(true);
    centralWidget->setPalette(palette);

    // main vertical layout
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(55, 40, 55, 45);
    mainLayout->setSpacing(18);

    // header
    QLabel* title = new QLabel("CLASH INTEL");
    title->setObjectName("title");

    QLabel* subtitle = new QLabel("BATTLE ANALYSIS  /  WIN PREDICTION");
    subtitle->setObjectName("subtitle");

    mainLayout->addWidget(title);
    mainLayout->addWidget(subtitle);

    // main analysis card
    QFrame* analysisCard = new QFrame();
    analysisCard->setObjectName("analysisCard");

    QHBoxLayout* cardLayout = new QHBoxLayout(analysisCard);
    cardLayout->setContentsMargins(35, 30, 35, 30);
    cardLayout->setSpacing(30);

    // current battle information
    QVBoxLayout* playerLayout = new QVBoxLayout();

    QLabel* battleTitle = new QLabel("CURRENT BATTLE");
    battleTitle->setObjectName("sectionTitle");

    trophiesLabel = new QLabel(QString("MY TROPHIES     %1").arg(trophies));
    opponentTrophiesLabel = new QLabel(QString("OPPONENT       %1").arg(opponentTrophies));
    levelLabel = new QLabel(QString("AVG CARD LVL   %1").arg(averageLevel, 0, 'f', 2));

    trophiesLabel->setObjectName("stat");
    opponentTrophiesLabel->setObjectName("stat");
    levelLabel->setObjectName("stat");

    playerLayout->addWidget(battleTitle);
    playerLayout->addSpacing(10);
    playerLayout->addWidget(trophiesLabel);
    playerLayout->addWidget(opponentTrophiesLabel);
    playerLayout->addWidget(levelLabel);

    cardLayout->addLayout(playerLayout, 1);

    // win prediction
    QVBoxLayout* predictionLayout = new QVBoxLayout();

    QLabel* predictionTitle = new QLabel("WIN PROBABILITY");
    predictionTitle->setObjectName("sectionTitle");

    predictionLabel = new QLabel(QString("%1%").arg(prediction * 100.0, 0, 'f', 1));
    predictionLabel->setObjectName("prediction");

    predictionBar = new QProgressBar();
    predictionBar->setRange(0, 100);
    predictionBar->setValue(static_cast<int>(prediction * 100.0));
    predictionBar->setTextVisible(false);

    resultLabel = new QLabel(predictedWin ? "PREDICTED WIN" : "PREDICTED LOSS");
    resultLabel->setObjectName(predictedWin ? "winResult" : "lossResult");

    predictionLayout->addWidget(predictionTitle);
    predictionLayout->addWidget(predictionLabel);
    predictionLayout->addWidget(predictionBar);
    predictionLayout->addWidget(resultLabel);

    cardLayout->addLayout(predictionLayout, 1);

    // clash royale logo in the corner of the blue card
    QLabel* logo = new QLabel(analysisCard);
    logo->setObjectName("logo");

    QPixmap logoPixmap("assets/p9Pox73kasEaARLt3w9S.png.webp");

    if (!logoPixmap.isNull()) {
        logoPixmap = logoPixmap.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        logo->setPixmap(logoPixmap);
    }

    logo->setAlignment(Qt::AlignRight | Qt::AlignTop);

    QVBoxLayout* logoLayout = new QVBoxLayout();
    logoLayout->setContentsMargins(0, 0, 0, 0);
    logoLayout->addWidget(logo, 0, Qt::AlignRight | Qt::AlignTop);
    logoLayout->addStretch();

    cardLayout->addLayout(logoLayout);

    mainLayout->addWidget(analysisCard);

    // historical statistics and refresh button
    QHBoxLayout* statsLayout = new QHBoxLayout();

    QFrame* historicalCard = new QFrame();
    historicalCard->setObjectName("statCard");

    QVBoxLayout* historicalLayout = new QVBoxLayout(historicalCard);

    QLabel* historicalTitle = new QLabel("HISTORICAL WIN RATE");
    historicalTitle->setObjectName("smallTitle");

    historicalLabel = new QLabel(QString("%1%").arg(historicalWinRate * 100.0, 0, 'f', 1));
    historicalLabel->setObjectName("historical");

    historicalLayout->addWidget(historicalTitle);
    historicalLayout->addWidget(historicalLabel);

    statsLayout->addWidget(historicalCard);

    QPushButton* refreshButton = new QPushButton("REFRESH ANALYSIS");
    refreshButton->setObjectName("refresh");

    statsLayout->addWidget(refreshButton);

    mainLayout->addLayout(statsLayout);

    // visual styling
    setStyleSheet(
        "QMainWindow {"
        "background-color: #111827;"
        "}"

        "QWidget {"
        "color: #111827;"
        "font-family: 'Courier New';"
        "}"

        "#title {"
        "font-size: 48px;"
        "font-weight: 900;"
        "color: #111827;"
        "letter-spacing: 5px;"
        "}"

        "#subtitle {"
        "font-size: 18px;"
        "font-weight: 900;"
        "color: #172033;"
        "letter-spacing: 3px;"
        "}"

        "#analysisCard {"
        "background-color: rgba(20, 55, 105, 235);"
        "border: 2px solid #3976c8;"
        "border-radius: 16px;"
        "}"

        "#sectionTitle {"
        "font-size: 14px;"
        "font-weight: 900;"
        "color: #d9edff;"
        "letter-spacing: 2px;"
        "}"

        "#stat {"
        "font-size: 17px;"
        "font-weight: bold;"
        "color: #ffffff;"
        "padding: 4px 0px;"
        "}"

        "#prediction {"
        "font-size: 52px;"
        "font-weight: 900;"
        "color: #6ee7ff;"
        "}"

        "#winResult {"
        "font-size: 16px;"
        "font-weight: 900;"
        "color: #55e68a;"
        "letter-spacing: 2px;"
        "}"

        "#lossResult {"
        "font-size: 16px;"
        "font-weight: 900;"
        "color: #ff6875;"
        "letter-spacing: 2px;"
        "}"

        "QProgressBar {"
        "height: 12px;"
        "border: none;"
        "border-radius: 6px;"
        "background-color: #17345b;"
        "}"

        "QProgressBar::chunk {"
        "background-color: #35c9f4;"
        "border-radius: 6px;"
        "}"

        "#statCard {"
        "background-color: rgba(15, 23, 42, 235);"
        "border: 1px solid #263b59;"
        "border-radius: 12px;"
        "padding: 10px;"
        "}"

        "#smallTitle {"
        "font-size: 11px;"
        "font-weight: bold;"
        "color: #7186a0;"
        "letter-spacing: 2px;"
        "}"

        "#historical {"
        "font-size: 28px;"
        "font-weight: bold;"
        "color: #f7c948;"
        "}"

        "#refresh {"
        "background-color: #2468c7;"
        "border: 2px solid #3984e8;"
        "border-radius: 10px;"
        "padding: 16px 28px;"
        "font-size: 13px;"
        "font-weight: bold;"
        "letter-spacing: 1px;"
        "color: white;"
        "}"

        "#refresh:hover {"
        "background-color: #3180e8;"
        "}"
    );
}