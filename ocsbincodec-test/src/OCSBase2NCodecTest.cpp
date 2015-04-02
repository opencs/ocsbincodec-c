/*
 * Copyright (c) 2015, Open Communications Security
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
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
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "OCSBase2NCodecTest.h"
#include <ocsb64al.h>
#include <ocsb2nco.h>


// Test vectors extracted from RFC4648 and other sources
#define OCSBase2NCodecTest_SAMPLES_SIZE 8
static const char * OCSBase2NCodecTest_SAMPLES[8][3] = {
	{ "", "", "" },
	{ "f", "Zg==", "Zg" },
	{ "fo", "Zm8=", "Zm8" },
	{ "foo", "Zm9v", "Zm9v" },
	{ "foob", "Zm9vYg==", "Zm9vYg" },
	{ "fooba", "Zm9vYmE=", "Zm9vYmE" },
	{ "foobar", "Zm9vYmFy", "Zm9vYmFy"},
	{ "This is just a test...\n", "VGhpcyBpcyBqdXN0IGEgdGVzdC4uLgo=", "VGhpcyBpcyBqdXN0IGEgdGVzdC4uLgo"}
};

//==============================================================================
// class OCSBase2NCodecTest
//------------------------------------------------------------------------------
OCSBase2NCodecTest::OCSBase2NCodecTest() {
}

//------------------------------------------------------------------------------
OCSBase2NCodecTest::~OCSBase2NCodecTest() {
}

//------------------------------------------------------------------------------
void OCSBase2NCodecTest::SetUp() {
}

//------------------------------------------------------------------------------
void OCSBase2NCodecTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(OCSBase2NCodecTest, ConstructorNoPaddingNoIgnore) {
	OCSBase64Alphabet * a;
	OCSBase2NCodec * c;
	OCSCodec * base;
	int retval;

	retval = OCSBase64Alphabet_New(&a, false);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	retval = OCSBase2NCodec_New(&c, (OCSAlphabet*)a, 0, 0, NULL);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	ASSERT_TRUE(c->alphabet == ((OCSAlphabet*)a));
	ASSERT_EQ(0x3F, c->clearMask);
	ASSERT_EQ(0, c->paddingBlockSize);
	ASSERT_EQ(0, c->paddingChar);
	ASSERT_EQ(6, c->size);
	ASSERT_TRUE(c->ignores == NULL);
	ASSERT_TRUE(c->isIgnored == OCSBase2NCodec_isIgnored);
	ASSERT_TRUE(c->isPadding == OCSBase2NCodec_isPadding);
	ASSERT_TRUE(c->usePadding == OCSBase2NCodec_usePadding);
	base = (OCSCodec *)c;
	ASSERT_TRUE(base->decode == OCSBase2NCodec_decode);
	ASSERT_TRUE(base->encode == OCSBase2NCodec_encode);
	ASSERT_TRUE(base->getDecodedSize == OCSBase2NCodec_getDecodedSize);
	ASSERT_TRUE(base->getEncodedSize == OCSBase2NCodec_getEncodedSize);
	OCSObjectDelete((OCSObject *) c);
}

//------------------------------------------------------------------------------
TEST_F(OCSBase2NCodecTest, ConstructorNoPaddingIgnore) {
	OCSBase64Alphabet * a;
	OCSBase2NCodec * c;
	OCSCodec * base;
	int retval;
	const char * spaces = OCSBase2NCodec_SPACES;

	retval = OCSBase64Alphabet_New(&a, false);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	retval = OCSBase2NCodec_New(&c, (OCSAlphabet*)a, 0, 0, spaces);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	ASSERT_TRUE(c->alphabet == ((OCSAlphabet*)a));
	ASSERT_EQ(0x3F, c->clearMask);
	ASSERT_EQ(0, c->paddingBlockSize);
	ASSERT_EQ(0, c->paddingChar);
	ASSERT_EQ(6, c->size);
	ASSERT_TRUE(c->ignores != NULL);
	ASSERT_TRUE(c->ignores != spaces);
	ASSERT_STREQ(spaces, c->ignores);
	ASSERT_TRUE(c->isIgnored == OCSBase2NCodec_isIgnored);
	ASSERT_TRUE(c->isPadding == OCSBase2NCodec_isPadding);
	ASSERT_TRUE(c->usePadding == OCSBase2NCodec_usePadding);
	base = (OCSCodec *)c;
	ASSERT_TRUE(base->decode == OCSBase2NCodec_decode);
	ASSERT_TRUE(base->encode == OCSBase2NCodec_encode);
	ASSERT_TRUE(base->getDecodedSize == OCSBase2NCodec_getDecodedSize);
	ASSERT_TRUE(base->getEncodedSize == OCSBase2NCodec_getEncodedSize);
	OCSObjectDelete((OCSObject *) c);
}

//------------------------------------------------------------------------------
TEST_F(OCSBase2NCodecTest, ConstructorPaddingNoIgnore) {
	OCSBase64Alphabet * a;
	OCSBase2NCodec * c;
	OCSCodec * base;
	int retval;

	retval = OCSBase64Alphabet_New(&a, false);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	retval = OCSBase2NCodec_New(&c, (OCSAlphabet*)a, '=', 4, NULL);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	ASSERT_TRUE(c->alphabet == ((OCSAlphabet*)a));
	ASSERT_EQ(0x3F, c->clearMask);
	ASSERT_EQ(4, c->paddingBlockSize);
	ASSERT_EQ('=', c->paddingChar);
	ASSERT_EQ(6, c->size);
	ASSERT_TRUE(c->ignores == NULL);
	ASSERT_TRUE(c->isIgnored == OCSBase2NCodec_isIgnored);
	ASSERT_TRUE(c->isPadding == OCSBase2NCodec_isPadding);
	ASSERT_TRUE(c->usePadding == OCSBase2NCodec_usePadding);
	base = (OCSCodec *)c;
	ASSERT_TRUE(base->decode == OCSBase2NCodec_decode);
	ASSERT_TRUE(base->encode == OCSBase2NCodec_encode);
	ASSERT_TRUE(base->getDecodedSize == OCSBase2NCodec_getDecodedSize);
	ASSERT_TRUE(base->getEncodedSize == OCSBase2NCodec_getEncodedSize);
	OCSObjectDelete((OCSObject *) c);
}

//------------------------------------------------------------------------------
TEST_F(OCSBase2NCodecTest, ConstructorPaddingIgnore) {
	OCSBase64Alphabet * a;
	OCSBase2NCodec * c;
	OCSCodec * base;
	int retval;
	const char * spaces = OCSBase2NCodec_SPACES;

	retval = OCSBase64Alphabet_New(&a, false);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	retval = OCSBase2NCodec_New(&c, (OCSAlphabet*)a, '=', 4, spaces);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	ASSERT_TRUE(c->alphabet == ((OCSAlphabet*)a));
	ASSERT_EQ(0x3F, c->clearMask);
	ASSERT_EQ(4, c->paddingBlockSize);
	ASSERT_EQ('=', c->paddingChar);
	ASSERT_EQ(6, c->size);
	ASSERT_TRUE(c->ignores != NULL);
	ASSERT_TRUE(c->ignores != spaces);
	ASSERT_STREQ(spaces, c->ignores);
	ASSERT_TRUE(c->isIgnored == OCSBase2NCodec_isIgnored);
	ASSERT_TRUE(c->isPadding == OCSBase2NCodec_isPadding);
	ASSERT_TRUE(c->usePadding == OCSBase2NCodec_usePadding);
	base = (OCSCodec *)c;
	ASSERT_TRUE(base->decode == OCSBase2NCodec_decode);
	ASSERT_TRUE(base->encode == OCSBase2NCodec_encode);
	ASSERT_TRUE(base->getDecodedSize == OCSBase2NCodec_getDecodedSize);
	ASSERT_TRUE(base->getEncodedSize == OCSBase2NCodec_getEncodedSize);
	OCSObjectDelete((OCSObject *) c);
}

//------------------------------------------------------------------------------
TEST_F(OCSBase2NCodecTest, getEncodedSize) {
	OCSBase64Alphabet * a;
	OCSBase2NCodec * c;
	OCSCodec * base;
	int retval;
	const char * spaces = OCSBase2NCodec_SPACES;
	int decSize;
	int expectedSize;

	// No padding, no ignore list
	retval = OCSBase64Alphabet_New(&a, false);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	retval = OCSBase2NCodec_New(&c, (OCSAlphabet*)a, 0, 0, NULL);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	base = (OCSCodec *)c;
	for (decSize = 0; decSize < 1024; decSize++) {
		expectedSize = ((decSize * 8) + 5) / 6;
		ASSERT_EQ(expectedSize, base->getEncodedSize(base, decSize));
	}
	OCSObjectDelete((OCSObject *) c);

	// Padding, no ignore list
	retval = OCSBase64Alphabet_New(&a, false);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	retval = OCSBase2NCodec_New(&c, (OCSAlphabet*)a, '=', 4, NULL);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	base = (OCSCodec *)c;
	for (decSize = 0; decSize < 1024; decSize++) {
		expectedSize = ((decSize * 8) + 5) / 6;
		expectedSize = expectedSize + ((4 - expectedSize % 4) % 4);
		ASSERT_EQ(expectedSize, base->getEncodedSize(base, decSize));
	}
	OCSObjectDelete((OCSObject *) c);

	// No padding, ignore list
	retval = OCSBase64Alphabet_New(&a, false);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	retval = OCSBase2NCodec_New(&c, (OCSAlphabet*)a, 0, 0, spaces);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	base = (OCSCodec *)c;
	for (decSize = 0; decSize < 1024; decSize++) {
		expectedSize = ((decSize * 8) + 5) / 6;
		ASSERT_EQ(expectedSize, base->getEncodedSize(base, decSize));
	}
	OCSObjectDelete((OCSObject *) c);

	// Padding, ignore list
	retval = OCSBase64Alphabet_New(&a, false);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	retval = OCSBase2NCodec_New(&c, (OCSAlphabet*)a, '=', 4, spaces);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	base = (OCSCodec *)c;
	for (decSize = 0; decSize < 1024; decSize++) {
		expectedSize = ((decSize * 8) + 5) / 6;
		expectedSize = expectedSize + ((4 - expectedSize % 4) % 4);
		ASSERT_EQ(expectedSize, base->getEncodedSize(base, decSize));
	}
	OCSObjectDelete((OCSObject *) c);
}

//------------------------------------------------------------------------------
TEST_F(OCSBase2NCodecTest, getDecodedSize) {
	OCSBase64Alphabet * a;
	OCSBase2NCodec * c;
	OCSCodec * base;
	int retval;
	const char * spaces = OCSBase2NCodec_SPACES;
	int encSize;
	int expectedSize;

	// No padding, no ignore list
	retval = OCSBase64Alphabet_New(&a, false);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	retval = OCSBase2NCodec_New(&c, (OCSAlphabet*)a, 0, 0, NULL);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	base = (OCSCodec *)c;
	for (encSize = 0; encSize < 1024; encSize++) {
		expectedSize = (encSize * 6) / 8;
		ASSERT_EQ(expectedSize, base->getDecodedSize(base, encSize));
	}
	OCSObjectDelete((OCSObject *) c);

	// Padding, no ignore list
	retval = OCSBase64Alphabet_New(&a, false);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	retval = OCSBase2NCodec_New(&c, (OCSAlphabet*)a, '=', 4, NULL);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	base = (OCSCodec *)c;
	for (encSize = 0; encSize < 1024; encSize++) {
		expectedSize = (encSize * 6) / 8;
		ASSERT_EQ(expectedSize, base->getDecodedSize(base, encSize));
	}
	OCSObjectDelete((OCSObject *) c);

	// No padding, ignore list
	retval = OCSBase64Alphabet_New(&a, false);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	retval = OCSBase2NCodec_New(&c, (OCSAlphabet*)a, 0, 0, spaces);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	base = (OCSCodec *)c;
	for (encSize = 0; encSize < 1024; encSize++) {
		expectedSize = (encSize * 6) / 8;
		ASSERT_EQ(expectedSize, base->getDecodedSize(base, encSize));
	}
	OCSObjectDelete((OCSObject *) c);

	// Padding, ignore list
	retval = OCSBase64Alphabet_New(&a, false);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	retval = OCSBase2NCodec_New(&c, (OCSAlphabet*)a, '=', 4, spaces);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	base = (OCSCodec *)c;
	for (encSize = 0; encSize < 1024; encSize++) {
		expectedSize = (encSize * 6) / 8;
		ASSERT_EQ(expectedSize, base->getDecodedSize(base, encSize));
	}
	OCSObjectDelete((OCSObject *) c);
}

//------------------------------------------------------------------------------
TEST_F(OCSBase2NCodecTest, padding) {
	OCSBase64Alphabet * a;
	OCSBase2NCodec * c;
	const char * spaces = OCSBase2NCodec_SPACES;
	int retval;
	int i;

	// No padding, no ignore list
	retval = OCSBase64Alphabet_New(&a, false);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	retval = OCSBase2NCodec_New(&c, (OCSAlphabet*)a, '=', 0, NULL);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	ASSERT_FALSE(c->usePadding(c));
	for (i = 0 ; i < 256; i++) {
		ASSERT_FALSE(c->isPadding(c, i));
	}
	OCSObjectDelete((OCSObject *) c);

	// No padding, ignore list
	retval = OCSBase64Alphabet_New(&a, false);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	retval = OCSBase2NCodec_New(&c, (OCSAlphabet*)a, '=', 0, spaces);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	ASSERT_FALSE(c->usePadding(c));
	for (i = 0 ; i < 256; i++) {
		ASSERT_FALSE(c->isPadding(c, i));
	}
	OCSObjectDelete((OCSObject *) c);

	// No padding, no ignore list
	retval = OCSBase64Alphabet_New(&a, false);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	retval = OCSBase2NCodec_New(&c, (OCSAlphabet*)a, '=', 1, NULL);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	ASSERT_FALSE(c->usePadding(c));
	for (i = 0 ; i < 256; i++) {
		ASSERT_FALSE(c->isPadding(c, i));
	}
	OCSObjectDelete((OCSObject *) c);

	// No padding, ignore list
	retval = OCSBase64Alphabet_New(&a, false);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	retval = OCSBase2NCodec_New(&c, (OCSAlphabet*)a, '=', 1, spaces);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	ASSERT_FALSE(c->usePadding(c));
	for (i = 0 ; i < 256; i++) {
		ASSERT_FALSE(c->isPadding(c, i));
	}
	OCSObjectDelete((OCSObject *) c);

	// No padding, no ignore list
	retval = OCSBase64Alphabet_New(&a, false);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	retval = OCSBase2NCodec_New(&c, (OCSAlphabet*)a, '=', 2, NULL);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	ASSERT_TRUE(c->usePadding(c));
	for (i = 0 ; i < 256; i++) {
		if (i == '=') {
			ASSERT_TRUE(c->isPadding(c, i));
		} else {
			ASSERT_FALSE(c->isPadding(c, i));
		}
	}
	OCSObjectDelete((OCSObject *) c);

	// No padding, ignore list
	retval = OCSBase64Alphabet_New(&a, false);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	retval = OCSBase2NCodec_New(&c, (OCSAlphabet*)a, '=', 2, spaces);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	ASSERT_TRUE(c->usePadding(c));
	for (i = 0 ; i < 256; i++) {
		if (i == '=') {
			ASSERT_TRUE(c->isPadding(c, i));
		} else {
			ASSERT_FALSE(c->isPadding(c, i));
		}
	}
	OCSObjectDelete((OCSObject *) c);

	// No padding, no ignore list
	retval = OCSBase64Alphabet_New(&a, false);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	retval = OCSBase2NCodec_New(&c, (OCSAlphabet*)a, '=', 4, NULL);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	ASSERT_TRUE(c->usePadding(c));
	for (i = 0 ; i < 256; i++) {
		if (i == '=') {
			ASSERT_TRUE(c->isPadding(c, i));
		} else {
			ASSERT_FALSE(c->isPadding(c, i));
		}
	}
	OCSObjectDelete((OCSObject *) c);

	// No padding, ignore list
	retval = OCSBase64Alphabet_New(&a, false);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	retval = OCSBase2NCodec_New(&c, (OCSAlphabet*)a, '=', 4, spaces);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	ASSERT_TRUE(c->usePadding(c));
	for (i = 0 ; i < 256; i++) {
		if (i == '=') {
			ASSERT_TRUE(c->isPadding(c, i));
		} else {
			ASSERT_FALSE(c->isPadding(c, i));
		}
	}
	OCSObjectDelete((OCSObject *) c);
}


//------------------------------------------------------------------------------
extern "C"
int OCSBase2NCodec_getPaddingSize(const OCSBase2NCodec * myself, int totalSize);
TEST_F(OCSBase2NCodecTest, getPaddingSize) {
	OCSBase64Alphabet * a;
	OCSBase2NCodec * c;
	int retval;
	int paddingBlockSize;
	int expected;
	int size;

	for (paddingBlockSize = 0; paddingBlockSize <= 4; paddingBlockSize++) {
		retval = OCSBase64Alphabet_New(&a, false);
		ASSERT_EQ(OCSERR_SUCCESS, retval);
		retval = OCSBase2NCodec_New(&c, (OCSAlphabet*)a, '=', paddingBlockSize,
				NULL);
		ASSERT_EQ(OCSERR_SUCCESS, retval);
		for (size = 0; size < 1024; size++) {
			if(c->usePadding(c)) {
				expected = (paddingBlockSize - (size % paddingBlockSize)) %
						paddingBlockSize;
			} else {
				expected = 0;
			}
			ASSERT_EQ(expected, OCSBase2NCodec_getPaddingSize(c, size));
		}
		OCSObjectDelete((OCSObject *) c);
	}
}

//------------------------------------------------------------------------------
TEST_F(OCSBase2NCodecTest, encodingNoPadding) {
	OCSBase64Alphabet * a;
	OCSBase2NCodec * c;
	OCSCodec * base;
	const char ** sample;
	char dst[256];
	int srcSize;
	int tmpSize;
	int dstSize;
	int dstSize2;
	int retval;
	int i;

	// No padding, no ignore list
	retval = OCSBase64Alphabet_New(&a, false);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	retval = OCSBase2NCodec_New(&c, (OCSAlphabet*)a, '=', 0, NULL);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	base = (OCSCodec *)c;
	for (i = 0 ; i < OCSBase2NCodecTest_SAMPLES_SIZE; i++) {
		sample = OCSBase2NCodecTest_SAMPLES[i];
		srcSize = strlen(sample[0]);
		dstSize = base->getEncodedSize(base, srcSize);
		for (tmpSize = 0; tmpSize < dstSize; tmpSize++) {
			dstSize2 = tmpSize;
			retval = base->encode(base, sample[0], srcSize, dst, &dstSize2);
			ASSERT_EQ(OCSERR_BUFFER_TOO_SMALL, retval);
		}
		memset(dst, '*', sizeof(dst));
		dstSize2 = dstSize;
		retval = base->encode(base, sample[0], srcSize, dst, &dstSize2);
		ASSERT_EQ(OCSERR_SUCCESS, retval);
		ASSERT_EQ('*', dst[dstSize2]);
		dst[dstSize2] = 0;
		ASSERT_STREQ(sample[2], dst);
	}
	OCSObjectDelete((OCSObject *) c);
}

//------------------------------------------------------------------------------
TEST_F(OCSBase2NCodecTest, encodingPadding) {
	OCSBase64Alphabet * a;
	OCSBase2NCodec * c;
	OCSCodec * base;
	const char ** sample;
	char dst[256];
	int srcSize;
	int tmpSize;
	int dstSize;
	int dstSize2;
	int retval;
	int i;

	// No padding, no ignore list
	retval = OCSBase64Alphabet_New(&a, false);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	retval = OCSBase2NCodec_New(&c, (OCSAlphabet*)a, '=', 4, NULL);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	base = (OCSCodec *)c;
	for (i = 0 ; i < OCSBase2NCodecTest_SAMPLES_SIZE; i++) {
		sample = OCSBase2NCodecTest_SAMPLES[i];
		srcSize = strlen(sample[0]);
		dstSize = base->getEncodedSize(base, srcSize);
		for (tmpSize = 0; tmpSize < dstSize; tmpSize++) {
			dstSize2 = tmpSize;
			retval = base->encode(base, sample[0], srcSize, dst, &dstSize2);
			ASSERT_EQ(OCSERR_BUFFER_TOO_SMALL, retval);
		}
		memset(dst, '*', sizeof(dst));
		dstSize2 = dstSize;
		retval = base->encode(base, sample[0], srcSize, dst, &dstSize2);
		ASSERT_EQ(OCSERR_SUCCESS, retval);
		ASSERT_EQ('*', dst[dstSize2]);
		dst[dstSize2] = 0;
		ASSERT_STREQ(sample[1], dst);
	}
	OCSObjectDelete((OCSObject *) c);
}


//------------------------------------------------------------------------------

