#pragma once

#include <algorithm>
#include <glm/glm.hpp>
#include "Object.h"

namespace s2d
{

	struct Particle
	{
		glm::vec2 position, velocity;
		float life;
		float scale;
		bool alive;
		Particle() : position(0.0f), velocity(0.0f), life(1.0f), scale(10.0f), alive(true) {}
	};

	class ParticleGenerator : public s2d::Object
	{

	public:

		bool active = true;
		std::vector<Particle> particles;

		ParticleGenerator(
			float x,
			float y,
			float scale,
			unsigned int amount,
			float duration
		)
		{
			move(x, y);
			this->scale = scale;
			this->size = glm::vec2(1.0f);
			this->amount = amount;
			this->duration = duration;

			renderType = PARTICLE;
			init();
		}

		~ParticleGenerator()
		{

		}

		void update(float dt)
		{
			// update particle duration
			duration -= dt;
			if (duration < 0 && active)
				active = false;

			// update all particles
			for (unsigned int i = 0; i < getNParticles(); ++i)
			{
				Particle& p = particles[i];
				if (p.alive)
					p.life -= dt; // reduce life
				if (p.life > 0.0f)
				{	// particle is alive, thus update
					p.position -= p.velocity * dt;
				}
				else if (active)
				{
					// reset particle attributes
					p = createParticle();
				}
				else
				{
					// remove particle
					particles.erase(particles.begin() + i);
				}
			}

		}

		unsigned int getNParticles()
		{
			return (unsigned int) particles.size();
		}

	private:

		// state
		unsigned int amount = 0;
		float duration = 1.0f;
		float scale = 1.0f;

		Particle createParticle()
		{
			Particle p;
			p.position = glm::vec2(0.0f);
			p.scale = scale;
			// random float between -1 and 1
			float velX = -1.f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2));
			float velY = -1.f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2));
			float life = 0.5f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2.5));
			p.velocity = glm::vec2(100.0f * velX, 100.0f * velY);
			p.life = life;
			return p;
		}

		void init()
		{
			for (unsigned int i = 0; i < this->amount; ++i)
				particles.push_back(createParticle());
		}

	};

}
