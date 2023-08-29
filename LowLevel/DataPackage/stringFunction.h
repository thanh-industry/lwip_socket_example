/*
 * stringFunction.h
 *
 *  Created on: Aug 25, 2023
 *      Author: nhat.tranminh
 */

#ifndef DATAPACKAGE_STRINGFUNCTION_H_
#define DATAPACKAGE_STRINGFUNCTION_H_

#include "stdint.h"
#include <string.h>
#include <ctype.h>

#define LENGTH_OF_STRING    64


unsigned int string2Uint(char* ptrBuff, unsigned int buffSize);
float string2Float(char *ptrBuff, unsigned int buffSize);
char *stringCpy(char * src, int x, int y);

#endif /* DATAPACKAGE_STRINGFUNCTION_H_ */
