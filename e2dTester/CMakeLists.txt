
file(GLOB e2dtester_source_files "*.c")
file(GLOB e2dtester_public_header "*.h")

if(MSVC)
    # If we are with msvc compiler, compile as c++. MSVC in C does not support C99.
    set_source_files_properties(${e2dtester_source_files} PROPERTIES LANGUAGE CXX )
endif()


add_executable (e2dTester ${e2dtester_source_files}) 

# include and link to the previously built lib
include_directories (${Ez2DS_SOURCE_DIR}\\Ez2DS)
target_link_libraries (e2dTester ${Ez2DS_BINARY_DIR}\\Ez2DS\\${DEPENDENCIE_LIB_PREFIX}Ez2DS${DEPENDENCIE_LIB_POSFIX}) 

target_link_libraries (e2dTester DevIL ILU ILUT opengl32 glut32 glu32) 

# target libs built with different compilers if we are in unix or windows
#if(MSVC)
#link_directories(${Ez2DS_SOURCE_DIR}\\Ez2DS\\dependencies\\mxml-2.7\\lib\\)
#target_link_libraries (Ez2DS ${Ez2DS_SOURCE_DIR}\\Ez2DS\\dependencies\\mxml-2.7\\libmsvc\\mxml1.lib) 
#else()
#link_directories(${Ez2DS_SOURCE_DIR}\\Ez2DS\\dependencies\\mxml-2.7\\libunix\\)
#target_link_libraries (Ez2DS ${Ez2DS_SOURCE_DIR}\\Ez2DS\\dependencies\\mxml-2.7\\libunix\\libmxml1.a) 
#endif()
