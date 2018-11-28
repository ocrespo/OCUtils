/*
 * EventList_test.cpp
 *
 *  Created on: 13 Jan 2018
 *      Author: Oscar Crespo
 */

#include <gtest/gtest.h>

#include <events/EventList.h>

class EventListTest : public ::testing::Test {

public:
	EventListTest():
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

TEST_F(EventListTest, Test) {

    EXPECT_EQ(summoned,false);
    EXPECT_EQ(count_summoned,0);

    ocutils::EventList<bool> event(2);

    bool ret{event.callArgs(true)};
    EXPECT_EQ(ret,false);

    bool ret_regis{event.registerCall(std::bind(&EventListTest::summon,this,std::placeholders::_1),0)};
    EXPECT_EQ(ret_regis,true);
    ret_regis = event.registerCall(std::bind(&EventListTest::summon,this,std::placeholders::_1),0);
    EXPECT_EQ(ret_regis,false);
    ret_regis = event.registerCall(std::bind(&EventListTest::summon,this,std::placeholders::_1),1);
    EXPECT_EQ(ret_regis,true);

    ret = event.callArgs(true);
    EXPECT_EQ(ret,true);
    EXPECT_EQ(summoned,true);
    EXPECT_EQ(count_summoned,2);

    ret_regis = event.unregisterCall(3);
    EXPECT_EQ(ret_regis,false);
    ret_regis = event.unregisterCall(1);
    EXPECT_EQ(ret_regis,true);
    ret_regis = event.unregisterCall(1);
    EXPECT_EQ(ret_regis,false);

    ret = event.callArgs(false);
	EXPECT_EQ(ret,true);
	EXPECT_EQ(summoned,false);
	EXPECT_EQ(count_summoned,3);

    ret_regis = event.unregisterCall(0);
    EXPECT_EQ(ret_regis,true);

    ret = event.callArgs(false);
	EXPECT_EQ(ret,false);
	EXPECT_EQ(summoned,false);
	EXPECT_EQ(count_summoned,3);


}
