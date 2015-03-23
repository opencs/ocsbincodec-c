/*
 * Copyright (c) 2015, Open Communications Security
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
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
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "OCSObjectTest.h"
#include <ocsobj.h>

//==============================================================================
// class OCSObjectTest
//------------------------------------------------------------------------------
OCSObjectTest::OCSObjectTest() {
}

//------------------------------------------------------------------------------
OCSObjectTest::~OCSObjectTest() {
}

//------------------------------------------------------------------------------
void OCSObjectTest::SetUp() {
}

//------------------------------------------------------------------------------
void OCSObjectTest::TearDown() {
}

//------------------------------------------------------------------------------
void OCSObjectTest_dispose(OCSObject * myself) {
}

//------------------------------------------------------------------------------
void OCSObjectTest_dispose2(OCSObject * myself) {
}

//------------------------------------------------------------------------------
TEST_F(OCSObjectTest, Constructor) {
	OCSObject * obj;
	int retval;

	obj = NULL;
	retval = OCSObject_New(&obj, sizeof(OCSObject), NULL);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	ASSERT_TRUE(obj->dispose != NULL);
	OCSObjectDelete(obj);

	obj = NULL;
	retval = OCSObject_New(&obj, sizeof(OCSObject), OCSObjectTest_dispose);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	ASSERT_TRUE(obj->dispose == OCSObjectTest_dispose);
	OCSObjectDelete(obj);
}

//------------------------------------------------------------------------------
TEST_F(OCSObjectTest, ConstructorAlreadyInitialized) {
	OCSObject * obj;
	int retval;

	// Call from superclass
	obj = NULL;
	retval = OCSObject_New(&obj, sizeof(OCSObject) + 1, OCSObjectTest_dispose);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	ASSERT_TRUE(obj->dispose == OCSObjectTest_dispose);

	// Call from base
	retval = OCSObject_New(&obj, sizeof(OCSObject), OCSObjectTest_dispose2);
	ASSERT_EQ(OCSERR_SUCCESS, retval);
	ASSERT_TRUE(obj->dispose == OCSObjectTest_dispose);

	// Wrong call
	retval = OCSObject_New(&obj, sizeof(OCSObject) + 2, NULL);
	ASSERT_EQ(OCSERR_BUFFER_TOO_SMALL, retval);

	OCSObjectDelete(obj);
}


//------------------------------------------------------------------------------
TEST_F(OCSObjectTest, ConstructorFail) {
	OCSObject * obj;
	int retval;

	retval = OCSObject_New(NULL, sizeof(OCSObject), NULL);
	ASSERT_EQ(OCSERR_INVALID_ARGUMENT, retval);

	obj = NULL;
	retval = OCSObject_New(&obj, sizeof(OCSObject) - 1, NULL);
	ASSERT_EQ(OCSERR_INVALID_ARGUMENT, retval);
	ASSERT_TRUE(obj == NULL);
}


//------------------------------------------------------------------------------
