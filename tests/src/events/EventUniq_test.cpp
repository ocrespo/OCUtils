/*
 * EventUniq_test.cpp
 *
 *  Created on: 13 Jan 2018
 *      Author: Oscar Crespo
 */

#include <gtest/gtest.h>

#include <events/EventUniq.h>

class EventUniqTest : public ::testing::Test {

public:
	EventUniqTest():
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

TEST_F(EventUniqTest, Test) {


    EXPECT_EQ(summoned,false);
    EXPECT_EQ(count_summoned,0);

    EventUniq<bool> event(std::bind(&EventUniqTest::summon,this,std::placeholders::_1));

    bool ret{event.callArgs(true)};

    EXPECT_EQ(ret,true);
    EXPECT_EQ(summoned,true);
    EXPECT_EQ(count_summoned,1);

    ret = event.callArgs(false);

    EXPECT_EQ(ret,true);
    EXPECT_EQ(summoned,false);
    EXPECT_EQ(count_summoned,2);

}

