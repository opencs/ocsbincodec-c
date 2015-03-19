/*
 * alphabet.h
 *
 *  Created on: Mar 19, 2015
 *      Author: fjtc
 */

#ifndef OCSCODEC_OCSALPHA_H_
#define OCSCODEC_OCSALPHA_H_

#include <stdint.h>
#include <ocsobj.h>

#ifdef _cplusplus
extern "C" {
#endif

typedef struct CAlphabet CAlphabet;

struct CAlphabet {
	OCSObject super;
	int (*getSize)(CAlphabet* myself);
	int (*getCharacter)(CAlphabet* myself, int c);
	int (*getValue)(CAlphabet* myself, int c);
};

int CAlphabet_Init(CAlphabet * myself);

#ifdef _cplusplus
} //extern "C"
#endif

#endif /* OCSCODEC_OCSALPHA_H_ */
