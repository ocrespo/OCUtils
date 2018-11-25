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

/**
 * Store the parameters to call the callback later
 */
template <typename ...Ts>
class EventStore: public EventUniq<Ts...> {

public:

	/**
	 * Default constructor
	 */
	EventStore() : EventUniq<Ts...>(){

	}

	/**
	 * Create and event with the given callback, need to set the args later
	 * @param arg
	 */
	EventStore(std::function<void(Ts...)> arg) : EventUniq<Ts...>(arg){
	}

	virtual ~EventStore(){

	}

	/**
	 * Call the callback with the saved args
	 * @return
	 */
	virtual bool call() override{
		if(this->function){
			callTuple(args,std::index_sequence_for<Ts...>());
			return true;
		}
		return false;
	}

	/**
	 * Set the values to use on the callback
	 * @param values
	 */
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
