
#include "main.h"

// sudo systemctl stop mosquitto.service

//const std::string SERVER_ADDRESS("tcp://broker.emqx.io:1883");
const std::string SERVER_ADDRESS("tcp://localhost:1883");
const std::string TOPIC("test/#");
const std::string CLIENT_ID("client_id_1");

class Test
{
	public:
		static void on_success_cb(void *object, const mqtt::token& tok)
		{
			Test *test = static_cast<Test *>(object);
			test->on_success(tok);
		}

		static void on_failure_cb(void *object, const mqtt::token& tok)
		{
			Test *test = static_cast<Test *>(object);
			test->on_failure(tok);
		}

		static void on_connected_cb(void *object, const std::string& cause)
		{
			Test *test = static_cast<Test *>(object);
			test->on_connected(cause);
		}

		static void on_message_arrived_cb(void *object, const std::string &topic, const MessageData &message, FileType type)
		{
			Test *test = static_cast<Test *>(object);
			test->on_message_arrived(topic, message, type);
		}

		static void on_connection_lost_cb(void *object, const std::string& cause)
		{
			Test *test = static_cast<Test *>(object);
			test->on_connection_lost(cause);
		}

		static void on_delivery_completed_cb(void *object, mqtt::delivery_token_ptr token)
		{
			Test *test = static_cast<Test *>(object);
			test->on_delivery_completed(token);
		}

		Test(int num) : num(num) {}
	
	private:
		void on_success(const mqtt::token& tok)
		{
			(void)tok;
			std::cerr << "on success callback: called: " << num++ << std::endl;
		}

		void on_failure(const mqtt::token& tok)
		{
			(void)tok;
			std::cerr << "on failure callback: called: " << num++ << std::endl;
		}

		void on_connected(const std::string& cause)
		{
			std::cerr << "on_connected: " << cause << std::endl;
		}

		void on_message_arrived(const std::string &topic, const MessageData &message, FileType type)
		{
			(void)message;
			(void)type;
			std::cerr << "on_message_arrived - topic: " << topic << std::endl;
		}

		void on_connection_lost(const std::string& cause)
		{
			std::cerr << "on_connection_lost: " << cause << std::endl;
		}

		void on_delivery_completed(mqtt::delivery_token_ptr token)
		{
			std::cerr << "on_delivery_completed: " << token.get()->get_message()->get_payload_str() << std::endl;
		}

		int num;
};

void func(void *class_object, const mqtt::token& tok)
{
	(void)class_object;
	(void)tok;
	std::cerr << "func call" << std::endl;
}

int main()
{
	mqtt::connect_options options;
	options.set_clean_session(true);

	Test test(153);

	std::mutex mutex;
	Listener listener(&test, &Test::on_success_cb, &Test::on_failure_cb);

	Listeners listeners(listener, listener, listener, listener, listener);
	Callbacks callbacks(&test, &Test::on_connected_cb, &test, &Test::on_message_arrived_cb, 
	 					&test, &Test::on_connection_lost_cb, &test, &Test::on_delivery_completed_cb);
	Client client(SERVER_ADDRESS, CLIENT_ID, listeners, callbacks, FileType::ALL);

	try 
	{
		std::cout << "Connecting to the MQTT server..." << std::endl;
		client.connect(options);
	}
	catch (const mqtt::exception& exc) 
	{
		std::cerr << "\nERROR: Unable to connect to MQTT server: '"
			<< SERVER_ADDRESS << "'" << exc << std::endl;
		return 1;
	}

	// press 's' and enter after successfull connection
	while (std::tolower(std::cin.get()) != 's')
		;

	client.subscribe("test/#", 1);
	client.subscribe("#", 1);
	client.subscribe("temp/#", 1);

	// press 'p' and enter after sucessfull subscription 
	while (std::tolower(std::cin.get()) != 'p')
		;
	
	client.publish("hello", "Hello World!");
	client.publish("test/publish", "Test of publishing.");

	// press 'u' and enter after publish
	while (std::tolower(std::cin.get()) != 'u')
		;
	
	client.unsubscribe("unknown");
	client.unsubscribe("test/#");

	client.publish("test/publish", "Retest of publishing.");

	// press 'q' and enter to disconect and quit
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

	std::cerr << "main ends" << std::endl;
 	exit(0);
}

