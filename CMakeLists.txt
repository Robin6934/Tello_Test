# CMakeList.txt : CMake project for Tello_Test, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("Tello_Test")

# Add source to this project's executable.
add_executable (Tello_Test "Tello_Test.cpp" "Tello_Test.h")

# add include directories for tello lib
target_include_directories(Tello_Test PRIVATE ${CMAKE_SOURCE_DIR}/extern/tello)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Tello_Test PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
