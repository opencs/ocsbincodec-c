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
#include "RandomAlphabetGeneratorTest.h"
#include <ocsralph.h>

//==============================================================================
// class RandomAlphabetGeneratorTest
//------------------------------------------------------------------------------
RandomAlphabetGeneratorTest::RandomAlphabetGeneratorTest() {
}

//------------------------------------------------------------------------------
RandomAlphabetGeneratorTest::~RandomAlphabetGeneratorTest() {
}

//------------------------------------------------------------------------------
void RandomAlphabetGeneratorTest::SetUp() {
}

//------------------------------------------------------------------------------
void RandomAlphabetGeneratorTest::TearDown() {
}

//------------------------------------------------------------------------------
#define RandomAlphabetGeneratorTest_CHARS "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

#define RandomAlphabetGeneratorTest_CHARS_SIZE 26

// Shuffle of CHARS with seed as 12345 and 100 rounds
#define RandomAlphabetGeneratorTest_SHUFFLE_STANDARD "MBYXGZEJKRSNOLCFQTUDIHAVWP"

//------------------------------------------------------------------------------
TEST_F(RandomAlphabetGeneratorTest, GenerateRandom) {
	char src[RandomAlphabetGeneratorTest_CHARS_SIZE + 1];
	char dst[RandomAlphabetGeneratorTest_CHARS_SIZE + 1];
	int retval;
	int size;
	int i;

	// Ensure that src remain unchanged
	memcpy(src, RandomAlphabetGeneratorTest_CHARS, sizeof(char) * RandomAlphabetGeneratorTest_CHARS_SIZE);
	retval = RandomAlphabetGenerator_generateRandom(1234, 100,
				src, RandomAlphabetGeneratorTest_CHARS_SIZE,
				dst, RandomAlphabetGeneratorTest_CHARS_SIZE);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	src[RandomAlphabetGeneratorTest_CHARS_SIZE] = 0;
	ASSERT_STREQ(RandomAlphabetGeneratorTest_CHARS, src);

	// Ensure that all characters in dst are indeed part of src
	for (size = 1; size <= RandomAlphabetGeneratorTest_CHARS_SIZE; size++) {
		memcpy(src, RandomAlphabetGeneratorTest_CHARS, sizeof(char) * RandomAlphabetGeneratorTest_CHARS_SIZE);
		retval = RandomAlphabetGenerator_generateRandom(size, 100,
					src, RandomAlphabetGeneratorTest_CHARS_SIZE,
					dst, size);
		ASSERT_EQ(OCSERR_SUCCESS, retval);
		for (i = 0; i < size; i++) {
			ASSERT_TRUE(strchr(src, dst[i]) != NULL);
		}
	}

}

//------------------------------------------------------------------------------
TEST_F(RandomAlphabetGeneratorTest, Shuffle) {
	char out[RandomAlphabetGeneratorTest_CHARS_SIZE + 1];
	char out2[RandomAlphabetGeneratorTest_CHARS_SIZE + 1];
	int retval;
	int i;
	int count;

	// All parameters remain the same
	memcpy(out, RandomAlphabetGeneratorTest_CHARS, sizeof(char) * RandomAlphabetGeneratorTest_CHARS_SIZE);
	retval = RandomAlphabetGenerator_shuffle(0, 0, out, RandomAlphabetGeneratorTest_CHARS_SIZE);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	out[RandomAlphabetGeneratorTest_CHARS_SIZE] = 0;
	ASSERT_STREQ(RandomAlphabetGeneratorTest_CHARS, out);

	// Four rounds
	memcpy(out, RandomAlphabetGeneratorTest_CHARS, sizeof(char) * RandomAlphabetGeneratorTest_CHARS_SIZE);
	retval = RandomAlphabetGenerator_shuffle(0, 4, out, RandomAlphabetGeneratorTest_CHARS_SIZE);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	out[RandomAlphabetGeneratorTest_CHARS_SIZE] = 0;
	count = 0;
	for (i = 0; i < RandomAlphabetGeneratorTest_CHARS_SIZE; i++) {
		if (out[i] != RandomAlphabetGeneratorTest_CHARS[i]) {
			count++;
		}
	}
	ASSERT_TRUE(count > (RandomAlphabetGeneratorTest_CHARS_SIZE / 3));

	// Same result for the same input
	memcpy(out, RandomAlphabetGeneratorTest_CHARS, sizeof(char) * RandomAlphabetGeneratorTest_CHARS_SIZE);
	memcpy(out2, RandomAlphabetGeneratorTest_CHARS, sizeof(char) * RandomAlphabetGeneratorTest_CHARS_SIZE);
	retval = RandomAlphabetGenerator_shuffle(123, 4, out, RandomAlphabetGeneratorTest_CHARS_SIZE);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	retval = RandomAlphabetGenerator_shuffle(123, 4, out2, RandomAlphabetGeneratorTest_CHARS_SIZE);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	out[RandomAlphabetGeneratorTest_CHARS_SIZE] = 0;
	out2[RandomAlphabetGeneratorTest_CHARS_SIZE] = 0;
	ASSERT_STREQ(out, out2);
}

//------------------------------------------------------------------------------
TEST_F(RandomAlphabetGeneratorTest, ShuffleStandard) {
	int retval;
	char out[RandomAlphabetGeneratorTest_CHARS_SIZE + 1];

	// No change
	retval = RandomAlphabetGenerator_generateRandom(0, 0,
			RandomAlphabetGeneratorTest_CHARS, RandomAlphabetGeneratorTest_CHARS_SIZE,
			out, RandomAlphabetGeneratorTest_CHARS_SIZE);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	out[RandomAlphabetGeneratorTest_CHARS_SIZE] = 0;
	ASSERT_STREQ(RandomAlphabetGeneratorTest_CHARS, out);

	retval = RandomAlphabetGenerator_generateRandom(12345, 100,
			RandomAlphabetGeneratorTest_CHARS, RandomAlphabetGeneratorTest_CHARS_SIZE,
			out, RandomAlphabetGeneratorTest_CHARS_SIZE);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	out[RandomAlphabetGeneratorTest_CHARS_SIZE] = 0;
	ASSERT_STREQ(RandomAlphabetGeneratorTest_SHUFFLE_STANDARD, out);
}
//------------------------------------------------------------------------------

