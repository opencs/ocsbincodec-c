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
#include "ocsb64al.h"

static const char * OCSBase64Alphabet_CHARS =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static const char * OCSBase64Alphabet_CHARS_SAFE =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";

//------------------------------------------------------------------------------
int OCSBase64Alphabet_New(OCSBase64Alphabet ** myself, bool safe) {
	int retval;

	// Call the constructor of the object
	retval = OCSObject_New((OCSObject **)myself, sizeof(OCSBase64Alphabet),
			OCSBase64Alphabet_dispose);
	if (retval == OCSERR_SUCCESS) {
		// Call my initializer
		retval = OCSBase64Alphabet_init(*myself, safe);
		if (retval != OCSERR_SUCCESS) {
			OCSObjectDelete((OCSObject *)*myself);
			*myself = NULL;
		}
	}
	return retval;
}

//------------------------------------------------------------------------------
int OCSBase64Alphabet_init(OCSBase64Alphabet * myself, bool safe) {
	int retval;
	OCSAlphabet * asBase;
	const char * map;

	if (safe) {
		map = OCSBase64Alphabet_CHARS_SAFE;
		myself->c62 = '-';
		myself->c63 = '_';
	} else {
		map = OCSBase64Alphabet_CHARS;
		myself->c62 = '+';
		myself->c63 = '/';
	}
	retval = OCSArrayAlphabet_init((OCSArrayAlphabet*)myself, map, 64, false,
			true);
	if (retval == OCSERR_SUCCESS) {
		// Register the methods
		asBase = (OCSAlphabet *)myself;
		asBase->getValue = OCSBase64Alphabet_getValue;
	}
	return retval;
}

//------------------------------------------------------------------------------
int OCSBase64Alphabet_getValue(const OCSAlphabet * myself, int c) {

	// Thanks to EBCDIC, this method must consider the ranges
	// A-I, J-R, S-Z and 0-9 as distinct ranges. Let the compiler optimize
	// this code in compile-time.
	if ((c >= 'A') && (c <= 'I')) {
		return c - 'A';
	} else if ((c >= 'J') && (c <= 'R')) {
		return c - 'J' + 9;
	} else if ((c >= 'S') && (c <= 'Z')) {
		return c - 'S' + 18;
	} else if ((c >= 'a') && (c <= 'i')) {
		return c - 'a' + 26;
	} else if ((c >= 'j') && (c <= 'r')) {
		return c - 'j' + 9 + 26;
	} else if ((c >= 's') && (c <= 'z')) {
		return c - 's' + 18 + 26;
	} else if ((c >= '0') && (c <= '9')) {
		return c - '0' + 26 + 26;
	} else if (c == (((OCSBase64Alphabet *)myself)->c62)) {
		return 62;
	} else if (c == (((OCSBase64Alphabet *)myself)->c63)) {
		return 63;
	} else {
		return -1;
	}
}

//------------------------------------------------------------------------------
void OCSBase64Alphabet_dispose(OCSObject * myself) {
	OCSArrayAlphabet_dispose(myself);
}

//------------------------------------------------------------------------------
