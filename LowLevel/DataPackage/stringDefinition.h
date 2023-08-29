/*
 * stringDefinition.h
 *
 *  Created on: Aug 25, 2023
 *      Author: nhat.tranminh
 */

#ifndef DATAPACKAGE_STRINGDEFINITION_H_
#define DATAPACKAGE_STRINGDEFINITION_H_

#define isEOL(c)                (c == 0x09 || c == 0x0a)
#define isSP(c)                 (c == '"' || c == 0x09 || c == 0x0a)
#define isSecret(c)             (c == '*')
#define isNum(c)                ((c >= '0') && (c <= '9'))
#define isCHAR(c)               ((c >= 'A') && (c < 'Z'))                               //is capitalized char
#define isChar(c)               (((c >= 'A') && (c < 'Z'))||((c >= 'a') && (c < 'z')))  //is mixed char
#define ischar(c)               ((c >= 'a') && (c < 'z'))   //is mixed char
#define isHex(c)                (cf_isNum(c) || ((c >= 'a') && (c <= 'f')) || ((c >= 'A') && (c <= 'F')))
#define isPortStart(c)          (c == '<')
#define isPortEnd(c)            (c == '>')
#define isSetStart(c)           (c == '{')
#define isSetEnd(c)             (c == '}')
#define isElemStart(c)          (c == '[')
#define isElemEnd(c)            (c == ']')
#define isElemDelimiter(c)      (c == ',')
#define isSetDelimiter(c)       (c == ',')
#define isPortDelimiter(c)      (c == ',')
#define isDot(c)                (c == '.')
#define isSpace(c)              (c == ' ')
#define isUnderScop(c)          (c == '_')
#define isMinus(c)              (c == '-')
#define isQuotation(c)          (c == '"')
#define isASCII(c)              (c >= ' ' && c < '~')
#define iodd_isDelimiter(c)     (c == ',')
#define isQuotation(c)          (c == '"')
#define isSpecialMark(c)        (c == '\\')
#define is_empty(c)             (c == 0xff)
#define c8y_ui_is_valid(c)      (cf_isChar(c) || cf_isNum(c))
#define host_is_ip(c)       (cf_isNum(c) || cf_isDot(c))

#endif /* DATAPACKAGE_STRINGDEFINITION_H_ */
