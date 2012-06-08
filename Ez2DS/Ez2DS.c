#include "Ez2DS.h"

E2D_BOOL wildcmp(const char *wild, const char *string) {
   while (*string) {
      switch (*wild) {
         case '?':
            break;
         case '*':
            return !*(wild + 1) ||
                   wildcmp(wild + 1, string) ||
                   wildcmp(wild, string + 1);
         default:
            if (*string != *wild) return E2D_FALSE;
            break;
      } /* endswitch */
      ++string, ++wild;
   } /* endwhile */
   while (*wild == '*') ++wild;
   if(*wild)
       return E2D_FALSE;
   return E2D_TRUE;
}
