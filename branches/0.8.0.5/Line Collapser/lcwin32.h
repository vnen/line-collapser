/*
 * lcwin32.h
 *
 *  Created on: 27/05/2010
 *      Author: root
 */

#ifndef _LC_LCWIN32_H_
#define _LC_LCWIN32_H_

/* This file contains the platform dependent statements
 * when compiling on Windows
 */
#ifdef _WIN32

/* Use 'sprintf_s()' instead of 'sprintf()' when compiled on Windows
 * (remove the warnings)
 */
#define sprintf sprintf_s

#endif

#endif /* LCWIN32_H_ */
