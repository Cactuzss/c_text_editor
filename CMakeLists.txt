cmake_minimum_required(VERSION 3.30)


project(c_text_editor)
set(SOURCES main.c src/graphics.c src/files.c src/strings.c src/charList.c )
add_executable(c_text_editor ${SOURCES})

target_include_directories(c_text_editor PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

target_link_libraries(c_text_editor ncurses)

