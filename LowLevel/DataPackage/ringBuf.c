/*
 * ringBuf.c
 *
 *  Created on: Aug 25, 2023
 *      Author: nhat.tranminh
 */

#include <string.h>
#include <ringBuf.h>

void initRingBuffer(ring_buffer_t *ring_buffer){
    memset(ring_buffer, 0, sizeof(ring_buffer));
    ring_buffer->writeIndex = 0;
    ring_buffer->readIndex = 0;
}

void writeData(ring_buffer_t *ring_buffer, const char *data)
{
    size_t dataLength = strlen(data);
    size_t i = 0;
    for(i = 0; i < dataLength; i++){
        ring_buffer->buffer[ring_buffer->writeIndex] = data[i];
        ring_buffer->writeIndex = (ring_buffer->writeIndex + 1) % RING_BUFFER_SIZE;
        if(ring_buffer->writeIndex == ring_buffer->readIndex){
            ring_buffer->readIndex = (ring_buffer->readIndex + 1) % RING_BUFFER_SIZE;
        }
    }
}


bool readData(ring_buffer_t *ring_buffer, int length, char *output)
{
    if(length > (RING_BUFFER_SIZE - 1)){
        return false;
    }
    int i = 0;
    while(i < length && ring_buffer->readIndex != ring_buffer->writeIndex){
         output[i] = ring_buffer->buffer[ring_buffer->readIndex];
         ring_buffer->readIndex = (ring_buffer->readIndex + 1) % RING_BUFFER_SIZE;
         i++;
    }
    output[i] = '\0';
    return true;
}


bool readSingleData(ring_buffer_t *ring_buffer, char *output)
{
    if(ring_buffer->readIndex != ring_buffer->writeIndex){
        *output = ring_buffer->buffer[ring_buffer->readIndex];
        ring_buffer->readIndex = (ring_buffer->readIndex + 1) % RING_BUFFER_SIZE;
        return true;
    }
    return false;
}




