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

namespace ParticleUniverse
{
	// Constants
    const Real CylinderEmitter::DEFAULT_RADIUS = 10.0f;
    const Real CylinderEmitter::DEFAULT_HEIGHT = 1.0f;

	//-----------------------------------------------------------------------
    CylinderEmitter::CylinderEmitter(void) :
		ParticleEmitter(),
		mRadius(DEFAULT_RADIUS),
        mHeight(DEFAULT_HEIGHT),
        mOrientation(Quaternion::IDENTITY),
		mX(0.0f),
        mY(0.0f),
		mZ(0.0f)
	{
	}
	//-----------------------------------------------------------------------
    const Real CylinderEmitter::getRadius(void) const
	{
		return mRadius;
	}
	//-----------------------------------------------------------------------
    void CylinderEmitter::setRadius(const Real radius)
	{
        mRadius = radius;
    }

    //-----------------------------------------------------------------------
    const Real CylinderEmitter::getHeight() const
    {
        return mHeight;
    }

    //-----------------------------------------------------------------------
    void CylinderEmitter::setHeight(const Real height)
    {
        mHeight = height;
    }

	//-----------------------------------------------------------------------
    const Quaternion& CylinderEmitter::getOrientation(void) const
	{
		return mOrientation;
	}

	//-----------------------------------------------------------------------
    void CylinderEmitter::_notifyStart (void)
	{
		// Reset the attributes to allow a restart.
		ParticleEmitter::_notifyStart();
	}
	//----------------------------------------------------------------------- 
    void CylinderEmitter::_initParticlePosition(Particle* particle)
    {
		Real angle = Math::RangeRandom(0, Math::TWO_PI);

		Real factor = Math::SymmetricRandom();

		mX = Math::Cos(angle) * factor;
		mY = Math::SymmetricRandom();
		mZ = Math::Sin(angle) *  factor;

		ParticleSystem* sys = mParentTechnique->getParentSystem();
		if (sys)
		{
			particle->position = getDerivedPosition() + 
				sys->getDerivedOrientation() * mOrientation * (_mEmitterScale * Vector3(mX * mRadius, mY * mHeight, mZ * mRadius));
		}
		else
		{
			particle->position = getDerivedPosition() + _mEmitterScale * ( mOrientation * Vector3(mX * mRadius, mY * mHeight, mZ * mRadius));
		}
		particle->originalPosition = particle->position;

	}
	//-----------------------------------------------------------------------
    void CylinderEmitter::_initParticleDirection(Particle* particle)
    {
		if (mAutoDirection)
		{
			// The value of the direction vector that has been set does not have a meaning for
            // the cylinder emitter.
			Radian angle;
			_generateAngle(angle);
			if (angle != Radian(0))
			{
				particle->direction = (mOrientation * Vector3(mX, 0, mZ) ).randomDeviant(angle, mUpVector);
				particle->originalDirection = particle->direction;
			}
			else
			{
				particle->direction = Vector3(mX, 0, mZ);
				particle->direction = mOrientation * Vector3(mX, 0, mZ);
			}
		}
		else
		{
			// Use the standard way
			ParticleEmitter::_initParticleDirection(particle);
		}
    }
	//-----------------------------------------------------------------------
    void CylinderEmitter::copyAttributesTo (ParticleEmitter* emitter)
	{
		ParticleEmitter::copyAttributesTo(emitter);

        CylinderEmitter* cylinderEmitter = static_cast<CylinderEmitter*>(emitter);
        cylinderEmitter->mRadius = mRadius;
        cylinderEmitter->mHeight = mHeight;
        cylinderEmitter->mOrientation = mOrientation;
	}
}
