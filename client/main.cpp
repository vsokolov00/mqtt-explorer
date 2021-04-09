
#include "main.h"

// sudo systemctl stop mosquitto.service

const std::string SERVER_ADDRESS("tcp://broker.emqx.io:1883");
const std::string TOPIC("test/#");

int main()
{
	mqtt::connect_options options;
	options.set_clean_session(true);

	ConnectListener connect_listener;
	SubscribeListener subscribe_listener;
	PublishListener publish_listener;
	UnsubscribeListener unsubscribe_listener;

    ClientAPI API(connect_listener, subscribe_listener, unsubscribe_listener, publish_listener);

	Client client(options, API, SERVER_ADDRESS);

	try 
	{
		std::cout << "Connecting to the MQTT server..." << std::endl;
		client.connect();
	}
	catch (const mqtt::exception& exc) 
	{
		std::cerr << "\nERROR: Unable to connect to MQTT server: '"
			<< SERVER_ADDRESS << "'" << exc << std::endl;
		return 1;
	}

	while (std::tolower(std::cin.get()) != 's')
		;

	client.subscribe("test/#", 1);
	client.subscribe("#", 1);
	client.subscribe("temp/#", 1);

	while (std::tolower(std::cin.get()) != 'p')
		;
	
	client.publish("hello", "Hello World!");
	client.publish("test/publish", "Test of publishing.");

	while (std::tolower(std::cin.get()) != 'u')
		;
	
	client.unsubscribe("unknown");
	client.unsubscribe("test/#");

	client.publish("test/publish", "Retest of publishing.");

	while (std::tolower(std::cin.get()) != 'q')
		;

	try 
	{
		// Disconnect
		std::cout << "\nDisconnecting from the MQTT server..." << std::flush;
		client.disconnect();
		std::cout << "OK" << std::endl;
	}
	catch (const mqtt::exception& exc) {
		std::cerr << exc << std::endl;
		return 1;
	}

 	return 0;
}

