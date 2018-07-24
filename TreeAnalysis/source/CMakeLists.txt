# Manadtory setting for minimal CMake requirement:
cmake_minimum_required( VERSION 2.8 )

# Create a project:
project( diHiggsbbyy )

# Only necessary on MacOS X to silence a warning:
set( CMAKE_MACOSX_RPATH ON )

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Build the library:
add_library( diHiggsAnalysis SHARED lib/diHiggsbbyyTreeAnalysis.h lib/diHiggsbbyyTreeAnalysis.cxx lib/diHiggsbbyyTreeInput.h lib/diHiggsbbyyTreeInput.cxx lib/diHiggsTMVATree.h lib/diHiggsTMVATree.cxx lib/diHiggsTMVAClassification.h lib/diHiggsTMVAClassification.cxx lib/diHiggsTreeInput_subsample.h lib/diHiggsTreeInput_subsample.cxx)
#add_library( diHiggsAnalysis SHARED lib/*)
target_include_directories( diHiggsAnalysis PUBLIC
   $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/lib>
   $<INSTALL_INTERFACE:include> )

# Find Boost:
find_package( Boost COMPONENTS program_options )

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

# Find ROOT:
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

# Check, if ROOTSYS is set.
if(NOT DEFINED ROOTSYS)
  set(ROOTSYS $ENV{ROOTSYS})
  if(NOT DEFINED ROOTSYS)
    message(FATAL_ERROR "ROOTSYS is not set!")
  endif()
endif()

# Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS):
#find_package(ROOT REQUIRED COMPONENTS RIO Net)
find_package(ROOT REQUIRED)
get_filename_component(ROOT_INCLUDE_DIR "${ROOTSYS}/include" ABSOLUTE)
set(ROOT_INCLUDE_DIRS ${ROOT_INCLUDE_DIR})
set(ROOT_LIBRARIES Core RIO Net Hist Gpad Tree Rint Matrix MathCore TMVA)
set(ROOT_root_CMD ${ROOTSYS}/bin/root.exe)
set(ROOT_genreflex_CMD ${ROOTSYS}/bin/genreflex)
set(ROOT_rootcint_CMD ${ROOTSYS}/bin/rootcint)
set(ROOT_rootcling_CMD rootcling)

if(BLAS_FOUND AND imt)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDNNCPU")
  set(DNN_CPU_LIBRARIES MathCore Matrix ${BLAS_LIBRARIES} ${TBB_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
  include_directories(SYSTEM ${TBB_INCLUDE_DIRS})
else()
  set(DNN_CPU_LIBRARIES)
  set(DNN_CPU_FILES)
  set(installoptions ${installoptions} FILTER "Cpu")
endif()

# include ROOT directories
message(${ROOT_INCLUDE_DIRS})
include_directories(${ROOT_INCLUDE_DIRS})

# include ROOT libraries
get_filename_component(ROOT_BINARY_DIR  "${ROOTSYS}/bin" ABSOLUTE)
get_filename_component(ROOT_LIBRARY_DIR "${ROOTSYS}/lib" ABSOLUTE)

# Detect bitness.
if(CMAKE_SYSTEM_PROCESSOR MATCHES amd64.*|x86_64.*|aarch64.*|ppc64.*
   OR (CMAKE_VERSION VERSION_LESS 3.0 AND CMAKE_SYSTEM_NAME STREQUAL Darwin) )
  set(64BIT 1)
  message("-- Check for bitness: Found 64 bit architecture.")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES i686.*|i386.*|x86.*)
  set(32BIT 1)
  message("-- Check for bitness: Found 32 bit architecture.")
endif()

# Find python.
if(ROOT_python_FOUND)
  find_package(PythonInterp)
  if(PYTHONINTERP_FOUND)
    execute_process(COMMAND ${PYTHON_EXECUTABLE} -c "import sys;sys.stdout.write(sys.prefix)"
                    OUTPUT_VARIABLE PYTHON_PREFIX)
    set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${PYTHON_PREFIX})
  endif()
  find_package(PythonLibs)
endif()

# Find OpenGL 
find_library(OPENGL_gl_LIBRARY NAMES GL)

# Setup standard includes / links.
include_directories(${ROOT_INCLUDE_DIRS} ${ROOT_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
link_directories(${ROOT_LIBRARY_DIR})

# Build the executable:
add_executable( RundiHiggs app/RundiHiggs.cxx )
target_link_libraries( RundiHiggs diHiggsAnalysis )
target_include_directories( RundiHiggs PRIVATE ${Boost_INCLUDE_DIRS} )
target_link_libraries( RundiHiggs ${Boost_LIBRARIES} )
target_link_libraries( RundiHiggs ${ROOT_LIBRARIES})
add_executable( RunTMVATree app/RunTMVATree.cxx )
target_link_libraries( RunTMVATree diHiggsAnalysis )
target_include_directories( RunTMVATree PRIVATE ${Boost_INCLUDE_DIRS} )
target_link_libraries( RunTMVATree ${Boost_LIBRARIES} )
target_link_libraries( RunTMVATree ${ROOT_LIBRARIES})
add_executable( RundiHiggsInput app/RundiHiggsInput.cxx )
target_link_libraries( RundiHiggsInput diHiggsAnalysis )
target_include_directories( RundiHiggsInput PRIVATE ${Boost_INCLUDE_DIRS} )
target_link_libraries( RundiHiggsInput ${Boost_LIBRARIES} )
target_link_libraries( RundiHiggsInput ${ROOT_LIBRARIES})
add_executable( RunTMVAClassification app/RunTMVAClassification.cxx )
target_link_libraries( RunTMVAClassification diHiggsAnalysis )
target_include_directories( RunTMVAClassification PRIVATE ${Boost_INCLUDE_DIRS} )
target_link_libraries( RunTMVAClassification ${Boost_LIBRARIES} )
target_link_libraries( RunTMVAClassification ${ROOT_LIBRARIES})
add_executable( RundiHiggsSubsampler app/RundiHiggsSubsampler.cxx )
target_link_libraries( RundiHiggsSubsampler diHiggsAnalysis )
target_include_directories( RundiHiggsSubsampler PRIVATE ${Boost_INCLUDE_DIRS} )
target_link_libraries( RundiHiggsSubsampler ${Boost_LIBRARIES} )
target_link_libraries( RundiHiggsSubsampler ${ROOT_LIBRARIES})



# Install the components:
install( TARGETS diHiggsAnalysis RundiHiggs RundiHiggsInput RunTMVATree RundiHiggsSubsampler
   EXPORT diHiggsTree
   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib )

# Install the header:
install( FILES lib/diHiggsbbyyTreeAnalysis.h
  DESTINATION include )
install( FILES lib/diHiggsbbyyTreeInput.h
  DESTINATION include )
install( FILES lib/diHiggsTMVATree.h
  DESTINATION include )
install( FILES lib/diHiggsTMVAClassification.h
  DESTINATION include )
install( FILES lib/diHiggsTreeInput_subsample.h
  DESTINATION include)

# Install a CMake description of this project:
install( EXPORT diHiggsTree
  DESTINATION cmake )

# Check warnings
if ( CMAKE_COMPILER_IS_GNUCC )
  set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall")
endif ( CMAKE_COMPILER_IS_GNUCC )
if ( MSVC )
  set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /W4")
endif ( MSVC )
