file(GLOB ez2ds_source_files "*.c")
file(GLOB ez2ds_public_header "*.h")

# Allow the developer to select if Dynamic or Static libraries are built
OPTION (BUILD_SHARED_LIBS "Build Shared Libraries" OFF)
# Set the LIB_TYPE variable to STATIC
SET (LIB_TYPE STATIC)
IF (BUILD_SHARED_LIBS)
    # User wants to build Dynamic Libraries, so change the LIB_TYPE variable to CMake keyword 'SHARED'
    SET (LIB_TYPE SHARED)
ENDIF (BUILD_SHARED_LIBS)

add_library (Ez2DS ${LIB_TYPE} ${ez2ds_source_files})

if(MSVC)
    # If we are with msvc compiler, compile as c++. MSVC in C does not support C99.
    set_source_files_properties(${ez2ds_source_files} PROPERTIES LANGUAGE CXX )
    # In windows we target .lib, in unix .a
    set (DEPENDENCIE_PLATFORM libwin32)
    set (DEPENDENCIE_LIB_POSFIX .lib)
else()
    set (DEPENDENCIE_PLATFORM libunix)
    set (DEPENDENCIE_LIB_PREFIX lib)
    set (DEPENDENCIE_LIB_POSFIX .a)
endif()

#MXML
include_directories (dependencies\\mxml-2.7\\include) 
target_link_libraries (Ez2DS ${Ez2DS_SOURCE_DIR}\\Ez2DS\\dependencies\\mxml-2.7\\${DEPENDENCIE_PLATFORM}\\${DEPENDENCIE_LIB_PREFIX}mxml1${DEPENDENCIE_LIB_POSFIX}) 

if(WIN32)
    set_target_properties(Ez2DS PROPERTIES PREFIX "")
endif()


