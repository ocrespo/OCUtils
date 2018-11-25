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

template <typename ...Ts>
class EventList: public Event {

public:

	EventList(){
		functionList.reserve(5);
	}

	EventList(int size){
		functionList.reserve(size);
	}


	virtual ~EventList(){};



	bool registerCall(const std::function<void(Ts...)>& call, int key){
		auto item_found (findElement(key));

		if( item_found == functionList.end() ){
			functionList.emplace_back(std::make_pair(key,call));

			return true;
		}

		return false;


	}

	bool unregisterCall(int key){
		auto item_found (findElement(key));

		if( item_found != functionList.end() ){
			functionList.erase(item_found);

			return true;
		}

		return false;
	}

	void clean(){
		functionList.clear();
	}

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

	auto findElement(int key){
		return std::find_if(functionList.begin(), functionList.end(),
				[&key](const element_t &item){
					return item.first == key;
				});
	}

	using element_t = std::pair<int, std::function<void(Ts...)>>;

	std::vector<element_t> functionList;

};



#endif /* SRC_EVENTS_EVENTLIST_H_ */
