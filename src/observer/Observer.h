/*
 * Observer.h
 *
 *  Created on: 30 Nov 2018
 *      Author: Oscar Crespo
 */

#ifndef SRC_OBSERVER_OBSERVER_H_
#define SRC_OBSERVER_OBSERVER_H_

namespace ocutils {


class Observer{
public:
	inline Observer(){
		id = Observer::id_counter++;

	}

	inline virtual ~Observer(){}

	inline int getObserverId(){
		return id;
	}

protected:

	int id;

	static int id_counter;

};

inline int Observer::id_counter = 0;


}  /* namespace ocutils */



#endif /* SRC_OBSERVER_OBSERVER_H_ */
