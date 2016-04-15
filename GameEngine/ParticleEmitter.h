#pragma once

#include <vector>
#include "Vector2f.h"
#include "Sprite.h"

namespace Moo
{
	class Particle
	{
	public:
		Particle() { }
		~Particle() {}
	private:
		Moo::Vector2f _direction;
		Moo::Vector2f _position;
		Moo::Vector2f _velocity;
		int _size;
		bool _enabled;
		int _lifeTime; //nb frame
		//Moo::Sprite _sprite;
	};

	class ParticleEmitter
	{
	public:
		ParticleEmitter(int nb) {}
		~ParticleEmitter() {}

		void emit(int nb) {}
		void clearParticles() {}
		std::list<Particle> getParticles() { return _particles; }

	private:
		std::list<Particle> _particles;
	};
}