/*
 * Copyright (c) 2015, Open Communications Security
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
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
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#include <ocsralph.h>
#include <string.h>

//------------------------------------------------------------------------------
int RandomAlphabetGenerator_generateRandom(uint32_t seed, int rounds,
		const char * candidates, int candidatesSize,
		char * alphabet, int alphabetSize) {
	char * tmp;
	int retval;

	// Check the parameters
	if ((candidatesSize <= 0) || (alphabetSize <= 0) ||
			(candidatesSize < alphabetSize))  {
		return OCSERR_INVALID_ARGUMENT;
	}

	if (rounds <= 0) {
		// Trivial case because rounds is zero
		memcpy(alphabet, candidates, sizeof(char) * alphabetSize);
		retval = OCSERR_SUCCESS;
	} else {
		// Let's shuffle
		tmp = malloc(sizeof(char) * candidatesSize);
		memcpy(tmp, candidates, sizeof(char) * candidatesSize);
		retval = RandomAlphabetGenerator_shuffle(seed, rounds,
				tmp, candidatesSize);
		if (retval == OCSERR_SUCCESS) {
			memcpy(alphabet, tmp, sizeof(char) * alphabetSize);
		}

		// Cleanup
		free(tmp);
	}

	return retval;
}

//------------------------------------------------------------------------------
int RandomAlphabetGenerator_shuffle(uint32_t seed, int rounds,
		char * alphabet, int alphabetSize) {
	int retval;
	int round;
	int pos;
	OCSRandomSource * random;

	// Check the arguments
	if ((rounds <= 0) || (alphabetSize <= 0)) {
		return OCSERR_SUCCESS;
	}

	// Create the random source
	random = NULL;
	retval = OCSRandomSource_New(&random, seed);
	if (retval != OCSERR_SUCCESS) {
		return retval;
	}

	// Process
	for (round = 0; round < rounds; round++) {
		for (pos = 0; pos < alphabetSize; pos++) {
			// Select a random position and swap pos with it
			int newPos = random->next(random) % alphabetSize;
			char tmp = alphabet[pos];
			alphabet[pos] = alphabet[newPos];
			alphabet[newPos] = tmp;
		}
	}

	// Cleanup
	OCSObjectDelete((OCSObject*)random);
	return retval;
}
//------------------------------------------------------------------------------
