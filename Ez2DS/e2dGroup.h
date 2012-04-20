
/**
 * @file   e2dGroup.h
 * 
 * @brief  File which contains the e2dGroup struct and its "methods".
 * 
 * @author Rui (ruir2c@gmail.com)
 * 
 * @date   February, 2012
 */

#ifndef E2DGROUP_H
#define	E2DGROUP_H

#include "Ez2ds.h"
#include "e2dElement.h"

#ifdef	__cplusplus
extern "C" {
#endif
    /**
     * @defgroup e2dGroup
     * @{
     **/

    /**
     *  @brief The e2dStruct is used to group elements in the scene, called childs.
     * This struct is created from the "g" element in SVG. It "inherits" from 
     * e2dElement by placing it as the first element in the struct, if you 
     * typecast e2dStruct* into e2dElement*, it will work thus mimicing 
     * inheritance in e.g. C++.
     * 
     **/
    struct e2dGroup {
        e2dElement element; /**< e2dGroup inherits from e2dElement. Typecasting
                             *< e2dGroup* to e2dElement* will work.**/
        unsigned int childNum;/**< Number of children in e2dGroup::childListArray **/
        e2dElement** childList; /**< child list array, allocated size given by
                                 *< e2dGroup::childListAlloc. 
                                 *< @see e2dGroupAddChild()**/
        unsigned int childListAlloc;/**< Allocated size of e2dGroup::childList**/

    };

    /**
     * @brief   This is the constructor of e2dGroup. It returns a pointer to a 
     * new e2dGroup. Inside it calls e2dGroupInit() to initialize the members
     * of the struct.
     * 
     * @param [in] scene  The e2dScene where this group will belong to.
     * 
     * @retval e2dGroup* A newly allocated and initialized pointer to e2dGroup.
     * 
     * @see e2dGroupInit()
     *
     **/
    e2dGroup*
    e2dGroupCreate(const e2dScene* scene);

    /**
     * @brief   This method will initialize the members of the struct, i.e.
     * it will allocate the e2dGroup::childList array, and call e2dElementInit(). It is called
     * by e2dGroupCreate().
     *
     *
     * @param [in] group  The e2dGroup which will have its members be initialized
     * @param [in] scene  The e2dScene where this group will belong to.
     * 
     * 
     * @see e2dGroupCreate()
     * @see e2dElementInit()
     *
     **/
    void
    e2dGroupInit(e2dGroup *group, const e2dScene* scene);


    /**
     * @brief  Calls e2dGroupFreeMembers(), e2dElementFreeMembers(), and 
     * then frees the pointer. e2dElementDestroy() will call this method.
     *
     * @param [in] group  The e2dGroup struct which will be destroyed.
     * 
     * @see e2dGroupFreeMembers()
     * @see e2dElementFreeMembers()
     * @see e2dElementDestroy()
     **/
    void
    e2dGroupDestroy(e2dGroup* group);    
    
    /**
     * @brief   Will free all the allocated memory inside the e2dGroup struct
     * pointed by elem, i.e. it calls e2dElementDestroy() on all the children,
     * and frees the e2dGroup::childList array (Warning, this might change in future versions).
     * It is called by e2dGroupDestroy().
     *
     * @param [in] group  The e2dGroup struct where the members will be freed.
     * 
     * @see e2dGroupDestroy()
     * @see e2dElementDestroy()
     **/
    void
    e2dGroupFreeMembers(e2dGroup* group);

    /**
     * @brief   Will add an element to the e2dGroup::childList array, increasing
     * allocated space if necessary. Also sets e2dElement::parent in "element" to 
     * be "group".
     *
     * @param [in] group  The e2dGroup struct where a new child will be added.
     * @param [in] element  The new child.
     * 
     * 
     **/
    void
    e2dGroupAddChild(e2dGroup* group, e2dElement* element);

    /**
     * @brief   Calculates the bounding box of the group using the
     * bounding boxes of the children. If a child doesn't have the bounding
     * box calculated, then e2dElementCalculateBoundingBox() is called in
     * the child.
     *
     * @param [in] group  The e2dGroup struct where the bounding box will be calculated.
     * 
     * 
     * @see e2dElementCalculateBoundingBox()
     **/
    void
    e2dGroupCalculateBoundingBox(e2dGroup* group);

    /**
     * @brief   Adds a transformation to the group which subtracts the position
     * of the Bounding Box, and adds the position of the bounding box to all the 
     * children, effectively bringing the origin of the local coordinate system
     * to the bounding box. See e2dElementCenterAtBBox() for an explanation on "tx"
     * and "ty".
     *
     * @param [in] group  The e2dGroup struct to be centered.
     * @param [in] tx  x offset in BBox width units.
     * @param [in] ty  y offset in BBox height units.
     * 
     * @see e2dElementCenterAtBBox()
     **/
    void
    e2dGroupCenterAtBBox(e2dGroup* group, float tx, float ty);

    /**
     * @brief  Recursively removes all the groups which are children (directly
     * or indirectly) and makes all the remaining elements have a e2dElement::localTransform
     * which yields a transformation equal to if there were groups. I.e., it flattens
     * the group, making it have only one level. Calling this on the e2dScene::root will
     * make "group" be the only in the tree. !!Warning!! custom (and non custom) tags written 
     * in groups are lost!
     *
     * @param [in] group  The e2dGroup to be flattened.
     * 
     **/
    void
    e2dGroupFlatten(e2dGroup* group);


    /**
     *  @brief An iterator for the children of e2dGroup.
     * 
     **/
    struct e2dGroupIterator {
        e2dGroup* group;/**< This iterator is working on this group. **/
        unsigned int currentIndex;/**< Current index in e2dGroup::childList.**/
    };

    
    /**
     * @brief   Makes an iterator to the children of the group.
     * 
     * @param [in] group The group to be iterated. 
     * 
     * @retval e2dGroupIterator* The iterator.
     * 
     *
     **/
    e2dGroupIterator
    e2dGroupGetChildIterator(e2dGroup* group);

    /**
     * @brief   Returns the current child and advances.
     * 
     * @param [in] iter The group iterator. 
     * 
     * @retval e2dElement* The child.
     * 
     *
     **/
    e2dElement*
    e2dGroupIteratorNext(e2dGroupIterator* iter);

    /**
     * @brief   Checks if we have a child at current element pointer by iter,
     * if not, we have reached the end of the child list.
     * 
     * @param [in] iter The group iterator. 
     * 
     * @retval E2D_BOOL If we still have a child, returns E2D_TRUE, if not, 
     * returns E2D_FALSE.
     * 
     *
     **/
    E2D_BOOL
    e2dGroupIteratorHasNext(e2dGroupIterator* iter);



    /**
     * @}
     **/

#ifdef	__cplusplus
}
#endif

#endif	/* E2DGROUP_H */

