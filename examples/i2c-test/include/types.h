/*
 * types.h
 *
 * define some frequently-used data types
 *
 * Copyright (C) 2017 Sinh Micro, Inc.
 * Subject to the GNU Public License, version 2.
 *
 * Author: lipeng<lp@sinhmicro.com>
 */

#ifndef __TYPES_H__
#define __TYPES_H__

typedef unsigned char   uint8_t;
typedef char            int8_t;
typedef unsigned short  uint16_t;
typedef short           int16_t;
typedef unsigned long   uint32_t;
typedef long            int32_t;
#if defined(__C51__)
typedef bit             bit_t;

#define CODE            code
#define INTERRUPT       interrupt
#define USING           using
#else
typedef __bit           bit_t;

#define CODE            __code
#define INTERRUPT       __interrupt
#define USING           __using
#endif

#ifndef bool
#define bool            bit_t
#endif

#ifndef true
#define true            1
#endif

#ifndef false
#define false           0
#endif

#ifndef NULL
#define NULL            (0)
#endif

#define ROUND_DIV(x, y) (((x) + (y) / 2) / (y))

#define ARRAY_SIZE(a)   (sizeof(a) / sizeof((a)[0]))

#define ABS(a)          (a > 0 ? a : -a)

#endif /* __TYPES_H__ */

