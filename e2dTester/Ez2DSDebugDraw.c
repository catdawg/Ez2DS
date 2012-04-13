#include "Ez2DSDebugDraw.h"

#include <stdio.h> 
#include <math.h>
 

#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>
 
#include <e2dElement.h>
#include <e2dGroup.h>
#include <e2dImage.h>
#include <e2dPath.h>
#include <e2dMatrix.h>
#include <e2dPoint.h>
#include <e2dScene.h>



#include "uthash.h"

struct pathAndTextureID   {
    char* path;
    GLuint textureID;
    ILuint width;
    ILuint height;
    UT_hash_handle hh; /* makes this structure hashable */
};

typedef struct pathAndTextureID Texture;

Texture *pathToTexTable = NULL;

Texture* 
getTextureID(char* path)  {
    Texture *s;
    HASH_FIND_STR( pathToTexTable, path, s );  /* s: output pointer */
    if(s == NULL)  {
        s = (Texture*)malloc(sizeof(Texture));
        s->path = (char*)malloc(strlen(path)*sizeof(char));
        strcpy(s->path, path);
        s->textureID = ilutGLLoadImage(path);
        s->width = ilGetInteger(IL_IMAGE_WIDTH);
        s->height = ilGetInteger(IL_IMAGE_HEIGHT);
        HASH_ADD_KEYPTR( hh, pathToTexTable, s->path, strlen(s->path), s );
    }
    return s;
}

void 
initDebugDraw()  {
    ilInit();
    iluInit();
    ilutInit();
    ilutRenderer(ILUT_OPENGL);
}

void 
setMatrix(float* matrix, e2dMatrix* mat)  {
    matrix[0] = mat->vals[0][0];
    matrix[4] = mat->vals[0][1];
    matrix[8] = 0;
    matrix[12] = mat->vals[0][2];
    
    matrix[1] = mat->vals[1][0];
    matrix[5] = mat->vals[1][1];
    matrix[9] = 0;
    matrix[13] = mat->vals[1][2];
    
    matrix[2] = 0;
    matrix[6] = 0;
    matrix[10] = 1;
    matrix[14] = 0;
    
    matrix[3] = mat->vals[2][0];
    matrix[7] = mat->vals[2][1];
    matrix[11] = 0;
    matrix[15] = mat->vals[2][2];
}

void 
loadMatrix(e2dMatrix* mat)  {
    static float matrix[16];
    setMatrix(matrix, mat);
    glLoadMatrixf(matrix);
}

void 
multMatrix(e2dMatrix* mat)  {
    static float matrix[16];
    setMatrix(matrix, mat);
    glMultMatrixf(matrix);
}

void 
drawElement(e2dElement* elem)  {
    glPushMatrix();
    
    multMatrix(&elem->localTransform);
    switch(elem->type)
    {
            
        case(E2D_GROUP):
            drawGroup((e2dGroup*)elem);
            break;
           
        case(E2D_PATH):
            drawPath((e2dPath*)elem);
            break;
            
        case(E2D_IMAGE):
            drawImage((e2dImage*)elem);
            break;
        
        default:
            break;
    }
        
    drawAxis();
    drawRect(elem->bboxPosition, elem->bboxWidth, elem->bboxHeight);
    glPopMatrix();
}

void 
drawGroup(e2dGroup* group)  {
    e2dGroupIterator iter = e2dGroupGetChildIterator(group);
    while(e2dGroupIteratorHasNext(&iter))  {
        drawElement(e2dGroupIteratorNext(&iter));
    }
}

void 
drawImage(e2dImage* image)  {
    Texture* tex = getTextureID(image->imagePath);
    unsigned int height = image->height == 0? tex->height:image->height;
    unsigned int width = image->width == 0? tex->width:image->width;
    glBindTexture(GL_TEXTURE_2D, tex->textureID);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex2f(image->position.x, image->position.y + height);
    glTexCoord2f(1.0, 0.0); glVertex2f(image->position.x + width, image->position.y + height);
    glTexCoord2f(1.0, 1.0); glVertex2f(image->position.x + width, image->position.y);
    glTexCoord2f(0.0, 1.0); glVertex2f(image->position.x, image->position.y);
    glEnd();
    
}

void
drawControlPoint(e2dPoint origin, e2dPoint point)  {
    
    glBindTexture(GL_TEXTURE_2D, 0);
    glBegin(GL_LINE_STRIP);

    glColor4ub(0, 255, 255, 255);
    
    glVertex3f(origin.x, origin.y, 5.0f);
    glVertex3f(point.x, point.y, 5.0f);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex3f(point.x - 10, point.y - 10, 5.0f);
    glVertex3f(point.x + 10, point.y - 10, 5.0f);
    glVertex3f(point.x + 10, point.y + 10, 5.0f);
    glVertex3f(point.x - 10, point.y + 10, 5.0f);
    
    glEnd();
    
    glColor4ub(255, 255, 255, 255);
}

void 
drawPath(e2dPath* path)  {
    glBindTexture(GL_TEXTURE_2D, 0);
    
    e2dPoint startPointOfSubPath;
    e2dPoint currentPoint;
    glBindTexture(GL_TEXTURE_2D, 0); 
    glColor4ub(255, 128, 128, 255);
    
    e2dPathElement* pathElem;
    e2dPathPoint* point;
    e2dPathCurve* curve;
    e2dPathElementIterator iter = e2dPathGetElementIterator(path);
    while(e2dPathElementIteratorHasNext(&iter))  {
        pathElem = e2dPathElementIteratorNext(&iter);
        switch(pathElem->type)
        {
            case(E2D_PATHPOINT):
                point = (e2dPathPoint*)pathElem;
                
                switch(pathElem->controlType)
                {
                    case(E2D_START_SUBPATH):
                        glBegin(GL_LINE_STRIP);
                        startPointOfSubPath = point->point;
                        glVertex3f(point->point.x, point->point.y, 5.0f);
                        currentPoint = point->point;
                        break;
                    case(E2D_END_SUBPATH):
                        glVertex3f(point->point.x, point->point.y, 5.0f);
                        glEnd();
                        currentPoint = point->point;
                        break;
                    case(E2D_END_SUBPATH_LOOP):
                        glVertex3f(point->point.x, point->point.y, 5.0f);
                        glVertex3f(startPointOfSubPath.x,
                                startPointOfSubPath.y,
                                2.5f);
                        
                        currentPoint = startPointOfSubPath;
                        glEnd();
                        break;
                    default:
                        glVertex3f(point->point.x, point->point.y, 5.0f);
                        currentPoint = point->point;
                        
                }
                
                break;
            case(E2D_PATHCURVE):
                curve = (e2dPathCurve*)pathElem;
                glEnd();
                drawControlPoint(curve->startPoint, curve->controlPoint1);
                drawControlPoint(curve->endPoint, curve->controlPoint2);
                glColor4ub(255, 128, 128, 255);
                glBegin(GL_LINE_STRIP);
                float t;
                for (t = 0.0f; t <= 1.0f; t += 0.05f)  {
                    float xt = 
                    powf(1.0f-t, 3.0f) * currentPoint.x + 
                    3.0f * t * powf (1.0f-t, 2.0f) * curve->controlPoint1.x +
                    3.0f * powf (t, 2.0f) * (1.0f-t) * curve->controlPoint2.x + 
                    powf (t, 3.0f) * curve->endPoint.x;

                    float yt = 
                    powf (1.0f-t, 3.0f) * currentPoint.y + 
                    3.0f * t * powf (1.0f-t, 2.0f) * curve->controlPoint1.y +
                    3.0f * powf (t, 2.0f) * (1.0f-t) * curve->controlPoint2.y + 
                    powf (t, 3.0f) * curve->endPoint.y;

                    glVertex3f(xt, yt, 5.0f);
                }
                
                currentPoint = curve->endPoint;
                if(pathElem->controlType == E2D_END_SUBPATH)
                    glEnd();
                else  {
                        if(pathElem->controlType == E2D_END_SUBPATH_LOOP)
                        {
                            glVertex3f(startPointOfSubPath.x, 
                                    startPointOfSubPath.y, 5.0f);
                            glEnd();
                            currentPoint = startPointOfSubPath;
                        }
                }
                    
                break;
        }
        
    }
    glColor4ub(255, 255, 255, 255);
    
    
}




void 
drawAxis()  {
    
    glBindTexture(GL_TEXTURE_2D, 0);
    glBegin(GL_LINES);

    glColor4ub(255, 0, 0, 255);
    glVertex3f(0.0f, 0.0f, 5.0f);
    glVertex3f(256.0f, 0.0f, 5.0f);
    
    glEnd();
    
    
    glBegin(GL_LINES);

    glColor4ub(0, 255, 0, 255);
    glVertex3f(0.0f, 0.0f, 5.0f);
    glVertex3f(0.0f, 256.0f, 5.0f);
    
    glEnd();
    
    glColor4ub(255, 255, 255, 255);
    
}

void 
drawRect(e2dPoint point, float width, float height)  {
    glBindTexture(GL_TEXTURE_2D, 0);
    glBegin(GL_LINE_LOOP);

    glColor4ub(255, 255, 0, 255);
    
    glVertex3f(point.x, point.y, 5.0f);
    glVertex3f(point.x + width, point.y, 5.0f);
    glVertex3f(point.x + width, point.y + height, 5.0f);
    glVertex3f(point.x, point.y + height, 5.0f);
    
    glEnd();
    
    glColor4ub(255, 255, 255, 255);
}
