set (OCUtilsTest_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/events)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/observer)

add_executable(OCUtilsTest ${OCUtilsTest_SOURCES})

find_package( Threads )

include_directories(${PROJECT_INCLUDE_DIR})

include_directories(${PROJECT_SOURCE_DIR})


target_link_libraries(OCUtilsTest ${CMAKE_THREAD_LIBS_INIT} 
								gmock
                              	gtest
                               	)

add_test(OCUtilsTest OCUtilsTest)