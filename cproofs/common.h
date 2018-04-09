/*
 *  Copyright (C) 2018  Clifford Wolf <clifford@clifford.at>
 *
 *  Permission to use, copy, modify, and/or distribute this software for any
 *  purpose with or without fee is hereby granted, provided that the above
 *  copyright notice and this permission notice appear in all copies.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

uint32_t xorshift32()
{
	static uint32_t x32 = 314159265;
	x32 ^= x32 << 13;
	x32 ^= x32 >> 17;
	x32 ^= x32 << 5;
	return x32;
}

uint64_t xorshift64()
{
	uint64_t r = xorshift32();
	return (r << 32) | xorshift32();
}

uint32_t bext32(uint32_t v, uint32_t mask)
{
	uint32_t c = 0, m = 1;
	while (mask) {
		uint32_t b = mask & -mask;
		if (v & b)
			c |= m;
		mask -= b;
		m <<= 1;
	}
	return c;
}

uint64_t bext64(uint64_t v, uint64_t mask)
{
	uint64_t c = 0, m = 1;
	while (mask) {
		uint64_t b = mask & -mask;
		if (v & b)
			c |= m;
		mask -= b;
		m <<= 1;
	}
	return c;
}

uint32_t bdep32(uint32_t v, uint32_t mask)
{
	uint32_t c = 0, m = 1;
	while (mask) {
		uint32_t b = mask & -mask;
		if (v & m)
			c |= b;
		mask -= b;
		m <<= 1;
	}
	return c;
}

uint64_t bdep64(uint64_t v, uint64_t mask)
{
	uint64_t c = 0, m = 1;
	while (mask) {
		uint64_t b = mask & -mask;
		if (v & m)
			c |= b;
		mask -= b;
		m <<= 1;
	}
	return c;
}

uint32_t grev32(uint32_t x, int k)
{
	if (k &  1) x = ((x & 0x55555555) <<  1) | ((x & 0xAAAAAAAA) >>  1);
	if (k &  2) x = ((x & 0x33333333) <<  2) | ((x & 0xCCCCCCCC) >>  2);
	if (k &  4) x = ((x & 0x0F0F0F0F) <<  4) | ((x & 0xF0F0F0F0) >>  4);
	if (k &  8) x = ((x & 0x00FF00FF) <<  8) | ((x & 0xFF00FF00) >>  8);
	if (k & 16) x = ((x & 0x0000FFFF) << 16) | ((x & 0xFFFF0000) >> 16);
	return x;
}

uint64_t grev64(uint64_t x, int k)
{
	if (k &  1) x = ((x & 0x5555555555555555ull) <<  1) | ((x & 0xAAAAAAAAAAAAAAAAull) >>  1);
	if (k &  2) x = ((x & 0x3333333333333333ull) <<  2) | ((x & 0xCCCCCCCCCCCCCCCCull) >>  2);
	if (k &  4) x = ((x & 0x0F0F0F0F0F0F0F0Full) <<  4) | ((x & 0xF0F0F0F0F0F0F0F0ull) >>  4);
	if (k &  8) x = ((x & 0x00FF00FF00FF00FFull) <<  8) | ((x & 0xFF00FF00FF00FF00ull) >>  8);
	if (k & 16) x = ((x & 0x0000FFFF0000FFFFull) << 16) | ((x & 0xFFFF0000FFFF0000ull) >> 16);
	if (k & 32) x = ((x & 0x00000000FFFFFFFFull) << 32) | ((x & 0xFFFFFFFF00000000ull) >> 32);
	return x;
}

uint32_t slo32(uint32_t x, int k)
{
	return ~((~x) << k);
}

uint32_t sro32(uint32_t x, int k)
{
	return ~((~x) >> k);
}

