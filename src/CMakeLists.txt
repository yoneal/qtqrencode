set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_definitions(-DQQRENCODE_LIBRARY)

set(qqrencode_SOURCES
  qqrencode.cpp
)

add_library(qtqrencode SHARED ${qqrencode_SOURCES})
target_link_libraries(qtqrencode Qt5::Core Qt5::Svg ${QRENCODE_LIBRARY})

install (TARGETS qtqrencode DESTINATION lib)
install (FILES qqrencode.h DESTINATION include)
install (FILES qqrencode_global.h DESTINATION include)
