#include "e2dPath.h"
#include <stdlib.h>
#include <float.h>
#include <math.h>

void
e2dPathInit(e2dPath *path, const e2dScene* scene) {
    path->pathElementsNum = 0;
    path->pathElementsAlloc = 32;
    path->pathElements = (e2dPathElement**) malloc(
            sizeof (e2dPathElement*) * path->pathElementsAlloc);

    e2dElementInit((e2dElement*) path, E2D_PATH, scene);
}

e2dPath*
e2dPathCreate(const e2dScene* scene) {
    e2dPath* path = (e2dPath*) malloc(sizeof (e2dPath));
    e2dPathInit(path, scene);
    return path;
}

void
e2dPathDestroy(e2dPath* path) {
    e2dPathFreeMembers(path);
    e2dElementFreeMembers((e2dElement*) path);
    free(path);
}

void
e2dPathFreeMembers(e2dPath* path) {

    int i;
    for (i = 0; i < path->pathElementsNum; ++i)
        e2dPathElementDestroy(path->pathElements[i]);
    free(path->pathElements);
    free(path);
}

void e2dPathIncreasePathAlloc(e2dPath* path) {
    path->pathElementsAlloc *= 2;
    path->pathElements = (e2dPathElement**) realloc(path->pathElements, path->pathElementsAlloc * sizeof (e2dPathElement*));
}

void
e2dPathAddPathElement(e2dPath* path, e2dPathElement* elem) {
    if (path->pathElementsNum + 1 > path->pathElementsAlloc)
        e2dPathIncreasePathAlloc(path);
    path->pathElements[path->pathElementsNum] = elem;
    path->pathElementsNum++;
}

/**
 * algorithm obtained from 
 * http://processingjs.nihongoresources.com/decasteljau/
 * (THANKS!!!)
 */
void
e2dPathCurveCalculateBBox(e2dPathCurve* curve, float* min_x, float* min_y, float* max_x, float* max_y) {

    float temp_min_x;
    float temp_min_y;
    float temp_max_x;
    float temp_max_y;
    float dcx0 = curve->controlPoint1.x - curve->startPoint.x;
    float dcy0 = curve->controlPoint1.y - curve->startPoint.y;
    float dcx1 = curve->controlPoint2.x - curve->controlPoint1.x;
    float dcy1 = curve->controlPoint2.y - curve->controlPoint1.y;
    float dcx2 = curve->endPoint.x - curve->controlPoint2.x;
    float dcy2 = curve->endPoint.y - curve->controlPoint2.y;
    temp_min_x = E2D_MIN(curve->startPoint.x, curve->endPoint.x);
    temp_min_y = E2D_MIN(curve->startPoint.y, curve->endPoint.y);
    temp_max_x = E2D_MAX(curve->startPoint.x, curve->endPoint.x);
    temp_max_y = E2D_MAX(curve->startPoint.y, curve->endPoint.y);

    if( curve->controlPoint1.x < temp_min_x ||
        curve->controlPoint1.x > temp_max_x ||
        curve->controlPoint2.x < temp_min_x ||
        curve->controlPoint2.x > temp_max_x) {
        
        float a = dcx0;
        float b = dcx1;
        float c = dcx2;
        if (a + c != 2 * b) {
            b += 0.01;
        }

        float numerator = 2 * (a - b);
        float denominator = 2 * (a - 2 * b + c);
        float quadroot = (2 * b - 2 * a)*(2 * b - 2 * a) - 2 * a*denominator;
        float root = sqrt(quadroot);


        float t1 = (numerator + root) / denominator;
        float t2 = (numerator - root) / denominator;

        if (0 < t1 && t1 < 1) {
            float mt = (1 - t1);
            float z1 = (mt * mt * mt * curve->startPoint.x) + (3 * mt * mt * t1 * curve->controlPoint1.x) +
                    (3 * mt * t1 * t1 * curve->controlPoint2.x) + (t1 * t1 * t1 * curve->endPoint.x);

            temp_min_x = E2D_MIN(temp_min_x, z1);
            temp_max_x = E2D_MAX(temp_max_x, z1);
        }

        if (0 < t2 && t2 < 1) {
            float mt = (1 - t2);
            float z2 = (mt * mt * mt * curve->startPoint.x) + (3 * mt * mt * t2 * curve->controlPoint1.x) +
                    (3 * mt * t2 * t2 * curve->controlPoint2.x) + (t2 * t2 * t2 * curve->endPoint.x);

            temp_min_x = E2D_MIN(temp_min_x, z2);
            temp_max_x = E2D_MAX(temp_max_x, z2);
        }
    }


    if (curve->controlPoint1.y < temp_min_y ||
        curve->controlPoint1.y > temp_max_y ||
        curve->controlPoint2.y < temp_min_y ||
        curve->controlPoint2.y > temp_max_y) {
        
        float a = dcy0;
        float b = dcy1;
        float c = dcy2;
        if (a + c != 2 * b) {
            b += 0.01;
        }

        float numerator = 2 * (a - b);
        float denominator = 2 * (a - 2 * b + c);
        float quadroot = (2 * b - 2 * a)*(2 * b - 2 * a) - 2 * a*denominator;
        float root = sqrt(quadroot);
        
        float t1 = (numerator + root) / denominator;
        float t2 = (numerator - root) / denominator;

        if (0 < t1 && t1 < 1) {
            float mt = (1 - t1);
            float z1 = (mt * mt * mt * curve->startPoint.y) + (3 * mt * mt * t1 * curve->controlPoint1.y) +
                    (3 * mt * t1 * t1 * curve->controlPoint2.y) + (t1 * t1 * t1 * curve->endPoint.y);

            temp_min_y = E2D_MIN(temp_min_y, z1);
            temp_max_y = E2D_MAX(temp_max_y, z1);
        }

        if (0 < t2 && t2 < 1) {
            float mt = (1 - t2);
            float z2 = (mt * mt * mt * curve->startPoint.y) + (3 * mt * mt * t2 * curve->controlPoint1.y) +
                    (3 * mt * t2 * t2 * curve->controlPoint2.y) + (t2 * t2 * t2 * curve->endPoint.y);

            temp_min_y = E2D_MIN(temp_min_y, z2);
            temp_max_y = E2D_MAX(temp_max_y, z2);
        }
    }
    
    
    *min_x = E2D_MIN(*min_x, temp_min_x);
    *min_y = E2D_MIN(*min_y, temp_min_y);
    *max_x = E2D_MAX(*max_x, temp_max_x);
    *max_y = E2D_MAX(*max_y, temp_max_y);
}

void
e2dPathCalculateBoundingBox(e2dPath* path) {
    float min_x = FLT_MAX;
    float max_x = -FLT_MAX;
    float min_y = FLT_MAX;
    float max_y = -FLT_MAX;

    int i;
    e2dPathElement* pathElem;
    for (i = 0; i < path->pathElementsNum; ++i) {
        pathElem = path->pathElements[i];
        switch (pathElem->type) {
            case(E2D_PATHPOINT):
                min_x = E2D_MIN(min_x, ((e2dPathPoint*) pathElem)->point.x);
                min_y = E2D_MIN(min_y, ((e2dPathPoint*) pathElem)->point.y);
                max_x = E2D_MAX(max_x, ((e2dPathPoint*) pathElem)->point.x);
                max_y = E2D_MAX(max_y, ((e2dPathPoint*) pathElem)->point.y);
                break;
            case(E2D_PATHCURVE):
                
                e2dPathCurveCalculateBBox(((e2dPathCurve*) pathElem), 
                        &min_x,
                        &min_y,
                        &max_x,
                        &max_y
                        );
                
                break;
        }
    }
    
    
    
    path->element.bboxPosition.x = min_x;
    path->element.bboxPosition.y = min_y;
    path->element.bboxHeight = max_y - min_y;
    path->element.bboxWidth = max_x - min_x;

}

void
e2dPathCenterAtBBox(e2dPath* path, float tx, float ty) {

    e2dMatrix mat;
    e2dPoint offset;
    offset.x = path->element.bboxPosition.x + path->element.bboxWidth*tx;
    offset.y = path->element.bboxPosition.y + path->element.bboxHeight*ty;

    e2dMatrixSetAsTranslation(&mat,
            offset.x,
            offset.y);

    path->element.localTransform =
            e2dMatrixMultiply(&path->element.localTransform, &mat);

    int i;
    e2dPathElement* pathElem;
    for (i = 0; i < path->pathElementsNum; ++i) {
        pathElem = path->pathElements[i];
        switch (pathElem->type) {
            case(E2D_PATHPOINT):
                ((e2dPathPoint*) pathElem)->point.x -= offset.x;
                ((e2dPathPoint*) pathElem)->point.y -= offset.y;
                break;
            case(E2D_PATHCURVE):
                ((e2dPathCurve*) pathElem)->startPoint.x -= offset.x;
                ((e2dPathCurve*) pathElem)->startPoint.y -= offset.y;
                ((e2dPathCurve*) pathElem)->controlPoint1.x -= offset.x;
                ((e2dPathCurve*) pathElem)->controlPoint1.y -= offset.y;
                ((e2dPathCurve*) pathElem)->controlPoint2.x -= offset.x;
                ((e2dPathCurve*) pathElem)->controlPoint2.y -= offset.y;
                ((e2dPathCurve*) pathElem)->endPoint.x -= offset.x;
                ((e2dPathCurve*) pathElem)->endPoint.y -= offset.y;
                break;
        }
    }

    path->element.bboxPosition.x -= offset.x;
    path->element.bboxPosition.y -= offset.y;
}


void
e2dPathElementInit(e2dPathElement* elem, e2dPathElementType type) {
    elem->type = type;
    elem->controlType = E2D_NOCONTROL;
}

void
e2dPathElementDestroy(e2dPathElement* elem) {
    switch (elem->type) {
        case(E2D_PATHPOINT):
            e2dPathPointDestroy((e2dPathPoint*) elem);
            break;
        case(E2D_PATHCURVE):
            e2dPathCurveDestroy((e2dPathCurve*) elem);
            break;
        default:
            break;
    }
}

void
e2dPathElementFreeMembers(e2dPathElement* elem) {

}

e2dPathPoint*
e2dPathPointCreate() {
    e2dPathPoint* point = (e2dPathPoint*) malloc(sizeof (e2dPathPoint));
    e2dPathPointInit(point);
    return point;
}

void
e2dPathPointInit(e2dPathPoint* point) {

    point->point = E2DPOINT_ZERO_ZERO;
    e2dPathElementInit((e2dPathElement*) point, E2D_PATHPOINT);

}

void
e2dPathPointDestroy(e2dPathPoint* point) {
    e2dPathPointFreeMembers(point);
    e2dPathElementFreeMembers((e2dPathElement*) point);
    free(point);
}

void
e2dPathPointFreeMembers(e2dPathPoint* point) {
}

e2dPathCurve*
e2dPathCurveCreate() {
    e2dPathCurve* curve = (e2dPathCurve*) malloc(sizeof (e2dPathCurve));
    e2dPathCurveInit(curve);
    return curve;
}

void
e2dPathCurveInit(e2dPathCurve* curve) {
    curve->controlPoint1 = E2DPOINT_ZERO_ZERO;
    curve->controlPoint2 = E2DPOINT_ZERO_ZERO;
    curve->endPoint = E2DPOINT_ZERO_ZERO;
    e2dPathElementInit((e2dPathElement*) curve, E2D_PATHCURVE);
}

void
e2dPathCurveFreeMembers(e2dPathCurve* curve) {
}

void
e2dPathCurveDestroy(e2dPathCurve* curve) {
    e2dPathCurveFreeMembers(curve);
    e2dPathElementFreeMembers((e2dPathElement*) curve);
    free(curve);
}

e2dPathElementIterator
e2dPathGetElementIterator(e2dPath* path)  {
    e2dPathElementIterator iter;
    iter.path = path;
    iter.currentIndex = 0;
    return iter;
}

e2dPathElement* 
e2dPathElementIteratorNext(e2dPathElementIterator* iter)  {
    if(!e2dPathElementIteratorHasNext(iter))
        return E2D_NULL;
    else
        return iter->path->pathElements[iter->currentIndex++];
}

E2D_BOOL
e2dPathElementIteratorHasNext(e2dPathElementIterator* iter)  {
    return iter->currentIndex < iter->path->pathElementsNum 
            && 
           iter->currentIndex >= 0;
}


