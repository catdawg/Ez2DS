/* 
 * File:   e2dMatrix.h
 * Author: Rui
 *
 * Created on 3 de Fevereiro de 2012, 19:00
 */

#ifndef E2DMATRIX_H
#define	E2DMATRIX_H

#include "Ez2DS.h"

#ifdef	__cplusplus
extern "C" {
#endif

    
    
struct e2dMatrix{
    float vals[3][3]; //3 rows by 3 columns
};
    
static e2dMatrix const E2D_IDENT_MATRIX = { {1, 0, 0, 0, 1, 0, 0, 0, 1} } ;

inline void 
e2dMatrixToIdent(e2dMatrix* mat);
    
inline void 
e2dMatrixSetCol(e2dMatrix* mat, 
                unsigned int col, 
                float val1, float val2, float val3);

inline void 
e2dMatrixSetRow(e2dMatrix* mat, 
                unsigned int row, 
                float val1, float val2, float val3);

inline void 
e2dMatrixSetRowCol(e2dMatrix* mat, 
                   unsigned int row,
                   unsigned int col,
                   float val1);

inline float
e2dMatrixGetCell(const e2dMatrix* mat, 
                 unsigned int col,
                 unsigned int row);

inline e2dMatrix 
e2dMatrixMultiply(const e2dMatrix* mat, const e2dMatrix* multiplicator);

inline void
e2dMatrixSetAsTranslation(e2dMatrix* mat, float x, float y);

inline void
e2dMatrixSetAsScale(e2dMatrix*mat, float x, float y);

inline void
e2dMatrixSetAsRotation(e2dMatrix* mat, float radians);

e2dMatrix
e2dMatrixGetInverse(const e2dMatrix* mat);

e2dPoint
e2dMatrixApplyToPoint(const e2dMatrix* mat, const e2dPoint* point);


#ifdef	__cplusplus
}
#endif

#endif	/* E2DMATRIX_H */

