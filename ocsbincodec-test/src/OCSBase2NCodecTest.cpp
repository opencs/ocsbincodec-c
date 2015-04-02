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

	// No padding, no ignore list
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

	// No padding, no ignore list
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

	// No padding, no ignore list
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

	// No padding, no ignore list
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

