/*
 * Observer_test.h
 *
 *  Created on: 30 Nov 2018
 *      Author: Oscar Crespo
 */


#include <gtest/gtest.h>

#include <observer/Observer.h>

class ObserverTest : public ::testing::Test, public ocutils::Observer{
public:
	ObserverTest(){};


protected:


private:

};

TEST_F(ObserverTest, Test) {
    EXPECT_EQ(getObserverId(),0);

    ocutils::Observer a;
    EXPECT_EQ(getObserverId(),0);
    EXPECT_EQ(a.getObserverId(),1);

    ocutils::Observer b;
    EXPECT_EQ(getObserverId(),0);
    EXPECT_EQ(a.getObserverId(),1);
    EXPECT_EQ(b.getObserverId(),2);

}
