#include "e2dGroup.h"
#include "e2dScene.h"
#include <float.h>
#include <stdlib.h>
#include <math.h>

static void 
e2dGroupInitChildList(e2dGroup* group)  {
    group->childNum = 0;
    group->childList = (e2dElement**) malloc(sizeof (e2dElement*));
    group->childListAlloc = 1;
}

void
e2dGroupInit(e2dGroup *group, const e2dScene* scene) {
    e2dGroupInitChildList(group);

    e2dElementInit((e2dElement*) group, E2D_GROUP, scene);
}

e2dGroup*
e2dGroupCreate(const e2dScene* scene) {
    e2dGroup* group = (e2dGroup*) malloc(sizeof (e2dGroup));
    e2dGroupInit(group, scene);
    return group;
}

void
e2dGroupDestroy(e2dGroup* group) {
    e2dGroupFreeMembers(group);
    e2dElementFreeMembers((e2dElement*)group);
    free(group);
}


void
e2dGroupFreeMembers(e2dGroup* group) {
    e2dGroupIterator iter = e2dGroupGetChildIterator(group);
    e2dElement* elem;
    while(e2dGroupIteratorHasNext(&iter))  {
        elem = e2dGroupIteratorNext(&iter);
        if(elem != E2D_NULL)
                e2dElementDestroy(elem);
    }
    free(group->childList);
}



static void 
e2dGroupIncreaseChildSpace(e2dGroup* group) {
    group->childListAlloc *= 2;
    group->childList = (e2dElement**) realloc(group->childList, group->childListAlloc * sizeof (e2dElement*));
}

void
e2dGroupAddChild(e2dGroup* group, e2dElement* element) {
    if (group->childNum + 1 > group->childListAlloc)
        e2dGroupIncreaseChildSpace(group);
    group->childList[group->childNum] = element;
    group->childNum++;
    element->parent = group;
}


void
e2dGroupCalculateBoundingBox(e2dGroup* group) {
    e2dPoint pos;
    pos.x = FLT_MAX;
    pos.y = FLT_MAX;
    float width = -1;
    float height = -1;
    
    e2dPoint nextBBoxPoint1, nextBBoxPoint2, nextBBoxPoint3, nextBBoxPoint4;
    float min_x, min_y, max_x, max_y;
    
    e2dGroupIterator iter = e2dGroupGetChildIterator(group);
    e2dElement* elem;
    while(e2dGroupIteratorHasNext(&iter))  {
        elem = e2dGroupIteratorNext(&iter);
        if (elem->bboxHeight == -1)
            e2dElementCalculateBoundingBox(elem);
        
        nextBBoxPoint1 = elem->bboxPosition;
        nextBBoxPoint2 = elem->bboxPosition;
        nextBBoxPoint3 = elem->bboxPosition;
        nextBBoxPoint4 = elem->bboxPosition;
        nextBBoxPoint2.x += elem->bboxWidth;
        nextBBoxPoint3.y += elem->bboxHeight;
        nextBBoxPoint4.x += elem->bboxWidth;
        nextBBoxPoint4.y += elem->bboxHeight;
        nextBBoxPoint1 = e2dMatrixApplyToPoint(&elem->localTransform, &nextBBoxPoint1);
        nextBBoxPoint2 = e2dMatrixApplyToPoint(&elem->localTransform, &nextBBoxPoint2);
        nextBBoxPoint3 = e2dMatrixApplyToPoint(&elem->localTransform, &nextBBoxPoint3);
        nextBBoxPoint4 = e2dMatrixApplyToPoint(&elem->localTransform, &nextBBoxPoint4);
        
        min_x = E2D_MIN(nextBBoxPoint1.x, E2D_MIN(nextBBoxPoint2.x, 
                E2D_MIN(nextBBoxPoint3.x, nextBBoxPoint4.x)));
        min_y = E2D_MIN(nextBBoxPoint1.y, E2D_MIN(nextBBoxPoint2.y, 
                E2D_MIN(nextBBoxPoint3.y, nextBBoxPoint4.y)));
        max_x = E2D_MAX(nextBBoxPoint1.x, E2D_MAX(nextBBoxPoint2.x, 
                E2D_MAX(nextBBoxPoint3.x, nextBBoxPoint4.x)));
        max_y = E2D_MAX(nextBBoxPoint1.y, E2D_MAX(nextBBoxPoint2.y, 
                E2D_MAX(nextBBoxPoint3.y, nextBBoxPoint4.y)));
        
        if (min_x < pos.x)
        {
            if(width != -1)
                width += fabs(pos.x - min_x);
            pos.x = min_x;
        }
        if (min_y < pos.y)
        {
            if(height != -1)
                height += fabs(pos.y - min_y);
            pos.y = min_y;
        }
        if (max_x > pos.x + width)
            width = fabs(pos.x - max_x);
        if (max_y > pos.y + height)
            height = fabs(pos.y - max_y);
    }
    group->element.bboxPosition = pos;
    group->element.bboxWidth = width;
    group->element.bboxHeight = height;
}


void
e2dGroupCenterAtBBox(e2dGroup* group, float tx, float ty) {
    
    e2dMatrix mat;
    e2dPoint offset;
    offset.x = group->element.bboxPosition.x + group->element.bboxWidth*tx;
    offset.y = group->element.bboxPosition.y + group->element.bboxHeight*ty;
    
    e2dMatrixSetAsTranslation(&mat, 
            offset.x, 
            offset.y);
    
    group->element.localTransform = 
            e2dMatrixMultiply(&group->element.localTransform, &mat);
     
    group->element.bboxPosition.x -= offset.x;
    group->element.bboxPosition.y -= offset.y;
    
    e2dMatrixSetAsTranslation(&mat, 
            -(offset.x),
            -(offset.y));
    
    e2dGroupIterator iter = e2dGroupGetChildIterator(group);
    e2dElement* elem;
    while(e2dGroupIteratorHasNext(&iter))  {
        elem = e2dGroupIteratorNext(&iter);
        elem->localTransform = e2dMatrixMultiply(&mat, &elem->localTransform);
    }
}

void _e2dGroupFlatten(e2dGroup* destination, e2dElement** childList, 
        unsigned int childNum, e2dMatrix currentTransform)  {
    
    unsigned int i;
    e2dElement* elem;
    e2dMatrix nextTransform;
    for(i = 0; i < childNum; i++)  {
        elem = childList[i];
        childList[i] = E2D_NULL;
        nextTransform = e2dMatrixMultiply(&elem->localTransform, &currentTransform);
        switch(elem->type)  {
            case(E2D_GROUP):
                _e2dGroupFlatten(destination, ((e2dGroup*)elem)->childList, 
                        ((e2dGroup*)elem)->childNum, nextTransform);
                e2dGroupDestroy((e2dGroup*)elem);
                break;
            default:
                elem->localTransform = nextTransform;
                e2dGroupAddChild(destination, elem);
        }
        
    }
}

void 
e2dGroupFlatten(e2dGroup* group)  {
    e2dElement** prevChildList = group->childList;
    unsigned int prevChildNum = group->childNum;
    e2dGroupInitChildList(group);
    
    _e2dGroupFlatten(group, prevChildList, prevChildNum, E2D_IDENT_MATRIX);
    
    free(prevChildList);
}


e2dGroupIterator 
e2dGroupGetChildIterator(e2dGroup* group)  {
    e2dGroupIterator iter;
    iter.group = group;
    iter.currentIndex = 0;
    return iter;
}

e2dElement* 
e2dGroupIteratorNext(e2dGroupIterator* iter)  {
    if(!e2dGroupIteratorHasNext(iter))
        return E2D_NULL;
    else
        return iter->group->childList[iter->currentIndex++];
}

E2D_BOOL
e2dGroupIteratorHasNext(e2dGroupIterator* iter)  {
    return iter->currentIndex < iter->group->childNum 
            && 
           iter->currentIndex >= 0;
}
