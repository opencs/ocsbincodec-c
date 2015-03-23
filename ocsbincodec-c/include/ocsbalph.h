/*
 * ocsbalph.h
 *
 *  Created on: Mar 23, 2015
 *      Author: fchino
 */

#ifndef OCSBALPH_H_
#define OCSBALPH_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <ocsalpha.h>

typedef struct OCSBinaryAlphabet OCSBinaryAlphabet;

struct OCSBinaryAlphabet {
	OCSAlphabet base;

	int _one;

	int _zero;
};

int OCSBinaryAlphabet_New(OCSBinaryAlphabet ** myself, int zero, int one);

int OCSBinaryAlphabet_init(OCSBinaryAlphabet * myself, int zero, int one);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* OCSBALPH_H_ */
