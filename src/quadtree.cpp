#include "quadtree.hpp"

int Quadtree::subNodes;

Quadtree::Quadtree(){}

Quadtree::Quadtree(std::vector<Particle> Particles, float x1, float x2, float y1, float y2, int maxSubTree)
{
	makeQuadtree(Particles,x1,x2,y1,y2,maxSubTree);
}

void Quadtree::makeQuadtree(std::vector<Particle> Particles, float x1, float x2, float y1, float y2, int maxSubTree)
{
	this->subNodes++;
	this->mass = 0.0f;
	this->cm_x = 0.0f;
	this->cm_y = 0.0f;	
	this->x1 = x1;
	this->x2 = x2;
	this->y1 = y1;
	this->y2 = y2;
	for (unsigned i=0; i<Particles.size(); i++)
	{
		Particle A = Particles[i];
		//is A in this quadrant?
		if (A.x >= x1 && A.x <= x2 &&
			A.y >= y1 && A.y <= y2)
		{
			this->Particles.push_back(A);
			this->mass += A.m;
			this->cm_x += A.m*A.x;
			this->cm_y += A.m*A.y;
		}
	}
	this->cm_x /= this->mass;
	this->cm_y /= this->mass;

	//if this quadrant has more than 1 particle, it must be subdivided
	if (this->Particles.size() > 3 && maxSubTree > 0)
	{
		//calc of the medium point on each axis
		float mx = (x1+x2)/2;
		float my = (y1+y2)/2;

		//create the eight sub Quadrants
		//and send the particles that are contained in this quadrant
		Quadrants.push_back(Quadtree(this->Particles,x1,mx,y1,my,maxSubTree-1));
		Quadrants.push_back(Quadtree(this->Particles,mx,x2,y1,my,maxSubTree-1));
		Quadrants.push_back(Quadtree(this->Particles,mx,x2,my,y2,maxSubTree-1));
		Quadrants.push_back(Quadtree(this->Particles,x1,mx,my,y2,maxSubTree-1));
	}
}

void Quadtree::computeForce(Particle &p, float G, float dt)
{
	//if this quadrant has no points then it makes no force
	if (Particles.size() == 0) return;

	//ratio between the particle and the center of mass of this quadrant
	float r = sqrtf(powf(cm_x-p.x,2)+powf(cm_y-p.y,2));

	//if r = 0 then this quadrant only have the same particle
	if (r == 0.0) return;

	//width of this quadrant
	float w = ((x2-x1)+(y2-y1))/2;

	//if width/ratio < value then this quadrant is far enough from the particle and we can use
	//its center of mass and total mass for the force calculation
	if (w/r < 0.5)	
	{

		float dx = cm_x - p.x;
		float dy = cm_y - p.y;
		float drSquared = (dx*dx) + (dy*dy);
		float m1m2 = p.m*mass;
		float dr2 = powf(sqrtf(drSquared),2);
		
		float F = (G*m1m2)/dr2;
		p.vx += dt*F*dx; p.vy += dt*F*dy;
	}
	//else this quadrant is close enough to the particle, so we must calculate the force of each sub-quadrant
	else 
	{
		//if this is a leaf compute force agains particles contained in this leaf
		if (Quadrants.size() == 0)
		{
			float Fx = 0.0f, Fy = 0.0f;
			for (unsigned i = 0; i < Particles.size(); i++)
			{
				if (p.id != Particles[i].id)
				{
					float dx = Particles[i].x - p.x;
					float dy = Particles[i].y - p.y;
					float drSquared = (dx*dx) + (dy*dy);
					float m1m2 = p.m*Particles[i].m;
					float dr2 = powf(sqrtf(drSquared),2);
					
					float F = (G*m1m2)/dr2;
					Fx += dx *F; Fy += dy *F;
				}
			}	
			p.vx += dt*Fx; p.vy += dt*Fy;
		}
		//else compute force on his sub quadrants
		else
		{
			for (unsigned i = 0; i < Quadrants.size(); i++)
			{
				Quadrants[i].computeForce(p,G,dt);
			}
		}
	}
}

void Quadtree::computeCollision(Particle &p)
{
	//if this is a leaf
	if (Quadrants.size() == 0)
	{
		//check if the particle is from this quadrant
		if (p.x >= x1 && p.x <= x2 &&
			p.y >= y1 && p.y <= y2)
		{
			//then check for collisions with the particles of this quadrant only
			for (unsigned i=0; i<Particles.size(); i++)
			{
				Particle A = Particles[i];
				//if not the same
				if (p.id != A.id)
				{
					float xDist = (p.x-A.x)*(p.x-A.x);
					float yDist = (p.y-A.y)*(p.y-A.y);
					float squaredDist = xDist+yDist;
					float powRadious = powf(p.r+A.r,2);
					if (squaredDist < powRadious )
					{
						p.vx = (p.vx * (p.m - A.m) + (2 * A.m * A.vx)) / (p.m + A.m);
						p.vy = (p.vy * (p.m - A.m) + (2 * A.m * A.vy)) / (p.m + A.m);
					}
				}
			}
		}
		return;
	}
	//if not a leaf then check its subquadrants
	else
	{
		for (unsigned i = 0; i < Quadrants.size(); i++)
		{
			Quadrants[i].computeCollision(p);
		}	
	}
}

void Quadtree::reset()
{
	this->subNodes = 0;
	for (unsigned i = 0; i < Quadrants.size(); i++)
	{
		Quadrants[i].reset();
	}
	this->Particles.clear();
	this->Quadrants.clear();
}