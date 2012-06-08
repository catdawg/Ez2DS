/**
 * @file   e2dPoint.h
 * 
 * @brief  File which contains a struct definition of a point (two floats).
 * 
 * @author Rui (ruir2c@gmail.com)
 * 
 * @date   February, 2012
 */

#ifndef E2DPOINT_H
#define	E2DPOINT_H

#include "Ez2DS.h"


    /**
     * @defgroup e2dPoint e2dPoint
     * @{
     **/
    
    
    /**
     *  @brief The e2dPoint struct which contains two floats.
     **/
    struct e2dPoint {
        float x; /**< The X coordinate of the point **/ 
        float y; /**< The Y coordinate of the point **/ 
    };

    /**
     *  @brief Utility constant which defines a (0,0) point.
     **/
    static e2dPoint const E2D_ZERO_ZERO_POINT = {0, 0};

    /**
     * @}
     **/

#endif	/* E2DPOINT_H */

