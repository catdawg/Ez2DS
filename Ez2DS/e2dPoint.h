/* 
 * File:   e2dPoint.h
 * Author: Rui
 *
 * Created on 3 de Fevereiro de 2012, 21:52
 */

#ifndef E2DPOINT_H
#define	E2DPOINT_H

#include "Ez2DS.h"

#ifdef	__cplusplus
extern "C" {
#endif

    struct e2dPoint{
        float x, y;
    };
    
static e2dPoint const E2DPOINT_ZERO_ZERO = { 0, 0 } ;
    
    
    


#ifdef	__cplusplus
}
#endif

#endif	/* E2DPOINT_H */

