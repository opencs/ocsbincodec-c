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
#ifndef OCSCODEC_OCSALPHA_H_
#define OCSCODEC_OCSALPHA_H_

#include <stdint.h>
#include <ocsobj.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OCSAlphabet OCSAlphabet;

/**
 * This is the data structure that represents the abstract class OCSObject.
 */
struct OCSAlphabet {
	/**
	 * The superclass.
	 */
	OCSObject super;

	/**
	 * The size of the alphabet.
	 */
	int _size;

	/**
	 * Returns the size of the alphabet.
	 *
	 * @param[in] myself A pointer to myself.
	 * @return The size of the alphabet in characters.
	 */
	int (*getSize)(const OCSAlphabet * myself);

	/**
	 * Returns the value of a given character.
	 *
	 * @param[in] myself A pointer to myself.
	 * @param[in] v The value. It must be a value between 0 and getSize() - 1.
	 * @return The character.
	 */
	int (*getCharacter)(const OCSAlphabet * myself, int v);

	/**
	 * Returns the value of a given character.
	 *
	 * @param[in] myself A pointer to myself.
	 * @param[in] c The character to be tested.
	 * @return The value of the character or -1 if the character is not in the
	 * alphabet.
	 */
	int (*getValue)(const OCSAlphabet * myself, int c);
};

/**
 * Initializes an OCSAlphabet instance.
 *
 * @param[in] myself A pointer to myself.
 * @param[in] size The size of the alphabet.
 */
int OCSAlphabet_init(OCSAlphabet * myself, int size);

#ifdef __cplusplus
} //extern "C"
#endif

#endif /* OCSCODEC_OCSALPHA_H_ */
