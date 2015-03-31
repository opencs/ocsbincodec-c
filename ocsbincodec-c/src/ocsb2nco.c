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
#include <ocsb2nco.h>
#include <string.h>

//------------------------------------------------------------------------------
int OCSBase2NCodec_New(OCSBase2NCodec ** myself, OCSAlphabet * alphabet,
		int paddingChar, int paddingBlock,
		const char * ignores) {
	int retval;

	// Call the constructor of the object
	retval = OCSObject_New((OCSObject **)myself, sizeof(OCSBase2NCodec),
			OCSBase2NCodec_dispose);
	if (retval == OCSERR_SUCCESS) {
		// Call my initializer
		retval = OCSBase2NCodec_init(*myself, alphabet,
				paddingChar, paddingBlock, ignores);
		if (retval != OCSERR_SUCCESS) {
			OCSObjectDelete((OCSObject *)*myself);
			*myself = NULL;
		}
	}
	return retval;
}

//------------------------------------------------------------------------------
int OCSBase2NCodec_setIgnores(OCSBase2NCodec * myself, const char * ignores) {
	int retval = OCSERR_SUCCESS;

	if (ignores == NULL) {
		myself->ignores = NULL;
	} else {
		myself->ignores = strdup(ignores);
		if (myself->ignores == NULL) {
			retval = OCSERR_OUT_OF_MEMORY;
		}
	}
	return retval;
}

//------------------------------------------------------------------------------
int OCSBase2NCodec_setAlphabet(OCSBase2NCodec * myself, OCSAlphabet * alphabet) {
	int retval;
	int size;
	int alphaSize;
	bool stop;

	if (alphabet == NULL) {
		retval = OCSERR_INVALID_ARGUMENT;
	} else {
		size = 1;
		do {
			alphaSize = (1 << size);
			if (alphaSize == alphabet->getSize(alphabet)) {
				stop = true;
			} else {
				size++;
				stop = size > 7;
			}
		} while (!stop);
		if (size < 8) {
			// Set the parameters
			myself->size = size;
			myself->clearMask = (alphaSize - 1);
			myself->alphabet = alphabet;
			retval = OCSERR_SUCCESS;
		} else {
			retval = OCSERR_INVALID_ARGUMENT;
		}
	}
	return retval;
}

//------------------------------------------------------------------------------
int OCSBase2NCodec_init(OCSBase2NCodec * myself, OCSAlphabet * alphabet,
		int paddingChar, int paddingBlock,
		const char * ignores) {
	int retval;
	OCSCodec * base;

	// Call the initializer of the superclass
	retval = OCSCodec_init((OCSCodec*)myself);
	if (retval != OCSERR_SUCCESS) {
		return retval;
	}

	// Start my initialization...
	retval = OCSBase2NCodec_setIgnores(myself, ignores);
	if (retval != OCSERR_SUCCESS) {
		return retval;
	}
	retval = OCSBase2NCodec_setAlphabet(myself, alphabet);
	if (retval != OCSERR_SUCCESS) {
		return retval;
	}
	myself->paddingChar = paddingChar;
	myself->paddingBlockSize = paddingBlock;

	// Initializes my methods
	myself->isIgnored = OCSBase2NCodec_isIgnored;
	myself->isPadding = OCSBase2NCodec_isPadding;
	myself->usePadding = OCSBase2NCodec_usePadding;
	// Initializes parent methods
	base = (OCSCodec*)myself;
	base->decode = OCSBase2NCodec_decode;
	base->encode = OCSBase2NCodec_encode;
	base->getDecodedSize = OCSBase2NCodec_getDecodedSize;
	base->getEncodedSize = OCSBase2NCodec_getEncodedSize;
	return OCSERR_SUCCESS;
}

//------------------------------------------------------------------------------
int OCSBase2NCodec_getPaddingSize(const OCSCodec * myself, int totalSize) {
	OCSBase2NCodec * me;

	me = (OCSBase2NCodec *)myself;
	if (me->usePadding(me)) {
		return (me->paddingBlockSize - (totalSize % me->paddingBlockSize)) %
				me->paddingBlockSize;
 	} else {
 		return 0;
 	}
}

//------------------------------------------------------------------------------
int OCSBase2NCodec_getEncodedSize(const OCSCodec * myself, int decSize) {

}

//------------------------------------------------------------------------------
int OCSBase2NCodec_getDecodedSize(const OCSCodec * myself, int encSize) {
	OCSBase2NCodec * me;

	me = (OCSBase2NCodec *)myself;
	return (me->size * encSize) / 8;
}

//------------------------------------------------------------------------------
int OCSBase2NCodec_encode(const OCSCodec * myself,
		const void * src, int srcSize,
		char * dst, int * dstSize) {

}

//------------------------------------------------------------------------------
int OCSBase2NCodec_decode(const OCSCodec * myself,
		const char * src, int srcSize,
		void * dst, int * dstSize) {

}

//------------------------------------------------------------------------------
bool OCSBase2NCodec_usePadding(const OCSBase2NCodec * myself) {

	return (myself->paddingBlockSize >= 2);
}

//------------------------------------------------------------------------------
bool OCSBase2NCodec_isPadding(const OCSBase2NCodec * myself, int c) {

	if (myself->usePadding(myself)) {
		return (c == myself->paddingChar);
	} else {
		return false;
	}
}

//------------------------------------------------------------------------------
bool OCSBase2NCodec_isIgnored(const OCSBase2NCodec * myself, int c) {

	if ((myself->ignores) && (c != 0)) {
		return (strchr(myself->ignores, c) != NULL);
	} else {
		return false;
	}
}

//------------------------------------------------------------------------------
void OCSBase2NCodec_dispose(OCSObject * myself) {
	OCSBase2NCodec * p;

	p = (OCSBase2NCodec *)myself;
	if (p->alphabet) {
		OCSObjectDelete((OCSObject *)p->alphabet);
	}
	if (p->ignores) {
		free(p->ignores);
	}
	OCSCodec_dispose(myself);
}
//------------------------------------------------------------------------------
