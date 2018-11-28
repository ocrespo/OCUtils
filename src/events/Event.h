/*
 * Event.h
 *
 *  Created on: 13 Jan 2018
 *      Author: Oscar Crespo
 */

#ifndef EVENT_H_
#define EVENT_H_

#include <assert.h>

namespace ocutils {

class Event{

public:

	virtual ~Event(){};

	virtual bool call(){
		assert(true == false);
		return false;
	};

protected:

	Event(){};

private:



};

}  /* namespace ocutils */



#endif /* SRC_EVENTS_EVENT_H_ */
