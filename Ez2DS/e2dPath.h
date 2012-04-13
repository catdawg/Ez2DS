/* 
 * File:   e2dPath.h
 * Author: Rui Campos
 *
 * Created on 29 de Março de 2012, 17:24
 */

#ifndef E2DPATH_H
#define	E2DPATH_H

#include "Ez2ds.h"
#include "e2dElement.h"

#ifdef	__cplusplus
extern "C" {
#endif

typedef enum e2dPathElementType {
    E2D_PATHELEMENT,
    E2D_PATHPOINT,
    E2D_PATHCURVE,
    E2D_PATHCONTROL
} e2dPathElementType;

typedef enum e2dPathControl {
    E2D_START_SUBPATH,
    E2D_END_SUBPATH,
    E2D_END_SUBPATH_LOOP,
    E2D_NOCONTROL
} e2dPathControl;

struct e2dPathElement {
    e2dPathElementType type;
    
    e2dPathControl controlType;
};

struct e2dPathPoint {
    e2dPathElement element;
    
    e2dPoint point;
};

struct e2dPathCurve {
    e2dPathElement element;
    
    e2dPoint startPoint; //redundant since it's the current point in the path.
                           //added for convenience so that we can iterate
                           //the path without keeping a state (knowing current
                           //point) which can be annoying given subpath loops
                           //and such...
    e2dPoint controlPoint1;
    e2dPoint controlPoint2;
    e2dPoint endPoint;
};

struct e2dPath {
    e2dElement element;

    unsigned int pathElementsNum;
    e2dPathElement** pathElements;
    unsigned int pathElementsAlloc;
};

e2dPath* 
e2dPathCreate(const e2dScene* scene);

void 
e2dPathInit(e2dPath *path, const e2dScene* scene);

void 
e2dPathDestroy(e2dPath* path);

void 
e2dPathFreeMembers(e2dPath* path);

e2dPathElement*
e2dPathElementCreate();

void 
e2dPathElementInit(e2dPathElement* elem, e2dPathElementType type);

void 
e2dPathElementDestroy(e2dPathElement* elem);

void 
e2dPathElementFreeMembers(e2dPathElement* elem);

e2dPathPoint*
e2dPathPointCreate();

void 
e2dPathPointInit(e2dPathPoint* point);

void
e2dPathPointDestroy(e2dPathPoint* point);

void 
e2dPathPointFreeMembers(e2dPathPoint* point);

e2dPathCurve*
e2dPathCurveCreate();

void 
e2dPathCurveInit(e2dPathCurve* curve);

void 
e2dPathCurveDestroy(e2dPathCurve* curve);

void 
e2dPathCurveFreeMembers(e2dPathCurve* curve);

void
e2dPathAddPathElement(e2dPath* path, e2dPathElement *elem);

void 
e2dPathCalculateBoundingBox(e2dPath* path);

void 
e2dPathCenterAtBBox(e2dPath* path, float tx, float ty);

struct e2dPathElementIterator  {
    e2dPath* path;
    unsigned int currentIndex;
};

e2dPathElementIterator
e2dPathGetElementIterator(e2dPath* path);

e2dPathElement* 
e2dPathElementIteratorNext(e2dPathElementIterator* iter);

E2D_BOOL
e2dPathElementIteratorHasNext(e2dPathElementIterator* iter);


#ifdef	__cplusplus
}
#endif

#endif	/* E2DPATH_H */

