/*
 * observer.h
 *
 *  Created on: 13 Jan 2018
 *      Author: Oscar Crespo
 */

#ifndef SRC_OBSERVER_OBSERVABLE_H_
#define SRC_OBSERVER_OBSERVABLE_H_

#include <vector>
#include <stdint.h>
#include <functional>

/**
 * Observable class, K is an enum with last item called "Max" and T a pointer to an event
 */
template<typename K,class T>
class Observable {
public:
	virtual ~Observable() {
		for(auto it = observers.begin(); it != observers.end();++it){
			if(*it != nullptr){
				delete *it;
			}
		}
	}

protected:

	/**
	 * Create a empty observer
	 */
    Observable(): observers(static_cast<int>(K::Max),nullptr){

    }

    /**
     * Create and add the given observer
     * @param key
     * @param observer
     */
	Observable(K key,T observer): observers(static_cast<int>(K::Max),nullptr){
		addObserver_priv(key,observer);
	}

	/**
	 * Add an observer into the list if the is no other observer
	 * @param key
	 * @param observer
	 * @return true if get added, false otherwise (already exist)
	 */
	bool addObserver(K key, T observer){
		return addObserver_priv(key,observer);
	}

	/**
	 * Register an event into the observer (for EventList only)
	 * @param key
	 * @param obsKey the observer key, has to be unique
	 * @param event
	 * @return true if can be register, false otherwise
	 */
	template<template<typename...> class Cast,typename ...args,typename callback>
	bool registerCall(K key,uint32_t obsKey,const callback& event){
		size_t pos (static_cast<int>(key));
		if(pos >= observers.size() || observers[pos] == nullptr){
			return false;
		}
		const std::function<void(args...)> a = event;
		Cast<args...>* cast = reinterpret_cast<Cast<args...>*>(observers[pos]);
		return cast->registerCall(event,obsKey);
	}

	/**
	 * Remove the observer
	 * @param key
	 * @return true on success
	 */
	bool removeObserver(K key){
		size_t pos (static_cast<int>(key));
		if(pos >= observers.size() || observers[pos] == nullptr){
			return false;
		}
		T obj(observers[pos]);

		observers[pos] = nullptr;

		delete obj;

		return true;
	}

	/**
	 * Unregister an event from the observer (for EventList only)
	 * @param key
	 * @param obsKey
	 * @return true on success
	 */
	template<template<typename...> class Cast,typename ...args>
	bool unregisterCall(K key,uint32_t obsKey){
		size_t pos (static_cast<int>(key));
		if(pos >= observers.size() || observers[pos] == nullptr){
			return false;
		}

		return ((Cast<args...>*)observers[pos])->unregisterCall(obsKey);
	}

	/**
	 * Call the observers
	 * @param key
	 * @param values
	 * @return true on success;
	 */
	template<template<typename...> class Cast,typename ...args>
	bool donotify(K key ,args... values){
		size_t pos (static_cast<int>(key));
		if(pos >= observers.size() || observers[pos] == nullptr){
			return false;
		}

		Cast<args...>* cast = reinterpret_cast<Cast<args...>*>(observers[pos]);
		return cast->callArgs(values...);
	}

private:

	/**
	 * Implementation to add an observer
	 * @param key
	 * @param observer
	 * @return true on success
	 */
	bool addObserver_priv(K key, T observer){
		size_t pos (static_cast<int>(key));
		if(pos >= observers.size()){
			return false;
		}
		bool ret(false);
		if(observers[pos] == nullptr){
			observers[pos] = observer;
			ret = true;
		}
		return ret;
	}

	std::vector<T> observers;

};

#endif /* SRC_OBSERVER_OBSERVABLE_H_ */
