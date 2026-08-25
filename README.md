# clashIntel

## Clash Royale Recommendation Tool

clashIntel is a C++17 application that uses the Clash Royale API and historical battle data to predict win probability and generate recommendations through a Qt-based graphical interface.

## Requirements

- C++17
- CMake
- Qt 6
- libcurl
- nlohmann/json
- Clash Royale API token

## Setup

Clone the repository:

git clone https://github.com/bluehimalayanpoppy/clashIntel.git

cd clashIntel

## Clash Royale API Token

clashIntel requires a Clash Royale API token to retrieve player and battle data.

Set your API token as an environment variable:

export CLASH_API_TOKEN="your_token"

Alternatively, create a `.env` file in the project directory:

CLASH_API_TOKEN=your_token

Do not commit your API token to the repository.

## Build

Configure the project with CMake:

cmake -S . -B build

Build the project:

cmake --build build

## Run

Run clashIntel with a Clash Royale player tag:

./build/clashintel "#PLAYER_TAG"

Example:

./build/clashintel "#EXAMPLE189"

The application retrieves the relevant Clash Royale data, processes the battle information, and displays the prediction through the Qt interface.

## Qt GUI

clashIntel uses Qt to provide the graphical user interface.

The main window is implemented using `QMainWindow`. The interface contains:

- Clash Intel title and subtitle
- Current battle statistics
- Player trophies
- Opponent trophies
- Average card level
- Win probability
- Prediction progress bar
- Predicted win/loss result
- Historical win rate
- Refresh analysis button
- Clash Royale artwork and logo

The main Qt window is responsible for constructing and displaying the application's interface.

The main window inherits from `QMainWindow`:

class MainWindow : public QMainWindow

The constructor initializes the Qt window and creates the widgets and layouts used by the interface.

The central widget is created as a child of the main window:

QWidget* centralWidget = new QWidget(this);

It is then assigned to the main window with:

setCentralWidget(centralWidget);

Qt uses a parent-child object system to manage widget ownership. When the parent widget is destroyed, its child widgets are automatically destroyed as well.

The interface is organized using Qt layouts such as:

- QVBoxLayout
- QHBoxLayout

Individual interface elements are created using widgets such as:

- QLabel
- QFrame
- QPushButton
- QProgressBar

The visual appearance is controlled with Qt Style Sheets (QSS), which work similarly to CSS.

The GUI also loads Clash Royale artwork from the project's assets directory.

## Qt Source Files

The Qt interface is primarily contained in:

src/MainWindow.cpp

and its corresponding header:

include/MainWindow.h

`MainWindow.cpp` constructs the interface, configures the widgets, loads images, and applies the visual styling.

`MainWindow.h` declares the `MainWindow` class and its members.

## CSV Data

Battle data is stored in:

data/battles.csv

New battle data is appended to the existing CSV, allowing a persistent historical dataset to be built over time.

Check the number of stored battles:

wc -l data/battles.csv

The CSV contains a header, so subtract 1 from the line count to get the approximate number of stored battles.

## Analyzer

The analyzer trains on the accumulated CSV data and predicts win probability using:

- Player trophies
- Opponent trophies
- Average card level
- Average deck elixir

Example output:

Battles in CSV: 1590

Predicted win probability: 49.5658%

Actual win rate: 49.9371%

The analyzer uses historical battle data to estimate the probability of winning the current matchup.

## Tests

### Card Parser

Build the CardParser test:

cmake --build build --target CardParserTest

Run it:

./build/CardParserTest

### Analyzer

Build the Analyzer test:

cmake --build build --target AnalyzerTest

Run it with a player tag:

./build/AnalyzerTest "#PLAYER_TAG"

Example:

./build/AnalyzerTest "#EXAMPLE189"

## Project Structure

clashIntel/

├── include/
│   ├── Analyzer.h
│   ├── CardParser.h
│   └── MainWindow.h
│
├── src/
│   ├── Analyzer.cpp
│   ├── CardParser.cpp
│   ├── MainWindow.cpp
│   └── main.cpp
│
├── tests/
│   ├── CardParserTest.cpp
│   └── AnalyzerTest.cpp
│
├── assets/
│   ├── 5HxZHBxQCd2ZLcEWnGJr.png.webp
│   └── p9Pox73kasEaARLt3w9S.png.webp
│
├── data/
│   └── battles.csv
│
├── CMakeLists.txt
└── README.md

## Data Flow

Clash Royale API
       ↓
   JSON Data
       ↓
  C++ Objects
       ↓
  CSV Storage
       ↓
Historical Battles
       ↓
    Analyzer
       ↓
 Win Probability
       ↓
 Recommendation
       ↓
    Qt GUI

## Architecture

The project is divided into several main components.

### API / Data Collection

The application communicates with the Clash Royale API using libcurl.

The API returns JSON data, which is parsed using nlohmann/json.

### Card Parser

The card parser converts card information from the API into C++ data structures that can be used by the rest of the application.

### Historical Data

Battle results are stored in `data/battles.csv`.

The accumulated data provides the historical dataset used by the analyzer.

### Analyzer

The analyzer processes historical battle data and uses the available matchup features to calculate a predicted win probability.

### Qt Interface

The Qt interface presents the analysis to the user through the `MainWindow` class.

The GUI receives the prediction and battle statistics and displays them using Qt widgets and layouts.

## Configuration

The application expects the Clash Royale API token to be available through:

CLASH_API_TOKEN

Example:

export CLASH_API_TOKEN="your_token"

Keep API credentials private and never commit them to Git.

## Dependencies

### Qt

Qt provides the graphical user interface framework used by clashIntel.

### libcurl

libcurl is used for HTTP requests to the Clash Royale API.

### nlohmann/json

nlohmann/json is used to parse JSON responses from the Clash Royale API.

### CMake

CMake is used to configure and build the project.

## Build From Scratch

A clean build can be created with:

rm -rf build

cmake -S . -B build

cmake --build build

Then run:

./build/clashintel "#PLAYER_TAG"

## Example

Example command:

./build/clashintel "#EXAMPLE189"

Example analyzer output:

Battles in CSV: 1590
Predicted win probability: 49.5658%
Actual win rate: 49.9371%

The resulting prediction and matchup information are displayed in the Qt graphical interface.

## Current Features

- Clash Royale API integration
- Player lookup using player tags
- Battle history collection
- Persistent CSV battle storage
- Card parsing
- Historical win-rate calculation
- Win-probability prediction
- Analyzer tests
- Card parser tests
- Qt graphical interface
- Clash Royale themed interface
- Battle statistics display
- Prediction progress bar
- Predicted win/loss result
- Historical win-rate display

## Data Flow Summary

1. The user provides a Clash Royale player tag.
2. clashIntel uses the API token to communicate with the Clash Royale API.
3. API responses are received as JSON.
4. JSON data is converted into C++ objects.
5. Battle information is stored in the historical CSV dataset.
6. The analyzer processes the accumulated historical data.
7. The analyzer calculates a win probability.
8. The Qt interface displays the matchup statistics and prediction.
9. The historical dataset can continue growing as additional battles are collected.

## License

This project is for educational and development purposes.

Clash Royale and its related assets are property of their respective owners.