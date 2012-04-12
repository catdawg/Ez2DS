/* 
 * File:   main.c
 * Author: Rui
 *
 * Created on 3 de Fevereiro de 2012, 16:38
 */

#include <stdio.h>
#include <stdlib.h>
 

#ifdef __APPLE__
	#include "OpenGL/gl.h"
	#include "OpenGL/glu.h"
	#include <GLUT/glut.h>
#else
#ifdef WIN32
	#include <windows.h>
#endif
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include <GL/glut.h>
#endif

#include "e2dScene.h"
#include "e2dMatrix.h"
#include "e2dElement.h"
#include <math.h>
#include "Ez2DSDebugDraw.h"


/*
 * 
 */

float angle = 0;
static void
reshape(int width, int height)
{
    glViewport(0, 0, width, height);

    double scale = (width/640.0 < height/480.0)?width/640.0:height/480.0;
    double hw = width*(0.5/scale)*4;
    double hh = height*(0.5/scale)*4;

    glLineWidth(scale);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-hw, hw, -hh, hh, -1.0, 1000.0);
    //gluPerspective(45,scale,1,10000);
    glTranslated(0, 0, -100.0);
    glMatrixMode(GL_MODELVIEW);
    
}
e2dScene* scene;
static void
display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    
    drawElement((e2dElement*)scene->root);
    
    glutSwapBuffers();
    

}

static void
idle(void)
{
    angle += 1;
    if(angle > 360)
        angle -= 360;
    glutPostRedisplay();
}

static void
initGL(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glEnableClientState(GL_VERTEX_ARRAY);

    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POINT_SMOOTH);

    //glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
    //glHint(GL_POINT_SMOOTH_HINT, GL_DONT_CARE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

static void
glutStuff(int argc, const char *argv[])
{
    glutInit(&argc, (char**)argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    glutInitWindowSize(640, 480);
    glutCreateWindow("Ez2DS test");

    initGL();

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    //glutTimerFunc(SLEEP_TICKS, timercall, 0);

    //glutIgnoreKeyRepeat(1);
    //glutKeyboardFunc(keyboard);

    //glutSpecialFunc(arrowKeyDownFunc);
    //glutSpecialUpFunc(arrowKeyUpFunc);

    //glutMotionFunc(mouse);
    //glutPassiveMotionFunc(mouse);
    //glutMouseFunc(click);
        
        
}

int main(int argc, const char* argv[]) {
    
    glutStuff(argc, argv);
    
    scene = createSceneFromFile("test5.svg");
    e2dGroupFlatten(scene->root);
    e2dMatrix mat;
    e2dMatrixSetAsScale(&mat, 1, -1);
    ((e2dElement*)scene->root)->localTransform = e2dMatrixMultiply(&(((e2dElement*)scene->root)->localTransform), &mat);
    e2dElementCalculateBoundingBox((e2dElement*)scene->root);
    e2dSceneCenterAllAtBBox(scene, 0.5, 0.5);
    e2dSceneCalculateEffectiveTransforms(scene);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    
    initDebugDraw();
    glutMainLoop();

    return (EXIT_SUCCESS);
}