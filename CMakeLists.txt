cmake_minimum_required(VERSION 3.12)
project(ProcessorSimulator CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Download cpp-httplib
include(FetchContent)
FetchContent_Declare(
  httplib
  GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
  GIT_TAG        v0.14.1
)
FetchContent_MakeAvailable(httplib)

# Create executable for simulator
add_executable(processor_simulator 
    src/processor_simulator.cpp 
    src/main.cpp
)

# Create server executable
add_executable(processor_server 
    src/http_server.cpp 
    src/processor_simulator.cpp
)

# Enable threading
find_package(Threads REQUIRED)
target_link_libraries(processor_simulator Threads::Threads)
target_link_libraries(processor_server Threads::Threads)

# Link httplib
target_include_directories(processor_server PRIVATE ${httplib_SOURCE_DIR})
target_link_libraries(processor_server httplib::httplib)

# Optional: Add compiler warnings
if(MSVC)
    target_compile_options(processor_simulator PRIVATE /W4)
    target_compile_options(processor_server PRIVATE /W4)
else()
    target_compile_options(processor_simulator PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(processor_server PRIVATE -Wall -Wextra -Wpedantic)
endif()
