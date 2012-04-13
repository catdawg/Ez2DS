/* 
 * File:   Ez2DSDebugDraw.h
 * Author: Rui
 *
 * Created on 6 de Fevereiro de 2012, 22:30
 */

#ifndef EZ2DSDEBUGDRAW_H
#define	EZ2DSDEBUGDRAW_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    
#include "Ez2DS.h"
    
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>


void initDebugDraw();

void drawElement(e2dElement* elem);
void drawGroup(e2dGroup* group);
void drawPath(e2dPath* path);
void drawImage(e2dImage* image);

void drawAxis();
void drawRect(e2dPoint point, float width, float height);


#ifdef	__cplusplus
}
#endif

#endif	/* EZ2DSDEBUGDRAW_H */

