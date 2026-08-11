# clashIntel

# clash royale analytics


## requirements
- cmake
- libcurl
- nlohmann/json
- clash royale api token

## setup
set your clash royale api token:
export CLASH_API_TOKEN="your_token"

## build
cmake -S . -B build
cmake --build build

## run

./build/clashintel "#PLAYER_TAG"

example:
./build/clashintel "#EXAMPLE189"

## csv export

battle data is automatically exported to: data/battles.csv

## data flow
clash royale api → json → c++ battle objects → csv