cmake_minimum_required(VERSION 3.10)
project(Checkers)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Находим SFML
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

# Добавляем исходные файлы
add_executable(Checkers 
    main.cpp
    Game/CheckersGame.cpp
)

# Подключаем заголовочные файлы
target_include_directories(Checkers PRIVATE ${CMAKE_SOURCE_DIR})

# Линкуем с SFML
target_link_libraries(Checkers sfml-graphics) 