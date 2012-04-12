/* 
 * File:   Ez2DS.h
 * Author: Rui
 *
 * Created on 3 de Fevereiro de 2012, 18:21
 */

#ifndef EZ2DS_H
#define	EZ2DS_H




    

#ifdef	__cplusplus
extern "C" {
#endif
    
    
    
    typedef enum {E2D_FALSE, E2D_TRUE} E2D_BOOL;
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
    
    
    
#define E2D_ALMOST_ZERO 1.0e-6f 
    
#define E2D_IS_ALMOST_ZERO(val) \
        ((val) < (E2D_ALMOST_ZERO) && (val) > -(E2D_ALMOST_ZERO))
    
#define E2D_NULL 0
    
#define E2D_MAX(a,b) \
({ __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a > _b ? _a : _b; })
    
#define E2D_MIN(a,b) \
({ __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a < _b ? _a : _b; })




#ifdef	__cplusplus
}
#endif

#endif	/* EZ2DS_H */

