#!/bin/python
# Copyright (c) 2015-2017, Open Communications Security
# All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
# 
# * Redistributions of source code must retain the above copyright notice, this
#   list of conditions and the following disclaimer.
# 
# * Redistributions in binary form must reproduce the above copyright notice,
#   this list of conditions and the following disclaimer in the documentation
#   and/or other materials provided with the distribution.
# 
# * Neither the name of ocsbincodec-c nor the names of its
#   contributors may be used to endorse or promote products derived from
#   this software without specific prior written permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#-------------------------------------------------------------------------------
# This script generates C++ code that contains examples of Base64 encoded values
# that can be used to test the Base64 implementation.
#
import base64;
import random;

COUNT=16

def gen_random_string(size):
	s=''
	for i in range(size):
		s = s + chr(random.randint(0, 255))
	return s

def str_to_c_byte_array(s):
	out=''
	for i in range(len(s)):
		out = out + '0x{0:02X}, '.format(ord(s[i]))
		if ((i % 8) == 7):
			out = out + '\n\t'
	out = out.strip()
	if (len(out) > 0):
		out = out[0:len(out) - 1]
	return '\t' + out

samples=[]
for size in range(1, COUNT + 1):
	samples.append(gen_random_string(size))
	
for s in samples:
	print('static const unsigned char Base64CodecTest_SAMPLE_BIN{0}[{0}] = {{'.format(len(s)) )
	print(str_to_c_byte_array(s))
	print('};')
	print('')


print('typedef struct {')
print('\tconst char * encoded;')
print('\tint decodedSize;')
print('\tconst unsigned char * decoded;')
print('} Base64CodecTest_sample_entry_t;')
print('')

print('#define B64_SAMPLES_SIZE {0}'.format(len(samples)))
print('static const Base64CodecTest_sample_entry_t Base64CodecTest_SAMPLES[B64_SAMPLES_SIZE] = {')
for s in samples:
	print('\t{{"{0}", sizeof(Base64CodecTest_SAMPLE_BIN{1}), Base64CodecTest_SAMPLE_BIN{1}}},'.format(
		base64.b64encode(s),
		len(s)))
print('};')
