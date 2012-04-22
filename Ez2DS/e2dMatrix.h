/**
 * @file   e2dMatrix.h
 * 
 * @brief  File which contains a 3x3 matrix implementation and utility methods.
 * 
 * @author Rui (ruir2c@gmail.com)
 * 
 * @date   February, 2012
 */

#ifndef E2DMATRIX_H
#define	E2DMATRIX_H

#include "Ez2DS.h"

#ifdef	__cplusplus
extern "C" {
#endif

    /**
     * @defgroup e2dMatrix
     * @{
     **/

    /**
     *  @brief The e2dMatrix struct contains the implementation of a 3x3
     * matrix which is row major. See http://en.wikipedia.org/wiki/Row-major_order
     * if you have doubts.
     **/
    struct e2dMatrix {
        float vals[3][3]; /**< Row major 3x3 matrix array **/
    };
    /**
     *  @brief Defines an identity matrix.
     **/
    static e2dMatrix const E2D_IDENT_MATRIX = {
        {1, 0, 0, 0, 1, 0, 0, 0, 1}
    };

    /**
     *  @brief Sets mat to be identity, basically assigns E2D_IDENT_MATRIX.
     **/
    inline void
    e2dMatrixToIdent(e2dMatrix* mat);
    /**
     *  @brief Changes the column defined by col (0 to 2) to be val1, val2 and val3.
     **/
    inline void
    e2dMatrixSetCol(e2dMatrix* mat,
            unsigned int col,
            float val1, float val2, float val3);

    /**
     *  @brief Changes the row defined by row (0 to 2) to be val1, val2 and val3.
     **/
    inline void
    e2dMatrixSetRow(e2dMatrix* mat,
            unsigned int row,
            float val1, float val2, float val3);

    /**
     *  @brief Changes the position in row "row", column "col" to be val1.
     **/
    inline void
    e2dMatrixSetRowCol(e2dMatrix* mat,
            unsigned int row,
            unsigned int col,
            float val1);

    /**
     *  @brief Returns the cell in row "row", column "column".
     * 
     * @retval float Returns the cell value.
     **/
    inline float
    e2dMatrixGetCell(const e2dMatrix* mat,
            unsigned int row,
            unsigned int col);

    /**
     *  @brief Multiplies the mat by multiplicator and returns the result in
     * another matrix.
     * 
     * @retval e2dMatrix The result of the multiplication.
     **/
    inline e2dMatrix
    e2dMatrixMultiply(const e2dMatrix* mat, const e2dMatrix* multiplicator);

    /**
     *  @brief Places an identity matrix and sets first and second row's last
     * cell to be x and y respectively.
     **/
    inline void
    e2dMatrixSetAsTranslation(e2dMatrix* mat, float x, float y);

    /**
     *  @brief Places an identity matrix and sets cell (0,0) and (1,1) to be x and y
     * respectively.
     **/
    inline void
    e2dMatrixSetAsScale(e2dMatrix*mat, float x, float y);

    /**
     *  @brief Places an identity matrix and sets a rotation according to 
     * http://en.wikipedia.org/wiki/Rotation_matrix.
     **/
    inline void
    e2dMatrixSetAsRotation(e2dMatrix* mat, float radians);

    /**
     *  @brief Inverts the matrix using Cramer's rule (see http://en.wikipedia.org/wiki/Cramer%27s_rule)
     * and returns the result
     * 
     * @retval e2dMatrix inverted matrix.
     **/
    e2dMatrix
    e2dMatrixGetInverse(const e2dMatrix* mat);

    /**
     *  @brief Applies the matrix to the point transforming it.
     * 
     * @retval e2dPoint The altered point.
     **/
    e2dPoint
    e2dMatrixApplyToPoint(const e2dMatrix* mat, const e2dPoint* point);


    /**
     * @}
     **/
#ifdef	__cplusplus
}
#endif

#endif	/* E2DMATRIX_H */

