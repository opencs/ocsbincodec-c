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
#ifndef OCSRALPH_H_
#define OCSRALPH_H_

#include <ocsrand.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Generates a random alphabet.
 *
 * <p>This algorithm is designed to guarantee that a given input will
 * always generate the same result.</p>
 *
 * @param[in] seed A 32 bit random seed.
 * @param[in] rounds The number of rounds. To achieve better results, this
 * value must be at least 4.
 * @param[in] candidates The list of candidates.
 * @param[in] candidatesSize The number of elements in candidates.
 * @param[out] alphabet The resulting alphabet.
 * @param[in] The size of the resulting alphabet.
 * @return OCSERR_SUCCESS for success or other error code in case of failure.
 */
int RandomAlphabetGenerator_generateRandom(uint32_t seed, int rounds,
		const char * candidates, int candidatesSize,
		char * alphabet, int alphabetSize);

/**
 * Shuffles the characters in the array using a pseudo random sequence.
 *
 * <p>This algorithm is designed to guarantee that a given input will
 * always generate the same result.</p>
 *
 * @param[in] seed A 32 bit random seed.
 * @param[in] rounds The number of rounds. To achieve better results, this
 * value must be at least 4.
 * @param[in,out] alphabet The array to be shuffled.
 * @param[in] alphabetSize The number of elements in alphabet.
 * @return OCSERR_SUCCESS for success or other error code in case of failure.
 */
int RandomAlphabetGenerator_shuffle(uint32_t seed, int rounds,
		char * alphabet, int alphabetSize);

#ifdef __cplusplus
} //extern "C"
#endif

#endif /* OCSRALPH_H_ */
