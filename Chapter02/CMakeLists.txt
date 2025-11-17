add_subdirectory(src)

file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "src/*.h")

# 添加头文件到可执行文件
add_executable(Chapter02 ${SOURCES} ${HEADERS})

# 设置包含路径
target_include_directories(Chapter01 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
