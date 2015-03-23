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
 #include <ocsobj.h>

//------------------------------------------------------------------------------
int OCSObject_New(OCSObject ** myself, size_t size,
		OCSObject_dispose_t dispose) {

	// Check arguments
	if (dispose == NULL) {
		return OCSERR_INVALID_ARGUMENT;
	}
	if (myself == NULL) {
		return OCSERR_INVALID_ARGUMENT;
	}
	if (size < sizeof(OCSObject)) {
		return OCSERR_INVALID_ARGUMENT;
	}

	if ((*myself) != NULL) {
		// Already allocated, just check the size.
		if ((*myself)->size < size) {
			return OCSERR_BUFFER_TOO_SMALL;
		} else {
			return OCSERR_SUCCESS;
		}
	} else {
		// Not allocated. Create a new one
		(*myself) = calloc(size, 1);
		(*myself)->size = size;
		(*myself)->dispose = dispose;
		return OCSERR_SUCCESS;
	}
}

//------------------------------------------------------------------------------
void OCSObject_Dispose(OCSObject * myself) {
}

//------------------------------------------------------------------------------
void OCSObjectDelete(OCSObject * obj) {

	if (obj) {
		obj->dispose(obj);
		free(obj);
	}
}
