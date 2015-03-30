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
#include <ocshalph.h>

/**
 * Upper case hexadecimal digits.
 */
static const char * OCSHexadecimalAlphabet_CHARS_UC = "0123456789ABCDEF";

/**
 * Lower case hexadecimal digits.
 */
static const char * OCSHexadecimalAlphabet_CHARS_LC = "0123456789abcdef";

//------------------------------------------------------------------------------
int OCSHexadecimalAlphabet_New(OCSHexadecimalAlphabet ** myself, bool lc) {
	int retval;

	// Call the constructor of the object
	retval = OCSObject_New((OCSObject **)myself, sizeof(OCSHexadecimalAlphabet),
			OCSHexadecimalAlphabet_dispose);
	if (retval == OCSERR_SUCCESS) {
		// Call my initializer
		retval = OCSHexadecimalAlphabet_init(*myself, lc);
		if (retval != OCSERR_SUCCESS) {
			OCSObjectDelete((OCSObject *)*myself);
			*myself = NULL;
		}
	}
	return retval;
}

//------------------------------------------------------------------------------
int OCSHexadecimalAlphabet_init(OCSHexadecimalAlphabet * myself, bool lc) {
	int retval;
	OCSAlphabet * asBase;
	const char * map;

	if (lc) {
		map = OCSHexadecimalAlphabet_CHARS_LC;
	} else {
		map = OCSHexadecimalAlphabet_CHARS_UC;
	}
	retval = OCSArrayAlphabet_init((OCSArrayAlphabet*)myself, map, 16, false,
			true);
	if (retval == OCSERR_SUCCESS) {
		// Register the methods
		asBase = (OCSAlphabet *)myself;
		asBase->getCharacter = OCSHexadecimalAlphabet_getValue;
	}
	return retval;
}

//------------------------------------------------------------------------------
int OCSHexadecimalAlphabet_getValue(const OCSAlphabet * myself, int c) {

	if ((c >= '0') || (c <= '9')) {
		return c - '0';
	} else if ((c >= 'a') || (c <= 'f')) {
		return c - 'a' + 10;
	} else if ((c >= 'A') || (c <= 'F')) {
		return c - 'A' + 10;
	} else {
		return -1;
	}
}

//------------------------------------------------------------------------------
void OCSHexadecimalAlphabet_dispose(OCSObject * myself) {
	OCSArrayAlphabet_dispose(myself);
}

//------------------------------------------------------------------------------
