/*
-----------------------------------------------------------------------------------------------
Copyright (C) 2013 Henry van Merode. All rights reserved.

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
-----------------------------------------------------------------------------------------------
*/

#include "ParticleUniversePCH.h"

#ifndef PARTICLE_UNIVERSE_EXPORTS
#define PARTICLE_UNIVERSE_EXPORTS
#endif

#include "ParticleEmitters/ParticleUniverseCylinderEmitter.h"
#include "ParticleEmitters/ParticleUniverseCylinderEmitterTokens.h"

#include "OgreLogManager.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
    bool CylinderEmitterTranslator::translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		PropertyAbstractNode* prop = reinterpret_cast<PropertyAbstractNode*>(node.get());
		ParticleEmitter* em = any_cast<ParticleEmitter*>(prop->parent->context);
        CylinderEmitter* emitter = static_cast<CylinderEmitter*>(em);

        if (prop->name == token[TOKEN_RADIUS])
		{
			// Property: radius
			if (passValidateProperty(compiler, prop, token[TOKEN_RADIUS], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					emitter->setRadius(val);
					return true;
				}
			}
		}
        else if (prop->name == token[TOKEN_HEIGHT])
		{
            // Property: height
            if(passValidateProperty(compiler, prop, token[TOKEN_HEIGHT], VAL_REAL))
            {
                Real val = 0.0f;
                if(getReal(prop->values.front(), &val))
                {
                    emitter->setHeight(val);
                    return true;
                }
            }
        }

		return false;
	}
	//-----------------------------------------------------------------------
    bool CylinderEmitterTranslator::translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		// No objects
		return false;
	}
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
    void CylinderEmitterWriter::write(ParticleScriptSerializer* serializer, const IElement* element)
	{
        // Cast the element to a CylinderEmitter
        const CylinderEmitter* emitter = static_cast<const CylinderEmitter*>(element);

        // Write the header of the CylinderEmitter
		serializer->writeLine(token[TOKEN_EMITTER], emitter->getEmitterType(), emitter->getName(), 8);
		serializer->writeLine("{", 8);

		// Write base attributes
		ParticleEmitterWriter::write(serializer, element);

		// Write own attributes
        if (emitter->getRadius() != CylinderEmitter::DEFAULT_RADIUS) serializer->writeLine(
			token[TOKEN_RADIUS], StringConverter::toString(emitter->getRadius()), 12);		
        if (emitter->getHeight() != CylinderEmitter::DEFAULT_HEIGHT) serializer->writeLine(
			token[TOKEN_HEIGHT], StringConverter::toString(emitter->getHeight()), 12);


		// Write the close bracket
		serializer->writeLine("}", 8);
	}

}
