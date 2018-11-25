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

template <typename ...Ts>
class EventUniq: public Event {

public:

	EventUniq(): Event(), function(nullptr){}

	EventUniq(const std::function<void(Ts...)>& call ) : Event(), function(call){}

	virtual ~EventUniq(){};


	bool registerCall(const std::function<void(Ts...)>& call,UNUSED int key = 0){
		function = call;
		return true;
	}

	bool unregisterCall(UNUSED int key = 0){
		function = nullptr;

		return true;
	}

	void clean(){
		unregisterCall();
	}

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
