/**
 * @file   e2dScene.h
 * 
 * @brief  File which contains the e2dScene struct and its "methods".
 * 
 * @author Rui (ruir2c@gmail.com)
 * 
 * @date   February, 2012
 */

#ifndef E2DSCENE_H
#define	E2DSCENE_H

    
#include "Ez2DS.h"

    /**
     * @defgroup e2dScene e2dScene
     * @{
     **/

    /**
     *  @brief The e2dScene struct defines a scene obtained from an SVG file.
     * The struct contains the root under which all the objects in the scene 
     * can be accessed.
     * 
     **/
    struct e2dScene {
        e2dGroup* root; /**< The root of the scene **/
    };
    
    /**
     * @brief   Assigns the effective transform (calculated by multiplying the local 
     * transform with the effective transform of the parent element) to every 
     * element in the scene. It is useful to have this information for 
     * calculating relative positions(for example, knowing world positions, or 
     * positions of elements relative to other elements.
     *
     *
     * @param [in] scene  The e2dScene which the elements will have their effective
     * transformations calculated
     * 
     * 
     * @see e2dElementGetLocalPosition()
     * @see e2dElementGetWorldPosition()
     * @see e2dElementGetRelativePosition()
     * @see e2dElementGetRelativePoint()
     *
     **/
    E2D_EXPORT void 
    e2dSceneCalculateEffectiveTransforms(e2dScene* scene); 
    
    /**
     * @brief   Calls e2dElementCenterAtBBox on all the elements in the scene. Needs
     * Bounding Boxes to have been calculated. See e2dGroupCenterAtBBox() for
     * an explanation on the tx and ty parameters.
     *
     * @param [in] scene  The e2dScene to have its elements centered.
     * @param [in] tx  x offset in BBox width units.
     * @param [in] ty  y offset in BBox height units.
     * 
     * @see e2dGroupCenterAtBBox()
     * @see e2dSceneCalculateAllBBox()
     **/
    E2D_EXPORT void 
    e2dSceneCenterAllAtBBox(e2dScene* scene, float tx, float ty);
    
    
    /**
     * @brief   Calls e2dGroupCalculateBBox() on the root of the scene.
     *
     * @param [in] scene  The e2dScene struct where its elements will have their
     * Bounding Boxes calculated.
     * 
     * @see e2dGroupCenterAtBBox()
     **/
    E2D_EXPORT void 
    e2dSceneCalculateAllBBox(e2dScene* scene);
    
    

    /**
     * @brief   Reads the SVG in the path "file" using MiniXML (http://minixml.org/)
     * and creates a e2dScene struct which is returned.
     *
     * @param [in] file Path to the SVG file.
     * 
     * @retval e2dScene The newly created scene.
     * 
     **/
    E2D_EXPORT e2dScene* 
    createSceneFromFile(char* file);
    
    /**
     *  @brief This struct represents the results returns by e2dSceneSearch. You should
     * always destroy the result with e2dSceneSearchResultDestroy().
     * 
     * @see e2dSceneSearch()
     * @see e2dSceneSearchResultDestroy() 
     * 
     **/
    struct e2dSceneSearchResult {
        
        unsigned int resultListNum;/**< Number of elements in e2dSceneSearchResult::resultList Array **/
        e2dElement** resultList;/**< Array containing the resulting elements **/
        unsigned int resultListAlloc;/**< Currently allocated memory in e2dSceneSearchResult::resultList **/
    };
    
    /**
     *  @brief Currently searches the tree for an element with an ID equal to searchString.
     * Features planned are for searching by type or by attribute and value combination, all with using
     * a path. For example, the search string '**\=tag\+image' will return all the images which are children
     * of an element with a tag attribute.
     **/
    e2dSceneSearchResult* 
    e2dSceneSearch(e2dScene* scene, char * searchString);
    
    /**
     *  @brief Destroys the search result struct. Call on the results of e2dSceneSearch()
     * when you are done with them.
     * 
     **/
    void 
    e2dSceneSearchResultDestroy(e2dSceneSearchResult* ssr);
    
    
    
    

    /**
     * @}
     **/

#endif	/* E2DSCENE_H */

