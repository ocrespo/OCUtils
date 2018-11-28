/*
 * ThreadSwapperSingle.h
 *
 *  Created on: 28 Nov 2018
 *      Author: Oscar Crespo
 */

#ifndef SRC_THREADUTILS_THREADSWAPPERSINGLE_H_
#define SRC_THREADUTILS_THREADSWAPPERSINGLE_H_

#include <concurrentqueue/readerwriterqueue.h>

#include "ThreadSwapper.h"

namespace ocutils {

/**
 * Swap the execution of the given Event to another thread
 */
class ThreadSwapperSingle : public ThreadSwapper<moodycamel::ReaderWriterQueue<Event*>>{
public:
	inline ThreadSwapperSingle(int reserve = 20, int sleep_for_ms = 500):
		ThreadSwapper(reserve,sleep_for_ms){}
	inline virtual ~ThreadSwapperSingle(){

	}

protected:


private:



};

} /* namespace ocutils */

#endif /* SRC_THREADUTILS_THREADSWAPPERSINGLE_H_ */
