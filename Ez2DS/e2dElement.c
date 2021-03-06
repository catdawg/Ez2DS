#include "e2dElement.h"

#include "e2dGroup.h"
#include "e2dImage.h"
#include "e2dPath.h"
#include "e2dClone.h"

#include "e2dScene.h"
#include "stdlib.h"
#include "string.h"

#define INITIAL_ATTRIBUTE_ALLOC 4

void
e2dElementInit(e2dElement *element, e2dElementType type, const e2dScene* scene) {

    e2dMatrixToIdent(&(element->localTransform));
    e2dMatrixToIdent(&(element->effectiveTransform));
    element->type = type;
    element->scene = (e2dScene*) scene;
    static int id = 0;
    element->unique_id = id++;
    element->id = 0;


    element->attributeNum = 0;
    element->attributeNames = (char**) malloc(sizeof (char*) *INITIAL_ATTRIBUTE_ALLOC);
    element->attributeValues = (char**) malloc(sizeof (char*) *INITIAL_ATTRIBUTE_ALLOC);
    element->attributeAlloc = INITIAL_ATTRIBUTE_ALLOC;

    element->parent = 0;

    element->bboxHeight = -1;
    element->bboxWidth = -1;
    element->bboxPosition.x = 0;
    element->bboxPosition.y = 0;
    
    element->clonesNum = 0;
    element->clonesAlloc = 1;
    element->clones = (e2dClone**) malloc(sizeof(e2dClone*)*
            element->clonesAlloc);

}

void
e2dElementFreeMembers(e2dElement* elem) {
    unsigned int i;
    for (i = 0; i < elem->attributeNum; ++i) {
        free(elem->attributeNames[i]);
        free(elem->attributeValues[i]);
    }
    free(elem->attributeNames);
    free(elem->attributeValues);
    if (elem->id)
        free(elem->id);
    free(elem->clones);
}

void
e2dElementDestroy(e2dElement* elem) {
    switch (elem->type) {
        case(E2D_GROUP):
            e2dGroupDestroy((e2dGroup*) elem);
            break;
        case(E2D_IMAGE):
            e2dImageDestroy((e2dImage*) elem);
            break;
        case(E2D_PATH):
            e2dPathDestroy((e2dPath*) elem);
            break;
        case(E2D_CLONE):
            e2dCloneDestroy((e2dClone*) elem);
            break;
        default:
            break;
    }
}

static void
e2dElementIncreaseAttributeSpace(e2dElement* element) {
    element->attributeAlloc *= 2;
    element->attributeNames = (char**) realloc(element->attributeNames, element->attributeAlloc * sizeof (char*));
    element->attributeValues = (char**) realloc(element->attributeValues, element->attributeAlloc * sizeof (char*));
}

void
e2dElementAddAttribute(e2dElement* element, const char* name, const char* value) {
    if (element->attributeNum + 1 > element->attributeAlloc)
        e2dElementIncreaseAttributeSpace(element);

    unsigned int size = strlen(name);
    element->attributeNames[element->attributeNum] =
            (char*) malloc(sizeof (char) *(size + 1));
    strcpy(element->attributeNames[element->attributeNum], name);

    size = strlen(value);
    element->attributeValues[element->attributeNum] =
            (char*) malloc(sizeof (char) *(size + 1));
    strcpy(element->attributeValues[element->attributeNum], value);

    element->attributeNum++;
}

const char*
e2dElementGetAttribute(e2dElement* element,
        const char* name) {
    unsigned int i;
    const char* n1;
    const char* n2;
    for (i = 0; i < element->attributeNum; ++i) {
        n1 = name;
        n2 = element->attributeNames[i];
        if (!strcmp(name, element->attributeNames[i]))
            return element->attributeValues[i];
    }
    return E2D_NULL;
}

e2dPoint
e2dElementGetLocalPosition(const e2dElement* elem) {
    e2dPoint ret;
    ret.x = e2dMatrixGetCell(&(elem->localTransform), 0, 2);
    ret.y = e2dMatrixGetCell(&(elem->localTransform), 1, 2);
    return ret;
}

e2dPoint
e2dElementGetWorldPosition(const e2dElement* elem) {
    e2dMatrix mat = e2dMatrixMultiply(&(elem->scene->root->element.effectiveTransform),
            &(elem->inverseEffectiveTransform));
    e2dPoint localP = e2dElementGetLocalPosition(elem);
    return e2dMatrixApplyToPoint(&mat, &localP);
}

e2dPoint
e2dElementGetRelativePosition(const e2dElement* elem,
        const e2dElement* relativeTo) {
    e2dMatrix mat = e2dMatrixMultiply(&(relativeTo->effectiveTransform),
            &(elem->inverseEffectiveTransform));
    e2dPoint localP = e2dElementGetLocalPosition(elem);
    return e2dMatrixApplyToPoint(&mat, &localP);
}

e2dPoint
e2dElementGetRelativePoint(const e2dElement* elem,
        const e2dElement* relativeTo, const e2dPoint *point) {
    e2dMatrix mat = e2dMatrixMultiply(&(relativeTo->effectiveTransform),
            &(elem->inverseEffectiveTransform));
    return e2dMatrixApplyToPoint(&mat, point);
}

void
e2dElementCalculateBoundingBox(e2dElement* elem) {
    switch (elem->type) {
        case(E2D_GROUP):
            e2dGroupCalculateBoundingBox((e2dGroup*) elem);
            break;
        case(E2D_IMAGE):
            e2dImageCalculateBoundingBox((e2dImage*) elem);
            break;
        case(E2D_PATH):
            e2dPathCalculateBoundingBox((e2dPath*) elem);
            break;
        case(E2D_CLONE):
            e2dCloneCalculateBoundingBox((e2dClone*) elem);
            break;
        default:
            break;
    }
}

void
e2dElementCenterAtBBox(e2dElement* elem, float tx, float ty) {
    switch (elem->type) {
        case(E2D_GROUP):
            e2dGroupCenterAtBBox((e2dGroup*) elem, tx, ty);
            break;
        case(E2D_IMAGE):
            e2dImageCenterAtBBox((e2dImage*) elem, tx, ty);
            break;
        case(E2D_PATH):
            e2dPathCenterAtBBox((e2dPath*) elem, tx, ty);
            break;
        case(E2D_CLONE):
            e2dCloneCenterAtBBox((e2dClone*) elem, tx, ty);
            break;
        default:
            break;
    }
}

static void
e2dElementIncreaseClonesSpace(e2dElement* element) {
    element->clonesAlloc *= 2;
    element->clones = (e2dClone**) realloc(element->clones, element->clonesAlloc * sizeof (e2dClone*));
}

void 
e2dElementAddClone(e2dElement* elem, e2dClone* clone) {
    if (elem->clonesNum + 1 > elem->clonesAlloc)
        e2dElementIncreaseClonesSpace(elem);

    elem->clones[elem->clonesNum] = clone;
    elem->clonesNum++;
}


void 
e2dElementApplyTransformationToAllClones(e2dElement* elem, e2dMatrix *transformation) {
    int i;
    for(i = 0; i < elem->clonesNum; ++i)
    {
        e2dClone* clone = elem->clones[i];
        clone->element.localTransform = e2dMatrixMultiply(&clone->element.localTransform, transformation);
    }
}

void 
e2dElementRecalculateBBoxOnClones(e2dElement* elem)  {
    int i;
    for(i = 0; i < elem->clonesNum; ++i) {
        if(elem->clones[i]->element.bboxHeight == -1)
            continue;
        e2dCloneCalculateBoundingBox(elem->clones[i]);
    }
}

