#include "nbody.hpp"

const float N_Body::DT = 0.01f;
const float N_Body::G = 6.67408e-11f;

N_Body::N_Body(int x, int y)
{
	this->x = x;
	this->y = y;
	this->g = G;
	this->dt = DT;
}

void N_Body::addParticle(float x, float y, int id)
{
	Particles.push_back(Particle(x,y,id));
}

void N_Body::addParticle(float x, float y, float m, float r, int id)
{
	Particles.push_back(Particle(x,y,m,r,id));
}

void N_Body::stepBruteForce()
{
	#pragma omp parallel for
	for (unsigned i=0; i<Particles.size(); i++)
	{
		float Fx = 0.0f, Fy = 0.0f;

		for (unsigned j=0; j < Particles.size(); j++)
		{
			if (j != i)
			{
				float dx = Particles[j].x - Particles[i].x;
				float dy = Particles[j].y - Particles[i].y;
				float drSquared = (dx*dx) + (dy*dy);
				float m1m2 = Particles[i].m*Particles[j].m;
				float dr2 = powf(sqrtf(drSquared),2);
				float F = (g*m1m2)/dr2;
				Fx += dx *F; Fy += dy *F;
			}
		}
		Particles[i].vx += dt*Fx; Particles[i].vy += dt*Fy;
	}
	#pragma omp parallel for
	for (unsigned i=0; i<Particles.size(); i++)
	{
		Particles[i].x += Particles[i].vx*dt;
		Particles[i].y += Particles[i].vy*dt;
	}
}

void N_Body::stepQuadtree()
{
	quadtree.reset();
	quadtree.makeQuadtree(Particles,0,x,0,y,8);
	#pragma omp parallel for
	for (unsigned i=0; i<Particles.size(); i++)
	{
		quadtree.computeForce(Particles[i],g,dt);
		Particles[i].x += Particles[i].vx*dt;
		Particles[i].y += Particles[i].vy*dt;
	}
}
void N_Body::detectCollision()
{
	#pragma omp parallel for
	for (unsigned i=0; i<Particles.size(); i++)
	{
		quadtree.computeCollision(Particles[i]);
	}
}


void N_Body::mirrorContainer()
{
	#pragma omp parallel for
	for (unsigned i=0; i<Particles.size(); i++)
	{
		if (Particles[i].x >= this->x)
		{
			Particles[i].x = 0;	
		}else if (Particles[i].x <= 0)
		{
			Particles[i].x = this->x;
		}
		if (Particles[i].y >= this->y)
		{
			Particles[i].y = 0;	
		}else if (Particles[i].y <= 0)
		{
			Particles[i].y = this->y;
		}
	}
}

void N_Body::bounceContainer()
{
	#pragma omp parallel for
	for (unsigned i=0; i<Particles.size(); i++)
	{
		if (Particles[i].x >= this->x || Particles[i].x <= 0)
		{
			Particles[i].vx *= -1;	
		}
		if (Particles[i].y >= this->y || Particles[i].y <= 0)
		{
			Particles[i].vy *= -1;	
		}
	}
}

void N_Body::topSpeed(float speed)
{
	#pragma omp parallel for
	for (unsigned i=0; i<Particles.size(); i++)
	{
		if (Particles[i].vx > speed)
		{
			Particles[i].vx = speed;	
		}
		if (Particles[i].vx < -speed)
		{
			Particles[i].vx = -speed;	
		}
		if (Particles[i].vy > speed)
		{
			Particles[i].vy = speed;	
		}
		if (Particles[i].vy < -speed)
		{
			Particles[i].vy = -speed;	
		}
	}
}

void N_Body::useGravitationalConstant(bool use)
{
	if (use)
		this->g = G;
	else 
		this->g = 1.0f;
}

void N_Body::setTimeConstant(float dt)
{
	this->dt = dt;
}

std::vector<Particle> N_Body::getParticles()
{
	return Particles;
}

