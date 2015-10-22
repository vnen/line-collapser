/*
 * mersenne_twister.h
 *
 ************ Mersenne Twister ************
 *
 * It is a random number generator I found at http://www.qbrundage.com/michaelb/pubs/essays/random_number_generation.html
 * It was "invented/discovered in 1996 by Matsumora and Nishimura"
 * The author of the code published it with a public domain license (http://creativecommons.org/licenses/publicdomain/deed.en)
 *
 */

#ifndef _MERSENNE_TWISTER_H_
#define _MERSENNE_TWISTER_H_

#define MT_LEN      	624
#define MT_IA           397
#define MT_IB           (MT_LEN - MT_IA)
#define UPPER_MASK      0x80000000
#define LOWER_MASK      0x7FFFFFFF
#define MATRIX_A        0x9908B0DF
#define TWIST(b,i,j)    ((b)[i] & UPPER_MASK) | ((b)[j] & LOWER_MASK)
#define MAGIC(s)        (((s)&1)*MATRIX_A)


void mt_init();
unsigned long mt_random();

#endif /* MERSENNE_TWISTER_H_ */
