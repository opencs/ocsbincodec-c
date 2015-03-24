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
#include "OCSBinaryAlphabetTest.h"
#include <ocsbalph.h>

//==============================================================================
// class OCSBinaryAlphabetTest
//------------------------------------------------------------------------------
OCSBinaryAlphabetTest::OCSBinaryAlphabetTest() {
}

//------------------------------------------------------------------------------
OCSBinaryAlphabetTest::~OCSBinaryAlphabetTest() {
}

//------------------------------------------------------------------------------
void OCSBinaryAlphabetTest::SetUp() {
}

//------------------------------------------------------------------------------
void OCSBinaryAlphabetTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(OCSBinaryAlphabetTest, Constructor) {
	OCSBinaryAlphabet * a;
	OCSAlphabet * pa;
	int retval;

	retval = OCSBinaryAlphabet_New(&a, '0', '1');
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	ASSERT_EQ('0', a->_zero);
	ASSERT_EQ('1', a->_one);

	pa = (OCSAlphabet*)a;
	ASSERT_TRUE(pa->getCharacter != NULL);
	ASSERT_TRUE(pa->getSize != NULL);
	ASSERT_TRUE(pa->getValue != NULL);
	ASSERT_EQ(2, pa->getSize(pa));

	OCSObjectDelete((OCSObject*)a);
}

//------------------------------------------------------------------------------
TEST_F(OCSBinaryAlphabetTest, getValue) {
	OCSBinaryAlphabet * a;
	OCSAlphabet * pa;
	int retval;
	int c;

	retval = OCSBinaryAlphabet_New(&a, '0', '1');
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	ASSERT_EQ('0', a->_zero);
	ASSERT_EQ('1', a->_one);

	pa = (OCSAlphabet*)a;
	ASSERT_EQ(0, pa->getValue(pa, '0'));
	ASSERT_EQ(1, pa->getValue(pa, '1'));

	for (c = 0; c < 256; c++) {
		if (c == '0') {
			ASSERT_EQ(0, pa->getValue(pa, c));
		} else if (c == '1') {
			ASSERT_EQ(1, pa->getValue(pa, c));
		} else {
			ASSERT_EQ(-1, pa->getValue(pa, c));
		}
	}

	OCSObjectDelete((OCSObject*)a);
}

//------------------------------------------------------------------------------
TEST_F(OCSBinaryAlphabetTest, getCharacter) {
	OCSBinaryAlphabet * a;
	OCSAlphabet * pa;
	int retval;
	int c;

	retval = OCSBinaryAlphabet_New(&a, '0', '1');
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	ASSERT_EQ('0', a->_zero);
	ASSERT_EQ('1', a->_one);

	pa = (OCSAlphabet*)a;
	ASSERT_EQ('0', pa->getCharacter(pa, 0));
	ASSERT_EQ('1', pa->getCharacter(pa, 1));

	OCSObjectDelete((OCSObject*)a);
}

//------------------------------------------------------------------------------


