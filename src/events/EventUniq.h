/*
 * EventUniq.h
 *
 *  Created on: 13 Jan 2018
 *      Author: Oscar Crespo
 */

#ifndef EVENTUNIQ_H_
#define EVENTUNIQ_H_

#include "Event.h"

//std
#include <functional>

#include "../utils/CompilerOptions.h"

/**
 * Event to call a individual function
 */
template <typename ...Ts>
class EventUniq: public Event {

public:

	EventUniq(): Event(), function(nullptr){}

	EventUniq(const std::function<void(Ts...)>& call ) : Event(), function(call){}

	virtual ~EventUniq(){};

	/**
	 * Assign the given callback
	 * @param call
	 * @param key
	 * @return always true
	 */
	bool registerCall(const std::function<void(Ts...)>& call,UNUSED int key = 0){
		function = call;
		return true;
	}

	/**
	 * Remove the current assigned callback
	 * @param key unused
	 * @return always true
	 */
	bool unregisterCall(UNUSED int key = 0){
		function = nullptr;

		return true;
	}

	/**
	 * Unregister the callback
	 */
	void clean(){
		unregisterCall();
	}

	/**
	 * Call the callback with the given args
	 * @param args
	 * @return
	 */
	bool callArgs(Ts... args){
		if(function){
			function(args...);
			return true;
		}
		return false;
	}

protected:

	std::function<void(Ts...)> function;


private:



};

#endif /* SRC_EVENTS_EVENTUNIQ_H_ */
