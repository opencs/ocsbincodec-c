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
#ifndef OCSHALPH_H_
#define OCSHALPH_H_

#include <ocsaalph.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup ClassOCSHexadecimalAlphabet Class OCSHexadecimalAlphabet
 * <p><b>@ref ClassOCSObject
 * &gt; @ref ClassOCSAlphabet
 * &gt; @ref ClassOCSArrayAlphabet</b>
 * &gt; @ref ClassOCSHexadecimalAlphabet</b></p>
 *
 * This class implements the hexadecimal alphabet.
 */
/**
 * @addtogroup ClassOCSHexadecimalAlphabet
 * @{
 */

/**
 * Type of the class OCSHexadecimalAlphabet.
 */
typedef struct OCSHexadecimalAlphabet OCSHexadecimalAlphabet;

/**
 * Structure of the class OCSHexadecimalAlphabet.
 */
struct OCSHexadecimalAlphabet {
	/**
	 * The base class.
	 */
	OCSArrayAlphabet base;
};

/**
 * Creates a new instance of OCSHexadecimalAlphabet.
 *
 * @param[out] myself The pointer to the pointer to myself.
 * @param[in] lc If 0, uses upper case characters otherwise uses
 * lower case characters.
 * @return OCSERR_SUCCESS for success or other error code in case of failure.
 */
int OCSHexadecimalAlphabet_New(OCSHexadecimalAlphabet ** myself, bool lc);

/**
 * Initializes a new instance of OCSHexadecimalAlphabet.
 *
 * @param[out] myself The pointer to myself.
 * @param[in] lc If 0, uses upper case characters otherwise uses
 * lower case characters.
 * @return OCSERR_SUCCESS for success or other error code in case of failure.
 * @note This method is called only by @ref OCSHexadecimalAlphabet_New() and
 * direct subclasses of it.
 */
int OCSHexadecimalAlphabet_init(OCSHexadecimalAlphabet * myself, bool lc);

/**
 * Returns the value of a given character.
 *
 * @param[in] myself A pointer to myself.
 * @param[in] c The character to be tested.
 * @return The value of the character or -1 if the character is not in the
 * alphabet.
 */
int OCSHexadecimalAlphabet_getValue(const OCSAlphabet * myself, int c);

/**
 * Disposes this instance and releases all allocated resources. This method is
 * called only by OCSObjectDelete() or subclasses of this class.
 *
 * @param[out] myself A pointer to myself.
 */
void OCSHexadecimalAlphabet_dispose(OCSObject * myself);

/** @} */

#ifdef __cplusplus
} // extern "C"
#endif




#endif /* OCSHALPH_H_ */
