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
#include "OCSRandomSourceTest.h"
#include "CIntegerFileReader.h"
#include <ocsrand.h>

//==============================================================================
// class OCSRandomSourceTest
//------------------------------------------------------------------------------
OCSRandomSourceTest::OCSRandomSourceTest() {
}

//------------------------------------------------------------------------------
OCSRandomSourceTest::~OCSRandomSourceTest() {
}

//------------------------------------------------------------------------------
void OCSRandomSourceTest::SetUp() {
}

//------------------------------------------------------------------------------
void OCSRandomSourceTest::TearDown() {
}

#define SAMPLE_FILES_SIZE 3
const static char * SAMPLE_FILES[SAMPLE_FILES_SIZE] = {
#ifndef _WIN32
		"data/RandomSequence1.txt",
		"data/RandomSequence2.txt",
		"data/RandomSequence3.txt"
#else
		"data\\RandomSequence1.txt",
		"data\\RandomSequence2.txt",
		"data\\RandomSequence3.txt"
#endif
};

//------------------------------------------------------------------------------
TEST_F(OCSRandomSourceTest, Constructor) {
	OCSRandomSource * r;
	int retval;

	r = NULL;
	retval = OCSRandomSource_New(&r, 0);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	ASSERT_TRUE(r->next != NULL);
	OCSObjectDelete((OCSObject*)r);
}

//------------------------------------------------------------------------------
TEST_F(OCSRandomSourceTest, next) {
	OCSRandomSource * r;
	CIntegerFileReader * inp;
	int i;
	int j;
	int v;
	int retval;

	for (i = 0; i < 3; i++) {
		inp = new CIntegerFileReader(SAMPLE_FILES[i]);
		ASSERT_TRUE(inp->isOpen());

		ASSERT_TRUE(inp->nextInt(v));
		r = NULL;
		retval = OCSRandomSource_New(&r, v);
		ASSERT_EQ(OCSERR_SUCCESS, retval);

		for (j = 0; j < 1000; j++) {
			std::cout << j << " " << v << "\n";
			ASSERT_TRUE(inp->nextInt(v));
			ASSERT_EQ(v, r->next(r));
		}

		OCSObjectDelete((OCSObject*)r);
		delete inp;
	}
}


//------------------------------------------------------------------------------
TEST_F(OCSRandomSourceTest, sync) {
	OCSRandomSource * r1;
	OCSRandomSource * r2;
	int i;
	int j;
	int retval;

	for (i = 0; i < 1000; i++) {
		r1 = NULL;
		retval = OCSRandomSource_New(&r1, i);
		r2 = NULL;
		retval = OCSRandomSource_New(&r2, i);

		for (j = 0; j < 1000; j++) {
			ASSERT_EQ(r1->next(r1), r2->next(r2));
		}

		OCSObjectDelete((OCSObject*)r1);
		OCSObjectDelete((OCSObject*)r2);
	}

}
//------------------------------------------------------------------------------

