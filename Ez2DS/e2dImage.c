#include "e2dImage.h"
#include <stdlib.h>

void
e2dImageInit(e2dImage *image, const e2dScene* scene) {
    image->imagePath = E2D_NULL;
    image->position = E2DPOINT_ZERO_ZERO;
    image->height = 0;
    image->width = 0;

    e2dElementInit((e2dElement*) image, E2D_IMAGE, scene);
}

e2dImage*
e2dImageCreate(const e2dScene* scene) {
    e2dImage* image = (e2dImage*) malloc(sizeof (e2dImage));
    e2dImageInit(image, scene);
    return image;
}

void
e2dImageDestroy(e2dImage* image) {
    e2dImageFreeMembers(image);
    e2dElementFreeMembers((e2dElement*)image);
    free(image);
}

void
e2dImageFreeMembers(e2dImage* image) {
    if(image->imagePath)
        free(image->imagePath);
}

void
e2dImageCenterAtBBox(e2dImage* image, float tx, float ty)  {
    e2dMatrix mat;
    e2dPoint offset;
    offset.x = image->element.bboxPosition.x + image->element.bboxWidth*tx;
    offset.y = image->element.bboxPosition.y + image->element.bboxHeight*ty;
    
    e2dMatrixSetAsTranslation(&mat, 
            offset.x, 
            offset.y);
    
    image->element.localTransform = 
            e2dMatrixMultiply(&image->element.localTransform, &mat);
    
    image->position.x -= offset.x; 
    image->position.y -= offset.y; 
    
    image->element.bboxPosition.x -= offset.x;
    image->element.bboxPosition.y -= offset.y;
}

void
e2dImageCalculateBoundingBox(e2dImage* image)  {
    image->element.bboxPosition = image->position;
    image->element.bboxWidth = image->width;
    image->element.bboxHeight = image->height;
}
