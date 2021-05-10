
<!---
File:        README.txt                                
Case:        VUT, FIT, ICP, project                                      
Author:      David Mihola, xmihol00@stud.fit.vutbr.cz        
Date:        summer semester 2021                                        
-->

# MQTT Explorer and Simulator

## Authors
### David Mihola, xmihol00@stud.fit.vutbr.cz
### Vladislav Sokolovskii, xsokol15@stud.fit.vutbr.cz

## Description
Summer semester 2021 C++ project implemented within The C++ Programming Language course at the Brno University of Technology.
The output of the project is a MQTT explorer application, which connects to a MQTT broker and enables the user to subscribe to 
topics send and recieve messages, display images and json files etc. Then there is a simulator of trafic, which generates 
messages in various formats: text, JSON, JPG, PNG and binary; and which can also recieve messages in JSON format specified in 
the examples. 

## Dependencies
GNU make                                https://www.gnu.org/software/make/  
GCC, the GNU Compiler Collection        https://gcc.gnu.org/, other C++ compilers may work as well  
QT Library Version 5.12.8               https://www.qt.io/  
qmake                                   build automatically with QT libraries.
Eclipse Paho MQTT C++ Version 1.2.0     https://github.com/eclipse/paho.mqtt.cpp  

## Used Third Party Libraries and Source Code
### QT Library
The QT Library is used for implementation of the graphical user interface of the MQTT Explorer. Additionaly files 
/src/explorer/flowlayout.cpp and src/explorer/flowlayout.h were downloaded from 
https://code.qt.io/cgit/qt/qtbase.git/tree/examples/widgets/layouts/flowlayout?h=5.15.    

### Eclipse Paho MQTT C++ Client Library
The Eclipse Paho MQTT C++ Client Library is used for connecting, recieving and publishing messages to
a MQTT broker in both the MQTT explorer and the simulator.

### JsonCpp Library
The JsonCpp Library is used to serilize and deserilize JSON configuration files in both applications and also for publishing 
and recieving messages from the MQTT broker. This library is included in the source code in directory /src/json all files 
apart from the Makefile were downloaded from https://github.com/open-source-parsers/jsoncpp.

## Implemented functionality
### MQTT explorer
Fully implemented.

### Dashboard
Devices can be added persistantly.
Devices can be deleted.
Messages can be displayed in a format based on a type of a device.
Communication with a device is not implemented.
Setpoints are not implemented.

### Simulator
Fully implemented.

## File Structure
### Clean Structure (after download or command 'make clean')
--doc/
    |
    |--Doxyfile

--examples/
    |
    |--images/          (Contains images used to show examples of usage.)
    |
    |--                 (Other files with written examples.)

--src/
    |
    |--client/          (Contains *.cpp, *.h files encapsulating the Eclipse Paho MQTT client and Makefile.)
    |
    |--explorer/
    |   |
    |   |--resources/   (Contains *.ui, *.qrc and *.png files specifying the design of the user interface.)
    |   |
    |   |--             (Contains *.cpp, *.h files implementing the MQTT explorer application and explorer.pro file used   
    |                    for generating Makefile for this directory.)
    |
    |--json/            
    |   |
    |   |--json/        (Contains header files for the jsoncpp library.)
    |   |
    |   |--             (Contains the jsoncpp.cpp source code and Makefile.)
    |
    |--simulator/
    |   |
    |   |--images/      (Contains images send by simulated cameras.)
    |   |
    |   |--             (Contains *.cpp, *.h files implementing the simulator, config.json and Makefile.)
    |
    |--Makefile

--Makefile

--README.txt

### Structure with Generated Files (after commands 'make' and 'make doc')
--doc/
    |
    |--html/            (Contains generated html documentation.)
    |
    |--Doxyfile

--examples/
    |
    |--images/          (Contains images used to show examples of usage.)
    |
    |--                 (Other files with written examples.)

--src/
    |
    |--bin/             (Contains compiled programs: explorer and simulator.)
    |
    |--build/
    |   |
    |   |--client/      (Contains *.o and *.d files needed to build the client library.)
    |   |
    |   |--explorer/    (Contains *.o files needed to build the explorer.)
    |   |
    |   |--json/json.o
    |   |
    |   |--simulator    (Contains *.o and *.d files needed to build the simulator.)
    |
    |--client/          (Contains *.cpp, *.h files encapsulating the Eclipse Paho MQTT client and Makefile.)
    |
    |--explorer/
    |   |
    |   |--moc/         (Contains generated moc_* files by QT.)
    |   |
    |   |--resources/   (Contains *.ui, *.qrc and *.png files specifying the design of the user interface, 
    |   |                generated Makefile and .qmake.stash.)
    |   |
    |   |--rrc/qrc_resources.cpp
    |   |
    |   |--ui/          (Contains generated ui_* files by QT.)
    |   |
    |   |--             (Contains *.cpp, *.h files implementing the MQTT explorer application and explorer.pro file used   
    |                    for generating Makefile for this directory.)
    |
    |--json/            
    |   |
    |   |--json/        (Contains header files for the jsoncpp library.)
    |   |
    |   |--             (Contains the jsoncpp.cpp source code and Makefile.)
    |
    |--libs/
    |   |
    |   |--client/libclient.a
    |   |
    |   |--json/libjson.a
    |
    |--simulator/
    |   |
    |   |--images/      (Contains images send by simulated cameras.)
    |   |
    |   |--             (Contains *.cpp, *.h files implementing the simulator, config.json and Makefile.)
    |
    |--Makefile

--Makefile

--README.txt

## Documentation
The documentation can be generated with commands 'make doxygen' or 'make doc'. To generate also graphs of dependencies, 
install the Graphviz software from https://graphviz.org/, or with command 'sudo apt install graphviz'.

## Examples
Examples are written in the examples/examples.cpp file, the examples/message_template.json file, the 
examples/simulator_template.json file and image examples are in the examples/images directory. All of these examples can be 
read on the main page of the generated documentation, which is far more convinient than going through the named files.

## Makefile Usage
See the examples.

## Simulator Usage
For specific cases of usage see the examples.
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
   --locks or -k:            Include or exclude locks.  
   --move or -m:             Include or exclude move sensors.  
   --relays or -r:           Include or exclude relays.  
   --thermometers or -t:     Include or exclude thermometers.  
   --thermostats or -e:      Include or exclude thermostats.  
   --valves or -u:           Include or exclude valves.  
   --wattmeters or -w:       Include or exclude wattmeters.

## MQTT explorer usage
For specific cases of usage see the examples.
### run in the /src/explorer directory as: ../bin/explorer
### or run from anywhere and specify the configuration file as an argument: ./explorer "path/to/configuration/file"
The application can be also started in verbose mode if -v or --verbose is specified in the command line arguments. If the 
configuration file cannot be opened, new file 'config.json' will be created and a state of the dashboard will be saved 
there at termination.
