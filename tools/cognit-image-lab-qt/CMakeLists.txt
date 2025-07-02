cmake_minimum_required(VERSION 3.20)

project(cognit-image-lab-qt)

include(../../.build-config.cmake)
include(${CONFIG_APEAL_CMAKE_DIR}/project_header.cmake)


enable_qt6()

enable_libpng()
enable_libturbojpeg()

include(sources.cmake)

include(${CONFIG_APEAL_CMAKE_DIR}/apeal_sources.cmake)
include(${CONFIG_COGNIT_CMAKE_DIR}/cognit_sources.cmake)


include(${CONFIG_APEAL_CMAKE_DIR}/project_target.cmake)
