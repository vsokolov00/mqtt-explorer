#include "mainwindow.h"
#include <string>
#include <QApplication>

//const std::string ADDRESS	{ "tcp://localhost:7412" };
//const std::string CLIENT_ID		{ "test_client" };
//const std::string TOPIC 			{ "hello" };

//const int  QOS = 1;

int main(int argc, char *argv[])
{
//    const std::string TOPIC { "hello" };
//    const std::string PAYLOAD1 { "Hello World!" };

//    const char* PAYLOAD2 = "Hi there!";

    // Create a client

//    mqtt::client cli(ADDRESS, CLIENT_ID);

//    mqtt::connect_options connOpts;
//    connOpts.set_keep_alive_interval(20);
    //connOpts.set_clean_session(true);

//    try
//    {
//        // Connect to the client

//        cli.connect();
//        //cli.connect(connOpts);

//        // Publish using a message pointer.

//        auto msg = mqtt::make_message(TOPIC, PAYLOAD1);
//        msg->set_qos(QOS);

//        cli.publish(msg);

//        // Now try with itemized publish.

//        cli.publish(TOPIC, PAYLOAD2, strlen(PAYLOAD2), 0, false);

//    }
//    catch (const mqtt::exception& exc) {
//        std::cerr << "Error: " << exc.what() << " ["
//            << exc.get_reason_code() << "]" << std::endl;
//        return 1;
//    }

//    // create some topics
//    mqtt::string_collection topics({"test", "temp", "speed", "wind"});
//    // add one more topic
//    topics.push_back("lol");
//    // subsribe to the topics
//    cli.subscribe(topics);

//    while (true) // TODO loop termination
//    {
//        // reciev a message from subscribed topics
//        mqtt::const_message_ptr message_ptr = cli.consume_message();
//        // print the recieved message
//        std::cout << "message on topic " << message_ptr.get()->get_topic() << ": " << message_ptr.get()->get_payload_str() << std::endl;
//    }
    
//    cli.disconnect();
    //return 0;

    // TODO incorporate the mechanismus above the GUI app
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
