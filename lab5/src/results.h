#ifndef RESULTS_H
#define RESULTS_H

typedef enum ReadResult {
	READ_OK = 0,
	READ_INVALID_SIGNATURE,
    READ_INVALID_BITS,
    READ_INVALID_HEADER
} read_result;

typedef enum WriteResult {
	WRITE_OK = 0,
	WRITE_ERROR
} write_result;

typedef enum FreeResult {
	FREE_OK = 0,
	FREE_ERROR
} free_result;

#endif
