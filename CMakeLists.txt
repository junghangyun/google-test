
cmake_minimum_required(VERSION 3.13)  # 자동 생성구문

# project(google-test c) --> CLion 프로젝트 생성 시 c 프로젝트로 생성하면 자동으로 생성되며,
#                            이로 인해 C++인 gtest가 빌드되지 않는다.
#                            따라서 아래와 같이 c를 제거한다.
project(google-test)

set(CMAKE_C_STANDARD 99) # C 프로젝트 생성 시 자동 생성구문

# 더하기(sum) 기능을 지원하는 내 라이브러리 빌드 (C 코드)
add_library(sum SHARED libsum/sum.c libsum/sum.h)

# 더하기 라이브러리를 이용하는 실행 프로그램 빌드 (C 코드)
# 테스트만 수행 시에는 사용되지 않으므로, 빌드하지 않아도 된다.
include_directories(libsum)
add_executable(google-test main.c)
target_link_libraries(google-test sum)

# gtest 빌드 (C++ 코드)
set(gtest_SRC_DIR test/googletest-release-1.8.1)
add_subdirectory(${gtest_SRC_DIR})

# 테스트 프로그램 빌드 (C++ 코드)
include_directories(libsum)
include_directories(${gtest_SRC_DIR}/googletest/include)
add_executable(runSumTests test/sum_test.cc)
target_link_libraries(runSumTests gtest gtest_main)
target_link_libraries(runSumTests sum)

# 사용되지 않음 (중간단계에서 테스트용으로 작성되었음)
##set(CMAKE_CXX_STANDARD 11)
##set(CMAKE_C_COMPILER g++)
##set(CMAKE_CXX_LINK_EXECUTABLE cxx)
#add_subdirectory(googletest-release-1.8.1)
#set(gtest_SRC_DIR googletest-release-1.8.1)
#include_directories(${gtest_SRC_DIR}/googletest/include ${gtest_SRC_DIR}/googletest)
#add_executable(runSumTests main.cc sum_test.cc)
##set_target_properties(runSumTests PROPERTIES LINKER_LANGUAGE CXX)
#target_link_libraries(runSumTests gtest gtest_main)
#target_link_libraries(runSumTests libsum)