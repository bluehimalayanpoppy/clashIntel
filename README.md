# clashIntel

## Clash Royale Recommendation Tool

clashIntel is a C++ application that uses the Clash Royale API and historical battle data to predict win probability and generate recommendations.

## Requirements

- C++17
- CMake
- libcurl
- nlohmann/json
- Clash Royale API token

## Setup

Clone the repository:

```bash
git clone https://github.com/bluehimalayanpoppy/clashIntel.git
cd clashIntel
```

Set your API token:

```bash
export CLASH_API_TOKEN="your_token"
```

Alternatively, create a `.env` file:

```text
CLASH_API_TOKEN=your_token
```

## Build

```bash
cmake -S . -B build
cmake --build build
```

## Run

```bash
./build/clashintel "#PLAYER_TAG"
```

Example:

```bash
./build/clashintel "#EXAMPLE189"
```

## CSV Data

Battle data is stored in:

```text
data/battles.csv
```

New data is appended to the existing CSV, allowing a persistent historical dataset to be built.

Check the number of stored battles:

```bash
wc -l data/battles.csv
```

The CSV contains a header, so subtract 1 from the line count to get the approximate number of battles.

## Analyzer

The analyzer trains on the accumulated CSV data and predicts win probability using:

- Player trophies
- Opponent trophies
- Average card level
- Average deck elixir

Example:

```text
Battles in CSV: 1590
Predicted win probability: 49.5658%
Actual win rate: 49.9371%
```

## Tests

### Card Parser

```bash
cmake --build build --target CardParserTest
./build/CardParserTest
```

### Analyzer

```bash
cmake --build build --target AnalyzerTest
./build/AnalyzerTest "#PLAYER_TAG"
```

## Project Structure

```text
clashIntel/
├── include/
├── src/
├── tests/
├── data/
├── CMakeLists.txt
└── README.md
```

## Data Flow

```text
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
```