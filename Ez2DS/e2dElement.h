/**
 * @file   e2dElement.h
 * 
 * @brief  File which contains the e2dElement struct and its "methods".
 * 
 * @author Rui (ruir2c@gmail.com)
 * 
 * @date   February, 2012
 */

#ifndef E2DELEMENT_H
#define	E2DELEMENT_H


#include "Ez2DS.h"
#include "e2dMatrix.h"
#include "e2dPoint.h"

    /**
     * @defgroup e2dElement e2dElement
     * @{
     **/

    /**
     *  @brief The e2dElementType enum defines the possible "substructs" of e2dElement.
     *  This is used for reflection. 
     **/
    typedef enum e2dElementType {
        E2D_GROUP,
        E2D_PATH,
        E2D_IMAGE,
        E2D_CLONE
    } e2dElementType;

     /**
     *  @brief The e2dElement struct is the base of all elements in the scene.
     *  Common scene information such as id, attribute values or transformations are 
     *  saved in the e2dElement struct. You are not meant to instance this struct by
     *  itself. By creating other elements such as e2dGroup or e2dImage, this struct
     *  will be automatically allocated in them. This "inheritance" is mimic'd by 
     *  placing the e2dElement struct as the first element in structs which are
     *  meant to be "substructs" of it.
     * 
     **/
     struct e2dElement {
        e2dScene* scene;/**< Belongs to this scene **/
        e2dElementType type;/**< Used for reflection **/
        char* id;/**< ID taken from SVG **/
        unsigned int unique_id; /**< unique id for this execution. 
                                 * (static int in e2dGroupInit() ) **/

        e2dMatrix localTransform; /**< LocalTransform taken from SVG **/
        e2dMatrix effectiveTransform; /**< Actual transform calculated applied here.
                                       * @see e2dSceneCalculateEffectiveTransforms() **/
        e2dMatrix inverseEffectiveTransform;   /**< Useful for point transformations.
                                                * 
                                                * @see e2dElementGetLocalPosition()
                                                * @see e2dElementGetWorldPosition()
                                                * @see e2dElementGetRelativePosition()
                                                * @see e2dElementGetRelativePoint()**/
        
        e2dGroup* parent;/**< parent of the element in the scene tree.**/
        
        unsigned int attributeNum;/**< Number of attributes in e2dElement::attributeNames and
                                   * e2dElement::attributeValues. **/
        unsigned int attributeAlloc;/**< Allocated size of e2dElement::clones**/
        char** attributeNames;  /**< Attribute names array, allocated size given by
                                 * e2dGroup::attributeAlloc. 
                                 * @see e2dElementAddAttribute()**/
        char** attributeValues;/**< Attribute values array, allocated size given by
                                 * e2dGroup::attributeAlloc. 
                                 * @see e2dElementAddAttribute()**/

        float bboxWidth;/**< Bounding box width.
                         * @see e2dElementCalculateBoundingBox()
                         * @see e2dElementCenterAtBBox() **/
        float bboxHeight;/**< Bounding box height.
                         * @see e2dElementCalculateBoundingBox()
                         * @see e2dElementCenterAtBBox() **/
        e2dPoint bboxPosition;/**< Bounding box position.
                         * @see e2dElementCalculateBoundingBox()
                         * @see e2dElementCenterAtBBox() **/
        
        e2dClone** clones;/**< Clones array, allocated size given by
                            * e2dElement::clonesAlloc. 
                            * @see e2dElementAddClone()**/
        unsigned int clonesNum;/**< Number of clones in e2dElement::clones**/
        unsigned int clonesAlloc;/**< Allocated size of e2dElement::clones**/
    };


    /**
     * @brief   Called by the create methods of 
     *          structs which inherit e2dElement (e.g. e2dGroupCreate). Will
     *          initialize all members of the struct with the parameters of this
     *          method and with default values on everything else.
     *
     *
     * @param [in] element  The e2dElement which will have its members be initialized
     * @param [in] type  The type of the struct where element is placed (e.g. if this 
     *                   element is placed in a e2dGroup then E2D_GROUP is passed here). 
     *                   This grants reflection capabilities to some level.
     * @param [in] scene  The e2dScene where this element will belong to.
     * 
     * 
     * @see e2dGroupCreate()
     * @see e2dImageCreate()
     * @see e2dPathCreate()
     *
     **/
    void
    e2dElementInit(e2dElement *element, e2dElementType type, const e2dScene* scene);

    /**
     * @brief   Will check the type member of elem and call the appropriate
     * destructor (e.g. e2dGroupDestroy())
     * @param [in] elem  The e2dElement to be destroyed.
     * 
     * 
     * @see e2dGroupDestroy()
     * @see e2dImageDestroy()
     * @see e2dPathDestroy()
     **/
    void E2D_EXPORT 
    e2dElementDestroy(e2dElement* elem);

    /**
     * @brief   Will free all the dynamically allocated memory inside the e2dElement struct
     * pointed by elem.
     *
     * @param [in] elem  The e2dElement struct where the members will be freed.
     **/
    void E2D_EXPORT 
    e2dElementFreeMembers(e2dElement* elem);

    /**
    * @brief   Will add an attribute to the element. Increases the size of
    * the array if necessary.
    *
    * @param [in] elem  The e2dElement where the attribute will be added.
    * @param [in] name  The name of the attribute.
    * @param [in] value The value of the attribute.
    * 
    */
    E2D_EXPORT void 
    e2dElementAddAttribute(e2dElement* elem,
            const char* name, const char* value);

    
    

    /**
    * @brief   Returns the value of an attribute with a given name.
    *
    * @param [in] elem  The e2dElement containing the attribute.
    * @param [in] name  The name of the attribute.
    * 
    * @retval const char* The value of the name. Null if not found.
    * 
    */
    E2D_EXPORT const char*
    e2dElementGetAttribute(e2dElement* elem,
            const char* name);

    /**
    * @brief   Returns the position of the element, taken from the localTransform.
    *
    * @param [in] elem  The e2dElement where the position will be requested.
    * 
    * @retval e2dPoint The position.
    **/
    E2D_EXPORT e2dPoint 
    e2dElementGetLocalPosition(const e2dElement* elem);

    /**
     * @brief   UNTESTED Will get the local position (e2dElementGetLocalPosition())
     * and multiply it by the inverseEffectiveTransform and obtain the world position.
     * Needs effective transformations to be calculated (
     * e2dSceneCalculateEffectiveTransforms() has been called)
     *
     * @param [in] elem  The e2dElement where the position will be requested.
     * 
     * @retval e2dPoint The position.
     * 
     * @see e2dElementGetLocalPosition()
     * @see e2dSceneCalculateEffectiveTransforms()
    **/
    E2D_EXPORT e2dPoint 
    e2dElementGetWorldPosition(const e2dElement* elem);
    
    /**
     * @brief   UNTESTED Will get the relative transformation by multiplying
     * the effective transform of elem with the inverse effective transform of
     * relativeTo. The multiply it with the local position of elem (e2dElementGetLocalPosition()).
     * Needs effective transformations to be calculated (e2dSceneCalculateEffectiveTransforms() 
     * has been called)
     *
     * @param [in] elem  The e2dElement where the position will be requested.
     * @param [in] relativeTo  The result will be relative to this e2dElement.
     * 
     * @retval e2dPoint The position.
     * 
     * @see e2dElementGetLocalPosition()
     * @see e2dSceneCalculateEffectiveTransforms()
    **/
    E2D_EXPORT e2dPoint 
    e2dElementGetRelativePosition(const e2dElement* elem,
            const e2dElement* relativeTo);

    /**
     * @brief   UNTESTED Will get the relative transformation by multiplying
     * the effective transform of elem with the inverse effective transform of
     * relativeTo. The multiply it with point.
     * Needs effective transformations to be calculated (e2dSceneCalculateEffectiveTransforms() 
     * has been called).
     *
     * @param [in] elem  The e2dElement where the position will be requested.
     * @param [in] relativeTo  The result will be relative to this e2dElement.
     * @param [in] point  The point to be transformed.
     * 
     * @retval e2dPoint The position.
     * 
     * @see e2dElementGetLocalPosition()
     * @see e2dSceneCalculateEffectiveTransforms()
    **/
    E2D_EXPORT e2dPoint 
    e2dElementGetRelativePoint(const e2dElement* elem,
            const e2dElement* relativeTo, const e2dPoint *point);

    /**
     * @brief   Will check type and calculate the appropriate method
     * (e.g. e2dGroupCalculateBoundingBox())
     *
     * @param [in] elem  The e2dElement to calculate.
     * 
     * @see e2dGroupCalculateBoundingBox()
     * @see e2dImageCalculateBoundingBox()
     * @see e2dPathCalculateBoundingBox()
     * 
    **/
    E2D_EXPORT void
    e2dElementCalculateBoundingBox(e2dElement* elem);
    
    /**
     * @brief   Needs bounding box to have been calculated.
     * Will check type and calculate the appropriate method
     * (e.g. e2dGroupCenterAtBBox()). (tx, ty) will define where in 
     * the bounding box, the element will be centered, e.g. (0,0, will center
     * on the top left corner, (0.5, 0.5) will center on the center of the bbox.
     *
     * @param [in] elem  The e2dElement to center.
     * @param [in] tx  x offset in BBox width units.
     * @param [in] ty  y offset in BBox height units.
     * 
     * 
     * @see e2dElementCalculateBoundingBox()
     * @see e2dGroupCenterAtBBox()
     * @see e2dImageCenterAtBBox()
     * @see e2dPathCenterAtBBox()
    **/
    E2D_EXPORT void 
    e2dElementCenterAtBBox(e2dElement* elem, float tx, float ty);
    
    /**
     * @brief   Adds a clone that references elem to the e2dElement.clonesReferencingThis array.
     * 
     * @param [in] elem  Referenced element
     * @param [in] clone  Referring clone.
     * 
    **/
    E2D_EXPORT void 
    e2dElementAddClone(e2dElement* elem, e2dClone* clone);
    
    /**
     * @brief   Applies a transformation to all clones referencing this element.
     * This is specially useful when you need to move an element, but don't want all
     * the clones to move in parallel, so you apply the inverse transformation to all clones.
     * This is used internally in e2dGroupCenterAtBBox(), since when you center the group you
     * move all the elements under it.
     * 
     * @param [in] elem  The element to have its clones moved.
     * @param [in] transformation  The transformation.
     * 
     * @see e2dElementCenterAtBBox()
    **/
    E2D_EXPORT void 
    e2dElementApplyTransformationToAllClones(e2dElement* elem, e2dMatrix *transformation);
    
    
    /**
     * @brief   Recalculates the bounding box on the clones. This is useful after you change
     * the bounding box of the element and want the clones to reflect that change.
     * 
     * @param [in] elem  The element to have its clones' bounding boxes recalculated.
     * 
     * @see e2dElementCenterAtBBox()
    **/
    E2D_EXPORT void 
    e2dElementRecalculateBBoxOnClones(e2dElement* elem);
    



    /**
     * @}
     **/


#endif	/* E2DELEMENT_H */

