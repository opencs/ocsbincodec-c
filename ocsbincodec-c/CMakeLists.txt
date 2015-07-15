cmake_minimum_required (VERSION 2.6)

project (ocsbincodec-c)

set (CMAKE_BINARY_DIR build)
set (CMAKE_BUILD_TYPE Release)
set (CMAKE_INSTALL_PREFIX release)

set (PROJECT_SOURCE_DIR src)
set (PROJECT_INCLUDE_DIR include)
set (PROJECT_LIB_DIR lib)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Build the libraries
include_directories(${PROJECT_INCLUDE_DIR})
ADD_LIBRARY(ocsbincodec-c STATIC
	${PROJECT_SOURCE_DIR}/ocsaalph.c
	${PROJECT_SOURCE_DIR}/ocsalpha.c
	${PROJECT_SOURCE_DIR}/ocsb2nco.c
	${PROJECT_SOURCE_DIR}/ocsb32al.c
	${PROJECT_SOURCE_DIR}/ocsb64al.c
	${PROJECT_SOURCE_DIR}/ocsbalph.c
	${PROJECT_SOURCE_DIR}/ocscodec.c
	${PROJECT_SOURCE_DIR}/ocshalph.c
	${PROJECT_SOURCE_DIR}/ocsobj.c
	${PROJECT_SOURCE_DIR}/ocsralph.c
	${PROJECT_SOURCE_DIR}/ocsrand.c
)

# Copy public headers
file(
	COPY ${PROJECT_INCLUDE_DIR}
	DESTINATION  ${CMAKE_BINARY_DIR}
)


