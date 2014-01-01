/* *  James Grandy *  Colorfield Digital Media Inc. * *  Copyright (c) 1999 Colorfield Digital Media Inc. *  Copyright (c) 2014 James Grandy * *  Permission is hereby granted, free of charge, to any person obtaining *  a copy of this software and associated documentation files (the "Software"), *  to deal in the Software without restriction, including without limitation *  the rights to use, copy, modify, merge, publish, distribute, sublicense, *  and/or sell copies of the Software, and to permit persons to whom the Software *  is furnished to do so, subject to the following conditions: * *  The above copyright notice and this permission notice shall be included in *  all copies or substantial portions of the Software. * *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, *  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN *  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */#ifndef __MATRIX_OPS_META_TMPL_H#define __MATRIX_OPS_META_TMPL_H#include "matrix.h"#include "matrix-ops.h"#include "matrix-exceptions.h"#include "cf-debug.h"namespace cf_algebra {template<class Op, class Extent, class Structure>inline void inline_update(      Op op,						        matrix<Extent,Structure> &A,						  const scalar_t a){	const typename Extent::height_t h = A.height();	const typename Extent::width_t  w = A.width();		for (int i=0; i<h; i++) {			typename matrix<Extent,Structure>::row_it_t A_it = A.row_it(i);				for (int j=0; j<w; j++) {					scalar_t &A_elt = *A_it;			++A_it;						A_elt = op(A_elt, a);		}	}}template<class Op, class Extent1, class Structure1, class Extent2, class Structure2>inline void inline_update(      Op op,								matrix<Extent1,Structure1> &A,						  const matrix<Extent2,Structure2> &B){	const typename Extent1::height_t h = A.height();	const typename Extent1::width_t  w = A.width();		AC_PRECONDITION(A.extent() == B.extent());		for (int i=0; i<h; i++) {			typename matrix<Extent1,Structure1>:: row_it_t A_it = A.row_it(i);		typename matrix<Extent2,Structure2>::crow_it_t B_it = B.row_it(i);				for (int j=0; j<w; j++) {					scalar_t &A_elt = *A_it;			const scalar_t B_elt = *B_it;			++A_it;			++B_it;						A_elt = op(A_elt, B_elt);		}	}}						  template<class T, class Op, class Extent, class Structure>inline void inline_reduce(      T &result,								Op op,						  const matrix<Extent,Structure> &A){	const typename Extent::height_t h = A.height();	const typename Extent::width_t  w = A.width();		for (int i=0; i<h; i++) {			typename matrix<Extent,Structure>::crow_it_t A_it = A.row_it(i);				for (int j=0; j<w; j++) {					const scalar_t A_elt = *A_it;			++A_it;						result = op(result, A_elt);		}	}}template<class T, class Op, class Extent, class Structure, class U>inline void inline_reduce(      T &result,								Op op,						  const matrix<Extent,Structure> &A,						  const U &b){	const typename Extent::height_t h = A.height();	const typename Extent::width_t  w = A.width();		for (int i=0; i<h; i++) {			typename matrix<Extent,Structure>::crow_it_t A_it = A.row_it(i);				for (int j=0; j<w; j++) {					const scalar_t A_elt = *A_it;			++A_it;						result = op(result, std::pair<scalar_t,U>(A_elt,b));		}	}}template<class T, class Op, class Extent1, class Structure1, class Extent2, class Structure2>inline void inline_reduce(      T &result,								Op op,						  const matrix<Extent1,Structure1> &A,						  const matrix<Extent2,Structure2> &B){	const typename Extent1::height_t h = A.height();	const typename Extent1::width_t  w = A.width();		AC_PRECONDITION(A.extent() == B.extent());		for (int i=0; i<h; i++) {			typename matrix<Extent1,Structure1>::crow_it_t A_it = A.row_it(i);		typename matrix<Extent2,Structure2>::crow_it_t B_it = B.row_it(i);				for (int j=0; j<w; j++) {					const scalar_t A_elt = *A_it;			const scalar_t B_elt = *B_it;			++A_it;			++B_it;						result = op(result, std::pair<scalar_t,scalar_t>(A_elt,B_elt));		}	}}} /* namespace cf_algebra */#endif /* __MATRIX_OPS_META_TMPL_H */