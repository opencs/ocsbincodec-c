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
#include <ocsrand.h>

/**
 * The module m.
 */
#define OCSRandomSource_M 0x7FFFFFFF

/**
 * The multiplier a.
 */
#define OCSRandomSource_A 1103515245

/**
 * The constant c.
 */
#define OCSRandomSource_C 12345

//------------------------------------------------------------------------------
void OCSRandomSource_dispose(OCSObject * myself) {
	OCSObject_dispose(myself);
}

//------------------------------------------------------------------------------
int OCSRandomSource_next(OCSRandomSource * myself) {
	uint64_t tmp;

	tmp = myself->_state;
	tmp = ((tmp * OCSRandomSource_A) + OCSRandomSource_C) & OCSRandomSource_M;
	myself->_state = (uint32_t)tmp;
	return (int)tmp;
}

//------------------------------------------------------------------------------
int OCSRandomSource_New(OCSRandomSource ** myself, uint32_t seed) {
	int retval;

	retval = OCSObject_New((OCSObject **)myself, sizeof(OCSRandomSource),
			OCSRandomSource_dispose);
	if (retval == OCSERR_SUCCESS) {
		retval = OCSRandomSource_init(*myself, seed);
		if (retval != OCSERR_SUCCESS) {
			OCSObjectDelete((OCSObject*)*myself);
			*myself = NULL;
		}
	}
	return retval;
}

//------------------------------------------------------------------------------
int OCSRandomSource_init(OCSRandomSource * myself, uint32_t seed) {

	myself->_state = seed & OCSRandomSource_M;
	myself->next = OCSRandomSource_next;
	return OCSERR_SUCCESS;
}
//------------------------------------------------------------------------------
