/* 
 * File:   e2dElement.h
 * Author: Rui
 *
 * Created on 3 de Fevereiro de 2012, 18:31
 */

#ifndef E2DELEMENT_H
#define	E2DELEMENT_H

#ifdef	__cplusplus
extern "C" {
#endif


#include "Ez2DS.h"
#include "e2dMatrix.h"
#include "e2dPoint.h"

typedef enum e2dElementType {
    E2D_ELEMENT,
    E2D_GROUP,
    E2D_PATH,
    E2D_IMAGE
} e2dElementType;


// **** ELEMENT ****
struct e2dElement{ 
    
    e2dScene* scene;
    e2dElementType type;
    char* id;
    unsigned int unique_id;
    
    e2dMatrix localTransform;
    e2dMatrix effectiveTransform;
    e2dMatrix inverseEffectiveTransform;

    unsigned int attributeNum;
    unsigned int _attributeAlloc;
    char** attributeNames;
    char** attributeValues;

    float bboxWidth;
    float bboxHeight;
    e2dPoint bboxPosition;
};

e2dElement* 
e2dElementCreate(const e2dScene* scene);

void
e2dElementInit(e2dElement *element, e2dElementType type, const e2dScene* scene);

void 
e2dElementDestroy(e2dElement* elem);

void 
e2dElementFreeMembers(e2dElement* elem);

void 
e2dElementAddAttribute(e2dElement* element, 
        const char* name, const char* value);

const char*
e2dElementGetAttribute(e2dElement* element, 
        const char* name);

e2dPoint 
e2dElementGetLocalPosition(const e2dElement* elem);

//UNTESTED
e2dPoint 
e2dElementGetWorldPosition(const e2dElement* elem);

//UNTESTED
e2dPoint 
e2dElementGetRelativePosition(const e2dElement* elem,
        const e2dElement* relativeTo);

//UNTESTED
e2dPoint 
e2dElementGetRelativePoint(const e2dElement* elem,
        const e2dElement* relativeTo, const e2dPoint *point);

void 
e2dElementCalculateBoundingBox(e2dElement* elem);

void 
e2dElementCenterAtBBox(e2dElement* elem, float tx, float ty);




#ifdef	__cplusplus
}
#endif

#endif	/* E2DELEMENT_H */

