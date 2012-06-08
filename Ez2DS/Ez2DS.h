
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






typedef struct e2dScene e2dScene; /**< Forward declaration **/
typedef struct e2dElement e2dElement; /**< Forward declaration **/
typedef struct e2dGroup e2dGroup; /**< Forward declaration **/
typedef struct e2dPath e2dPath; /**< Forward declaration **/
typedef struct e2dPathElement e2dPathElement; /**< Forward declaration **/
typedef struct e2dPathPoint e2dPathPoint; /**< Forward declaration **/
typedef struct e2dPathCurve e2dPathCurve; /**< Forward declaration **/
typedef struct e2dImage e2dImage; /**< Forward declaration **/
typedef struct e2dClone e2dClone; /**< Forward declaration **/
typedef struct e2dPoint e2dPoint; /**< Forward declaration **/
typedef struct e2dMatrix e2dMatrix; /**< Forward declaration **/
typedef struct e2dPathElementIterator e2dPathElementIterator; /**< Forward declaration **/
typedef struct e2dGroupIterator e2dGroupIterator; /**< Forward declaration **/
typedef struct e2dSearchResult e2dSearchResult; /**< Forward declaration **/





/**
*  @brief Cross platform shared library exporting
**/
#if defined (_MSC_VER)
  #if defined(Ez2DS_EXPORTS)
    #define E2D_EXPORT __declspec(dllexport)
  #else
    #define E2D_EXPORT __declspec(dllimport)
  #endif /* Ez2DS_EXPORTS */
#else /* defined (_MSC_VER) */
 #define E2D_EXPORT
#endif


/**
*  @brief Boolean implementation
**/
#ifdef _MSC_VER
#define E2D_BOOL bool
#define E2D_TRUE true
#define E2D_FALSE false
#else
typedef enum {
	E2D_FALSE, E2D_TRUE
} E2D_BOOL;
#endif

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


#define E2D_MAX(X,Y) ((X) > (Y) ?  (X) : (Y))
/**
* @brief Returns the smallest number between a and b.
* @retval comparable The smallest.
**/
#define E2D_MIN(X,Y) ((X) < (Y) ?  (X) : (Y))

/* Here lie  very cool macros that didn't work in msvc ;_;
#define E2D_MIN(a,b) \
({ __typeof__ (a) _a = (a); \
__typeof__ (b) _b = (b); \
_a < _b ? _a : _b; })

#define E2D_MAX(a,b) \
({ __typeof__ (a) _a = (a); \
__typeof__ (b) _b = (b); \
_a > _b ? _a : _b; })
*/

/**
* @brief Compares the two strings where wild can have wildcard symbols like this:
 * "*thing?" matches with "lotsofthings" and with "onething", but not with "thingsarenice"
 * and not with "thiiings".
* @param [in] wild  A wild card string.
* @param [in] string  The string where the wildcard will be matched
* @retval boolean True if the wild card matched correctly, false otherwise.
**/
E2D_BOOL wildcmp(const char *wild, const char *string);





#endif	/* EZ2DS_H */

