/* *  James Grandy *  Colorfield Digital Media Inc. * *  Copyright (c) 1995 Colorfield Digital Media Inc. *  Copyright (c) 2014 James Grandy * *  Permission is hereby granted, free of charge, to any person obtaining *  a copy of this software and associated documentation files (the "Software"), *  to deal in the Software without restriction, including without limitation *  the rights to use, copy, modify, merge, publish, distribute, sublicense, *  and/or sell copies of the Software, and to permit persons to whom the Software *  is furnished to do so, subject to the following conditions: * *  The above copyright notice and this permission notice shall be included in *  all copies or substantial portions of the Software. * *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, *  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN *  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */#ifndef __EULER_TMPL_H#define __EULER_TMPL_H#include "euler.h"namespace cf_algebra {template<class Q>midpoint_solver<Q>::~midpoint_solver(void){	if (tmp_) delete tmp_;}template<class Q>void midpoint_solver<Q>::set_state(const time_t &t, const q_t &q, const qdot_t &qdot){	const typename q_t::height_t qsize = q.height();		base_t::set_state(t,q,qdot);		if ((!tmp_) || (tmp_->height() != qsize)) {		if (tmp_) delete tmp_;		tmp_ = new q_t(qsize, one_t());	}}template<class Q>typename midpoint_solver<Q>::time_t midpoint_solver<Q>::step(void){	this->assert_solver_initialized();		time_t t = this->get_time();	const time_t halfstep = (time_t) (0.5 * this->delta_t_);	// first, calculate a half-step in the direction of dqdt	*tmp_ = *(this->q_);	axpy(halfstep, *(this->qdot_), (scalar_t) 1.0, *tmp_);		// now, calculate the derivative at that point	this->set_time(t + halfstep);	*(this->qdot_) = (scalar_t) 0.0;	(this->f_).apply(*(this->qdot_), *(this->tmp_), this->t_);//clog << "half-step t=" << t_store_ << endl;//clog << "          q=" << *tmp_ << endl;//clog << "          dqdt=" << *qdot_ << endl;		// finally, use the intermediate derivative to estimate a full	// step from the original point	axpy((this->delta_t_), *(this->qdot_), (scalar_t) 1.0, *(this->q_));		if (has_nan(*(this->q_)))		throw matrix_invalid("nan");		// and fill in the rest of the simulation state at the new point	t += this->delta_t_;	this->set_time(t);	*(this->qdot_) = (scalar_t) 0.0;	(this->f_).apply(*(this->qdot_), *(this->q_), this->t_);//clog << "full-step t=" << t_store_ << endl;//clog << "          q=" << *q_ << endl;//clog << "          dqdt=" << *qdot_ << endl;		if (has_nan(*(this->qdot_)))		throw matrix_invalid("nan");		return this->get_time();}} /* namespace cf_algebra */#endif /* __EULER_TMPL_H */