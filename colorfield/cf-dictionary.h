/* *  James Grandy *  Colorfield Digital Media Inc. * *  Copyright (c) 1999 Colorfield Digital Media Inc. *  Copyright (c) 2014 James Grandy * *  Permission is hereby granted, free of charge, to any person obtaining *  a copy of this software and associated documentation files (the "Software"), *  to deal in the Software without restriction, including without limitation *  the rights to use, copy, modify, merge, publish, distribute, sublicense, *  and/or sell copies of the Software, and to permit persons to whom the Software *  is furnished to do so, subject to the following conditions: * *  The above copyright notice and this permission notice shall be included in *  all copies or substantial portions of the Software. * *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, *  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN *  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */#ifndef __CF_DICTIONARY_H#define __CF_DICTIONARY_H#include "colorfield.h"#include <map>#include <stdexcept>namespace colorfield {/*1.				2.					3.*/template<class T> inline uint32_t encode_value(const T &val);template<> inline uint32_t encode_value<uint32_t>(const uint32_t &val) { return val; }template<> inline uint32_t encode_value<bool>(const bool &val) { return (uint32_t) val; }template<class T> inline T decode_value(const uint32_t eval);template<> inline uint32_t decode_value<uint32_t>(const uint32_t eval) { return eval; }template<> inline bool decode_value<bool>(const uint32_t eval) { return (bool) eval; }class dictionary {public:		typedef dictionary			this_t;		typedef uint32_t				tag_t;					class bad_tag : public std::logic_error {	public :	explicit						bad_tag(tag_t which_tag) 					: std::logic_error("bad tag: " + which_tag) {}	};	class wrong_type : public std::logic_error {	public :	explicit						wrong_type(std::string given_type, std::string expected_type) 																				: std::logic_error("wrong type. expected: " + expected_type + " given: " + given_type) {}	};									dictionary(void)							: store_() {}template<typename T> T				get(tag_t tag) const throw(wrong_type,bad_tag)																				{																				  store_t::const_iterator sit = store_.find(tag); 																				  if (sit == store_.end()) { throw bad_tag(tag); return 0; } 																				  else return sit->second.get<T>();																				} 					void			remove(tag_t tag) throw(wrong_type,bad_tag)																				{																				  store_t::iterator sit = store_.find(tag); 																				  if (sit != store_.end())																				  	store_.erase(sit);																				} 					bool			has(tag_t tag) const throw(wrong_type,bad_tag)																				{																				  store_t::const_iterator sit = store_.find(tag); 																				  return (sit != store_.end());																				} template<typename T> void			set(tag_t tag, T val) throw(wrong_type)																				{ value v(value_traits<T>::type_tag); v.set<T>(val); store_[tag] = v; }					uint32_t			get_uint32(tag_t tag) const throw(wrong_type,bad_tag)																				{																				  store_t::const_iterator sit = store_.find(tag); 																				  if (sit == store_.end()) { throw bad_tag(tag); return 0; } 																				  else return sit->second.get<uint32_t>();																				}					void			set_uint32(tag_t tag, uint32_t val) throw(wrong_type)																				{ value v(value::uint32_type); v.set<uint32_t>(val); store_[tag] = v; }					bool			get_bool(tag_t tag) const throw(wrong_type,bad_tag)																				{																				  store_t::const_iterator sit = store_.find(tag); 																				  if (sit == store_.end()) { throw bad_tag(tag); return 0; } 																				  else return sit->second.get<bool>();																				}					void			set_bool(tag_t tag, bool val) throw(wrong_type)																				{ value v(value::bool_type); v.set<bool>(val); store_[tag] = v; }private:	class value {	public:		typedef enum { no_type, uint32_type, bool_type } type_t;									value(void)									: type_(no_type), val_(0) {}explicit							value(type_t t)								: type_(t), val_(0) {}									value(const value &v)						: type_(v.type_), val_(v.val_) {}				value&				operator= (const value &v)					{ type_ = v.type_; val_ = v.val_; return *this; }template<class T> void				set(const T &v)								{ val_ = encode_value(v); }template<class T> T					get(void) const								{ return decode_value<T>(val_); }	private:				void				check_type(type_t t) const throw(wrong_type) { if (t != type_) throw wrong_type(type_name(t), type_name(type_)); }		  const char*				type_name(type_t t) const					{ switch (t) { case uint32_type: return "uint32_t"; bool_type: return "bool"; default: return "unknown"; } }		  				type_t				type_;				uint32_t				val_;	};	template<typename T> class value_traits;		typedef std::map<tag_t,value>	store_t;					store_t			store_;};    template<> class dictionary::value_traits<uint32_t>	{ public: static const value::type_t type_tag = value::uint32_type; };template<> class dictionary::value_traits<bool>	{ public: static const value::type_t type_tag = value::bool_type; };} // namespace colorfield#endif /* __CF_DICTIONARY_H */ 