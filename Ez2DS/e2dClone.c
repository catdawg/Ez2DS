#include "e2dClone.h"
#include "e2dGroup.h"
#include "e2dScene.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

e2dClone* 
e2dCloneCreate(const e2dScene* scene) {
    e2dClone* clone = (e2dClone*) malloc(sizeof (e2dClone));
    e2dCloneInit(clone, scene);
    return clone;
}

void 
e2dCloneInit(e2dClone *clone, const e2dScene* scene) {
    clone->pointsToID = E2D_NULL;
    clone->pointsToElement = E2D_NULL;
    clone->position = E2D_ZERO_ZERO_POINT;

    e2dElementInit((e2dElement*) clone, E2D_CLONE, scene);
}

void
e2dCloneDestroy(e2dClone* clone) {
    e2dCloneFreeMembers(clone);
    e2dElementFreeMembers((e2dElement*)clone);
    free(clone);
}

void
e2dCloneFreeMembers(e2dClone* clone) {
    if(clone->pointsToID)
        free(clone->pointsToID);
}

e2dElement*
e2dCloneDereference(e2dClone* clone) {
    e2dSearchResult *ssr = e2dGroupSearchByID(clone->element.scene->root, clone->pointsToID);
    e2dElement *result;
    if(ssr->resultListNum > 0)
        result = ssr->resultList[0];
    e2dSearchResultDestroy(ssr);
    return result;
}

void
e2dCloneNormalize(e2dClone* clone) {
    e2dMatrix translate;
    e2dMatrix currentMatrix = clone->element.localTransform;
    
    e2dMatrixSetAsTranslation(&translate, 
               (clone)->position.x,
               (clone)->position.y);
    currentMatrix = e2dMatrixMultiply(&currentMatrix, &translate);
    
    e2dElement* current = clone->pointsToElement;
    while(current->type == E2D_CLONE) {
        e2dMatrixSetAsTranslation(&translate, 
               ((e2dClone*)current)->position.x,
               ((e2dClone*)current)->position.y);
       currentMatrix = e2dMatrixMultiply(&currentMatrix, &current->localTransform);
       currentMatrix = e2dMatrixMultiply(&currentMatrix, &translate);

       current = ((e2dClone*)current)->pointsToElement;
    }
    clone->element.localTransform = currentMatrix;
    if(clone->pointsToID)
        free(clone->pointsToID);
    clone->pointsToID = (char*) malloc(sizeof(char)*(strlen(current->id) + 1));
    strcpy(clone->pointsToID, current->id);
    clone->pointsToElement = current;
}

void
e2dCloneCalculateBoundingBox(e2dClone* clone)  {
    
    e2dMatrix currentMatrix = E2D_IDENT_MATRIX;
    e2dMatrixSetAsTranslation(&currentMatrix, 
               clone->position.x,
               clone->position.y);
    e2dElement* current = clone->pointsToElement;
    currentMatrix = e2dMatrixMultiply(&currentMatrix, &current->localTransform);
   
    if(current->bboxWidth == -1) //not calculated
        e2dElementCalculateBoundingBox(current);
    
    e2dPoint topLeft, bottomRight, topRight, bottomLeft;
    
    topLeft = current->bboxPosition;
    
    topRight.x = current->bboxPosition.x + current->bboxWidth;
    topRight.y = current->bboxPosition.y;
    
    bottomLeft.x = current->bboxPosition.x;
    bottomLeft.y = current->bboxPosition.y + current->bboxWidth;
    
    bottomRight.x = current->bboxPosition.x + current->bboxWidth;
    bottomRight.y = current->bboxPosition.y + current->bboxHeight;
    
    topLeft = e2dMatrixApplyToPoint(&currentMatrix, &topLeft);
    topRight = e2dMatrixApplyToPoint(&currentMatrix, &topRight);
    bottomLeft = e2dMatrixApplyToPoint(&currentMatrix, &bottomLeft);
    bottomRight = e2dMatrixApplyToPoint(&currentMatrix, &bottomRight);
    
    float min_x, min_y, max_x, max_y;
    
    min_x = E2D_MIN(topLeft.x, E2D_MIN(topRight.x, 
            E2D_MIN(bottomLeft.x, bottomRight.x)));
    min_y = E2D_MIN(topLeft.y, E2D_MIN(topRight.y, 
            E2D_MIN(bottomLeft.y, bottomRight.y)));
    max_x = E2D_MAX(topLeft.x, E2D_MAX(topRight.x, 
            E2D_MAX(bottomLeft.x, bottomRight.x)));
    max_y = E2D_MAX(topLeft.y, E2D_MAX(topRight.y, 
            E2D_MAX(bottomLeft.y, bottomRight.y)));
    
    clone->element.bboxPosition.x = min_x;
    clone->element.bboxPosition.y = min_y;
    clone->element.bboxWidth = fabs(max_x - min_x);
    clone->element.bboxHeight = fabs(max_y - min_y);
    
    
}

void
e2dCloneCenterAtBBox(e2dClone* clone, float tx, float ty)  {
    e2dMatrix mat;
    e2dPoint offset;
    offset.x = clone->element.bboxPosition.x + clone->element.bboxWidth*tx;
    offset.y = clone->element.bboxPosition.y + clone->element.bboxHeight*ty;
     
    e2dMatrixSetAsTranslation(&mat, 
            offset.x, 
            offset.y);
    clone->element.localTransform = 
            e2dMatrixMultiply(&clone->element.localTransform, &mat);
    
    clone->position.x -= offset.x; 
    clone->position.y -= offset.y; 
    
    clone->element.bboxPosition.x -= offset.x;
    clone->element.bboxPosition.y -= offset.y;
    
    
}

