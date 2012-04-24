
/**
 * @file   Ez2DS.h
 * 
 * @brief  File which contains global definitions useful to be included
 * on every other file of the library. These definitions include forward
 * declaration of all the structs, and some utility functions. 
 * 
 * @author Rui (ruir2c@gmail.com)
 * 
 * @date   February, 2012
 */

#ifndef EZ2DS_H
#define	EZ2DS_H

 




#ifdef	__cplusplus
extern "C" {
#endif

    /**
     *  @brief Boolean implementation
     **/
    typedef enum {
        E2D_FALSE, E2D_TRUE
    } E2D_BOOL;


    /**
     *  @brief Forward declarations
     *  @{
     **/
    typedef struct e2dScene e2dScene;
    typedef struct e2dElement e2dElement;
    typedef struct e2dGroup e2dGroup;
    typedef struct e2dPath e2dPath;
    typedef struct e2dPathElement e2dPathElement;
    typedef struct e2dPathPoint e2dPathPoint;
    typedef struct e2dPathCurve e2dPathCurve;
    typedef struct e2dImage e2dImage;
    typedef struct e2dPoint e2dPoint;
    typedef struct e2dMatrix e2dMatrix;
    typedef struct e2dPathElementIterator e2dPathElementIterator;
    typedef struct e2dGroupIterator e2dGroupIterator;
    /**
     *  @}
     **/



    /**
     * @brief Defines a value which is almost zero. 
     * @see E2D_IS_ALMOST_ZERO()
     **/
#define E2D_ALMOST_ZERO 1.0e-6f 
    /**
     * @brief Checks if val is within the threshold defined by E2D_ALMOST_ZERO,
     * i.e. it checks if val is below E2D_ALMOST_ZERO and above - E2D_ALMOST_ZERO
     * @see E2D_ALMOST_ZERO
     * 
     * @retval bool Returns true if almost zero, else false.
     **/
#define E2D_IS_ALMOST_ZERO(val) \
        ((val) < (E2D_ALMOST_ZERO) && (val) > -(E2D_ALMOST_ZERO))
    /**
     * @brief NULL definition
     **/
#define E2D_NULL 0
    /**
     * @brief Returns the biggest number between a and b.
     * 
     * @retval comparable The biggest.
     **/
#define E2D_MAX(a,b) \
({ __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a > _b ? _a : _b; })

    /**
     * @brief Returns the smallest number between a and b.
     * @retval comparable The smallest.
     **/
#define E2D_MIN(a,b) \
({ __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a < _b ? _a : _b; })




#ifdef	__cplusplus
}
#endif

#endif	/* EZ2DS_H */

