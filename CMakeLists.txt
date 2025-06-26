# CMakeList.txt : CMake project for Tello_Test, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 26)
# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("Tello_Test")

# Set the path to OpenCV
set(OpenCV_DIR "C:/opencv/build/x64/vc16/lib")

set(Cascades_DIR "${CMAKE_SOURCE_DIR}/Resources/Cascades")
set(Output_Cascades_DIR "${CMAKE_BINARY_DIR}/Resources/Cascades")

# Find OpenCV
find_package(OpenCV REQUIRED)
# Add source to this project's executable.
add_executable (Tello_Test "Tello_Test.cpp" "Tello_Test.h")

# add include directories for tello lib
target_include_directories(Tello_Test PRIVATE ${OpenCV_INCLUDE_DIRS})
target_include_directories(Tello_Test PRIVATE ${CMAKE_SOURCE_DIR}/extern/tello)

# Link OpenCV libraries
target_link_libraries(Tello_Test ${OpenCV_LIBS})

# Create the output directory if it doesn't exist
file(MAKE_DIRECTORY ${Output_Cascades_DIR})


# Copy the cascade files to the output directory
configure_file("${Cascades_DIR}/haarcascade_eye_tree_eyeglasses.xml"
               "${Output_Cascades_DIR}/haarcascade_eye_tree_eyeglasses.xml" COPYONLY)

configure_file("${Cascades_DIR}/haarcascade_frontalface_default.xml"
               "${Output_Cascades_DIR}/haarcascade_frontalface_default.xml" COPYONLY)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Tello_Test PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
