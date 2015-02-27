/*
 * LGDictModule.cc
 *
 * Copyright (C) 2014 OpenCog Foundation
 *
 * Author: William Ma <https://github.com/williampma>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License v3 as
 * published by the Free Software Foundation and including the exceptions
 * at http://opencog.org/wiki/Licenses
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program; if not, write to:
 * Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */


#include "LGDictModule.h"


using namespace opencog::nlp;
using namespace opencog;


DECLARE_MODULE(LGDictModule);

/**
 * The constructor for LGDictModule.
 *
 * @param cs   the OpenCog server
 */
LGDictModule::LGDictModule(CogServer& cs) : Module(cs)
{

}

/**
 * The destructor for LGDictModule.
 */
LGDictModule::~LGDictModule()
{
    delete m_scm;
}

/**
 * The required implementation for the pure virtual init method.
 */
void LGDictModule::init(void)
{
    m_scm = new LGDictSCM();
}
