/*
 * EventStore_test.cpp
 *
 *  Created on: 13 Jan 2018
 *      Author: Oscar Crespo
 */

#include <gtest/gtest.h>

#include <events/EventStore.h>

class EventStoreTest : public ::testing::Test {

public:
	EventStoreTest():
		count_summoned(0),
		summoned(false)
	{};

	void summon(bool summon){
		++count_summoned;
		summoned = summon;
	}

protected:

    int8_t count_summoned;
    bool summoned;

private:

};

TEST_F(EventStoreTest, Test) {

    EXPECT_EQ(summoned,false);
    EXPECT_EQ(count_summoned,0);

    ocutils::EventStore<bool> event(std::bind(&EventStoreTest::summon,this,std::placeholders::_1));

    event.setValues(true);

    bool ret{event.call()};

    EXPECT_EQ(ret,true);
    EXPECT_EQ(summoned,true);
    EXPECT_EQ(count_summoned,1);

    event.setValues(false);

    ret = event.call();

    EXPECT_EQ(ret,true);
    EXPECT_EQ(summoned,false);
    EXPECT_EQ(count_summoned,2);
}
