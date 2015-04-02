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
#ifndef OCSB2NCO_H_
#define OCSB2NCO_H_


#ifdef __cplusplus
extern "C" {
#endif

#include <ocscodec.h>
#include <ocsalpha.h>
#include <stdbool.h>

/**
 * @defgroup ClassOCSBase2NCodec Class OCSBase2NCodec
 *
 * <p><b>@ref ClassOCSObject &gt;
 * @ref ClassOCSCodec &gt;
 * @ref ClassOCSBase2NCodec</b></p>
 *
 * This class implements the Base2N codec. The Base2N codec can use any alphabet
 * with 2, 4, 8, 16, 32, 64 or 128 characters to encode data.
 */
/**
 * @addtogroup ClassOCSBase2NCodec
 * @{
 */
/**
 * Type of the class OCSBase2NCodec.
 */
typedef struct OCSBase2NCodec OCSBase2NCodec;

/**
 * Structure of class OCSBase2NCodec.
 */
struct OCSBase2NCodec {
	/**
	 * Base class.
	 */
	OCSCodec base;
	/**
	 * The alphabet.
	 */
	OCSAlphabet * alphabet;
	/**
	 * The padding character.
	 */
	int paddingChar;
	/**
	 * The padding block size.
	 */
	int paddingBlockSize;
	/**
	 * The list of ignores if any.
	 */
	char * ignores;
	/**
	 * Size of the character in bits.
	 */
	int size;
	/**
	 * Clear mask.
	 */
	int clearMask;
	/**
	 * Verifies it this instance uses padding.
	 *
     * @param[in] myself The pointer to myself.
     * @return true if the padding is enabled or false otherwise.
	 */
	bool (*usePadding)(const OCSBase2NCodec * myself);
	/**
	 * Verifies if the given character is a padding character or not.
	 *
     * @param[in] myself The pointer to myself.
     * @param[in] c The character to be tested.
     * @return true if the padding is enabled or false otherwise.
	 */
	bool (*isPadding)(const OCSBase2NCodec * myself, int c);
	/**
	 * Verifies if the given character is ignored or not.
	 *
     * @param[in] myself The pointer to myself.
     * @param[in] c The character to be tested.
     * @return true if the character should be ignored or false otherwise.
	 */
	bool (*isIgnored)(const OCSBase2NCodec * myself, int c);
};

/**
 * List of blank characters.
 */
#define OCSBase2NCodec_SPACES " \n\r\f\v\t"

/**
 * Creates a new instance of OCSBase2NCodec.
 *
 * @param[out] myself The pointer to the pointer to myself.
 * @param[in] alphabet The alphabet to be used. It must have the sizes 2, 4, 8,
 * 16, 32, 64 or 128. The alphabet instance will be disposed by the destructor
 * of this class.
 * @param[in] paddingChar The padding character.
 * @param[in] paddingBlock The size of the padding block. If this value is
 * smaller than 2, the padding will not be used.
 * @param[in] ignores A null terminated string with the characters to be
 * ignored. Set to null if no character will be ignored.
 * @return OCSERR_SUCCESS for success or other error code in case of failure.
 * @warning In case of error, the instance of alphabet will not be disposed.
 */
int OCSBase2NCodec_New(OCSBase2NCodec ** myself, OCSAlphabet * alphabet,
		int paddingChar, int paddingBlock,
		const char * ignores);

/**
 * Initializes a new instance of OCSBase2NCodec.
 *
 * @param[out] myself The pointer to myself.
 * @param[in] alphabet The alphabet to be used. It must have the sizes 2, 4, 8,
 * 16, 32, 64 or 128. The alphabet instance will be disposed by the destructor
 * of this class.
 * @param[in] paddingChar The padding character.
 * @param[in] paddingBlock The size of the padding block. If this value is
 * smaller than 2, the padding will not be used.
 * @param[in] ignores A null terminated string with the characters to be
 * ignored. Set to null if no character will be ignored.
 * @return OCSERR_SUCCESS for success or other error code in case of failure.
 * @note This method is called only by @ref OCSBase2NCodec_New() and
 * direct subclasses of
 * @warning In case of error, the instance of alphabet will not be disposed.
 */
int OCSBase2NCodec_init(OCSBase2NCodec * myself, OCSAlphabet * alphabet,
		int paddingChar, int paddingBlock,
		const char * ignores);

/**
 * Returns the expected size of the encoded data based on the size of the
 * decoded data.
 *
 * @param[in] myself The pointer to myself.
 * @param[in] decSize The size of the decoded data in bytes.
 * @return The number of characters required to encode the data.
 *
 */
int OCSBase2NCodec_getEncodedSize(const OCSCodec * myself, int decSize);

/**
 * Returns the expected size of the decoded data based on the size of the
 * encoded data.
 *
 * @param[in] myself The pointer to myself.
 * @param[in] encSize The size of the encoded data in characters.
 * @return The number of bytes required to hold the decoded data. This size
 * is guaranteed to be larger or equal to the actual decoded size.
 */
int OCSBase2NCodec_getDecodedSize(const OCSCodec * myself, int encSize);

/**
 * Encodes the data.
 *
 * @param[in] myself The pointer to myself.
 * @param[in] src The source data.
 * @param[in] srcSize The size of the source data in bytes.
 * @param[out] dst Destination buffer.
 * @param[in,out] dstSize On input, the actual size of the of dst in
 * characters, on output, the size of the encoded data.
 * @return OCSERR_SUCCESS on success or other error code in case of failure.
 * @warning This method doesn't add the null terminator to the output.
 */
int OCSBase2NCodec_encode(const OCSCodec * myself,
		const void * src, int srcSize,
		char * dst, int * dstSize);

/**
 * Decodes the data.
 *
 * @param[in] myself The pointer to myself.
 * @param[in] src The source data.
 * @param[in] srcSize The size of the source data in bytes.
 * @param[out] dst Destination buffer.
 * @param[in,out] dstSize On input, the actual size of the of dst in
 * characters, on output, the size of the encoded data.
 * @return OCSERR_SUCCESS on success or other error code in case of failure.
 * @warning This method doesn't add the null terminator to the output.
 */
int OCSBase2NCodec_decode(const OCSCodec * myself,
		const char * src, int srcSize,
		void * dst, int * dstSize);


/**
 * Verifies it this instance uses padding.
 *
 * @param[in] myself The pointer to myself.
 * @return true if the padding is enabled or false otherwise.
 */
bool OCSBase2NCodec_usePadding(const OCSBase2NCodec * myself);
/**
 * Verifies if the given character is a padding character or not.
 *
 * @param[in] myself The pointer to myself.
 * @param[in] c The character to be tested.
 * @return true if the padding is enabled or false otherwise.
 */
bool OCSBase2NCodec_isPadding(const OCSBase2NCodec * myself, int c);
/**
 * Verifies if the given character is ignored or not.
 *
 * @param[in] myself The pointer to myself.
 * @param[in] c The character to be tested.
 * @return true if the character should be ignored or false otherwise.
 */
bool OCSBase2NCodec_isIgnored(const OCSBase2NCodec * myself, int c);

/**
 * Disposes this instance and releases all allocated resources. This method is
 * called only by OCSObjectDelete() or subclasses of this class.
 *
 * @param[out] myself A pointer to myself.
 */
void OCSBase2NCodec_dispose(OCSObject * myself);

/** @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* OCSB2NCO_H_ */
