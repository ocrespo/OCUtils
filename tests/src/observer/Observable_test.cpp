/*
 * Observable_test.cpp
 *
 *  Created on: 25 Nov 2018
 *      Author: Oscar Crespo
 */

#include <gtest/gtest.h>

#include <observer/Observable.h>

#include <events/EventList.h>
#include <events/EventUniq.h>


enum class EObserverTest{
	Increase,
	Reduce,
	Clear,

	Max
};

class ObservableTest : public ::testing::Test,
						public Observable<EObserverTest,Event*>{

public:
	ObservableTest():
		count_summoned(0),
		summoned(false)
	{};

	void summonIncrease(bool summon){
		++count_summoned;
		summoned = summon;
	}

	void summonDecrease(bool summon){
		--count_summoned;
		summoned = summon;
	}

	void summonClear(){
		count_summoned = 0;
		summoned = false;
	}

protected:

    int8_t count_summoned;
    bool summoned;

private:

};

TEST_F(ObservableTest, Test) {

    EXPECT_EQ(summoned,false);
    EXPECT_EQ(count_summoned,0);

    bool ret{addObserver(EObserverTest::Increase,new EventList<bool>)};
    EXPECT_EQ(ret,true);
    ret = addObserver(EObserverTest::Reduce,new EventUniq<bool>(std::bind(&ObservableTest::summonIncrease,this,std::placeholders::_1)));
    EXPECT_EQ(ret,true);
    ret = addObserver(EObserverTest::Clear,new EventUniq<>(std::bind(&ObservableTest::summonClear,this)));
    EXPECT_EQ(ret,true);
    EventUniq<bool>* event{new EventUniq<bool>(std::bind(&ObservableTest::summonDecrease,this,std::placeholders::_1))};
    ret = addObserver(EObserverTest::Reduce,event);
    EXPECT_EQ(ret,false);
    delete event;

	ret = donotify<EventList,bool>(EObserverTest::Increase,true);
    EXPECT_EQ(ret,false);
    EXPECT_EQ(summoned,false);
    EXPECT_EQ(count_summoned,0);

    ret = donotify<EventUniq,bool>(EObserverTest::Reduce,true);
    EXPECT_EQ(ret,true);
    EXPECT_EQ(summoned,true);
    EXPECT_EQ(count_summoned,1);

    ret = registerCall<EventUniq,bool>(EObserverTest::Reduce,0,std::bind(&ObservableTest::summonDecrease,this,std::placeholders::_1));
    ret = donotify<EventUniq,bool>(EObserverTest::Reduce,false);
    EXPECT_EQ(ret,true);
    EXPECT_EQ(summoned,false);
    EXPECT_EQ(count_summoned,0);

    ret = registerCall<EventList,bool>(EObserverTest::Increase,0,std::bind(&ObservableTest::summonIncrease,this,std::placeholders::_1));
    EXPECT_EQ(ret,true);
    ret = registerCall<EventList,bool>(EObserverTest::Increase,0,std::bind(&ObservableTest::summonIncrease,this,std::placeholders::_1));
    EXPECT_EQ(ret,false);
    ret = registerCall<EventList,bool>(EObserverTest::Increase,1,std::bind(&ObservableTest::summonIncrease,this,std::placeholders::_1));
    EXPECT_EQ(ret,true);
    ret = registerCall<EventList,bool>(EObserverTest::Increase,2,std::bind(&ObservableTest::summonIncrease,this,std::placeholders::_1));
    EXPECT_EQ(ret,true);

	ret = donotify<EventList,bool>(EObserverTest::Increase,true);
    EXPECT_EQ(ret,true);
    EXPECT_EQ(summoned,true);
    EXPECT_EQ(count_summoned,3);

	ret = donotify<EventUniq>(EObserverTest::Clear);
    EXPECT_EQ(ret,true);
    EXPECT_EQ(summoned,false);
    EXPECT_EQ(count_summoned,0);

    ret = unregisterCall<EventList,bool>(EObserverTest::Increase,2);
    EXPECT_EQ(ret,true);
    ret = unregisterCall<EventList,bool>(EObserverTest::Increase,2);
    EXPECT_EQ(ret,false);

	ret = donotify<EventList,bool>(EObserverTest::Increase,true);
    EXPECT_EQ(ret,true);
    EXPECT_EQ(summoned,true);
    EXPECT_EQ(count_summoned,2);

}


