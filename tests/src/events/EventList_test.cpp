/*
 * EventList_test.cpp
 *
 *  Created on: 13 Jan 2018
 *      Author: Oscar Crespo
 */

#include <gtest/gtest.h>
#include "benchmark/benchmark.h"

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

    bool ret_regis{event.registerCall([this](bool val){
            this->summon(val);
        },0)
    };
    EXPECT_EQ(ret_regis,true);
    ret_regis = event.registerCall([this](bool val){
        this->summon(val);
    },0);
    EXPECT_EQ(ret_regis,false);
    ret_regis = event.registerCall([this](bool val){
        this->summon(val);
    },1);
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

class EventListBench : public benchmark::Fixture {

public:
    EventListBench():
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

BENCHMARK_DEFINE_F(EventListBench, testingBind)(benchmark::State& st){
    ocutils::EventList<bool> event(2);
    event.registerCall(std::bind(&EventListBench::summon,this,std::placeholders::_1),0);

    for(auto _ : st) {
        event.callArgs(true);
    }

}

BENCHMARK_DEFINE_F(EventListBench, testingLambda)(benchmark::State& st){
    ocutils::EventList<bool> event(2);
    event.registerCall([this](bool val){
               this->summon(val);
    },0);
    for(auto _ : st) {
        event.callArgs(true);
    }

}

// Register the function as a benchmark
BENCHMARK_REGISTER_F(EventListBench,testingLambda)->Complexity();
BENCHMARK_REGISTER_F(EventListBench,testingBind)->Complexity();

