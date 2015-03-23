/*
 * ocsbalph.c
 *
 *  Created on: Mar 23, 2015
 *      Author: fchino
 */

#include <ocsbalph.h>

//------------------------------------------------------------------------------
int OCSBinaryAlphabet_getCharacter(const OCSAlphabet * myself, int v) {
	OCSBinaryAlphabet * me;

	me = (OCSBinaryAlphabet *)myself;
	if (v == 0) {
		return me->_zero;
	} else {
		return me->_one;
	}
}

//------------------------------------------------------------------------------
int OCSBinaryAlphabet_getValue(const OCSAlphabet * myself, int c) {
	OCSBinaryAlphabet * me;

	me = (OCSBinaryAlphabet *)myself;
	if (c == me->_zero) {
		return 0;
	} else 	if (c == me->_one) {
		return 1;
	} else {
		return -1;
	}
}

//------------------------------------------------------------------------------
int OCSBinaryAlphabet_New(OCSBinaryAlphabet ** myself, int zero, int one) {
	int retval;

	// Call the constructor of the object
	retval = OCSObject_New((OCSObject **)myself, sizeof(OCSBinaryAlphabet),
			NULL);
	if (retval != OCSERR_SUCCESS) {
		return retval;
	}

	// Call the base initializer
	retval = OCSAlphabet_init((OCSAlphabet*)(*myself), 2);
	if (retval != OCSERR_SUCCESS) {
		return retval;
	}

	// Call my initializer
	retval = OCSBinaryAlphabet_init(*myself, zero, one);
	return retval;
}

//------------------------------------------------------------------------------
int OCSBinaryAlphabet_init(OCSBinaryAlphabet * myself, int zero, int one) {

	if (one == zero) {
		return OCSERR_INVALID_ARGUMENT;
	}

	myself->_zero = zero;
	myself->_one = one;
	myself->base.getCharacter = OCSBinaryAlphabet_getCharacter;
	myself->base.getValue = OCSBinaryAlphabet_getValue;
	return OCSERR_SUCCESS;
}
//------------------------------------------------------------------------------
