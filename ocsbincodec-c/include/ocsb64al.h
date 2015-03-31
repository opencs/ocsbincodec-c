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
#ifndef OCSB64AL_H_
#define OCSB64AL_H_

#include <ocsaalph.h>

#ifdef __cplusplus
extern "C" {
#endif



/**
 * @defgroup ClassOCSBase64Alphabet Class OCSBase64Alphabet
 * <p><b>@ref ClassOCSObject
 * &gt; @ref ClassOCSAlphabet
 * &gt; @ref ClassOCSArrayAlphabet</b>
 * &gt; @ref ClassOCSBase64Alphabet</b></p>
 *
 * This class implements the Base32 alphabet.
 */
/**
 * @addtogroup ClassOCSBase64Alphabet
 * @{
 */

/**
 * Type of the class OCSBase64Alphabet.
 */
typedef struct OCSBase64Alphabet OCSBase64Alphabet;

/**
 * Structure of the class OCSBase64Alphabet.
 */
struct OCSBase64Alphabet {
	/**
	 * The base class.
	 */
	OCSArrayAlphabet base;
	int c62;
	int c63;
};

/**
 * Creates a new instance of OCSBase64Alphabet.
 *
 * @param[out] myself The pointer to the pointer to myself.
 * @param[in] safe If true, uses the Base 64 safe alphabet, otherwise uses the
 * standard alphabet.
 * @return OCSERR_SUCCESS for success or other error code in case of failure.
 */
int OCSBase64Alphabet_New(OCSBase64Alphabet ** myself, bool safe);

/**
 * Initializes a new instance of OCSBase64Alphabet.
 *
 * @param[out] myself The pointer to myself.
 * @param[in] safe If true, uses the Base 64 safe alphabet, otherwise uses the
 * standard alphabet.
 * @return OCSERR_SUCCESS for success or other error code in case of failure.
 * @note This method is called only by @ref OCSBase64Alphabet_New() and
 * direct subclasses of it.
 */
int OCSBase64Alphabet_init(OCSBase64Alphabet * myself, bool safe);

/**
 * Returns the value of a given character.
 *
 * @param[in] myself A pointer to myself.
 * @param[in] c The character to be tested.
 * @return The value of the character or -1 if the character is not in the
 * alphabet.
 */
int OCSBase64Alphabet_getValue(const OCSAlphabet * myself, int c);

/**
 * Disposes this instance and releases all allocated resources. This method is
 * called only by OCSObjectDelete() or subclasses of this class.
 *
 * @param[out] myself A pointer to myself.
 */
void OCSBase64Alphabet_dispose(OCSObject * myself);

/** @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* OCSB64AL_H_ */
