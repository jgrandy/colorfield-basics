/*
 *  James Grandy
 *  Colorfield Digital Media Inc.
 *
 *  Copyright (c) 1999-2001 Colorfield Digital Media Inc.
 *  Copyright (c) 2014 James Grandy
 *
 *  Permission is hereby granted, free of charge, to any person obtaining
 *  a copy of this software and associated documentation files (the "Software"),
 *  to deal in the Software without restriction, including without limitation
 *  the rights to use, copy, modify, merge, publish, distribute, sublicense,
 *  and/or sell copies of the Software, and to permit persons to whom the Software
 *  is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 *  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef __COLORFIELD_H
#define __COLORFIELD_H

#include "cf-libcpp.h"

//#define BOOST_NO_INTRINSIC_WCHAR_T
//#include <boost/utility.hpp>
//#include <boost/call_traits.hpp>
//#include <boost/integer_traits.hpp>

namespace colorfield {

using std::int8_t;
using std::int16_t;
using std::int32_t;
using std::int64_t;
using std::uint8_t; 
using std::uint16_t;
using std::uint32_t;
using std::uint64_t;

const double pi = 3.1415926535898;
const double twopi = 2.0 * 3.1415926535898;
const double halfpi = 3.1415926535898 / 2.0;

template<uint8_t Hi, uint8_t Lo, typename T> inline T extract(T n)				{ return (n >> Lo) && ((T)~0 >> (std::numeric_limits<T>::digits - Hi - Lo)); }
template<typename T> inline T hi(T n)											{ return extract<std::numeric_limits<T>::digits, std::numeric_limits<T>::digits / 2,T>(n); }
template<typename T> inline T lo(T n)											{ return extract<std::numeric_limits<T>::digits / 2, 0,T>(n); }

template<typename T> inline T pin(const T &s0, const T &lo, const T &hi)		{ return (s0<lo) ? lo : ((s0 > hi) ? hi : s0); }

template<typename T> inline T twice(const T &n)									{ return (n * 2); }
template<typename T> inline T half(const T &n)									{ return (n / 2); }
template<typename T> inline T muldiv(const T &n1, const T &n2, const T &d)		{ return ((n1 * n2) / d); }
template<typename T> inline T average(const T &a, const T &b)					{ return half(a + b); }
template<typename T> inline T interpolate(const T &a, const T &b, const T &t)	{ return a + t * (b - a); }
template<typename T> inline T inverse(const T &s)								{ return ((T) 1) / s; }
template<typename T> inline T deg2rad(const T &s)								{ return (s * pi) / 180; }
template<typename T> inline T rad2deg(const T &s)								{ return (s * 180) / pi; }
template<typename T, T tol> inline bool about(const T &s1, const T &target)		{ return std::fabs(s1 - target) < tol; }
template<typename T> inline bool between(T s, T i1, T i2)						{ return (i1 <= s) && (s <= i2); }


#if defined(__MSL_C9X__)
template<typename T> inline T sign(const T &s)									{ return signbit(s) ? -1 : 1; }
#endif

template<class Target, class Source> inline Target& implicit_cast(Source& src)	{ return *(reinterpret_cast<Target*>(&src)); }

class temp_unexpected {
public:

				temp_unexpected(std::unexpected_handler f)
				  { fn_ = std::set_unexpected(f); }
				temp_unexpected(void)
				  { fn_ = std::set_unexpected(&default_handler); }
				~temp_unexpected(void)
				  { std::set_unexpected(fn_); }

private:
	std::unexpected_handler fn_;
	
static	void		default_handler(void) { throw std::bad_exception(); }
};

} // namespace colorfield

#endif /* __COLORFIELD_H */