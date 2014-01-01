/*
 *  James Grandy
 *  Colorfield Digital Media Inc.
 *
 *  Copyright (c) 2000 Colorfield Digital Media Inc.
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

#ifndef __CF_LIBCPP_H
#define __CF_LIBCPP_H

// Support
#include <exception>
#include <new>
#include <climits>
#include <typeinfo>
// Diagnostics
#include <stdexcept>
// Iterators
#include <iterator>
// Utilities
#include <functional>
#include <memory>
#include <utility>
// Algorithms
#include <algorithm>
// Strings
#include <string>
// Containers
#include <deque>
#include <list>
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <stack>
// Input/Output
#include <iostream>
#include <iomanip>
#include <fstream>
// Numerics
#include <complex>
#include <numeric>

// ANSI C Support

#include <math.h>

#include <stdint.h>

#define CF_HAS_MEMBER_TEMPLATES 1
#define AC_HAS_MEMBER_TEMPLATES 1

#define CF_HAS_CLASS_TEMPLATE_PARTIAL_SPECIALIZATION 1
#define AC_HAS_CLASS_TEMPLATE_PARTIAL_SPECIALIZATION 1

#define AC_DEFAULT_TEMPLATE_PARAMETERS 1

#ifdef __has_feature
#endif

#endif