cmake_minimum_required(VERSION 3.16)
project(Deadweight LANGUAGES CXX)

# Use C++17 (or adjust as needed)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Define source files explicitly or glob all .cpp in src/
file(GLOB_RECURSE SOURCES
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Include directories for headers
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/src
)

# (Optional) If you use SDL2 or other libs, link them here
# find_package(SDL2 REQUIRED)
# target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})
# target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES})

# (Optional) Add compile definitions or flags
# target_compile_definitions(${PROJECT_NAME} PRIVATE SOME_DEFINE)
# target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)

# (Optional) Specify output directory for the executable
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build/bin"
)

# Note: Assets folder is not included in the build but should be copied or referenced at runtime.