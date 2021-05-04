
/**
 * @file        listener.h
 * Case:        VUT, FIT, ICP, project                          <br>
 * Author:      David Mihola, xmihol00@stud.fit.vutbr.cz        <br>
 * Date:        summer semester 2021                            <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0        <br>
 * @brief       Declaration of types and classes for listener.cpp and other files.
 **/

#pragma once

#include <string>
#include <mqtt/async_client.h>

using OnSuccessCallback = void(*)(void *, const mqtt::token&);
using OnFailureCallback = void(*)(void *, const mqtt::token&);

using OnConnectionFailureCB = OnFailureCallback;
using OnSubscribeSucessCB = OnSuccessCallback;
using OnSubscribeFailureCB = OnFailureCallback;
using OnUnsubscribeSucessCB = OnSuccessCallback;
using OnUnsubscribeFailureCB = OnFailureCallback;
using OnPublishSucessCB = OnSuccessCallback;
using OnPublishFailureCB = OnFailureCallback;
using OnDisconectSucessCB = OnSuccessCallback;
using OnDisconectFailureCB = OnFailureCallback;

/**
 * @brief A Listener callback class which derives from the virtual mqtt class, overrides the virtual methods
 *        to call registered success/failure callbacks.
 **/
class Listener : public virtual mqtt::iaction_listener
{
    private:
        void *_class_object;                        ///< callback object
        OnSuccessCallback _on_success_callback;     ///< callback when operation succeeds
        OnFailureCallback _on_failure_callback;     ///< callback when operation fails

        /**
         * @brief Function called when an operation fails.
         * @param token the token describing the operation.
         **/
        void on_failure(const mqtt::token& token) override;

        /**
         * @brief Function called when an operation succeeds
         * @param token the token describing the operation.
         **/
        void on_success(const mqtt::token& token) override;

    public:
        Listener(void *class_object, OnSuccessCallback on_success_callback, OnFailureCallback on_failure_callback);
};
