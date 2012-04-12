/* 
 * File:   e2dGroup.h
 * Author: Rui Campos
 *
 * Created on 29 de Março de 2012, 17:22
 */

#ifndef E2DGROUP_H
#define	E2DGROUP_H

#include "Ez2ds.h"
#include "e2dElement.h"

#ifdef	__cplusplus
extern "C" {
#endif
    

struct e2dGroup {
    e2dElement element;

    e2dGroup* parent;

    unsigned int childNum;
    e2dElement** childList;
    unsigned int childListAlloc;

};

e2dGroup* 
e2dGroupCreate(const e2dScene* scene, const e2dGroup* parent);

void
e2dGroupInit(e2dGroup *group, const e2dScene* scene, const e2dGroup* parent);

void 
e2dGroupFreeMembers(e2dGroup* group);

void 
e2dGroupDestroy(e2dGroup* group);

void 
e2dGroupAddChild(e2dGroup* group, e2dElement* element);

void 
e2dGroupCalculateBoundingBox(e2dGroup* group);

void 
e2dGroupCenterAtBBox(e2dGroup* group, float tx, float ty);

void 
e2dGroupFlatten(e2dGroup* group);

struct e2dGroupIterator  {
    e2dGroup* group;
    unsigned int currentIndex;
};

e2dGroupIterator
e2dGroupGetChildIterator(e2dGroup* group);

e2dElement* 
e2dGroupIteratorNext(e2dGroupIterator* iter);

E2D_BOOL
e2dGroupIteratorHasNext(e2dGroupIterator* iter);




#ifdef	__cplusplus
}
#endif

#endif	/* E2DGROUP_H */

