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
			queue(reserve),
			stop(false),
			thread(&ThreadSwapper::loop,this),
			sleep(sleep_for_ms){
	};

private:

	void loop(){
		Event* event;
		while(!stop){
			if(queue.wait_dequeue_timed(event,std::chrono::milliseconds(500))){
				event->call();
				delete event;
			}
		}
	}

	T queue;

	bool stop;
	std::thread thread;
	int sleep;

};

} /* namespace threads */

#endif /* SRC_THREADUTILS_THREADSWAPPER_H_ */
