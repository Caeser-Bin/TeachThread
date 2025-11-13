add_subdirectory(src)

file(GLOB SOURCES "src/*.cpp")

add_executable(Chapter01 ${SOURCES})