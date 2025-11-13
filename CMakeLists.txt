# 设置CMake最低版本
cmake_minimum_required(VERSION 3.10)

# 项目信息
project(MyProject
        VERSION 1.0.0
        DESCRIPTION "多线程程序示例教学"
        LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

## 编译选项
#if (MSVC)
#    target_compile_options(my_target PRIVATE /W4)
#else ()
#    target_compile_options(my_target PRIVATE -Wall -Wextra -pedantic)
#endif ()

# 查找依赖包（如果需要）
# find_package(PkgConfig REQUIRED)
# pkg_check_modules(DEPS REQUIRED dependency_name)

# 包含目录
#include_directories(include)

## 添加可执行文件
#file(GLOB SOURCES "src/*.cpp")
#add_executable(${PROJECT_NAME} ${SOURCES})

add_subdirectory(Chapter01)


# 链接库
# target_link_libraries(${PROJECT_NAME} ${DEPS_LIBRARIES})
