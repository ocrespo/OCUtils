set (OCUtilsTest_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/events)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/observer)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/threadutils)


add_executable(OCUtilsTest ${OCUtilsTest_SOURCES})

find_package( Threads )

include_directories(${PROJECT_INCLUDE_DIR})

include_directories(${PROJECT_SOURCE_DIR})


target_link_libraries(OCUtilsTest ${CMAKE_THREAD_LIBS_INIT} 
								gmock
                              	gtest
                               	)

add_custom_command(TARGET OCUtilsTest
                    POST_BUILD
                    COMMAND OCUtilsTest
                    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                    COMMENT "Running OCUtilsTest" VERBATIM)