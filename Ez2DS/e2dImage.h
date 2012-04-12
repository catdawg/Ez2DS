/* 
 * File:   e2dImage.h
 * Author: Rui Campos
 *
 * Created on 29 de Março de 2012, 17:22
 */

#ifndef E2DIMAGE_H
#define	E2DIMAGE_H

#include "Ez2ds.h"
#include "e2dElement.h"

#ifdef	__cplusplus
extern "C" {
#endif

struct e2dImage {
    e2dElement element;
    
    e2dPoint position;
    float width;
    float height;
    char* imagePath;
};

e2dImage* 
e2dImageCreate(const e2dScene* scene);

void
e2dImageInit(e2dImage *image, const e2dScene* scene);

void 
e2dImageDestroy(e2dImage* image);

void 
e2dImageFreeMembers(e2dImage* image);

void 
e2dImageCalculateBoundingBox(e2dImage* image);

void 
e2dImageCenterAtBBox(e2dImage* image, float tx, float ty);



#ifdef	__cplusplus
}
#endif

#endif	/* E2DIMAGE_H */

