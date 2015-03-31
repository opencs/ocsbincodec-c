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
#include "OCSBase32AlphabetTest.h"
#include <ocsb32al.h>


#define OCSBase32AlphabetTest_CHARS "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567"
#define OCSBase32AlphabetTest_CHARS_LC "abcdefghijklmnopqrstuvwxyz234567"

#define OCSBase32AlphabetTest_CHARS_ALL "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567abcdefghijklmnopqrstuvwxyz234567"

//==============================================================================
// class OCSBase32AlphabetTest
//------------------------------------------------------------------------------
OCSBase32AlphabetTest::OCSBase32AlphabetTest() {
}

//------------------------------------------------------------------------------
OCSBase32AlphabetTest::~OCSBase32AlphabetTest() {
}

//------------------------------------------------------------------------------
void OCSBase32AlphabetTest::SetUp() {
}

//------------------------------------------------------------------------------
void OCSBase32AlphabetTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(OCSBase32AlphabetTest, Constructor) {
	OCSBase32Alphabet * a;
	OCSAlphabet * base;
	int retval;

	retval = OCSBase32Alphabet_New(&a, false);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	base = (OCSAlphabet *) a;
	ASSERT_EQ(32, base->getSize(base));
	ASSERT_EQ(OCSBase32Alphabet_getValue, base->getValue);
	ASSERT_TRUE(base->getCharacter != NULL);
	ASSERT_TRUE(base->getSize != NULL);
	OCSObjectDelete((OCSObject*)a);

	retval = OCSBase32Alphabet_New(&a, true);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	base = (OCSAlphabet *) a;
	ASSERT_EQ(32, base->getSize(base));
	ASSERT_EQ(OCSBase32Alphabet_getValue, base->getValue);
	ASSERT_TRUE(base->getCharacter != NULL);
	ASSERT_TRUE(base->getSize != NULL);
	OCSObjectDelete((OCSObject*)a);

}

//------------------------------------------------------------------------------
TEST_F(OCSBase32AlphabetTest, getCharacter) {
	OCSBase32Alphabet * a;
	OCSAlphabet * base;
	int retval;

	retval = OCSBase32Alphabet_New(&a, false);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	base = (OCSAlphabet *) a;
	base = (OCSAlphabet *) a;
	for (int i = 0; i < 32; i++) {
		ASSERT_EQ(OCSBase32AlphabetTest_CHARS[i], base->getCharacter(base, i));
	}
	OCSObjectDelete((OCSObject*)a);


	retval = OCSBase32Alphabet_New(&a, true);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	base = (OCSAlphabet *) a;
	base = (OCSAlphabet *) a;
	for (int i = 0; i < 32; i++) {
		ASSERT_EQ(OCSBase32AlphabetTest_CHARS_LC[i], base->getCharacter(base, i));
	}
	OCSObjectDelete((OCSObject*)a);
}

//------------------------------------------------------------------------------
TEST_F(OCSBase32AlphabetTest, getValue) {
	OCSBase32Alphabet * a;
	OCSAlphabet * base;
	int retval;

	retval = OCSBase32Alphabet_New(&a, false);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	base = (OCSAlphabet *) a;
	for (int i = 1; i < 256; i++) {
		const char * p = strchr(OCSBase32AlphabetTest_CHARS_ALL, i);
		if (p) {
			int v = (p - OCSBase32AlphabetTest_CHARS_ALL) % 32;
			ASSERT_EQ(v, base->getValue(base, i));
		} else {
			ASSERT_EQ(-1, base->getValue(base, i));
		}
	}
	OCSObjectDelete((OCSObject*)a);

	retval = OCSBase32Alphabet_New(&a, true);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	base = (OCSAlphabet *) a;
	for (int i = 1; i < 256; i++) {
		const char * p = strchr(OCSBase32AlphabetTest_CHARS_ALL, i);
		if (p) {
			int v = (p - OCSBase32AlphabetTest_CHARS_ALL) % 32;
			ASSERT_EQ(v, base->getValue(base, i));
		} else {
			ASSERT_EQ(-1, base->getValue(base, i));
		}
	}
	OCSObjectDelete((OCSObject*)a);
}


//------------------------------------------------------------------------------

