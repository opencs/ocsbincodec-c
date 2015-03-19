/*
 * ocsobj.c
 *
 *  Created on: Mar 19, 2015
 *      Author: fjtc
 */
#include <ocsobj.h>


int OCSObject_Init(OCSObject * myself) {
	myself->dispose = NULL;
	return 0;
}

void OCSObject_SetDisposeMethod(OCSObject * myself, OCSObject_dispose_t dispose) {
	myself->dispose = dispose;
}

void OCSDispose(OCSObject * obj) {

	if (obj->dispose) {
		obj->dispose(obj);
	}
}
