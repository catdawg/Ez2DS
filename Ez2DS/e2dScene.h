/* 
 * File:   e2dScene.h
 * Author: Rui
 *
 * Created on 3 de Fevereiro de 2012, 18:12
 */

#ifndef E2DSCENE_H
#define	E2DSCENE_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    
#include "Ez2DS.h"

    struct e2dScene{
        e2dGroup* root;
    };
    
    //Assigns the effective transform (calculated by multiplying the local 
    //transform with the effective transform of the parent element) to every 
    //element in the scene it is useful to have this information for 
    //calculating relative positions(for example, knowing world positions, or 
    //positions of elements relative to other elements.
    void e2dSceneCalculateEffectiveTransforms(e2dScene* scene); 
    
    void e2dSceneCenterAllAtBBox(e2dScene* scene, float tx, float ty);

    e2dScene* createSceneFromFile(char* file);
    


#ifdef	__cplusplus
}
#endif

#endif	/* E2DSCENE_H */

