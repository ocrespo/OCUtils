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

template <typename ...Ts>
class EventUniq: public Event {

public:

	EventUniq(): Event(), function(nullptr){}

	EventUniq(const std::function<Ts...>& call) : Event(), function(call){}


	virtual ~EventUniq(){};


	bool registerCall(const std::function<Ts...>& call, int key = 0){
		function = call;
		return true;
	}

	bool unregisterCall(int key = 0){
		function = nullptr;

		return true;
	}

	void clean(){
		unregisterCall();
	}

	bool call(Ts... args){
		if(function){
			function(args...);
			return true;
		}
		return false;
	}


protected:

	std::function<Ts...> function;


private:



};

#endif /* SRC_EVENTS_EVENTUNIQ_H_ */
