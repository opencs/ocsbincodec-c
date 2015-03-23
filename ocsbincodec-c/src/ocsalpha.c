/*
 * alphabet.c
 *
 *  Created on: Mar 19, 2015
 *      Author: fjtc
 */
#include <ocsalpha.h>

//------------------------------------------------------------------------------
int OCSAlphabet_getSize(const OCSAlphabet * myself) {
	return myself->_size;
}

//------------------------------------------------------------------------------
int OCSAlphabet_init(OCSAlphabet * myself, int size) {
	myself->_size = size;
	myself->getSize = OCSAlphabet_getSize;
	return OCSERR_SUCCESS;
}
//------------------------------------------------------------------------------
