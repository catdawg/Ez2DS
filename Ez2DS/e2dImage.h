/**
 * @file   e2dImage.h
 * 
 * @brief  File which contains the e2dImage struct and its "methods".
 * 
 * @author Rui (ruir2c@gmail.com)
 * 
 * @date   February, 2012
 */

#ifndef E2DIMAGE_H
#define	E2DIMAGE_H

#include "Ez2DS.h"
#include "e2dElement.h"

#ifdef	__cplusplus
extern "C" {
#endif

    /**
     * @defgroup e2dImage
     * @{
     **/

    /**
     *  @brief The e2dImage struct is used for holding the paths to images and 
     * their size and position. The struct is composed directly from the contents
     * of the SVG image element. It "inherits" from e2dElement by placing it as 
     * the first element in the struct, if you typecast e2dStruct* into 
     * e2dElement*, it will work thus mimicing inheritance in e.g. C++.
     * 
     **/
    struct e2dImage {
        e2dElement element;/**< e2dImage inherits from e2dElement. Typecasting
                            * e2dImage* to e2dElement* will work.**/
        e2dPoint position;/**< Position of the image. Note that it is after applying the 
                           * transformation present in e2dElement::localTransform. **/
        float width;/**< Width of the image, may be -1 if not defined in the SVG**/
        float height;/**< Height of the image, may be -1 if not defined in the SVG**/
        
        char* imagePath; /**< Path to the image. This is taken directly from the
                          * SVG, so if you are getting a local path for example,
                          * you need to fix it on the SVG. **/
    };

    /**
     * @brief   This is the constructor of e2dImage. It returns a pointer to a 
     * new e2dImage. Inside it calls e2dImageInit() to initialize the members
     * of the struct.
     * 
     * @param [in] scene  The e2dScene where this image will belong to.
     * 
     * @retval e2dImage* A newly allocated and initialized pointer to e2dImage.
     * 
     * @see e2dImageInit()
     *
     **/
    e2dImage*
    e2dImageCreate(const e2dScene* scene);

    /**
     * @brief   This method will initialize the members of the struct, i.e.
     * it will zero the members, and call e2dElementInit(). It is called
     * by e2dImageCreate().
     *
     *
     * @param [in] image  The e2dImage which will have its members initialized.
     * @param [in] scene  The e2dScene where this group will belong to.
     * 
     * 
     * @see e2dImageCreate()
     * @see e2dElementInit()
     *
     **/
    void
    e2dImageInit(e2dImage *image, const e2dScene* scene);

    /**
     * @brief  Calls e2dImageFreeMembers(), e2dElementFreeMembers(), and 
     * then frees the pointer. e2dElementDestroy() will call this method.
     *
     * @param [in] image  The e2dImage struct which will be destroyed.
     * 
     * @see e2dImageFreeMembers()
     * @see e2dElementFreeMembers()
     * @see e2dElementDestroy()
     **/
    void
    e2dImageDestroy(e2dImage* image);
    
    /**
     * @brief   Will free all the allocated memory inside the e2dImage struct
     * pointed by elem, i.e. it checks if e2dImage::imagePath has been defined and frees
     * the pointer. It is called by e2dImageDestroy().
     *
     * @param [in] image  The e2dImage struct where the members will be freed.
     * 
     * @see e2dImageDestroy()
     * @see e2dElementDestroy()
     **/
    void
    e2dImageFreeMembers(e2dImage* image);

    /**
     * @brief   A quite straight forward function which simply makes the e2dImage::width, 
     * e2dImage::height and e2dImage::position of the image also be the bounding box. 
     * If a e2dImage::width and e2dImage::height is not supplied, the bounding box won't
     * be calculated. We can't check the actual image size as that would bring additional 
     * dependencies to the library, so be careful with it.
     *
     * @param [in] image  The e2dImage struct where the bounding box will be calculated.
     * 
     * 
     * @see e2dElementCalculateBoundingBox()
     **/
    void
    e2dImageCalculateBoundingBox(e2dImage* image);

    /**
     * @brief   Adds a transformation to the image which subtracts the position (offset by (tx,ty))
     * of the Bounding Box, and adds the position of the bounding box to the image
     * position, effectively bringing the origin of the local coordinate system
     * to the bounding box. See e2dElementCenterAtBBox() for an explanation on "tx"
     * and "ty".
     *
     * @param [in] image  The e2dImage struct to be centered.
     * @param [in] tx  x offset in BBox width units.
     * @param [in] ty  y offset in BBox height units.
     * 
     * @see e2dElementCenterAtBBox()
     **/
    void
    e2dImageCenterAtBBox(e2dImage* image, float tx, float ty);


    /**
     * @}
     **/

#ifdef	__cplusplus
}
#endif

#endif	/* E2DIMAGE_H */

