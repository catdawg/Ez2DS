file(GLOB ez2ds_source_files "*.c")
file(GLOB ez2ds_public_header "*.h")

# Create a library called "Hello" which includes the source file "hello.cxx". 
# The extension is already found. Any number of sources could be listed here. 

# Allow the developer to select if Dynamic or Static libraries are built
OPTION (BUILD_SHARED_LIBS "Build Shared Libraries" OFF)
# Set the LIB_TYPE variable to STATIC
SET (LIB_TYPE STATIC)
IF (BUILD_SHARED_LIBS)
  # User wants to build Dynamic Libraries, so change the LIB_TYPE variable to CMake keyword 'SHARED'
  SET (LIB_TYPE SHARED)
ENDIF (BUILD_SHARED_LIBS)


include_directories (dependencies\\mxml-2.7\\include) 

if(MSVC)
set_source_files_properties(${ez2ds_source_files} PROPERTIES LANGUAGE CXX )
endif()
add_library (Ez2DS ${LIB_TYPE} ${ez2ds_source_files})

link_directories(${Ez2DS_SOURCE_DIR}\\Ez2DS\\dependencies\\mxml-2.7\\lib\\)
# Link the executable to the Hello library. 
target_link_libraries (Ez2DS ${Ez2DS_SOURCE_DIR}\\Ez2DS\\dependencies\\mxml-2.7\\lib\\mxml1.lib) 