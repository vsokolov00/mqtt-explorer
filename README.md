
<!---
File:        README.txt                                
Case:        VUT, FIT, ICP, project                                      
Authors:     David Mihola, xmihol00@stud.fit.vutbr.cz
             Vladislav Sokolovskii, xsokol15@stud.fit.vutbr.cz           
Date:        summer semester 2021                                        
-->

# MQTT Explorer and Simulator

## Authors
### David Mihola, xmihol00@stud.fit.vutbr.cz
### Vladislav Sokolovskii, xsokol15@stud.fit.vutbr.cz

## Description
Summer semester 2021 C++ project implemented within The C++ Programming Language course at the Brno University of Technology.
The output of the project is a MQTT explorer application, which connects to a MQTT broker and enables the user to subscribe to topics send and recieve messages, display images and json files etc. Then there is a simulator of trafic, which generates messages in various formats: text, json, images - binary; and can also recieve messages. 

## Dependencies
QT Library Version 5.12.8               https://www.qt.io/  
QT Charts Library                       can be installed with command 'sudo apt install libqt5charts5-dev'  
Eclipse Paho MQTT C++ Version 1.2.0     https://github.com/eclipse/paho.mqtt.cpp  

## Used Third Party Libraries and Code
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

## File Structure
### Clean Structure (after 'make clean')

### Structure with Generated Files (after 'make')

## Simulator Usage
### run in the /src/simulator directory as: ../bin/simulator [options ...]  
### or run from anywhere and specify the configuration file: ./simulator --file "path/to/configuration/file" [options ...]
  
### Options:  
   --help or -h:             Display this help/usage message to STDOUT.  
   --file or -f <file name>: JSON file from which application configuration is loaded, default file is 'config.json'.  
   --server or -s:           MQTT server address, default address is 'tcp://localhost:1883'.  
   --verbose or -v:          Display log messages.  
   --apart or -a:            If specified before all other options below, devices will be excluded from the running list,  
                             rather then included.  
   --cameras or -c:          Include or exclude cameras.  
   --hygrometers or -g:      Include or exclude hygrometers.  
   --lights or -l:           Include or exclude lights.  
   --locks or -l:            Include or exclude locks.  
   --move or -m:             Include or exclude move sensors.  
   --relays or -r:           Include or exclude relays.  
   --thermometers or -t:     Include or exclude thermometers.  
   --thermostats or -e:      Include or exclude thermostats.  
   --valves or -u:           Include or exclude valves.  
   --wattmeters or -w:       Include or exclude wattmeters.

## MQTT explorer usage
### run in the /src/explorer directory as: ../bin/explorer
### or run from anywhere and specify the configuration file as an argument: ./explorer "path/to/configuration/file"
The application can be also started in verbose mode if -v or --verbose is specified in the command line arguments. If the configuration file cannot be opened, new file 'config.json' will be created and a state of the dashboard will be saved there at termination.
