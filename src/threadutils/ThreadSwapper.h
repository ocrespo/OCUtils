/*
 * ThreadSwapper.h
 *
 *  Created on: 28 Nov 2018
 *      Author: Oscar Crespo
 */

#ifndef SRC_THREADUTILS_THREADSWAPPER_H_
#define SRC_THREADUTILS_THREADSWAPPER_H_

#include <thread>

#include "../events/Event.h"

namespace ocutils {

template<class T>
class ThreadSwapper {
public:
	virtual ~ThreadSwapper(){
		if(!stop){
			stop = true;
			if(thread.joinable()){
				thread.join();
			}
		}
	}

	void execute(Event* event){
		queue.enqueue(event);
	}

protected:

	ThreadSwapper(int reserve = 20, int sleep_for_ms = 500):
			stop(false),
			thread(&ThreadSwapper::loop,this),
			sleep(sleep_for_ms),
			queue(reserve){
	};

private:

	void loop(){
		Event* event(nullptr);
		while(!stop){
			queue.wait_dequeue(event);
			event->call();
			delete event;
		}
	}

	bool stop;
	std::thread thread;
	int sleep;

	T queue;
};

} /* namespace threads */

#endif /* SRC_THREADUTILS_THREADSWAPPER_H_ */
