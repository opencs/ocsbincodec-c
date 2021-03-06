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
#ifndef OCSERR_H_
#define OCSERR_H_

/**
 * Error code for success.
 *
 * @ingroup OCSERR
 */
#define OCSERR_SUCCESS 0

/**
 * Error code for out of memory.
 *
 * @ingroup OCSERR
 */
#define OCSERR_OUT_OF_MEMORY -1

/**
 * Error code for buffer to small.
 *
 * @ingroup OCSERR
 */
#define OCSERR_BUFFER_TOO_SMALL -2

/**
 * Error code for invalid argument.
 *
 * @ingroup OCSERR
 */
#define OCSERR_INVALID_ARGUMENT -3

/**
 * Error code for corrupted encoded data.
 *
 * @ingroup OCSERR
 */
#define OCSERR_CORRUPTED_ENCODED_DATA -4

/**
 * Error code for bad padding.
 *
 * @ingroup OCSERR
 */
#define OCSERR_BAD_PADDING -5

#endif /* OCSERR_H_ */
