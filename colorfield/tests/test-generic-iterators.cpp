/* *  James Grandy *  Colorfield Digital Media Inc. * *  Copyright (c) 1999 Colorfield Digital Media Inc. *  Copyright (c) 2014 James Grandy * *  Permission is hereby granted, free of charge, to any person obtaining *  a copy of this software and associated documentation files (the "Software"), *  to deal in the Software without restriction, including without limitation *  the rights to use, copy, modify, merge, publish, distribute, sublicense, *  and/or sell copies of the Software, and to permit persons to whom the Software *  is furnished to do so, subject to the following conditions: * *  The above copyright notice and this permission notice shall be included in *  all copies or substantial portions of the Software. * *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, *  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN *  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */#include "colorfield.h"#include "generic-iterators.h"#include "cf-debug.h"using colorfield::pi;typedef double_t scalar_t;static const scalar_t data[]  = { (scalar_t) (pi+0), (scalar_t) (pi+1), (scalar_t) (pi+2),							   (scalar_t) (pi+3), (scalar_t) (pi+4), (scalar_t) (pi+5),							   (scalar_t) (pi+6) };void test_generic_iterators(void);void test_generic_iterators(void){	using namespace colorfield;		dummy_iterator<double_t> dit(pi);		FAILNEQ(*dit, pi)		++dit;		FAILNEQ(*dit, pi)		dit++;		FAILNEQ(*dit, pi)			const_slice_iterator<scalar_t,three_t> csi(data, three_t()),										csi2(&(data[6]), three_t());											FAILNEQ(*csi,pi)		++csi;		FAILNEQ(*csi,pi+3)		csi++;		FAILNEQ(*csi,pi+6)		FAILFALSE(csi == csi2)	}