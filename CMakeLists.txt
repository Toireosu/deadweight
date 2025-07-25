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

find_package(raylib REQUIRED)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Include directories for headers
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# (Optional) Add compile definitions or flags
# target_compile_definitions(${PROJECT_NAME} PRIVATE SOME_DEFINE)
# target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)

# (Optional) Specify output directory for the executable
# Set where the executable is placed
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build/bin"
)

# Copy assets to the same directory as the executable
file(COPY ${PROJECT_SOURCE_DIR}/assets
     DESTINATION ${PROJECT_SOURCE_DIR}/build/bin)

# Note: Assets folder is not included in the build but should be copied or referenced at runtime.