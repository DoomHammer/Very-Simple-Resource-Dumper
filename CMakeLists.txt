cmake_minimum_required (VERSION 2.6)

project (Very-Simple-Resource-Dumper)
set (Very-Simple-Resource-Dumper_VERSION_MAJOR 0)
set (Very-Simple-Resource-Dumper_VERSION_MINOR 0)
set (Very-Simple-Resource-Dumper_VERSION_PATCH 3)

add_executable(vsrd CmdLine.cpp Dumper.cpp Main.cpp Parser.cpp)

install(TARGETS vsrd DESTINATION bin)

# build a CPack driven installer package
include (InstallRequiredSystemLibraries)
set (CPACK_PACKAGE_NAME "vsrd")
set (CPACK_RESOURCE_FILE_LICENSE
  "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set (CPACK_PACKAGE_VERSION_MAJOR "${Very-Simple-Resource-Dumper_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${Very-Simple-Resource-Dumper_VERSION_MINOR}")
set (CPACK_PACKAGE_VERSION_PATCH "${Very-Simple-Resource-Dumper_VERSION_PATCH}")
include (CPack)
