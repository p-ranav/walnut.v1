#pragma once
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>

namespace walnut
{

namespace utf8
{

typedef uint8_t u_int8_t;
typedef uint16_t u_int16_t;
typedef uint32_t u_int32_t;

/* is c the start of a utf8 sequence? */
#define IsUtf8(c) (((c)&0xC0) != 0x80)

/* returns length of next utf-8 sequence */
int SequenceLength(char *s);

} // namespace utf8

} // namespace walnut