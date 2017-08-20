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
#include "Base64CodecTest.h"
#include <ocsb64al.h>
#include <ocsb2nco.h>

//==============================================================================
// class Base64CodecTest
//------------------------------------------------------------------------------
Base64CodecTest::Base64CodecTest() {
}

//------------------------------------------------------------------------------
Base64CodecTest::~Base64CodecTest() {
}

//------------------------------------------------------------------------------
void Base64CodecTest::SetUp() {
}

//------------------------------------------------------------------------------
void Base64CodecTest::TearDown() {
}

//------------------------------------------------------------------------------
// Samples
static const unsigned char Base64CodecTest_SAMPLE_BIN1[1] = {
	0xAD
};

static const unsigned char Base64CodecTest_SAMPLE_BIN2[2] = {
	0x9E, 0x49
};

static const unsigned char Base64CodecTest_SAMPLE_BIN3[3] = {
	0x2E, 0xD7, 0xB5
};

static const unsigned char Base64CodecTest_SAMPLE_BIN4[4] = {
	0xB0, 0x3E, 0x94, 0x77
};

static const unsigned char Base64CodecTest_SAMPLE_BIN5[5] = {
	0x78, 0x81, 0x20, 0x57, 0x4B
};

static const unsigned char Base64CodecTest_SAMPLE_BIN6[6] = {
	0xBC, 0xD1, 0x8B, 0x16, 0x8A, 0x26
};

static const unsigned char Base64CodecTest_SAMPLE_BIN7[7] = {
	0x59, 0xDE, 0x17, 0x27, 0x87, 0xD1, 0xFC
};

static const unsigned char Base64CodecTest_SAMPLE_BIN8[8] = {
	0x75, 0x11, 0x23, 0x81, 0xC2, 0x38, 0xEC, 0x65
};

static const unsigned char Base64CodecTest_SAMPLE_BIN9[9] = {
	0x13, 0xF2, 0x74, 0x36, 0xF8, 0x03, 0xC8, 0x1D,
	0x3C
};

static const unsigned char Base64CodecTest_SAMPLE_BIN10[10] = {
	0x2B, 0x43, 0x44, 0xD5, 0xD5, 0x8F, 0xF4, 0x45,
	0x96, 0xA3
};

static const unsigned char Base64CodecTest_SAMPLE_BIN11[11] = {
	0x6B, 0xBA, 0xA4, 0x3F, 0x4B, 0x65, 0x47, 0xAC,
	0x3A, 0x28, 0x6E
};

static const unsigned char Base64CodecTest_SAMPLE_BIN12[12] = {
	0xE4, 0x72, 0x01, 0x5A, 0xED, 0xE8, 0x26, 0xDD,
	0xA9, 0x03, 0x2D, 0x4B
};

static const unsigned char Base64CodecTest_SAMPLE_BIN13[13] = {
	0x6F, 0x31, 0xDA, 0xCE, 0x08, 0xAE, 0x36, 0x24,
	0xF1, 0x90, 0x0F, 0x4E, 0x06
};

static const unsigned char Base64CodecTest_SAMPLE_BIN14[14] = {
	0x96, 0x6F, 0x27, 0xD7, 0x7F, 0x9F, 0xE4, 0x9D,
	0x75, 0x89, 0xE9, 0x19, 0x30, 0xCE
};

static const unsigned char Base64CodecTest_SAMPLE_BIN15[15] = {
	0x77, 0x81, 0xFF, 0xAC, 0x5D, 0x92, 0xB4, 0x62,
	0x29, 0x15, 0x66, 0x2A, 0x84, 0xF1, 0xC2
};

static const unsigned char Base64CodecTest_SAMPLE_BIN16[16] = {
	0xA8, 0x78, 0xC3, 0x3A, 0xA8, 0xEF, 0x41, 0xC7,
	0x05, 0x30, 0x6D, 0x29, 0x01, 0xB9, 0x84, 0x9C
};

typedef struct {
	const char * encoded;
	int decodedSize;
	const unsigned char * decoded;
} Base64CodecTest_sample_entry_t;

#define B64_SAMPLES_SIZE 16
static const Base64CodecTest_sample_entry_t Base64CodecTest_SAMPLES[B64_SAMPLES_SIZE] = {
	{"rQ==", sizeof(Base64CodecTest_SAMPLE_BIN1), Base64CodecTest_SAMPLE_BIN1},
	{"nkk=", sizeof(Base64CodecTest_SAMPLE_BIN2), Base64CodecTest_SAMPLE_BIN2},
	{"Lte1", sizeof(Base64CodecTest_SAMPLE_BIN3), Base64CodecTest_SAMPLE_BIN3},
	{"sD6Udw==", sizeof(Base64CodecTest_SAMPLE_BIN4), Base64CodecTest_SAMPLE_BIN4},
	{"eIEgV0s=", sizeof(Base64CodecTest_SAMPLE_BIN5), Base64CodecTest_SAMPLE_BIN5},
	{"vNGLFoom", sizeof(Base64CodecTest_SAMPLE_BIN6), Base64CodecTest_SAMPLE_BIN6},
	{"Wd4XJ4fR/A==", sizeof(Base64CodecTest_SAMPLE_BIN7), Base64CodecTest_SAMPLE_BIN7},
	{"dREjgcI47GU=", sizeof(Base64CodecTest_SAMPLE_BIN8), Base64CodecTest_SAMPLE_BIN8},
	{"E/J0NvgDyB08", sizeof(Base64CodecTest_SAMPLE_BIN9), Base64CodecTest_SAMPLE_BIN9},
	{"K0NE1dWP9EWWow==", sizeof(Base64CodecTest_SAMPLE_BIN10), Base64CodecTest_SAMPLE_BIN10},
	{"a7qkP0tlR6w6KG4=", sizeof(Base64CodecTest_SAMPLE_BIN11), Base64CodecTest_SAMPLE_BIN11},
	{"5HIBWu3oJt2pAy1L", sizeof(Base64CodecTest_SAMPLE_BIN12), Base64CodecTest_SAMPLE_BIN12},
	{"bzHazgiuNiTxkA9OBg==", sizeof(Base64CodecTest_SAMPLE_BIN13), Base64CodecTest_SAMPLE_BIN13},
	{"lm8n13+f5J11iekZMM4=", sizeof(Base64CodecTest_SAMPLE_BIN14), Base64CodecTest_SAMPLE_BIN14},
	{"d4H/rF2StGIpFWYqhPHC", sizeof(Base64CodecTest_SAMPLE_BIN15), Base64CodecTest_SAMPLE_BIN15},
	{"qHjDOqjvQccFMG0pAbmEnA==", sizeof(Base64CodecTest_SAMPLE_BIN16), Base64CodecTest_SAMPLE_BIN16},
};

//------------------------------------------------------------------------------
TEST_F(Base64CodecTest, EncodeWithPadding) {
	OCSBase64Alphabet * a;
	OCSBase2NCodec * c;
	OCSCodec * base;
	char enc[256];
	int encSize;
	int retval;

	retval = OCSBase64Alphabet_New(&a, false);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	retval = OCSBase2NCodec_New(&c, (OCSAlphabet*)a, '=', 4, NULL);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	base = (OCSCodec *)c;
	for (int i = 0; i < B64_SAMPLES_SIZE; i++) {
		// Test the size first
		encSize = base->getEncodedSize(base, Base64CodecTest_SAMPLES[i].decodedSize);
		ASSERT_EQ(strlen(Base64CodecTest_SAMPLES[i].encoded) , encSize);

		encSize = sizeof(enc);
		retval = base->encode(base,
				Base64CodecTest_SAMPLES[i].decoded, Base64CodecTest_SAMPLES[i].decodedSize,
				enc, &encSize);
		ASSERT_EQ(OCSERR_SUCCESS, retval);
		ASSERT_EQ(strlen(Base64CodecTest_SAMPLES[i].encoded) , encSize);
		enc[encSize] = 0;
		ASSERT_STREQ(Base64CodecTest_SAMPLES[i].encoded, enc);
	}

	// Cleanup
	OCSObjectDelete((OCSObject *) c);
}

//------------------------------------------------------------------------------
TEST_F(Base64CodecTest, DecodeWithPadding) {
	OCSBase64Alphabet * a;
	OCSBase2NCodec * c;
	OCSCodec * base;
	unsigned char dec[256];
	int decSize;
	int retval;

	retval = OCSBase64Alphabet_New(&a, false);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	retval = OCSBase2NCodec_New(&c, (OCSAlphabet*)a, '=', 4, NULL);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	base = (OCSCodec *)c;
	for (int i = 0; i < B64_SAMPLES_SIZE; i++) {
		// Test the size first
		decSize = base->getDecodedSize(base, strlen(Base64CodecTest_SAMPLES[i].encoded));
		ASSERT_LE(Base64CodecTest_SAMPLES[i].decodedSize, decSize);

		decSize = sizeof(dec);
		retval = base->decode(base,
				Base64CodecTest_SAMPLES[i].encoded, strlen(Base64CodecTest_SAMPLES[i].encoded),
				dec, &decSize);
		ASSERT_EQ(OCSERR_SUCCESS, retval);
		ASSERT_EQ(Base64CodecTest_SAMPLES[i].decodedSize , decSize);
		ASSERT_EQ(0, memcmp(Base64CodecTest_SAMPLES[i].decoded, dec, decSize));
	}

	// Cleanup
	OCSObjectDelete((OCSObject *) c);
}
//------------------------------------------------------------------------------

