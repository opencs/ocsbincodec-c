/*
 * Copyright (c) 2015, Open Communications Security
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of ocsbincodec-c nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#include <ocsbalph.h>

//------------------------------------------------------------------------------
void OCSBinaryAlphabet_dispose(OCSObject * myself) {
	OCSAlphabet_dispose(myself);
}

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
			OCSBinaryAlphabet_dispose);
	if (retval == OCSERR_SUCCESS) {
		// Call my initializer
		retval = OCSBinaryAlphabet_init(*myself, zero, one);
		if (retval != OCSERR_SUCCESS) {
			OCSObjectDelete((OCSObject *)*myself);
			*myself = NULL;
		}
	}
	return retval;
}

//------------------------------------------------------------------------------
int OCSBinaryAlphabet_init(OCSBinaryAlphabet * myself, int zero, int one) {
	int retval;

	// Check the parameters
	if (one == zero) {
		return OCSERR_INVALID_ARGUMENT;
	}

	// Call the base initializer
	retval = OCSAlphabet_init((OCSAlphabet*)(myself), 2);
	if (retval != OCSERR_SUCCESS) {
		return retval;
	}

	myself->_zero = zero;
	myself->_one = one;
	myself->base.getCharacter = OCSBinaryAlphabet_getCharacter;
	myself->base.getValue = OCSBinaryAlphabet_getValue;
	return OCSERR_SUCCESS;
}
//------------------------------------------------------------------------------
