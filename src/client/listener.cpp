
/**
 * @file        listener.cpp                                
 * Case:        VUT, FIT, ICP, project                      <br>
 * Author:      David Mihola, xmihol00@stud.fit.vutbr.cz    <br>
 * Date:        summer semester 2021                        <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0    <br>
 * @brief       API encapsulating the mqtt paho listener used for success/failure callbacks.
 **/

#include "listener.h"

Listener::Listener(void *class_object, OnSuccessCallback on_success_callback, 
                           OnFailureCallback on_failure_callback)
             : _class_object(class_object), _on_success_callback(on_success_callback),
               _on_failure_callback(on_failure_callback) {}

void Listener::on_success(const mqtt::token& token)
{
    _on_success_callback(_class_object, token);
}

void Listener::on_failure(const mqtt::token& token)
{
    _on_failure_callback(_class_object, token);
}
