/*
 * lcwin32.h
 *
 *  Created on: 27/05/2010
 *      Author: George Marques
 */

#ifndef _LC_LCWIN32_H_
#define _LC_LCWIN32_H_

/* This file contains the platform dependent statements
 * when compiling on Windows
 */
#ifdef _WIN32

/* These things don't work when using MinGW
 * so I defined a symbol to avoid errors
 */
#ifndef __MINGW32

/* Use 'sprintf_s()' instead of 'sprintf()' when compiled on Windows
 * (removes the warnings)
 */
#define sprintf sprintf_s



#endif /* #ifndef __MINGW32 */

#endif /* #ifdef _WIN32 */
#endif /* LCWIN32_H_ */
