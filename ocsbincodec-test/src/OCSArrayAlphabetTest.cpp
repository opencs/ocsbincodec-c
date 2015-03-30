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
#include "OCSArrayAlphabetTest.h"

#include <ocsaalph.h>

const static char * CSArrayAlphabetTest_CHARS = "ABCDEFGHIJ";
#define CSArrayAlphabetTest_CHARS_SIZE 10

//==============================================================================
// class CSArrayAlphabetTest
//------------------------------------------------------------------------------
OCSArrayAlphabetTest::OCSArrayAlphabetTest() {
}

//------------------------------------------------------------------------------
OCSArrayAlphabetTest::~OCSArrayAlphabetTest() {
}

//------------------------------------------------------------------------------
void OCSArrayAlphabetTest::SetUp() {
}

//------------------------------------------------------------------------------
void OCSArrayAlphabetTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(OCSArrayAlphabetTest, Constructor) {
	OCSArrayAlphabet * a;
	OCSAlphabet * base;
	int retval;

	retval = OCSArrayAlphabet_New(&a, CSArrayAlphabetTest_CHARS, CSArrayAlphabetTest_CHARS_SIZE, 0);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	ASSERT_TRUE(a->alphabet != CSArrayAlphabetTest_CHARS);
	base = (OCSAlphabet*)a;
	ASSERT_TRUE(base->getCharacter == OCSArrayAlphabet_getCharacter);
	ASSERT_TRUE(base->getSize != NULL);
	ASSERT_TRUE(base->getValue == OCSArrayAlphabet_getValue);
	ASSERT_EQ(CSArrayAlphabetTest_CHARS_SIZE, base->getSize(base));
	OCSObjectDelete((OCSObject*)a);

	retval = OCSArrayAlphabet_New(&a, CSArrayAlphabetTest_CHARS, CSArrayAlphabetTest_CHARS_SIZE, 1);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	ASSERT_TRUE(a->alphabet != CSArrayAlphabetTest_CHARS);
	base = (OCSAlphabet*)a;
	ASSERT_TRUE(base->getCharacter == OCSArrayAlphabet_getCharacter);
	ASSERT_TRUE(base->getSize != NULL);
	ASSERT_TRUE(base->getValue == OCSArrayAlphabet_getValueCI);
	ASSERT_EQ(CSArrayAlphabetTest_CHARS_SIZE, base->getSize(base));
	OCSObjectDelete((OCSObject*)a);

}

//------------------------------------------------------------------------------
TEST_F(OCSArrayAlphabetTest, getCharacter) {
	OCSArrayAlphabet * a;
	OCSAlphabet * base;
	int retval;

	retval = OCSArrayAlphabet_New(&a, CSArrayAlphabetTest_CHARS, CSArrayAlphabetTest_CHARS_SIZE, 0);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	base = (OCSAlphabet*)a;

	for (int i = 0; i < base->getSize(base); i++) {
		ASSERT_EQ(CSArrayAlphabetTest_CHARS[i], base->getCharacter(base, i));
	}
	OCSObjectDelete((OCSObject*)a);
}

//------------------------------------------------------------------------------
TEST_F(OCSArrayAlphabetTest, getValue) {
	OCSArrayAlphabet * a;
	OCSAlphabet * base;
	int retval;

	retval = OCSArrayAlphabet_New(&a, CSArrayAlphabetTest_CHARS, CSArrayAlphabetTest_CHARS_SIZE, 0);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	base = (OCSAlphabet*)a;

	for (int i = 1; i < 256; i++) {
		const char * p = strchr(CSArrayAlphabetTest_CHARS, i);
		if (p) {
			int v = p - CSArrayAlphabetTest_CHARS;
			ASSERT_EQ(v, base->getValue(base, i));
		} else {
			ASSERT_EQ(-1, base->getValue(base, i));
		}
	}
	OCSObjectDelete((OCSObject*)a);
}

//------------------------------------------------------------------------------
TEST_F(OCSArrayAlphabetTest, getValueCI) {
	OCSArrayAlphabet * a;
	OCSAlphabet * base;
	int retval;

	retval = OCSArrayAlphabet_New(&a, CSArrayAlphabetTest_CHARS, CSArrayAlphabetTest_CHARS_SIZE, 1);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	base = (OCSAlphabet*)a;

	for (int i = 1; i < 256; i++) {
		const char * p = strchr(CSArrayAlphabetTest_CHARS, toupper(i));
		if (p) {
			int v = p - CSArrayAlphabetTest_CHARS;
			ASSERT_EQ(v, base->getValue(base, i));
		} else {
			ASSERT_EQ(-1, base->getValue(base, i));
		}
	}
	OCSObjectDelete((OCSObject*)a);
}
//------------------------------------------------------------------------------

