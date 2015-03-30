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
#include "ocsaalph.h"
#include <string.h>
#include <ctype.h>

//------------------------------------------------------------------------------
int OCSArrayAlphabet_New(OCSArrayAlphabet ** myself, const char * chars,
		int charsSize, bool caseInsensitive) {
	return OCSArrayAlphabet_NewEx(myself, chars, charsSize, caseInsensitive,
			false);
}

//------------------------------------------------------------------------------
int OCSArrayAlphabet_NewEx(OCSArrayAlphabet ** myself, const char * chars,
		int charsSize, bool caseInsensitive, bool noCopy) {
	int retval;

	// Call the constructor of the object
	retval = OCSObject_New((OCSObject **)myself, sizeof(OCSArrayAlphabet),
			OCSArrayAlphabet_dispose);
	if (retval == OCSERR_SUCCESS) {
		// Call my initializer
		retval = OCSArrayAlphabet_init(*myself, chars, charsSize,
				caseInsensitive, noCopy);
		if (retval != OCSERR_SUCCESS) {
			OCSObjectDelete((OCSObject *)*myself);
			*myself = NULL;
		}
	}
	return retval;
}

//------------------------------------------------------------------------------
int OCSArrayAlphabet_init(OCSArrayAlphabet * myself, const char * chars,
		int charsSize, bool caseInsensitive, bool noCopy) {
	int retval;
	OCSAlphabet * asBase;

	// Check the arguments first
	if ((chars == NULL) || (charsSize < 1) ||
			(charsSize > OCSArrayAlphabet_MAX_SIZE)){
		return OCSERR_INVALID_ARGUMENT;
	}

	retval = OCSAlphabet_init((OCSAlphabet*)myself, charsSize);
	if (retval == OCSERR_SUCCESS) {
		// Register the methods
		asBase = (OCSAlphabet *)myself;
		asBase->getCharacter = OCSArrayAlphabet_getCharacter;
		if (caseInsensitive) {
			asBase->getValue = OCSArrayAlphabet_getValueCI;
		} else {
			asBase->getValue = OCSArrayAlphabet_getValue;
		}

		// Initialize the map
		if (noCopy) {
			myself->alphabet = chars;
			myself->myAlphabet = NULL;
		} else {
			myself->myAlphabet = malloc(sizeof(char) * charsSize);
			if (myself->myAlphabet) {
				memcpy(myself->myAlphabet, chars, sizeof(char) * charsSize);
				myself->alphabet = myself->myAlphabet;
			} else {
				retval = OCSERR_OUT_OF_MEMORY;
			}
		}
	}
	return retval;
}

//------------------------------------------------------------------------------
int OCSArrayAlphabet_getCharacter(const OCSAlphabet * myself, int v) {
	const OCSArrayAlphabet * p;

	p = (const OCSArrayAlphabet *)myself;

	return p->alphabet[v];
}

//------------------------------------------------------------------------------
int OCSArrayAlphabet_getValue(const OCSAlphabet * myself, int c) {
	const OCSArrayAlphabet * p;
	int i;

	// The list is usually very small. Given that, a sequential scan
	// should do the job in most cases.
	p = (const OCSArrayAlphabet *)myself;
	for (i = 0; i < p->base._size; i++) {
		if (p->alphabet[i] == c) {
			return i;
		}
	}
	return -1;
}

//------------------------------------------------------------------------------
int OCSArrayAlphabet_getValueCI(const OCSAlphabet * myself, int c) {
	const OCSArrayAlphabet * p;
	int i;

	c = toupper(c);
	// The list is usually very small. Given that, a sequential scan
	// should do the job in most cases.
	p = (const OCSArrayAlphabet *)myself;
	for (i = 0; i < p->base._size; i++) {
		if (toupper(p->alphabet[i]) == c) {
			return i;
		}
	}
	return -1;
}

//------------------------------------------------------------------------------
void OCSArrayAlphabet_dispose(OCSObject * myself) {
	OCSArrayAlphabet * p;

	p = (OCSArrayAlphabet *)myself;
	if (p->myAlphabet) {
		free(p->myAlphabet);
	}
	OCSAlphabet_dispose(myself);
}

//------------------------------------------------------------------------------

