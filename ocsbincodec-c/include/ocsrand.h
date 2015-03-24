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
#ifndef OCSRAND_H_
#define OCSRAND_H_

#include <ocsobj.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup OCSRandomSource
 * @{
 */

/**
 * This class implements a simple random source.
 *
 * <p>Internally, this implementation uses a linear congruential generator with
 * the same parameters used by the glibc.</p>
 *
 * <p>This implementation is not thread safe.</p>
 */
typedef struct OCSRandomSource OCSRandomSource;

/**
 * Data structure for the class OCSRandomSource.
 *
 */
struct OCSRandomSource {
	/**
	 * Base class.
	 */
	OCSObject base;

	/**
	 * The inner state.
	 */
	uint32_t _state;

	/**
	 * Returns the next random integer.
	 *
	 * @param[in] myself A pointer to myself.
	 * @return The next 31 bit integer.
	 */
	int (*next)(OCSRandomSource * myself);
};

/**
 * Creates a new instance of OCSRandomSource.
 *
 * @param[out] myself A pointer to the pointer of myself.
 * @param[in] seed The 31-bit seed.
 */
int OCSRandomSource_New(OCSRandomSource ** myself, uint32_t seed);

/**
 * The initialization method for the class OCSRandomSource.
 *
 * @param[in,out] myself A pointer to myself.
 * @param[in] seed The 31-bit seed.
 */
int OCSRandomSource_init(OCSRandomSource * myself, uint32_t seed);

/**
 * Disposes this instance and releases all allocated resources. This method is
 * called only by OCSObjectDelete() or subclasses of this class.
 *
 * <p>This implementation does nothing.</p>
 *
 * @param[out] myself A pointer to myself.
 */
void OCSRandomSource_dispose(OCSObject * myself);

/** @} */

#ifdef __cplusplus
} // extern "C"
#endif


#endif /* OCSRAND_H_ */
