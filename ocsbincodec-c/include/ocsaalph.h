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
#ifndef OCSAALPH_H_
#define OCSAALPH_H_

#include <ocsalpha.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup ClassOCSArrayAlphabet Class OCSArrayAlphabet
 * <p><b>@ref ClassOCSObject
 * &gt; @ref ClassOCSAlphabet
 * &gt; @ref ClassOCSArrayAlphabet</b></p>
 *
 * This class implements an alphabet that uses a char array as the character
 * mapping.
 */
/**
 * @addtogroup ClassOCSArrayAlphabet
 * @{
 */

/**
 * Maximum size of the alphabet.
 */
#define OCSArrayAlphabet_MAX_SIZE 256

/**
 * Type of the class OCSArrayAlphabet.
 */
typedef struct OCSArrayAlphabet OCSArrayAlphabet;

/**
 * Structure of the class OCSArrayAlphabet.
 */
struct OCSArrayAlphabet {
	/**
	 * The base class.
	 */
	OCSAlphabet base;
	/**
	 * The alphabet.
	 */
	const char * alphabet;
	/**
	 * My copy of the alphabet.
	 */
	char * myAlphabet;
};

/**
 * Creates a new instance of OCSArrayAlphabet.
 *
 * @param[out] myself The pointer to the pointer to myself.
 * @param[in] chars The characters of the alphabet.
 * @param[in] charsSize The size of chars in characters.
 * @param[in] caseInsensitive Sets the behavior of getValue(). If false,
 * getValue() is case sensitive, otherwise, getValue() is case insensitive.
 * @return OCSERR_SUCCESS for success or other error code in case of failure.
 */
int OCSArrayAlphabet_New(OCSArrayAlphabet ** myself, const char * chars,
		int charsSize, bool caseInsensitive);

/**
 * Creates a new instance of OCSArrayAlphabet.
 *
 * @param[out] myself The pointer to the pointer to myself.
 * @param[in] chars The characters of the alphabet.
 * @param[in] charsSize The size of chars in characters.
 * @param[in] caseInsensitive Sets the behavior of getValue(). If false,
 * getValue() is case sensitive, otherwise, getValue() is case insensitive.
 * @param[in] noCopy If false, the chars array is copied to a new buffer,
 * otherwise the chars array is used directly.
 * @return OCSERR_SUCCESS for success or other error code in case of failure.
 */
int OCSArrayAlphabet_NewEx(OCSArrayAlphabet ** myself, const char * chars,
		int charsSize, bool caseInsensitive, bool noCopy);

/**
 * Initializes a new instance of OCSArrayAlphabet.
 *
 * @param[out] myself The pointer to myself.
 * @param[in] chars The characters of the alphabet.
 * @param[in] charsSize The size of chars in characters.
 * @param[in] caseInsensitive Sets the behavior of getValue(). If false,
 * getValue() is case sensitive, otherwise, getValue() is case insensitive.
 * @param[in] noCopy If false, the chars array is copied to a new buffer,
 * otherwise the chars array is used directly.
 * @return OCSERR_SUCCESS for success or other error code in case of failure.
 * @note This method is called only by @ref OCSArrayAlphabet_New() and
 * direct subclasses of it.
 */
int OCSArrayAlphabet_init(OCSArrayAlphabet * myself, const char * chars,
		int charsSize, bool caseInsensitive, bool noCopy);


/**
 * Returns the value of a given character.
 *
 * @param[in] myself A pointer to myself.
 * @param[in] v The value. It must be a value between 0 and getSize() - 1.
 * @return The character.
 */
int OCSArrayAlphabet_getCharacter(const OCSAlphabet * myself, int v);

/**
 * Returns the value of a given character.
 *
 * @param[in] myself A pointer to myself.
 * @param[in] c The character to be tested.
 * @return The value of the character or -1 if the character is not in the
 * alphabet.
 */
int OCSArrayAlphabet_getValue(const OCSAlphabet * myself, int c);

/**
 * Returns the value of a given character. This is the case insensitive version
 * of OCSArrayAlphabet_getValue().
 *
 * @param[in] myself A pointer to myself.
 * @param[in] c The character to be tested.
 * @return The value of the character or -1 if the character is not in the
 * alphabet.
 */
int OCSArrayAlphabet_getValueCI(const OCSAlphabet * myself, int c);

/**
 * Disposes this instance and releases all allocated resources. This method is
 * called only by OCSObjectDelete() or subclasses of this class.
 *
 * @param[out] myself A pointer to myself.
 */
void OCSArrayAlphabet_dispose(OCSObject * myself);

/** @} */

#ifdef __cplusplus
} // extern "C"
#endif


#endif /* OCSAALPH_H_ */
