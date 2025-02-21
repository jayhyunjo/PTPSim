add_library( PTP SHARED
  Ptp.cc
  GeoPtpFactory.cc
  #DichroiconArrayFactory.cc
  HitmanProc.cc
  NtupleProc.cc
  LaserballGenerator.cc
  sipmConstruction.cc
)

include_directories(include)

target_include_directories( PTP PUBLIC
  $<BUILD_INTERFACE:${PTP_INCLUDE_DIR}>
  $<INSTALL_INTERFACE:include>)

file(COPY include/ DESTINATION ${PTP_INCLUDE_DIR})

add_executable(ptp ptp.cpp)
target_link_libraries(ptp PUBLIC 
  PTP ${ROOT_LIBRARIES} ${Geant4_LIBRARIES} ${Ratpac_LIBRARIES} ${NLOPT_LIBRARIES})

set_target_properties(PTP ptp
  PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY ${PTP_LIBRARY_DIR}
  LIBRARY_OUTPUT_DIRECTORY ${PTP_LIBRARY_DIR})

install(TARGETS PTP ptp 
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin)

install(DIRECTORY ${PTP_INCLUDE_DIR}
  DESTINATION ${CMAKE_INSTALL_PREFIX})
