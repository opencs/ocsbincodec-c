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
#ifndef OCSCODEC_H_
#define OCSCODEC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <ocsobj.h>

/**
 * @defgroup ClassOCSCodec Class OCSCodec
 *
 * <p><b>@ref ClassOCSObject &gt;
 * @ref ClassOCSCodec</b></p>
 *
 * This class implements the base class for all codecs.
 */
/**
 * @addtogroup ClassOCSCodec
 * @{
 */
/**
 * Type of the class OCSCodec.
 */
typedef struct OCSCodec OCSCodec;

/**
 * Structure of class OCSCodec.
 */
struct OCSCodec {
	/**
	 * Base class.
	 */
	OCSObject base;
	/**
	 * Returns the expected size of the encoded data based on the size of the
	 * decoded data.
	 *
     * @param[in] myself The pointer to myself.
     * @param[in] decSize The size of the decoded data in bytes.
     * @return The number of characters required to encode the data.
	 *
	 */
	int (*getEncodedSize)(const OCSCodec * myself, int decSize);
	/**
	 * Returns the expected size of the decoded data based on the size of the
	 * encoded data.
	 *
     * @param[in] myself The pointer to myself.
     * @param[in] encSize The size of the encoded data in characters.
     * @return The number of bytes required to hold the decoded data. This size
     * is guaranteed to be larger or equal to the actual decoded size.
	 */
	int (*getDecodedSize)(const OCSCodec * myself, int encSize);

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
	int (*encode)(const OCSCodec * myself, const void * src, int srcSize,
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
	int (*decode)(const OCSCodec * myself, const char * src, int srcSize,
			void * dst, int * dstSize);
};

/**
 * Initializes a new instance of OCSCodec.
 *
 * @param[out] myself The pointer to myself.
 * @return OCSERR_SUCCESS for success or other error code in case of failure.
 * @note This method is called only by @ref OCSCodec_New() and
 * direct subclasses of
 */
int OCSCodec_init(OCSCodec * myself);

/**
 * Disposes this instance and releases all allocated resources. This method is
 * called only by OCSObjectDelete() or subclasses of this class.
 *
 * @param[out] myself A pointer to myself.
 */
void OCSCodec_dispose(OCSObject * myself);

/** @} */

#ifdef __cplusplus
} // extern "C"
#endif


#endif /* OCSCODEC_H_ */
