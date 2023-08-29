/*
 * stringFunction.c
 *
 *  Created on: Aug 25, 2023
 *      Author: nhat.tranminh
 */

#include <stringFunction.h>
#include <stringDefinition.h>

/**
 * Convert the integer string to integer value.
 *
 * @param  ptrBuff  pointer to scan buffer
 * @param  buffSize Size of the Buffer to Scan
 * @return  float value of the string
 * @see
 */
unsigned int string2Uint(char *ptrBuff, unsigned int buffSize)
{
    unsigned int retVal = 0;

    if (ptrBuff == 0)
    {
        return 0;
    }

    for (unsigned int indx = 0; indx < buffSize; indx++)
    {
        if (isNum(ptrBuff[indx]))
        {
            retVal = retVal * 10 + (unsigned int) ptrBuff[indx] - '0';
        }
        else
        {
            //return 0;
            break;
        }
    }
    return retVal;
}


/**
 * Convert the float string to float value. the atiof or strtof could not be applied here.
 *
 * @param  ptrBuff  pointer to scan buffer
 * @param  buffSize Size of the Buffer to Scan
 * @return  float value of the string
 * @see
 */
float string2Float(char *ptrBuff, unsigned int buffSize)
{
    unsigned int intVal = 0;
    float retVal = 0;
    unsigned int devider = 1;
    unsigned char fraction = 0;
    float negative = 1;
    unsigned int indx = 0;

    if (ptrBuff[indx] == '-')
    {
        negative = -1;
        indx++;
    }
    for (; indx < buffSize; indx++)
    {
        if (ptrBuff[indx] == '.')
        {
            fraction = 1;
            continue;
        }

        if (ptrBuff[indx] > '9' || ptrBuff[indx] < '0')
        {
            break;
        }
        else
        {
            if (fraction == 1)
            {
                devider *= 10;
            }
            intVal = intVal * 10 + (unsigned int)ptrBuff[indx] - '0';
        }
    }
    retVal = negative * (((float) intVal) / (float)devider);

    return retVal;
}

char *stringCpy(char * src, int start, int end)
{
	if(src == NULL || start < 0 || end < start){
		return NULL;
	}
	if(end >= strlen(src)){
		end = strlen(src) - 1;
	}
	int subStrLength = end - start + 1;
	char *subStr = (char *)malloc((subStrLength) * sizeof(char));
	if(subStr == NULL){
		return NULL;
	}
	strncpy(subStr, src + start, subStrLength);
	subStr[subStrLength] = '\0';
	return subStr;
}










