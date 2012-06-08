/**
 * @file   e2dClone.h
 * 
 * @brief  File which contains the e2dClone struct and its "methods".
 * 
 * @author Rui (ruir2c@gmail.com)
 * 
 * @date   May, 2012
 */

#ifndef E2DCLONE_H
#define	E2DCLONE_H

#include "Ez2DS.h"
#include "e2dElement.h"

    /**
     * @defgroup e2dClone e2dClone
     * @{
     **/

    /**
     *  @brief The e2dClone struct is used for holding a pointer to another element
     * in the scene, by having its ID. It is taken from the use tag in SVG, with the
     * exception of the (width,height) attributes being ignored, as they seem
     * to be useless in Inkscape. 
     * 
     * e2dClone::pointsToElement is added for convenience. When you load a scene,
     * all clones are dereferenced (using e2dCloneDereference()) and the result is 
     * saved here.
     * 
     * 
     * It "inherits" from e2dElement by placing it as 
     * the first element in the struct, if you typecast e2dClone* into 
     * e2dElement*, it will work thus mimicing inheritance in e.g. C++.
     * 
     **/
    struct e2dClone {
        e2dElement element;/**< e2dClone inherits from e2dElement. Typecasting
                            * e2dClone* to e2dElement* will work.**/
        e2dPoint position; /**< Position of the clone, refers to the x and y attributes
                            * of the SVG specification for clones.**/
        
        char* pointsToID;/**< ID of the element pointed by this struct **/
        e2dElement* pointsToElement; /**< The actual element pointed by this clone,
                                      * this is calculated by the e2dSceneUpdateClones() method **/
    };

    /**
     * @brief   This is the constructor of e2dClone. It returns a pointer to a 
     * new e2dClone. Inside it calls e2dCloneInit() to initialize the members
     * of the struct.
     * 
     * @param [in] scene  The e2dScene where this clone will belong to.
     * 
     * @retval e2dClone* A newly allocated and initialized pointer to e2dClone.
     * 
     * @see e2dCloneInit()
     *
     **/
    E2D_EXPORT e2dClone* 
    e2dCloneCreate(const e2dScene* scene);

    /**
     * @brief   This method will initialize the members of the struct, i.e.
     * it will zero the members, and call e2dElementInit(). It is called
     * by e2dCloneCreate().
     *
     *
     * @param [in] clone  The e2dClone which will have its members initialized.
     * @param [in] scene  The e2dScene where this group will belong to.
     * 
     * 
     * @see e2dCloneCreate()
     * @see e2dElementInit()
     *
     **/
    E2D_EXPORT void 
    e2dCloneInit(e2dClone *clone, const e2dScene* scene);

    /**
     * @brief  Calls e2dCloneFreeMembers(), e2dElementFreeMembers(), and 
     * then frees the pointer. e2dElementDestroy() will call this method.
     *
     * @param [in] clone  The e2dClone struct which will be destroyed.
     * 
     * @see e2dCloneFreeMembers()
     * @see e2dElementFreeMembers()
     * @see e2dElementDestroy()
     **/
    void E2D_EXPORT 
    e2dCloneDestroy(e2dClone* clone);
    
    /**
     * @brief   Will free all the dynamically allocated memory inside the e2dClone struct
     * pointed by elem, i.e. it checks if e2dClone::pointsTo has been defined and frees
     * the pointer. It is called by e2dCloneDestroy().
     *
     * @param [in] clone  The e2dClone struct where the members will be freed.
     * 
     * @see e2dCloneDestroy()
     * @see e2dElementDestroy()
     **/
    E2D_EXPORT void 
    e2dCloneFreeMembers(e2dClone* clone);
    
    /**
     * @brief   This method simply calls e2dGroupSearchByID() on the root of the scene
     * where this clone belongs to, and returns the result. You usually do not need this
     * as the target clone is already provided in e2dClone::pointsToElement . If you receive a clone here
     * it means that you have a clone of a clone, which is usually not desired, but quite
     * common problem. To avoid this, you should always call e2dCloneNormalize() to remove
     * the middle clones.
     *
     * @param [in] clone  The e2dClone struct where the e2dElement will be dereferenced.
     * 
     * @retval e2dElement* The referenced element.
     * 
     * @see e2dCloneNormalize()
     * @see e2dGroupSearchByID()
     **/
    E2D_EXPORT e2dElement*
    e2dCloneDereference(e2dClone* clone);
    
    /**
     * @brief   This method, will deference the clone recursively until it finds something
     * which is not clone, it will save the transformations of each redirection and apply
     * to this clone, making it point to the actual non-clone element. It is useful to do this when you 
     * accidentally make clones of clones.
     *
     * @param [in] clone  The e2dClone struct to be normalized.
     * 
     **/
    E2D_EXPORT void
    e2dCloneNormalize(e2dClone* clone);
    

    /**
     * @brief   Will check the element pointed by this clone, check if the element already has a BoundingBox, if it doesn't, call 
     * e2dElementCalculateBoundingBox() on it. Using the bounding boxes limits, we will calculate the bounding box in this
     * element.
     * This method is also called by e2dElementCalculateBoundingBox() using the reflection provided
     * by the e2dElement::type attribute.
     *
     * @param [in] clone  The e2dClone struct where the bounding box will be calculated.
     * 
     * 
     * @see e2dElementCalculateBoundingBox()
     **/
    E2D_EXPORT void 
    e2dCloneCalculateBoundingBox(e2dClone* clone);

    /**
     * @brief   Adds a transformation to the clone which subtracts the position (offset by (tx,ty))
     * of the Bounding Box, and adds the position of the bounding box to the clone
     * position, effectively bringing the origin of the local coordinate system
     * to the bounding box. See e2dElementCenterAtBBox() for an explanation on "tx"
     * and "ty".
     *
     * @param [in] clone  The e2dClone struct to be centered.
     * @param [in] tx  x offset in BBox width units.
     * @param [in] ty  y offset in BBox height units.
     * 
     * @see e2dElementCenterAtBBox()
     **/
    E2D_EXPORT void 
    e2dCloneCenterAtBBox(e2dClone* clone, float tx, float ty);


    /**
     * @}
     **/

#endif	/* E2DCLONE_H */

