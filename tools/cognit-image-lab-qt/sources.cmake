# Source Group: ImageLab
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
set(src
  ${CMAKE_CURRENT_SOURCE_DIR}/src/image_graphics_view.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/image_graphics_view.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/image_scene.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/image_scene.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/image_toolkit.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/image_toolkit.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/image_view.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/image_view.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/image_view_actions.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/image_widget.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/image_widget.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main_application.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main_stylesheet.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main_window.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main_window.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main_window_actions.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main_window_layout.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main_window_loadimage.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main_window_panels.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/panels/filters_panel.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/panels/filters_panel.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/panels/images_directory_panel.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/panels/images_directory_panel.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/panels/image_info_panel.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/panels/image_info_panel.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/panels/panel.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/panels/panel.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/panels/pixel_info_panel.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/panels/pixel_info_panel.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/settings.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/settings.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/types.h
)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src PREFIX "Sources\\ImageLab" FILES ${src})
list(APPEND main_SRC ${src})

# Source Group: Resources
set(src
  ${CMAKE_CURRENT_SOURCE_DIR}/res/image_toolkit.qrc
)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/res PREFIX "Sources\\Resources" FILES ${src})
list(APPEND main_SRC ${src})

