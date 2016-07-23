#ifndef PARTICLE_H_
#define PARTICLE_H_

class Particle
{
public:
    float x;
    float y;
    float vx;
    float vy;
    float m;    
    float r;
    int id;
    Particle(float x, float y, int id)
    {
    	this->x = x;
    	this->y = y;
    	this->vx = 0.0;
    	this->vy = 0.0;
        this->m = 1.0;
        this->r = 1.0;
        this->id = id;
    }
    Particle(float x, float y, float m, float r, int id)
    {
        this->x = x;
        this->y = y;
        this->vx = 0.0;
        this->vy = 0.0;
        this->m = m;
        this->r = r;
        this->id = id;
    }
};

#endif