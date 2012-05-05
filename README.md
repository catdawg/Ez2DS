###WEBSITE

Visit http://catdawg.github.com/Ez2DS/ for info on the project.

###DOCUMENTATION

http://catdawg.github.com/Ez2DS/documentation/html/index.html (in progress)


###COMPILATION

If you want to work on the lib I strongly recommend using Netbeans with MinGW. Just make sure "...\MinGW\msys\1.0\bin; ...\MinGW\bin;" is on the system path.

If you want to compile it for production use, you can use [CMake](http://www.cmake.org/cmake/help/runningcmake.html).  I'm currently working on this, here is the status:

#####Main library (Ez2DS)

Dependencies:

Included in the project for both Unix and Win32 (only mxml anyway)

CMake:

MinGW - Works

Visual Studio 2010 - Creates the .DLL but it hasn't been tested because the test program also needs to be msvc compatible, and it isn't yet.

Unix and OSx - Not tested, but should work if MinGW works. Just make sure you have mxml installed

#####Test program (e2dTester)

Dependencies:

Only included for Win32 (since they work on MinGW and MSVC). Unix users will have to install the dependencies. They are Glut (OpenGL also but it should be already there and DevIL.

CMake:

MinGW - Compiles on Netbeans, but not on CMake yet

Visual Studio 2010 - Doesn't work yet

Unix and OSx - Doesn't work yet


###LICENSE 

ZLIB license (http://en.wikipedia.org/wiki/Zlib_License)

Please tell me if you use this on a project, I would be very happy if you did!!


