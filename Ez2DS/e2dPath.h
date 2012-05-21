/**
 * @file   e2dPath.h
 * 
 * @brief  File which contains the e2dPath struct and its "methods".
 * 
 * @author Rui (ruir2c@gmail.com)
 * 
 * @date   February, 2012
 */

#ifndef E2DPATH_H
#define	E2DPATH_H

#include "Ez2DS.h"
#include "e2dElement.h"

    /**
     * @defgroup e2dPath e2dPath
     * @{
     **/

/**
     *  @brief The e2dPathElementType enum defines the possible "substructs" of e2dPathElement.
     *  This is used for reflection. 
     **/
    typedef enum e2dPathElementType {
        E2D_PATHPOINT,
        E2D_PATHCURVE
    } e2dPathElementType;

/**
     *  @brief The e2dPathElementType enum defines the possible control types that
     * each e2dPathElement can be. 
     **/
    typedef enum e2dPathControl {
        E2D_START_SUBPATH,
        E2D_END_SUBPATH,
        E2D_END_SUBPATH_LOOP,
        E2D_NOCONTROL
    } e2dPathControl;

    /**
     *  @brief The e2dPathElement is the "super struct" of all path elements in the scene.
     * Its inheritting functionality works in much the same way as e2dElement, so you should
     * look into it to understand..
     * 
     * @see e2dElement
     * 
     **/
    struct e2dPathElement {
        e2dPathElementType type; /**< Used for reflection, so that if you receive a pointer to
                              * e2dPathElement, you can cast it to either e2dPathPoint or
                              * e2dPathCurve. **/

        e2dPathControl controlType; /**< With this element you can know if you should
                                 * for example, close the sub path by looping to the
                                 * begginning(E2D_END_SUBPATH_LOOP) or not(E2D_END_SUBPATH), 
                                 * or even do nothing (E2D_NOCONTROL).**/
    };

/**
     *  @brief This struct represents a point in the path. It "inherits" from 
     * e2dPathElement by placing it as the first element in the struct, if you 
     * typecast e2dPathPoint* into e2dPathElement*, it will work thus mimicing 
     * inheritance in e.g. C++.
     * 
     **/
    struct e2dPathPoint {
        e2dPathElement element; /**< e2dPathPoint inherits from e2dPathElement. Typecasting
                             * e2dPathPoint* to e2dPathElement* will work.**/

        e2dPoint point; /**< The point of this path element.**/
    };

/**
     *  @brief This struct represents a curve in the path. It is a cubic bezier curve,
     * having two control points. It "inherits" from e2dPathElement by placing 
     * it as the first element in the struct, if you typecast e2dPathPoint* into 
     * e2dPathElement*, it will work thus mimicing inheritance in e.g. C++.
     * 
     **/
    struct e2dPathCurve {
        e2dPathElement element; /**< e2dPathCurve inherits from e2dPathElement. Typecasting
                             * e2dPathCurve* to e2dPathElement* will work.**/

        e2dPoint startPoint; /**< The start point of this curve. Redundant since it's 
                          * the current point in the path. Added for convenience 
                          * so that we can iterate the path without keeping a state 
                          * (knowing current point) which can be annoying given 
                          * subpath loops and such... **/
        e2dPoint controlPoint1; /**< The first control point of the curve. **/
        e2dPoint controlPoint2; /**< The second control point of the curve. **/
        e2dPoint endPoint; /**< The end point the curve. **/
    };

    /**
     *  @brief The e2dPath struct is used for holding the information of path. 
     * The struct is composed directly from the contents
     * of the SVG path element. It "inherits" from e2dElement by placing it as 
     * the first element in the struct, if you typecast e2dPath* into 
     * e2dElement*, it will work thus mimicing inheritance in e.g. C++.
     **/
    struct e2dPath {
        e2dElement element;/**< e2dPath inherits from e2dElement. Typecasting
                            * e2dPath* to e2dElement* will work.**/

        unsigned int pathElementsNum;/**< Number of elements in e2dPath::pathElements Array **/
        e2dPathElement** pathElements;/**< Array containing the path elements **/
        unsigned int pathElementsAlloc;/**< Currently allocated memory in the e2dPath::pathElements **/
    };

    /**
     * @brief   This is the constructor of e2dPath. It returns a pointer to a 
     * new e2dPath. Inside it calls e2dPathInit() to initialize the members
     * of the struct.
     * 
     * @param [in] scene  The e2dScene where this path will belong to.
     * 
     * @retval e2dPath* A newly allocated and initialized pointer to e2dPath.
     * 
     * @see e2dPathInit()
     *
     **/
    E2D_EXPORT e2dPath* 
    e2dPathCreate(const e2dScene* scene);
    
    /**
     * @brief   This method will initialize the members of the struct, i.e.
     * it will allocate the e2dPath::pathElements array, and call e2dElementInit(). It is called
     * by e2dPathCreate().
     *
     *
     * @param [in] path  The e2dPath which will have its members initialized
     * @param [in] scene  The e2dScene where this group will belong to.
     * 
     * 
     * @see e2dPathCreate()
     * @see e2dElementInit()
     *
     **/
    E2D_EXPORT void 
    e2dPathInit(e2dPath *path, const e2dScene* scene);

    /**
     * @brief  Calls e2dPathFreeMembers(), e2dElementFreeMembers(), and 
     * then frees the pointer. e2dElementDestroy() will call this method.
     *
     * @param [in] path  The e2dPath struct which will be destroyed.
     * 
     * @see e2dPathFreeMembers()
     * @see e2dElementFreeMembers()
     * @see e2dElementDestroy()
     **/
    E2D_EXPORT void 
    e2dPathDestroy(e2dPath* path);

    /**
     * @brief   Will free all the dynamically allocated memory inside the e2dPath struct
     * pointed by elem, i.e. it calls free on e2dPath::pathElements.
     *
     * @param [in] path  The e2dPath struct where the members will be freed.
     * 
     * @see e2dPathDestroy()
     * @see e2dElementDestroy()
     **/
    E2D_EXPORT void 
    e2dPathFreeMembers(e2dPath* path);

    /**
     * @brief  Called by the create methods of structs which inherit e2dPathElement 
     * (e.g. e2dPointCreate) This method will initialize the members of the struct, i.e.
     * it will assign type to e2dPathElement::type. 
     *
     *
     * @param [in] elem  e2dPathElement which will have its members initialized.
     * @param [in] type  The type of the path element.
     * 
     * 
     * @see e2dPointCreate()
     * @see e2dCurveCreate()
     *
     **/
    E2D_EXPORT void 
    e2dPathElementInit(e2dPathElement* elem, e2dPathElementType type);

    /**
     * @brief   Will check the type member of elem and call the appropriate
     * destructor (e.g. e2dPointDestroy())
     * @param [in] elem  The e2dPathElement to be destroyed.
     * 
     * 
     * @see e2dPointDestroy()
     * @see e2dCurveDestroy()
     **/
    E2D_EXPORT void 
    e2dPathElementDestroy(e2dPathElement* elem);

    /**
     * @brief   Will free all the dynamically allocated memory inside the e2dPathElement struct
     * pointed by elem. Which is isn't actually any memory, but still it's important
     * to have this method for consistency.
     *
     * @param [in] elem  The e2dPathElement struct where the members will be freed.
     **/
    E2D_EXPORT void 
    e2dPathElementFreeMembers(e2dPathElement* elem);

    /**
     * @brief   This is the constructor of e2dPathPoint. It returns a pointer to a 
     * new e2dPathPoint. Inside it calls e2dPathPointInit() to initialize the members
     * of the struct.
     * 
     * @retval e2dPathPoint* A newly allocated and initialized pointer to e2dPathPoint.
     * 
     * @see e2dPathPointInit()
     *
     **/
    E2D_EXPORT e2dPathPoint* 
    e2dPathPointCreate();

    /**
     * @brief   This method will initialize the members of the struct, i.e.
     * it will place a (0,0) point on the e2dPathPoint::point, and call e2dPathElementInit(). 
     * It is called by e2dPathPointCreate().
     *
     *
     * @param [in] point  The e2dPathPoint which will have its members initialized
     * 
     * 
     * @see e2dPathPointCreate()
     * @see e2dPathElementCreate()
     * @see e2dPathElementInit()
     *
     **/
    E2D_EXPORT void 
    e2dPathPointInit(e2dPathPoint* point);

    /**
     * @brief  Calls e2dPathPointFreeMembers(), e2dPathElementFreeMembers(), and 
     * then frees the pointer. e2dPathElementDestroy() will call this method.
     *
     * @param [in] point  The e2dPathPoint struct which will be destroyed.
     * 
     * @see e2dPathPointFreeMembers()
     * @see e2dPathElementFreeMembers()
     * @see e2dPathElementDestroy()
     **/
    E2D_EXPORT void 
    e2dPathPointDestroy(e2dPathPoint* point);

    /**
     * @brief   Will free all the dynamically allocated memory inside the e2dPathPoint struct
     * pointed by point, which is actually none, but is kept here for consistency. Called by
     * e2dPathPointDestroy();
     *
     * @param [in] point  The e2dPathPoint struct where the members will be freed.
     * 
     * @see e2dPathPointDestroy()
     * @see e2dPathElementDestroy()
     **/
    E2D_EXPORT void 
    e2dPathPointFreeMembers(e2dPathPoint* point);

    /**
     * @brief   This is the constructor of e2dPathCurve. It returns a pointer to a 
     * new e2dPathCurve. Inside it calls e2dPathCurveInit() to initialize the members
     * of the struct.
     * 
     * @retval e2dPathCurve* A newly allocated and initialized pointer to e2dPathCurve.
     * 
     * @see e2dPathCurveInit()
     *
     **/
    E2D_EXPORT e2dPathCurve* 
    e2dPathCurveCreate();
    
    /**
     * @brief   This method will initialize the members of the struct, i.e.
     * it will place a (0,0) point on the points of the struct, and call e2dPathElementInit(). 
     * It is called by e2dPathCurveCreate().
     *
     *
     * @param [in] curve  The e2dPathCurve which will have its members initialized
     * 
     * 
     * @see e2dPathCurveCreate()
     * @see e2dPathElementCreate()
     * @see e2dPathElementInit()
     *
     **/
    E2D_EXPORT void 
    e2dPathCurveInit(e2dPathCurve* curve);

    /**
     * @brief  Calls e2dPathCurveFreeMembers(), e2dPathElementFreeMembers(), and 
     * then frees the pointer. e2dPathElementDestroy() will call this method.
     *
     * @param [in] curve  The e2dPathCurve struct which will be destroyed.
     * 
     * @see e2dPathCurveFreeMembers()
     * @see e2dPathElementFreeMembers()
     * @see e2dPathElementDestroy()
     **/
    E2D_EXPORT void 
    e2dPathCurveDestroy(e2dPathCurve* curve);

    /**
     * @brief   Will free all the dynamically allocated memory inside the e2dPathCurve struct
     * pointed by curve, which is actually none, but is kept here for consistency. Called by
     * e2dPathCurveDestroy();
     *
     * @param [in] curve  The e2dPathCurve struct where the members will be freed.
     * 
     * @see e2dPathCurveDestroy()
     * @see e2dPathElementDestroy()
     **/
    E2D_EXPORT void 
    e2dPathCurveFreeMembers(e2dPathCurve* curve);
    
    /**
    * @brief   Will add a path element to the e2dPath::pathElements array. Increases the size of
    * the array if necessary.
    *
    * @param [in] path  The e2dPath where the element will be added.
    * @param [in] elem  The new path element.
    * 
    */
    E2D_EXPORT void 
    e2dPathAddPathElement(e2dPath* path, e2dPathElement *elem);
    
    /**
     * @brief   Calculates the bounding box of the path using by checking the space occupied
     * ball the elements in the path. For the curves, it uses an algorithm taken from here
     * http://processingjs.nihongoresources.com/decasteljau/
     *
     * @param [in] path  The e2dPath struct where the bounding box will be calculated.
     * 
     * 
     * @see e2dElementCalculateBoundingBox()
     **/
    E2D_EXPORT void 
    e2dPathCalculateBoundingBox(e2dPath* path);

        /**
     * @brief   Adds a transformation to the path which subtracts the position
     * of the Bounding Box (offset by (tx, ty)), and adds the position of the bounding box to all the 
     * path elements, effectively bringing the origin of the local coordinate system
     * to the bounding box. See e2dElementCenterAtBBox() for an explanation on "tx"
     * and "ty".
     *
     * @param [in] path  The e2dPath struct to be centered.
     * @param [in] tx  x offset in BBox width units.
     * @param [in] ty  y offset in BBox height units.
     * 
     * @see e2dElementCenterAtBBox()
     **/
    E2D_EXPORT void 
    e2dPathCenterAtBBox(e2dPath* path, float tx, float ty);

    /**
     *  @brief An iterator for the path elements.
     * 
     **/
    struct e2dPathElementIterator {
        e2dPath* path; /**< The path being iterated**/
        unsigned int currentIndex; /**< Current index relative to e2dPath::pathElements**/
    };
    /**
     * @brief   Makes an iterator to the path elements of the path.
     * 
     * @param [in] path The path to be iterated. 
     * 
     * @retval e2dPathElementIterator* The iterator.
     * 
     *
     **/
    E2D_EXPORT e2dPathElementIterator 
    e2dPathGetElementIterator(e2dPath* path);
    
    /**
     * @brief   Returns the current path element and advances.
     * 
     * @param [in] iter The path iterator. 
     * 
     * @retval e2dPathElement* The path element. Remember that you can cast this pointer
     * to the actual path element type by checking e2dPathElement::type.
     * 
     *
     **/
    E2D_EXPORT e2dPathElement* 
    e2dPathElementIteratorNext(e2dPathElementIterator* iter);
    
    /**
     * @brief   Checks if we have a path element at current path element pointed by iter,
     * if not, we have reached the end of the path elements list.
     * 
     * @param [in] iter The path iterator. 
     * 
     * @retval E2D_BOOL If we still have a path element, returns E2D_TRUE, if not, 
     * returns E2D_FALSE.
     * 
     *
     **/
    E2D_EXPORT E2D_BOOL 
    e2dPathElementIteratorHasNext(e2dPathElementIterator* iter);

    /**
     * @}
     **/

#endif	/* E2DPATH_H */

