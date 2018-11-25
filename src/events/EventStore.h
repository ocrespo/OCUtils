/*
 * EventStore.h
 *
 *  Created on: 13 Jan 2018
 *      Author: Oscar Crespo
 */

#ifndef EVENTSTORE_H_
#define EVENTSTORE_H_

//std
#include <functional>
#include <utility>


#include "EventUniq.h"

#include <tuple>

template <typename ...Ts>
class EventStore: public EventUniq<Ts...> {

public:

	EventStore() : EventUniq<Ts...>(){

	}

	EventStore(std::function<void(Ts...)> arg) : EventUniq<Ts...>(arg){
	}

	virtual ~EventStore(){

	}

	virtual bool call() override{
		if(this->function){
			callTuple(args,std::index_sequence_for<Ts...>());
			return true;
		}
		return false;
	}

	void setValues(Ts... values){
		args = std::make_tuple(values...);
	}

protected:


private:

	template<std::size_t... Is>
	void callTuple(const std::tuple<Ts...>& tuple,std::index_sequence<Is...>) {
		this->function(std::get<Is>(tuple)...);
	}

	std::tuple<Ts...> args;

};



#endif /* SRC_EVENTS_EVENTSTORE_H_ */
