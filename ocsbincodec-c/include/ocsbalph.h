/*
 * ocsbalph.h
 *
 *  Created on: Mar 23, 2015
 *      Author: fchino
 */

#ifndef OCSBALPH_H_
#define OCSBALPH_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <ocsalpha.h>

/**
 * @defgroup ClassOCSBinaryAlphabet Class OCSBinaryAlphabet
 *
 * <p><b>@ref ClassOCSObject &gt;
 * @ref ClassOCSAlphabet &gt;
 * @ref ClassOCSBinaryAlphabet</b></p>
 *
 * This class implements the binary alphabet.
 */
/**
 * @addtogroup ClassOCSBinaryAlphabet
 * @{
 */
/**
 * Type of the class OCSBinaryAlphabet.
 */
typedef struct OCSBinaryAlphabet OCSBinaryAlphabet;

/**
 * Structure of class OCSBinaryAlphabet.
 */
struct OCSBinaryAlphabet {
	/**
	 * Base class.
	 */
	OCSAlphabet base;
	/**
	 * Character for one.
	 */
	int _one;
	/**
	 * Character for zero.
	 */
	int _zero;
};

/**
 * Creates a new instance of OCSBinaryAlphabet.
 *
 * @param[out] myself The pointer to the pointer to myself.
 * @param[in] zero The character for zero.
 * @param[in] one The character for one.
 * @return OCSERR_SUCCESS for success or other error code in case of failure.
 */
int OCSBinaryAlphabet_New(OCSBinaryAlphabet ** myself, int zero, int one);

/**
 * Initializes a new instance of OCSBinaryAlphabet.
 *
 * @param[out] myself The pointer to myself.
 * @param[in] zero The character for zero.
 * @param[in] one The character for one.
 * @return OCSERR_SUCCESS for success or other error code in case of failure.
 * @note This method is called only by @ref OCSBinaryAlphabet_New() and
 * direct subclasses of
 */
int OCSBinaryAlphabet_init(OCSBinaryAlphabet * myself, int zero, int one);

/**
 * Disposes this instance and releases all allocated resources. This method is
 * called only by OCSObjectDelete() or subclasses of this class.
 *
 * @param[out] myself A pointer to myself.
 */
void OCSBinaryAlphabet_dispose(OCSObject * myself);

/** @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* OCSBALPH_H_ */
