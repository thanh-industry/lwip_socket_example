/*
 * ringBuf.h
 *
 *  Created on: Aug 25, 2023
 *      Author: tranm
 */

#ifndef DATAPACKAGE_RINGBUF_H_
#define DATAPACKAGE_RINGBUF_H_

#include <stdbool.h>

#define RING_BUFFER_SIZE    (512)

typedef struct{
    char buffer[RING_BUFFER_SIZE];
    int writeIndex;
    int readIndex;
}ring_buffer_t;

void initRingBuffer(ring_buffer_t *ring_buffer);
void writeData(ring_buffer_t *ring_buffer, const char *data);
bool readData(ring_buffer_t *ring_buffer, int length, char *output);
bool readSingleData(ring_buffer_t *ring_buffer, char *output);

#endif /* DATAPACKAGE_RINGBUF_H_ */
