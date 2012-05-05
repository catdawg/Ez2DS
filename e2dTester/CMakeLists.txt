# Make sure the compiler can find include files from our Hello library. 
include_directories (${Ez2DS_SOURCE_DIR}/Ez2DS) 

# Make sure the linker can find the Hello library once it is built. 
link_directories (${Ez2DS_BINARY_DIR}/Ez2DS) 

# Add executable called "helloDemo" that is built from the source files 
# "demo.cxx" and "demo_b.cxx". The extensions are automatically found. 
add_executable (e2dTester main.c Ez2DSDebugDraw.c) 

# Link the executable to the Hello library. 
target_link_libraries (e2dTester Ez2DS) 