/* *  James Grandy *  Colorfield Digital Media Inc. * *  Copyright (c) 1999 Colorfield Digital Media Inc. *  Copyright (c) 2014 James Grandy * *  Permission is hereby granted, free of charge, to any person obtaining *  a copy of this software and associated documentation files (the "Software"), *  to deal in the Software without restriction, including without limitation *  the rights to use, copy, modify, merge, publish, distribute, sublicense, *  and/or sell copies of the Software, and to permit persons to whom the Software *  is furnished to do so, subject to the following conditions: * *  The above copyright notice and this permission notice shall be included in *  all copies or substantial portions of the Software. * *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, *  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN *  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */#pragma warn_notinlined on#include "block.h"#include "cf-debug.h"#pragma inline_depth(12)using namespace colorfield;static void test_block_basics(void){	FAILFALSE(sizeof(range_t<>) == sizeof(uint64_t) / 2)	block_t<> b1;	b1.row_range() = range_t<>(0,3);	b1.column_range() = range_t<>(1,2);	FAILFALSE(b1.top() == 0)	FAILFALSE(b1.left() == 1)	FAILFALSE(b1.height() == 3)	FAILFALSE(b1.width() == 2)		block_t<> b2(0,3,1,2);	FAILFALSE(b2.top() == 0)	FAILFALSE(b2.left() == 1)	FAILFALSE(b2.height() == 3)	FAILFALSE(b2.width() == 2)	block_t<> b3 = b1;	FAILFALSE(b3.top() == 0)	FAILFALSE(b3.left() == 1)	FAILFALSE(b3.height() == 3)	FAILFALSE(b3.width() == 2)		FAILFALSE(b3 == b1)		b3 = b1.transpose();	FAILFALSE(b3.height() == b1.width())	FAILFALSE(b3.width() == b1.height())	}static void test_block_accessors(void){	block_t<> b1(0,3,1,2);	FAILFALSE(b1.row_range() == range_t<>(0,3))	FAILFALSE(b1.column_range() == range_t<>(1,2))		FAILFALSE(b1.top() == 0)	FAILFALSE(b1.left() == 1)	FAILFALSE(b1.height() == 3)	FAILFALSE(b1.width() == 2)		FAILFALSE(b1.bottom() == 2)	FAILFALSE(b1.right() == 2)		FAILFALSE(b1.top_left() == coord_t<>(0,1))	FAILFALSE(b1.bottom_right() == coord_t<>(2,2))		FAILFALSE(b1.extent() == coord_t<>(3,2))		FAILFALSE(b1.diagonal_extent() == 2)}void test_block(void);void test_block(void){	test_block_basics();	test_block_accessors();		typedef range_t<index_t,index_t> gen_range_t;	typedef block_t<gen_range_t,gen_range_t> gen_block_t;	typedef coord_t<index_t,index_t> gen_coord_t;		const gen_block_t b1(gen_range_t(1, 2), gen_range_t(0, 4)), 					  b2(gen_range_t(2, 3), gen_range_t(1, 5));	FAILFALSE(b1 == b1)	FAILFALSE(b1.width() == 4)	FAILFALSE(b1.height() == 2)	FAILFALSE(b1.extent() == gen_coord_t(2,4))		FAILFALSE(b1.contains(gen_coord_t(1,0)))	FAILFALSE(b1.contains(gen_coord_t(2,3)))	FAILTRUE(b1.contains(gen_coord_t(0,0)))	FAILTRUE(b1.contains(gen_coord_t(3,2)))		FAILFALSE(b1.map_out(gen_coord_t(1,2)) == gen_coord_t(2,2))		const gen_coord_t c21(2,1);	const gen_block_t::coord_traits<>::outset_t b2o = b2.outset(c21);	FAILFALSE(b2o == gen_block_t(gen_range_t(0,7), gen_range_t(0,7)))		gen_block_t::transpose_t b1_t = b1.transpose();		FAILFALSE(b1_t.width() == 2)	FAILFALSE(b1_t.height() == 4)}