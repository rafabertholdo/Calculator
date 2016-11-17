#set (CMAKE_C_FLAGS "-Wall -g")

# Find source files
file(GLOB SOURCES *.cpp include/*.hpp)

# Include header files
include_directories ("${PROJECT_SOURCE_DIR}/src/include")

# Create shared library
add_library(${PROJECT_NAME} STATIC ${SOURCES})
