set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(../src)

set(tester_SOURCES
  qqrencodetestsuite.cpp
  testrunner.cpp
  main.cpp
)

add_executable(tester WIN32 ${tester_SOURCES})
target_link_libraries(tester Qt5::Core Qt5::Gui Qt5::Svg Qt5::Test qtqrencode)
