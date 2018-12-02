/*
 * ThreadSwapperSingle_test.cpp
 *
 *  Created on: 28 Nov 2018
 *      Author: Oscar Crespo
 */


#include <gtest/gtest.h>


#include <threadutils/ThreadSwapperSingle.h>
#include <events/EventStore.h>


class ThreadSwapperSingleTest : public ::testing::Test {

public:
	ThreadSwapperSingleTest():
		thread_id(0),
		summoned(false)
	{};

	void summon(bool summon){
		summoned = summon;
		thread_id = std::this_thread::get_id();
	}

protected:

    std::thread::id thread_id;
    bool summoned;

private:

};

TEST_F(ThreadSwapperSingleTest, Test) {

	ocutils::ThreadSwapperSingle thread1;
	ocutils::ThreadSwapperSingle thread2;

    std::thread::id thread_id_1;
    std::thread::id thread_id_2;

	ocutils::EventStore<bool> *event(new ocutils::EventStore<bool>(std::bind(&ThreadSwapperSingleTest::summon,this,std::placeholders::_1)));
	event->setValues(false);
	thread1.execute(event);
	event = new ocutils::EventStore<bool>(std::bind(&ThreadSwapperSingleTest::summon,this,std::placeholders::_1));
	event->setValues(true);
	thread1.execute(event);
	while(!summoned){
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	thread_id_1 = thread_id;
    EXPECT_NE(thread_id,std::this_thread::get_id());

    summoned = false;
	event = new ocutils::EventStore<bool>(std::bind(&ThreadSwapperSingleTest::summon,this,std::placeholders::_1));
	event->setValues(true);
	thread2.execute(event);
	while(!summoned){
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	thread_id_2 = thread_id;

    EXPECT_NE(thread_id_2,thread_id_1);


}


