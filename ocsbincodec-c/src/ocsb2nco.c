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
		// Discover the size of the alphabet in bits
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
int OCSBase2NCodec_getPaddingSize(const OCSBase2NCodec * myself, int totalSize) {

	if (myself->usePadding(myself)) {
		return (myself->paddingBlockSize - (totalSize % myself->paddingBlockSize)) %
				myself->paddingBlockSize;
 	} else {
 		return 0;
 	}
}

//------------------------------------------------------------------------------
int OCSBase2NCodec_getEncodedSize(const OCSCodec * myself, int decSize) {
	OCSBase2NCodec * me;
	int totalSize;

	me = (OCSBase2NCodec *)myself;
	totalSize = ((decSize * 8) + me->size - 1) / me->size;
	return totalSize + OCSBase2NCodec_getPaddingSize(me, totalSize);
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
	int bitBuffer;
	int bitBufferSize;
	int srcOffs;
	int dstOffs;
	int paddingSize;
	const uint8_t * pSrc;
	OCSBase2NCodec * me;

	me = (OCSBase2NCodec *)myself;

	// Ensure that the output buffer is large enough to hold the output.
	if ((*dstSize) < myself->getEncodedSize(myself, srcSize)) {
		return OCSERR_BUFFER_TOO_SMALL;
	}

	// Due to potential problems with pointer arithmetic on mainframes, we will
	// use offsets instead of pointers.
	bitBufferSize = 0;
	bitBuffer = 0;
	srcOffs = 0;
	dstOffs = 0;
	pSrc = (const uint8_t *)src;
	while (srcOffs < srcSize) {
		// Get a byte from source
		bitBuffer = (bitBuffer << 8) | pSrc[srcOffs];
		srcOffs++;
		bitBuffer += 8;
		// Add to dst
		while (bitBufferSize >= me->size) {
			bitBufferSize -= me->size;
			dst[dstOffs] = me->alphabet->getCharacter(me->alphabet,
					(bitBuffer >> bitBufferSize) & me->clearMask);
			dstOffs++;
		}
	}

	// Add the last char
	while (bitBufferSize > 0) {
		bitBuffer = bitBuffer << (me->size - bitBufferSize);
		dst[dstOffs] = me->alphabet->getCharacter(me->alphabet,
				bitBuffer & me->clearMask);
		dstOffs++;
	}

	// Add the padding?
	paddingSize = OCSBase2NCodec_getPaddingSize(me, dstOffs);
	while (paddingSize) {
		dst[dstOffs] = (char)me->paddingChar;
		dstOffs++;
		paddingSize--;
	}

	*dstSize = dstOffs;
	return OCSERR_SUCCESS;
}

//------------------------------------------------------------------------------
int OCSBase2NCodec_decode(const OCSCodec * myself,
		const char * src, int srcSize,
		void * dst, int * dstSize) {
	int bitBuffer;
	int bitBufferSize;
	int dstOffs;
	int srcOffs;
	int c;
	int v;
	bool stop;
	int paddingSize;
	int srcTrueSize;
	uint8_t * pDst;
	OCSBase2NCodec * me;

	me = (OCSBase2NCodec *)myself;

	// Ensure that the dst is large enough to hold the output
	if ((*dstSize) < myself->getDecodedSize(myself, srcSize)) {
		return OCSERR_BUFFER_TOO_SMALL;
	}

	// Due to potential problems with pointer arithmetic on mainframes, we will
	// use offsets instead of pointers.
	bitBuffer = 0;
	bitBufferSize = 0;
	paddingSize = 0;
	srcOffs = 0;
	dstOffs = 0;
	pDst = (uint8_t *) dst;
	srcTrueSize = 0;
	stop = (srcOffs >= dstOffs);
	while (!stop) {
		// Get the character from the input
		c = src[srcOffs];
		srcOffs++;
		stop = (srcOffs >= dstOffs);

		// Test ignored first!
		if (!me->isIgnored(me, c)) {
			srcTrueSize++;
			if (me->isPadding(me, c)) {
				stop = true;
				paddingSize = 1;
			} else {
				v = me->alphabet->getValue(me->alphabet, c);
				if (v < 0) {
					return OCSERR_CORRUPTED_ENCODED_DATA;
				} else {
					bitBuffer = (bitBuffer << me->size) | v;
					bitBufferSize += me->size;

					while (bitBuffer >= 8) {
						bitBufferSize -= 8;
						pDst[dstOffs] = (bitBuffer >> bitBufferSize) & 0xFF;
						dstOffs++;
					}
				}
			}
		}
	}

	// Verify the padding
	if (me->usePadding(me)) {
		if (paddingSize > 0) {
			// Removes the rest of the padding
			stop = (srcOffs >= dstOffs);
			while (!stop) {
				c = src[srcOffs];
				src++;
				if (!me->isIgnored(me, c)) {
					srcTrueSize++;
					if (!me->isPadding(me, c)) {
						return OCSERR_BAD_PADDING;
					}
				}
			}
		}
		// Check if srcTrueSize is indeed multiple of padding block size.
		if ((srcTrueSize % me->paddingBlockSize) != 0) {
			return OCSERR_BAD_PADDING;
		}
	}

	*dstSize = dstOffs;
	return OCSERR_SUCCESS;
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
