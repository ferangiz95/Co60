cmake_minimum_required(VERSION 3.16...3.21)

project(Simulation1)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})

file(GLOB sources ${PROJECT_SOURCE_DIR}/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/*.hh)

set(project1_SCRIPTS
  init_vis.mac
  vis.mac
  run1.mac
  run2.mac
  )

add_executable(project1 project1.cc ${sources} ${headers})
target_link_libraries(project1 ${Geant4_LIBRARIES})

add_custom_target(Simulation1 DEPENDS project1)
