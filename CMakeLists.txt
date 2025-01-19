cmake_minimum_required(VERSION 3.10)

# 프로젝트 이름과 버전 설정
project(GameEngine VERSION 1.0)

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 헤더 파일 디렉토리 포함
include_directories(include)

set(SDL2_DIR "C:/SDL2/cmake")
#SDL2 라이브러리 설정
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})                    #Include include directory(headers)

# 소스 파일 설정
file(GLOB SOURCES "src/*.cpp")

# 실행 파일 생성
add_executable(GameEngine ${SOURCES})

target_link_libraries(GameEngine ${SDL2_LIBRARIES})