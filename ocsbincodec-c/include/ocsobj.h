/*
 * ocsobj.h
 *
 *  Created on: Mar 19, 2015
 *      Author: fjtc
 */

#ifndef OCSOBJ_H_
#define OCSOBJ_H_

#include <stdlib.h>

#ifdef _cplusplus
extern "C" {
#endif

typedef struct OCSObject OCSObject;

/**
 * This is the type used by all dispose methods.
 *
 * @param[in] myself Myself.
 */
typedef void (*OCSObject_dispose_t)(OCSObject * myself);

/**
 * This is the data structure that represents the class OCSObject.
 */
struct OCSObject {
	OCSObject_dispose_t dispose;
};

/**
 * Initializes this instance.
 *
 * @param[in] myself Myself.
 * @return 0 for success or non zero value for failure.
 */
int OCSObject_Init(OCSObject * myself);

/**
 * Sets the dispose method.
 *
 * @param[in] myself Myself.
 * @param[in] dipose The dispose method.
 */
void OCSObject_SetDisposeMethod(OCSObject * myself, OCSObject_dispose_t dispose);

/**
 * Disposes objects.
 *
 * @param[in] obj The object to be disposed.
 */
void OCSDispose(OCSObject * obj);

#ifdef _cplusplus
} //extern "C"
#endif

#endif /* OCSOBJ_H_ */
