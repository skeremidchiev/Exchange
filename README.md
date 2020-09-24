## Dependecies:

### WebSocket Library
sudo apt-get install libcpprest-dev

### JSON
https://github.com/nlohmann/json

**SET UP**
  - Download the zip file to Ubuntu machine.
  - Unzip the package
  - mkdir build
  - cd build
  - cmake ..
  - make
  - make install
  
## How to build & run:
  - mkdir build && cd build
  - cmake ..
  - make
  - ./../bin/exchange
  
## Known issues:
  * websocket is timeouting (assume maximum number of request per minute reached)
