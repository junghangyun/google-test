# Google test 샘플 프로젝트

본 프로젝트는 C 언어로 작성된 코드에 대해, 
CLion과 Cmake 개발 환경에서 gtest를 적용하여 단위테스트를 수행하는 방법을 참고할 수 있도록 작성된 샘플 프로젝트이다.

## 개요

* 더하기(sum) 기능을 지원하는 라이브러리(libsum/sum.c libsum/sum.h)를 개발한다 -> 단위테스트 대상
* 더하기 라이브러리의 기능을 사용하는 실행 프로그램(main.c)을 개발한다. 
    * 단, 이 프로그램은 단위테스트 수행 시에는 사용되지 않는다.
* gtest 를 이용하여 더하기 기능에 대한 단위테스트를 수행한다. 

## 프로젝트 진행 절차
### CLion 프로젝트 생성

* CLion에서 C 프로젝트를 생성한다.
* 프로젝트 내에서 C++ 도 사용해야 하므로(gtest 및 테스트코드), CMakeLists.txt의 project() 항목에서 c를 제거한다.
    * project(google-test c) -> project(google-test)

### 라이브러리 개발 및 빌드 설정 - libsum

* 더하기 기능을 지원하는 라이브러리 코드를 작성한다. (libsum/sum.c, libsum/sum.h)
* 헤더파일(sum.h)은 C++로 작성되는 테스트코드에서도 포함(#include)되어야 하므로, 다음과 같은 구문을 작성하여 C++에서도 빌드될 수 있도록 한다.
```
#ifdef __cplusplus
extern "C" {
#endif
.....
#ifdef __cplusplus
}
#endif
```
* CMakeLists.txt에 라이브러리 빌드 구문을 추가한다.
```$xslt
add_library(sum SHARED libsum/sum.c libsum/sum.h)
```

### 실행 프로그램 개발 및 빌드 설정 - google-test

* 더하기 기능을 사용하는 실행 프로그램 코드를 작성한다. (main.c)
* 본 프로그램은 단위테스트에서는 사용되지 않는다.
* CMakeLists.txt에 빌드 구문을 추가한다.
```
include_directories(libsum)
add_executable(google-test main.c)
target_link_libraries(google-test sum)
```

### gtest 다운로드 및 빌드 설정

* 다음 링크에서 gtest를 다운로드한다. (본 예제에서는 1.8.1 버전을 사용한다)
    * https://github.com/google/googletest/releases
* 다운로드한 gtest를 프로젝트 내에 복사한다 - test/googletest-release-1.8.1
* CMakeLists.txt에 빌드 구문을 추가한다.
```
set(gtest_SRC_DIR test/googletest-release-1.8.1)
add_subdirectory(${gtest_SRC_DIR})
```

### 테스트 프로그램 작성 및 빌드 설정 - runSumTests

* 더하기 기능에 대한 단위테스트 코드를 작성한다 - test/sum_test.cc
* CMakeLists.txt에 빌드 구문을 추가한다.
```
include_directories(libsum)
include_directories(${gtest_SRC_DIR}/googletest/include)
add_executable(runSumTests test/sum_test.cc)
target_link_libraries(runSumTests gtest gtest_main)
target_link_libraries(runSumTests sum)
```

### 프로젝트 빌드

* CLion의 Build -> Build Project 메뉴를 선택하여 프로젝트 전체를 빌드한다.

### 단위테스트 실행

* CLion의 Run -> Run 메뉴에서 runSumTests를 선택하여 단위테스트를 수행한다.

## 참고

* https://www.jetbrains.com/help/clion/creating-google-test-run-debug-configuration-for-test.html
* https://hiseon.me/2018/06/30/google-test/
* https://lightandtruth.tistory.com/110