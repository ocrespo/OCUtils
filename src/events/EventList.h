/*
 * EventList.h
 *
 *  Created on: 13 Jan 2018
 *      Author: Oscar Crespo
 */

#ifndef SRC_EVENTS_EVENTLIST_H_
#define SRC_EVENTS_EVENTLIST_H_


#include "Event.h"

//std
#include <functional>
#include <vector>
#include <algorithm>

namespace ocutils {


/**
 * Store a list of callbacks
 */
template <typename ...Ts>
class EventList: public Event {

public:

	/**
	 * Create an empty (pre-reserve 5)
	 */
	EventList(){
		functionList.reserve(5);
	}

	/**
	 * Initialise the give size
	 * @param size
	 */
	EventList(int size){
		functionList.reserve(size);
	}


	virtual ~EventList(){};

	/**
	 * Register a call
	 * @param call
	 * @param key the key to identify the callback
	 * @return true on success
	 */
	bool registerCall(const std::function<void(Ts...)>& call, int key){
		auto item_found (findElement(key));

		if( item_found == functionList.end() ){
			functionList.emplace_back(std::make_pair(key,call));

			return true;
		}

		return false;
	}

	/**
	 * Unregister a call
	 * @param key the key to identify the callback
	 * @return true on success
	 */
	bool unregisterCall(int key){
		auto item_found (findElement(key));

		if( item_found != functionList.end() ){
			functionList.erase(item_found);

			return true;
		}

		return false;
	}

	/**
	 * Remove all the registered calls
	 */
	void clean(){
		functionList.clear();
	}

	/**
	 * Call the events
	 * @param args the arguments to use
	 * @return true if there is any event to call
	 */
	bool callArgs(Ts... args){
		if (functionList.empty()){
			return false;
		}

		for(auto it = functionList.cbegin(); it != functionList.cend(); ++it){
			it->second(args...);
		}

		return true;
	}



protected:


private:

	/**
	 * Find the event with the given key
	 * @param key
	 * @return
	 */
	auto findElement(int key){
		return std::find_if(functionList.begin(), functionList.end(),
				[&key](const element_t &item){
					return item.first == key;
				});
	}

	using element_t = std::pair<int, std::function<void(Ts...)>>;

	std::vector<element_t> functionList;

};

}  /* namespace ocutils */


#endif /* SRC_EVENTS_EVENTLIST_H_ */
