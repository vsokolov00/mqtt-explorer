
/**
 * @file        examples.cpp
 * Case:        VUT, FIT, ICP, project                          <br>
 * Author:      David Mihola, xmihol00@stud.fit.vutbr.cz        <br>
 * Date:        summer semester 2021                            <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0        <br>
 * @brief       Documentation of the mainpage of the generated HTML output with Doxygen.
 **/

/**
 * @mainpage MQTT Explorer and Simulator
 * @brief Applications implemented within The C++ Programming Language course at the Brno University of Technology.
 * @author David Mihola, xmihol00@stud.fit.vutbr.cz
 * @author Vladislav Sokolovskii, xsokol15@stud.fit.vutbr.cz
 * 
 * @tableofcontents
 * 
 * @section S1 User Interface Preview
 * 
 * \image html ../examples/images/login_window.png "The login window of the MQTT Explorer." <br>
 * 
 * \image html ../examples/images/main_window.png "The main window of the MQTT Explorer." <br>
 * 
 * \image html ../examples/images/dashboard.png "The dashboard of the MQTT Explorer." <br>
 *
 * \image html ../examples/images/add_device.png "The add new device dialog." <br>
 * 
 * \image html ../examples/images/delete_device.png "The delete device dialog." <br>
 *  
 * @section S2 Examples of Makefile Usage
 * @verbatim
 'make'                 - builds both the MQTT explorer as well as the simulator.
 'make explorer'        - builds the MQTT explorer.
 'make simulator'       - builds the simulator.
 'make run'             - builds both the MQTT explorer as well as the simulator and starts both applications.
                          The simulator is terminated by pressing ENTER, the MQTT explorer terminates when the window is closed.
 'make run-explorer'    - builds the MQTT explorer and starts the applications.
 'make run-simulator'   - builds the simulator and starts the applications.
 'make doc'             - generates Doxygen HTML documentation.
 'make doxygen'         - same as above.
 'make clean'           - removes all generated files apart from the MQTT explorer configuration file.
 'make pack'            - removes all generated files apart from the MQTT explorer configuration file and packs the repository.
 @endverbatim 
 *
 * @section S3 Examples of Usage of The MQTT Explorer
 * 
 * \image html ../examples/images/login_window_example.png "Example how to start a session." <br>
 * 
 * \image html ../examples/images/main_window_example.png "Example how to use the main window of the application." <br>
 * 
 * \image html ../examples/images/history_example.png "Example how to view a history of a topic and a detail of a specific message." <br>
 * 
 * \image html ../examples/images/dashboard_example.png "Example of displayed data on the dashboard." <br>
 * 
 * \image html ../examples/images/new_device_example.png "Example of how to add a new device to the dashboard." <br>
 * 
 * \image html ../examples/images/delete_device_example.png "Example of how delete a device or devices on the dashboard." <br>
 * 
 * @section S4 Examples of Usage of The Simulator
 * @subsection ss1 Startup examples
 * @verbatim
 './simulator --help'                      - displays help message. 
 './simulator -v'                          - starts the simulator in a 'verbose', in which the acctions of the simulator are printed to STDERR.
 './simulator --verbose'                   - same as above.
 './simulator -f file.json'                - uses 'file.json' as a configuration file.
 './simulator -s tcp://servername:port'    - connects to a server 'tcp://servername:port'.
 './simulator -l'                          - simulates only lights.
 './simulator -lcrt --wattmeters'          - simulates light, cameras, relays and wattmeters.
 './simulator --lights --cameras --relays --wattmeters --thermometers'    - same as above.
 './simulator -a --wattmeters'             - simulates all devices apart from wattmeters.
 './simulator --apart -wlk'                - simulates all devices apart from wattmeters, lights and locks.
 @endverbatim 
 * 
 * @subsection ss2 Template JSON file for simulated devices configuration.
 * @verbinclude ../examples/simulator_template.json <br>
 * 
 * @subsection ss3 Template JSON file for sending a message to a device.
 * @verbinclude ../examples/message_template.json <br>
 **/