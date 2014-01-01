/* *  James Grandy *  Colorfield Digital Media Inc. * *  Copyright (c) 1999 Colorfield Digital Media Inc. *  Copyright (c) 2014 James Grandy * *  Permission is hereby granted, free of charge, to any person obtaining *  a copy of this software and associated documentation files (the "Software"), *  to deal in the Software without restriction, including without limitation *  the rights to use, copy, modify, merge, publish, distribute, sublicense, *  and/or sell copies of the Software, and to permit persons to whom the Software *  is furnished to do so, subject to the following conditions: * *  The above copyright notice and this permission notice shall be included in *  all copies or substantial portions of the Software. * *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, *  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN *  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */#include "constrained-simulation.h"#include "objective-function-tmpl.h"//#include "vector-function-tmpl.h"namespace cf_algebra {    template class stacked_vf<cf_simcore::constrained_simulation::objective_t>;    template class stacked_vf<cf_simcore::constrained_simulation::constraint_t>;}namespace cf_simcore {constrained_simulation::~constrained_simulation(void){}typename constrained_simulation::time_t	constrained_simulation::step(time_t delta){	this->objectives()->update(time(),state());				return simulation::step(delta);}} // namespace cf_simcore