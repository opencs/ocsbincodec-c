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
#include <ocsb32al.h>

/**
 * Upper case hexadecimal digits.
 */
static const char * OCSBase32Alphabet_CHARS_UC =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";

/**
 * Lower case hexadecimal digits.
 */
static const char * OCSBase32Alphabet_CHARS_LC =
		"abcdefghijklmnopqrstuvwxyz234567";

//------------------------------------------------------------------------------
int OCSBase32Alphabet_New(OCSBase32Alphabet ** myself, bool lc) {
	int retval;

	// Call the constructor of the object
	retval = OCSObject_New((OCSObject **)myself, sizeof(OCSBase32Alphabet),
			OCSBase32Alphabet_dispose);
	if (retval == OCSERR_SUCCESS) {
		// Call my initializer
		retval = OCSBase32Alphabet_init(*myself, lc);
		if (retval != OCSERR_SUCCESS) {
			OCSObjectDelete((OCSObject *)*myself);
			*myself = NULL;
		}
	}
	return retval;
}

//------------------------------------------------------------------------------
int OCSBase32Alphabet_init(OCSBase32Alphabet * myself, bool lc) {
	int retval;
	OCSAlphabet * asBase;
	const char * map;

	if (lc) {
		map = OCSBase32Alphabet_CHARS_LC;
	} else {
		map = OCSBase32Alphabet_CHARS_UC;
	}
	retval = OCSArrayAlphabet_init((OCSArrayAlphabet*)myself, map, 32, false,
			true);
	if (retval == OCSERR_SUCCESS) {
		// Register the methods
		asBase = (OCSAlphabet *)myself;
		asBase->getCharacter = OCSBase32Alphabet_getValue;
	}
	return retval;
}

//------------------------------------------------------------------------------
int OCSBase32Alphabet_getValue(const OCSAlphabet * myself, int c) {

	// Thanks to EBCDIC, this method must consider the ranges
	// A-I, J-R, S-Z and 0-9 as distinct ranges. Let the compiler optimize
	// this code in compile-time.
	if ((c >= 'A') && (c <= 'I')) {
		return c - 'A';
	} else if ((c >= 'a') && (c <= 'i')) {
		return c - 'a';
	} else if ((c >= 'J') && (c <= 'R')) {
		return c - 'J' + 9;
	} else if ((c >= 'j') && (c <= 'r')) {
		return c - 'j' + 9;
	} else if ((c >= 'S') && (c <= 'Z')) {
		return c - 'S' + 18;
	} else if ((c >= 's') && (c <= 'z')) {
		return c - 's' + 18;
	} else if ((c >= '2') && (c <= '7')) {
		return c - '2' + 26;
	} else {
		return -1;
	}
}

//------------------------------------------------------------------------------
void OCSBase32Alphabet_dispose(OCSObject * myself) {
	OCSArrayAlphabet_dispose(myself);
}

//------------------------------------------------------------------------------
