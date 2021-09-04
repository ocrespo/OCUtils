/*
 * main.cpp
 *
 *  Created on: 13 Jan 2018
 *      Author: Oscar Crespo
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "benchmark/benchmark.h"


int main(int argc, char **argv) {

    ::benchmark::Initialize(&argc, argv);
    if (::benchmark::ReportUnrecognizedArguments(argc, argv)) return 1;
    ::benchmark::RunSpecifiedBenchmarks();
    ::benchmark::Shutdown();

	::testing::InitGoogleTest(&argc, argv);

	// The following line causes Google Mock to throw an exception on failure,
	// which will be interpreted by your testing framework as a test failure.
	::testing::GTEST_FLAG(throw_on_failure) = true;
	::testing::InitGoogleMock(&argc, argv);

	return RUN_ALL_TESTS();
}

