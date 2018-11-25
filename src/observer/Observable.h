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

template<typename K,class T>
class Observable {
public:
	virtual ~Observable() {
		for(auto it = observers.begin(); it != observers.end();++it){
			if(*it != NULL){
				delete *it;
			}
		}
	}

protected:

    Observable(): observers(static_cast<int>(K::Max),NULL){

    }

	Observable(K key,T observer): observers(static_cast<int>(K::Max),NULL){
		addObserver_priv(key,observer);
	}

	bool addObserver(K key, T observer){
		return addObserver_priv(key,observer);
	}

	bool addObserver_priv(K key, T observer){
		size_t pos (static_cast<int>(key));
		if(pos >= observers.size()){
			return false;
		}
		bool ret(false);
		if(observers[pos] == NULL){
			observers[pos] = observer;
			ret = true;
		}
		return ret;
	}


	template<template<typename...> class Cast,typename ...args,typename callback>
	bool registerObserver(K key,const callback& event,uint32_t obsKey){
		size_t pos (static_cast<int>(key));
		if(pos >= observers.size() || observers[pos] == NULL){
			return false;
		}
		const std::function<void(args...)> a = event;
		Cast<args...>* cast = reinterpret_cast<Cast<args...>*>(observers[pos]);
		return cast->registerCall(event,obsKey);
	}

	bool removeObserver(K key){
		size_t pos (static_cast<int>(key));
		if(pos >= observers.size() || observers[pos] == NULL){
			return false;
		}
		T obj(observers[pos]);

		observers[pos] = NULL;

		delete obj;

		return true;
	}

	template<template<typename...> class Cast,typename ...args>
	bool unregisterObserver(K key,uint32_t obsKey){
		size_t pos (static_cast<int>(key));
		if(pos >= observers.size() || observers[pos] == NULL){
			return false;
		}

		return ((Cast<args...>*)observers[pos])->unregisterCall(obsKey);
	}

	template<template<typename...> class Cast,typename ...args>
	bool donotify(K key ,args... values){
		size_t pos (static_cast<int>(key));
		if(pos >= observers.size() || observers[pos] == NULL){
			return false;
		}

		Cast<args...>* cast = reinterpret_cast<Cast<args...>*>(observers[pos]);
		return cast->callArgs(values...);
	}

private:

	std::vector<T> observers;

};

#endif /* SRC_OBSERVER_OBSERVABLE_H_ */
