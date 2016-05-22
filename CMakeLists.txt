###############   CMakeLists for arislite build    #####################
#  Written by Quentin Riffard (riffard@apc.in2p3.fr)                  #

#  To create an Xcode project:                                         #
#         cmake -G Xcode .                                             #

###############             cmake version          #####################
cmake_minimum_required(VERSION 2.6)

###############              Project name          #####################
project(ARISLITE)

###############            Minimal flags           #####################
IF(${UNIX})
  set (CMAKE_CXX_FLAGS "-std=c++11 -g3 -Wall -O0")
ENDIF(${UNIX})

IF(${APPLE})
  set (CMAKE_CXX_FLAGS "-std=c++0x -g3 -Wall -fPIC -fno-common -O0")
ENDIF(${APPLE})

if(NOT DEFINED CMAKE_MACOSX_RPATH)
  set(CMAKE_MACOSX_RPATH 0)
endif()

#######   Check the compiler and set the compile and link flags  #######
set(CMAKE_BUILD_TYPE Debug)


###############        Root include/lib dir        #####################
include(config/cmake/FindROOT.cmake)
include_directories( ${ROOT_INCLUDE_DIR}  )
link_directories( ${ROOT_LIBRARY_DIR})

###############        boost include/lib dir       #####################
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})


###############             Root flags            #####################
if (CMAKE_SYSTEM_NAME MATCHES Darwin)
   EXEC_PROGRAM("sw_vers -productVersion | cut -d . -f 1-2" OUTPUT_VARIABLE MAC_OS_VERSION)
   MESSAGE("--- Found a Mac OS X System ${MAC_OS_VERSION}")
   if (CMAKE_COMPILER_IS_GNUCXX)
      MESSAGE("--- Found GNU compiler collection")

      STRING(COMPARE EQUAL "10.5" "${MAC_OS_VERSION}" MAC_OS_10_5)
      IF(MAC_OS_10_5)
        SET(CMAKE_CXX_FLAGS "-m64")
        SET(CMAKE_Fortran_FLAGS "-m64")
      ENDIF(MAC_OS_10_5)

      SET(CMAKE_SHARED_LIBRARY_CREATE_C_FLAGS "${CMAKE_SHARED_LIBRARY_CREATE_C_FLAGS} -flat_namespace -single_module -undefined dynamic_lookup")
      SET(CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS "${CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS} -flat_namespace -single_module -undefined dynamic_lookup")

      # Select flags.
      set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")
      set(CMAKE_CXX_FLAGS_RELEASE        "-O2")
      set(CMAKE_CXX_FLAGS_DEBUG          "-g -O2 -fno-reorder-blocks -fno-schedule-insns -fno-inline")
      set(CMAKE_CXX_FLAGS_DEBUGFULL      "-g3 -fno-inline -Wnon-virtual-dtor -Wno-long-long -ansi -Wundef -Wcast-align -Wchar-subscripts -Wall -W -Wpointer-arith -Wformat-security -fno-exceptions -fno-check-new -fno-common")
      set(CMAKE_CXX_FLAGS_PROFILE        "-g3 -fno-inline -ftest-coverage -fprofile-arcs")
      set(CMAKE_C_FLAGS_RELWITHDEBINFO   "-O2 -g")
      set(CMAKE_C_FLAGS_RELEASE          "-O2")
      set(CMAKE_C_FLAGS_DEBUG            "-g -O2 -fno-reorder-blocks -fno-schedule-insns -fno-inline")
      set(CMAKE_C_FLAGS_DEBUGFULL        "-g3 -fno-inline -Wno-long-long -std=iso9899:1990 -Wundef -Wcast-align -Werror-implicit-function-declaration -Wchar-subscripts -Wall -W -Wpointer-arith -Wwrite-strings -Wformat-security -Wmissing-format-attribute -fno-common")
      set(CMAKE_C_FLAGS_PROFILE          "-g3 -fno-inline -ftest-coverage -fprofile-arcs")

      endif (CMAKE_COMPILER_IS_GNUCXX)

endif (CMAKE_SYSTEM_NAME MATCHES Darwin)


###############             Project files           #####################

include_directories (${PostgreSQL_INCLUDE_DIR})

include_directories (${PROJECT_SOURCE_DIR}/reader/include)
include_directories (${PROJECT_SOURCE_DIR}/modules/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/reader/src/*.cc ${PROJECT_SOURCE_DIR}/modules/src/*.cc)

file(GLOB headers ${PROJECT_SOURCE_DIR}/reader/include/*.hh ${PROJECT_SOURCE_DIR}/modules/include/*.hh)

###############      library extension  #####################
IF(${UNIX})
  SET(LIBRARY_PROPERTIES ${LIBRARY_PROPERTIES}
    SUFFIX ".so"
    )
ENDIF(${UNIX})

IF(${APPLE})
  SET(LIBRARY_PROPERTIES ${LIBRARY_PROPERTIES}
    VERSION "${LIB_VERSION}"
    SOVERSION "${MAJOR_VERSION}"
    SUFFIX ".dylib"
    )
ENDIF(${APPLE})

#set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")


###############          Output directory          #####################
set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")


###############      build the library     #####################
add_library(ArisLite SHARED ${sources} ${headers})

target_link_libraries(ArisLite ${ROOT_LIBRARIES})
target_link_libraries(ArisLite ${FFTW_LIBRARIES})
target_link_libraries(ArisLite ${Boost_LIBRARIES})


LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/lib)


file( GLOB  APP_SOURCES ${PROJECT_SOURCE_DIR}/exe/*.cc)


foreach( testsourcefile ${APP_SOURCES} )
	 # I used a simple string replace, to cut off .cpp.
	 string( REPLACE ".cc" ".bin" testname_ ${testsourcefile} )
	 string( REPLACE "${PROJECT_SOURCE_DIR}/exe/" "" testname ${testname_} )
	 add_executable(${testname} ${testsourcefile})

	 # Make sure YourLib is linked to each app
	 target_link_libraries(${testname} ArisLite )
	 target_link_libraries(${testname} ${ROOT_LIBRARIES})
	 target_link_libraries(${testname} ${FFTW_LIBRARIES})
	 target_link_libraries(${testname} ${Boost_LIBRARIES})

endforeach( testsourcefile ${APP_SOURCES} )



############### install the library ###################
install(TARGETS ArisLite DESTINATION ${PROJECT_SOURCE_DIR}/lib)
#install(FILES ${headers} DESTINATION ${PROJECT_SOURCE_DIR}/include)
