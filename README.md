
<!---
File:        README.txt                                
Case:        VUT, FIT, ICP, project                                      
Authors:     David Mihola, xmihol00@stud.fit.vutbr.cz
             Vladislav Sokolovskii, xsokol15@stud.fit.vutbr.cz           
Date:        summer semester 2021                                        
-->

# MQTT Explorer and Simulator

## Dependencies
QT Library Version 5.12.8               https://www.qt.io/
QT Charts Library                       can be installed with command 'sudo apt install libqt5charts5-dev'
Eclipse Paho MQTT C++ Version 1.2.0     https://github.com/eclipse/paho.mqtt.cpp  

## Used Third Party Libraries
### QT Library
The QT Library is used for implementation of the graphical user interface of the MQTT Explorer. Additionaly files /src/explorer/flowlayout.cpp and src/explorer/flowlayout.h were downloaded from https://code.qt.io/cgit/qt/qtbase.git/tree/examples/widgets/layouts/flowlayout?h=5.15.    

### Eclipse Paho MQTT C++ Client Library
The Eclipse Paho MQTT C++ Client Library is used for connecting, recieving and publishing messages to
a MQTT broker in both the MQTT explorer and the Simulator.

### JsonCpp Library
The JsonCpp Library is used to serilize and deserilize JSON configuration files for both applications and also for publishing and recieving messages from the MQTT broker. This library is included in the source code in directory /src/json all files apart from the Makefile were downloaded from https://github.com/open-source-parsers/jsoncpp.

## Implemented functionality
### MQTT explorer
Fully implemented.

### Dashboard
TODO

### Simulator
Fully implemented.