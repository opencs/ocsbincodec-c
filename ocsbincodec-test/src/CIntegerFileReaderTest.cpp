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
#include "CIntegerFileReaderTest.h"
#include "CIntegerFileReader.h"

//==============================================================================
// class CIntegerFileReaderTest
//------------------------------------------------------------------------------
CIntegerFileReaderTest::CIntegerFileReaderTest() {

}

//------------------------------------------------------------------------------
CIntegerFileReaderTest::~CIntegerFileReaderTest() {
}

//------------------------------------------------------------------------------
void CIntegerFileReaderTest::SetUp() {
}

//------------------------------------------------------------------------------
void CIntegerFileReaderTest::TearDown() {
}

//------------------------------------------------------------------------------
#define SAMPLE_FILES_SIZE 5
const static char * SAMPLE_FILES[SAMPLE_FILES_SIZE] = {
#ifndef _WIN32
		"data/IntegerFileReaderTest1.txt",
		"data/IntegerFileReaderTest2.txt",
		"data/IntegerFileReaderTest3.txt",
		"data/IntegerFileReaderTest4.txt",
		"data/IntegerFileReaderTest5.txt"
#else
		"data\\IntegerFileReaderTest1.txt",
		"data\\IntegerFileReaderTest2.txt",
		"data\\IntegerFileReaderTest3.txt",
		"data\\IntegerFileReaderTest4.txt",
		"data\\IntegerFileReaderTest5.txt"
#endif
};

//------------------------------------------------------------------------------
TEST_F(CIntegerFileReaderTest, Constructor) {
	CIntegerFileReader * r;

	r = new CIntegerFileReader(SAMPLE_FILES[0]);
	ASSERT_TRUE(r->isOpen());
	delete r;
}

//------------------------------------------------------------------------------
TEST_F(CIntegerFileReaderTest, Close) {
	CIntegerFileReader * r;

	r = new CIntegerFileReader(SAMPLE_FILES[0]);
	ASSERT_TRUE(r->isOpen());
	r->close();
	ASSERT_FALSE(r->isOpen());
	delete r;
}

//------------------------------------------------------------------------------
TEST_F(CIntegerFileReaderTest, nextInt) {
	CIntegerFileReader * r;
	int i;
	int j;
	int v;

	for (i = 0; i < 4; i++) {
		r = new CIntegerFileReader(SAMPLE_FILES[0]);
		ASSERT_TRUE(r->isOpen());
		for (j = 0; j < 10; j++) {
			ASSERT_TRUE(r->nextInt(v));
			ASSERT_EQ(j, v);
		}
		ASSERT_FALSE(r->nextInt(v));
		delete r;
	}
}

//------------------------------------------------------------------------------
TEST_F(CIntegerFileReaderTest, nextIntBroken) {
	CIntegerFileReader * r;
	int i;
	int j;
	int v;

	for (i = 0; i < 4; i++) {
		r = new CIntegerFileReader(SAMPLE_FILES[4]);
		ASSERT_TRUE(r->isOpen());
		for (j = 0; j < 7; j++) {
			ASSERT_TRUE(r->nextInt(v));
			ASSERT_EQ(j, v);
		}
		ASSERT_FALSE(r->nextInt(v));
		delete r;
	}
}
//------------------------------------------------------------------------------

