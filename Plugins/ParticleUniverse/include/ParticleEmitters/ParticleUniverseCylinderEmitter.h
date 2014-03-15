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

#ifndef __PU_CYLINDER_EMITTER_H__
#define __PU_CYLINDER_EMITTER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseSystem.h"
#include "ParticleUniverseEmitter.h"

namespace ParticleUniverse
{
    /** The CylinderEmitter is a ParticleEmitter that emits particles on a cylinder shape. Particle can be emitted
        random on the cylinder, but it can also follow the cylinders' contours.
    */
    class _ParticleUniverseExport CylinderEmitter : public ParticleEmitter
	{
        protected:
            Real mRadius;
            Real mHeight;
			Real mX;
            Real mY;
            Real mZ;
			Quaternion mOrientation;
			Vector3 mNormal;

		public:
			// Constants
			static const Real DEFAULT_RADIUS;
            static const Real DEFAULT_HEIGHT;

            CylinderEmitter(void);
            virtual ~CylinderEmitter(void) {};

			/** 
	        */
			const Real getRadius(void) const;
			void setRadius(const Real radius);

            /**
            */
            const Real getHeight(void) const;
            void setHeight(const Real height);


			/* 
			*/ 
			const Quaternion& getOrientation(void) const;
			/** See ParticleEmiter
	        */
			void _notifyStart(void);

            /** Determine a particle position on the cylinder.
	        */
			virtual void _initParticlePosition(Particle* particle);

			/** Determine the particle direction.
	        */
			virtual void _initParticleDirection(Particle* particle);

			/** 
	        */
			virtual void copyAttributesTo (ParticleEmitter* emitter);
	};

}
#endif
