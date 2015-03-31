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
#include "OCSBase64AlphabetTest.h"
#include <ocsb64al.h>
#include <string.h>

#define OCSBase64AlphabetTest_CHARS "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
#define OCSBase64AlphabetTest_CHARS_SAFE "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_"

//==============================================================================
// class OCSBase64AlphabetTest
//------------------------------------------------------------------------------
OCSBase64AlphabetTest::OCSBase64AlphabetTest() {
}

//------------------------------------------------------------------------------
OCSBase64AlphabetTest::~OCSBase64AlphabetTest() {
}

//------------------------------------------------------------------------------
void OCSBase64AlphabetTest::SetUp() {
}

//------------------------------------------------------------------------------
void OCSBase64AlphabetTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(OCSBase64AlphabetTest,Constructor) {
	OCSBase64Alphabet * a;
	OCSAlphabet * base;
	int retval;

	retval = OCSBase64Alphabet_New(&a, false);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	base = (OCSAlphabet *) a;
	ASSERT_EQ(64, base->getSize(base));
	ASSERT_EQ(OCSBase64Alphabet_getValue, base->getValue);
	ASSERT_TRUE(base->getCharacter != NULL);
	ASSERT_TRUE(base->getSize != NULL);
	OCSObjectDelete((OCSObject*)a);

	retval = OCSBase64Alphabet_New(&a, true);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	base = (OCSAlphabet *) a;
	ASSERT_EQ(64, base->getSize(base));
	ASSERT_EQ(OCSBase64Alphabet_getValue, base->getValue);
	ASSERT_TRUE(base->getCharacter != NULL);
	ASSERT_TRUE(base->getSize != NULL);
	OCSObjectDelete((OCSObject*)a);

}

//------------------------------------------------------------------------------
TEST_F(OCSBase64AlphabetTest,getCharacter) {
	OCSBase64Alphabet * a;
	OCSAlphabet * base;
	int retval;

	retval = OCSBase64Alphabet_New(&a, false);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	base = (OCSAlphabet *) a;
	for (int i = 0; i < 64; i++) {
		ASSERT_EQ(OCSBase64AlphabetTest_CHARS[i], base->getCharacter(base, i));
	}
	OCSObjectDelete((OCSObject*)a);

	retval = OCSBase64Alphabet_New(&a, true);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	base = (OCSAlphabet *) a;
	for (int i = 0; i < 64; i++) {
		ASSERT_EQ(OCSBase64AlphabetTest_CHARS_SAFE[i], base->getCharacter(base, i));
	}
	OCSObjectDelete((OCSObject*)a);
}


//------------------------------------------------------------------------------
TEST_F(OCSBase64AlphabetTest,getValue) {
	OCSBase64Alphabet * a;
	OCSAlphabet * base;
	int retval;

	retval = OCSBase64Alphabet_New(&a, false);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	base = (OCSAlphabet *) a;
	for (int i = 1; i < 256; i++) {
		const char * p = strchr(OCSBase64AlphabetTest_CHARS, i);
		if (p) {
			int v = (p - OCSBase64AlphabetTest_CHARS);
			ASSERT_EQ(v, base->getValue(base, i));
		} else {
			ASSERT_EQ(-1, base->getValue(base, i));
		}
	}
	OCSObjectDelete((OCSObject*)a);

	retval = OCSBase64Alphabet_New(&a, true);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	base = (OCSAlphabet *) a;
	for (int i = 1; i < 256; i++) {
		const char * p = strchr(OCSBase64AlphabetTest_CHARS_SAFE, i);
		if (p) {
			int v = (p - OCSBase64AlphabetTest_CHARS_SAFE);
			ASSERT_EQ(v, base->getValue(base, i));
		} else {
			ASSERT_EQ(-1, base->getValue(base, i));
		}
	}
	OCSObjectDelete((OCSObject*)a);
}
//------------------------------------------------------------------------------

