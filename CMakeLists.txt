cmake_minimum_required(VERSION 3.10)

# 프로젝트 이름과 버전 설정
project(GameEngine VERSION 1.0)

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 헤더 파일 디렉토리 포함
include_directories(include)

#SDL2 라이브러리 설정 https://eachan.tistory.com/182
find_package(SDL2 REQUIRED)

# SDL2_image 라이브러리 설정
find_package(SDL2_image REQUIRED)

# SDL2_mixer 라이브러리 설정
find_package(SDL2_mixer REQUIRED)

# 소스 파일 설정
file(GLOB SOURCES "src/*.cpp")

# 실행 파일 생성
add_executable(GameEngine ${SOURCES})

target_link_libraries(GameEngine ${SDL2_LIBRARIES} SDL2_image::SDL2_image SDL2_mixer::SDL2_mixer)