#include "e2dMatrix.h"

#include "e2dPoint.h"
#include <math.h>

inline void
e2dMatrixSetCol(e2dMatrix* mat,
        unsigned int col,
        float val1, float val2, float val3) {
    mat->vals[0][col] = val1;
    mat->vals[1][col] = val2;
    mat->vals[2][col] = val3;
}

inline void
e2dMatrixSetRow(e2dMatrix* mat,
        unsigned int row,
        float val1, float val2, float val3) {
    mat->vals[row][0] = val1;
    mat->vals[row][1] = val2;
    mat->vals[row][2] = val3;
}

inline void
e2dMatrixToIdent(e2dMatrix* mat) {
    *mat = E2D_IDENT_MATRIX;
}

inline void
e2dMatrixSetCell(e2dMatrix* mat,
        unsigned int row,
        unsigned int col,
        float val1) {
    mat->vals[row][col] = val1;
}

inline float
e2dMatrixGetCell(const e2dMatrix* mat,
        unsigned int row,
        unsigned int col) {
    return mat->vals[row][col];
}

inline e2dMatrix
e2dMatrixMultiply(const e2dMatrix* mat, const e2dMatrix* mult) {
    e2dMatrix ret;
    ret.vals[0][0] =
            mat->vals[0][0] * mult->vals[0][0] +
            mat->vals[0][1] * mult->vals[1][0] +
            mat->vals[0][2] * mult->vals[2][0];

    ret.vals[0][1] =
            mat->vals[0][0] * mult->vals[0][1] +
            mat->vals[0][1] * mult->vals[1][1] +
            mat->vals[0][2] * mult->vals[2][1];

    ret.vals[0][2] =
            mat->vals[0][0] * mult->vals[0][2] +
            mat->vals[0][1] * mult->vals[1][2] +
            mat->vals[0][2] * mult->vals[2][2];

    ret.vals[1][0] =
            mat->vals[1][0] * mult->vals[0][0] +
            mat->vals[1][1] * mult->vals[1][0] +
            mat->vals[1][2] * mult->vals[2][0];

    ret.vals[1][1] =
            mat->vals[1][0] * mult->vals[0][1] +
            mat->vals[1][1] * mult->vals[1][1] +
            mat->vals[1][2] * mult->vals[2][1];

    ret.vals[1][2] =
            mat->vals[1][0] * mult->vals[0][2] +
            mat->vals[1][1] * mult->vals[1][2] +
            mat->vals[1][2] * mult->vals[2][2];

    ret.vals[2][0] =
            mat->vals[2][0] * mult->vals[0][0] +
            mat->vals[2][1] * mult->vals[1][0] +
            mat->vals[2][2] * mult->vals[2][0];

    ret.vals[2][1] =
            mat->vals[2][0] * mult->vals[0][1] +
            mat->vals[2][1] * mult->vals[1][1] +
            mat->vals[2][2] * mult->vals[2][1];

    ret.vals[2][2] =
            mat->vals[2][0] * mult->vals[0][2] +
            mat->vals[2][1] * mult->vals[1][2] +
            mat->vals[2][2] * mult->vals[2][2];

    return ret;
}

inline void
e2dMatrixSetAsTranslation(e2dMatrix* mat, float x, float y) {
    
    e2dMatrixToIdent(mat);
    e2dMatrixSetCell(mat, 0, 2, x);
    e2dMatrixSetCell(mat, 1, 2, y);
}

inline void
e2dMatrixSetAsScale(e2dMatrix* mat, float x, float y) {
    e2dMatrixToIdent(mat);
    e2dMatrixSetCell(mat, 0, 0, x);
    e2dMatrixSetCell(mat, 1, 0, 0);
    e2dMatrixSetCell(mat, 2, 0, 0);
    e2dMatrixSetCell(mat, 0, 1, 0);
    e2dMatrixSetCell(mat, 1, 1, y);
    e2dMatrixSetCell(mat, 2, 1, 0);
    e2dMatrixSetCell(mat, 0, 2, 0);
    e2dMatrixSetCell(mat, 1, 2, 0);
    e2dMatrixSetCell(mat, 2, 2, 1);
}

inline void
e2dMatrixSetAsRotation(e2dMatrix* mat, float radians) {
    e2dMatrixSetCell(mat, 0, 0, cos(radians));
    e2dMatrixSetCell(mat, 1, 0, sin(radians));
    e2dMatrixSetCell(mat, 2, 0, 0);
    e2dMatrixSetCell(mat, 0, 1, -sin(radians));
    e2dMatrixSetCell(mat, 1, 1, cos(radians));
    e2dMatrixSetCell(mat, 2, 1, 0);
    e2dMatrixSetCell(mat, 0, 2, 0);
    e2dMatrixSetCell(mat, 1, 2, 0);
    e2dMatrixSetCell(mat, 2, 2, 1);
}

#define DET2X2(m00,m01,m10,m11) ((m00)*(m11) - (m10)*(m01))

inline float e2dMatrixGetDeterminant(const e2dMatrix* mat) {

    return  mat->vals[0][0]
            *
            DET2X2(
            mat->vals[1][1], mat->vals[1][2], mat->vals[2][1], mat->vals[2][2]
            )
            -
            mat->vals[0][1]
            *
            DET2X2(
            mat->vals[1][0], mat->vals[1][2], mat->vals[2][0], mat->vals[2][2]
            )
            +
            mat->vals[0][2]
            *
            DET2X2(
            mat->vals[1][0], mat->vals[1][1], mat->vals[2][0], mat->vals[2][1]
            );

}
inline e2dMatrix
e2dMatrixGetInverse(const e2dMatrix* mat) {
    float det = e2dMatrixGetDeterminant(mat);

    if (E2D_IS_ALMOST_ZERO(det))
        return E2D_IDENT_MATRIX;

    e2dMatrix ret;

    det = 1.0f / det;
    ret.vals[0][0] = det * DET2X2(
            mat->vals[1][1], mat->vals[1][2], mat->vals[2][1], mat->vals[2][2]);
    ret.vals[1][0] = -det * DET2X2(
            mat->vals[1][0], mat->vals[1][2], mat->vals[2][0], mat->vals[2][2]);
    ret.vals[2][0] = det * DET2X2(
            mat->vals[1][0], mat->vals[1][1], mat->vals[2][0], mat->vals[2][1]);

    ret.vals[0][1] = -det * DET2X2(
            mat->vals[0][1], mat->vals[0][2], mat->vals[2][1], mat->vals[2][2]);
    ret.vals[1][1] = det * DET2X2(
            mat->vals[0][0], mat->vals[0][2], mat->vals[2][0], mat->vals[2][2]);
    ret.vals[2][1] = -det * DET2X2(
            mat->vals[0][0], mat->vals[0][1], mat->vals[2][0], mat->vals[2][1]);

    ret.vals[0][2] = det * DET2X2(
            mat->vals[0][1], mat->vals[0][2], mat->vals[1][1], mat->vals[1][2]);
    ret.vals[1][2] = -det * DET2X2(
            mat->vals[0][0], mat->vals[0][2], mat->vals[1][0], mat->vals[1][2]);
    ret.vals[2][2] = det * DET2X2(
            mat->vals[0][0], mat->vals[0][1], mat->vals[1][0], mat->vals[1][1]);

    return ret;
}


e2dPoint
e2dMatrixApplyToPoint(const e2dMatrix* mat, const e2dPoint* point)
{
    e2dPoint ret;
    
    ret.x = point->x*e2dMatrixGetCell(mat, 0, 0) + 
            point->y*e2dMatrixGetCell(mat, 0, 1) + 
            e2dMatrixGetCell(mat, 0, 2);
    ret.y = point->x*e2dMatrixGetCell(mat, 1, 0) + 
            point->y*e2dMatrixGetCell(mat, 1, 1) +
            e2dMatrixGetCell(mat, 1, 2);
    
    return ret;
}