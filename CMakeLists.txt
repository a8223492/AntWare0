cmake_minimum_required(VERSION 3.27)
project(AntWare0 CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)

#如果用的是MSVC，添加编译选项，以支持UTF-8编码
if(MSVC)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif()


# 添加编译选项


# 查找所需的依赖包

find_package(glad CONFIG REQUIRED)
if(glad_FOUND)
    message("find glad=${glad_VERSION}")
endif()

# 显式指定 SFML 库的完整路径
find_package(SFML COMPONENTS system window graphics audio CONFIG REQUIRED)
if(SFML_FOUND)
    message("find SFML=${SFML_VERSION}")
endif()

find_package(glm CONFIG REQUIRED)
if(GLM_FOUND)
    message("find glm=${glm_VERSION}")
endif()

find_package(assimp CONFIG REQUIRED)
if(assimp_FOUND)
    message("find assimp=${assimp_VERSION}")
endif()

find_package(RapidJSON CONFIG REQUIRED)
if(RapidJSON_FOUND)
    message("find RapidJSON=${RapidJSON_VERSION}")
endif()

# 收集源文件
file(GLOB_RECURSE SOURCES
        "src/*.cpp"
)

# 创建可执行文件
add_executable(${PROJECT_NAME} ${SOURCES})


# 添加头文件目录
target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 链接所需的库
target_link_libraries(${PROJECT_NAME} PRIVATE
        glad::glad
        sfml-system sfml-network sfml-graphics sfml-window sfml-audio
        glm::glm
        assimp::assimp
        rapidjson
)

# Windows平台特定设置
if(WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE
            WINDOWS_LEAN_AND_MEAN
            NOMINMAX
    )
endif()