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
#include "CIntegerFileReader.h"
#include <string.h>
#include <stdlib.h>

//==============================================================================
// Class CIntegerFileReader
//------------------------------------------------------------------------------
CIntegerFileReader::CIntegerFileReader(const char * fileName) {

	this->linenum = 0;
	this->inp.open(fileName);
}

//------------------------------------------------------------------------------
CIntegerFileReader::~CIntegerFileReader() {
	this->close();
}

//------------------------------------------------------------------------------
bool CIntegerFileReader::readLine() {
	int c;
	bool stop;

	if (inp.eof()) {
		return false;
	}

	// Start the extraction
	this->linenum++;
	this->line.clear();
	stop = false;
	do {
		c = this->inp.get();
		switch (c) {
		case EOF:
		case '\n':
			stop = true;
			break;
		default:
			this->line.append(1, (char)c);
			break;
		}
	} while(!stop);
	return true;
}

//------------------------------------------------------------------------------
bool CIntegerFileReader::readValidLine() {
	bool retry;

	do {
		if (!this->readLine()) {
			return false;
		} else {
			rtrim(this->line);
			ltrim(this->line);
			if (this->line.length() == 0) {
				retry = true;
			} else if (this->line[0] == '#') {
				retry = true;
			} else {
				retry = false;
			}
		}
	} while (retry);
	return true;
}

//------------------------------------------------------------------------------
void CIntegerFileReader::rtrim(std::string & s) {
	std::string::iterator i;

	i = s.end();
	do {
		i--;
	} while ((i >= s.begin()) && (isspace(*i)));

	i++;
	s.erase(i, s.end());
}

//------------------------------------------------------------------------------
void CIntegerFileReader::ltrim(std::string & s) {
	std::string::iterator i;

	i = s.begin();
	while ((i < s.end()) && (isspace(*i))) {
		i++;
	}
	s.erase(s.begin(), i);
}

//------------------------------------------------------------------------------
bool CIntegerFileReader::isLineInteger() {
	std::string::iterator i;

	i = this->line.begin();
	while (i < this->line.end()) {
		if (!isdigit(*i)) {
			return false;
		}
		i++;
	}
	return true;
}

//------------------------------------------------------------------------------
void CIntegerFileReader::close() {

	if (this->inp.is_open()) {
		this->inp.close();
	}
}

//------------------------------------------------------------------------------
bool CIntegerFileReader::nextInt(int & v) {

	if (this->readValidLine()) {
		if (isLineInteger()) {
			v = atoi(this->line.c_str());
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

//------------------------------------------------------------------------------
