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
#ifndef OCSOBJ_H_
#define OCSOBJ_H_

#include <stdlib.h>
#include <ocserr.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup ClassOCSObject Class OCSObject
 *
 * <p><b>@ref ClassOCSObject</b></p>
 *
 * This class is the base class for all classes in this library.
 */

/**
 * @addtogroup ClassOCSObject
 * @{
 */

/**
 * Type of the class OCSObject.
 */
typedef struct OCSObject OCSObject;

/**
 * This is the type used by all dispose methods. It must clear all allocated
 * resources and call the dispose method of parent classes.
 *
 * @param[in] myself Myself.
 */
typedef void (*OCSObject_dispose_t)(OCSObject * myself);

/**
 * Internal structure of class OCSObject.
 */
struct OCSObject {
	/**
	 * Size of this structure in bytes.
	 */
	size_t _size;

	/**
	 * Pointer to the dispose method.
	 */
	OCSObject_dispose_t dispose;
};

/**
 * Allocates and initializes a instance of OCSObject.
 *
 * @param[out] myself A pointer to the pointer of myself.
 * @param[in] size The size of this structure.
 * @param[in] The dispose function. If NULL, assumes the default implementation
 * that does nothing.
 * @return OCSERR_SUCCESS for success or other error code in case of failure.
 * @note In case of failure, myself will point to nothing.
 */
int OCSObject_New(OCSObject ** myself, size_t size,
		OCSObject_dispose_t dispose);

/**
 * Disposes this instance and releases all allocated resources. This method is
 * called only by OCSObjectDelete() or subclasses of this class.
 *
 * <p>This implementation does nothing.</p>
 *
 * @param[out] myself A pointer to myself.
 */
void OCSObject_dispose(OCSObject * myself);

/**
 * Disposes instances of OCSObject.
 *
 * @param[in] obj The object to be disposed.
 */
void OCSObjectDelete(OCSObject * obj);

/** @} */

#ifdef __cplusplus
} //extern "C"
#endif

#endif /* OCSOBJ_H_ */
