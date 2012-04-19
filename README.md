Are you developing a 2D game and just reached the part of development where you need to make a lot of levels? Need to easily place and update positions of your waypoints/obstacles/powerups/triggers? Don't really have resources to develop a map editor?

Tired of asking your designer which size the button is? or bugging him to send you the size for each element in the interface so that you can hardcode it?

Would like to test out physics scenarios, but don't really fancy creating the scenarios and playing with the physics element parameters in code?

Maybe this library can help you!

#####EZ2DS


Easy 2D Scene (Ez2DS), is a library for transforming an SVG file into a 2D scene tree with an API. In essence, the library provides the means for applications to quickly have a 2D editor.

SVG is used, not with vector graphics in mind, but with the idea of using SVG to organize and tag raster images in a scene. The other supported elements are Paths, Groups and Clones. For example, Paths can be used to define the outline of a given image and Groups can be used for custom tagging and transformation management.

Since the SVG capabilities are immense, it would be very difficult to support everything, thus this subset is used. As long as this limitation is understood, the library should provide an easy to use solution for many applications in need of an editor.

SVG was chosen because there are many editors available for this file format, although Inkscape(www.inkscape.org) is recommended because it allows editting the SVG text directly, giving the possibility of adding custom information to elements in the scene. 

The library was created with programming language wrapping in mind to allow the connection with any Graphical/Physics Engine. The main library is developed in C to hopefully facilitate this wrapping.

Examples of usage are: 
 *A 2D map editor for games! Specify the position/appearance of waypoints/triggers/obstacles of your scenarions in Inkscape and then read them easily using this API.
 *When a 2D Engine does not have an editor, you can quickly use this library to provide an editor for your 2D interfaces/scenes; 
 *Creating a 2D Physics Engine scenario by tagging elements to specify physical characteristics. Using the common physics engine concept of Body(element which contains speed, momentum, mass and such) and Geometry(used for collision calculation), we can make the analogy that a Group can be the Body, which has a Path as a child, defining the Geometry of this body, and an Image which gives the physics object a visible appearance.

#####COMPILE INSTRUCTIONS

I'm developing this on Windows in Netbeans and MinGW for compiling. Plans are for providing crossplatform compilation capabilities, such as CMake, but for now this will do. In order to compile this you just have to import the project into Netbeans, make sure you have MinGW installed and that the following folders are on the system path: "...\MinGW\msys\1.0\bin; ...\MinGW\bin;". 
 
#####PROJECT STRUCTURE

Ez2DS folder contains the main library. e2dTester contains a sample application which uses the library to draw an SVG file in OpenGL using the API provided by the library.

#####CURRENT STATUS

Core functionality is mostly finished, just missing some utility methods, and supporting extra functionality on Paths (only supports straight line segments and simple curves).

Will very soon start experimenting with wrapping on Python and Java( Android! ).

Will only be useful for production use when I have some wrappers developed and examples in popular Graphics Engines.



#####LICENSE 

ZLIB license (http://en.wikipedia.org/wiki/Zlib_License)

Please tell me if you use this on a project, I would be very happy if you did!!

