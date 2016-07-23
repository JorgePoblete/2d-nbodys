#ifndef QUADTREE_H_
#define QUADTREE_H_

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <omp.h>
#include "particle.hpp"

class Quadtree
{
public:
    /*****constructor*****/
    Quadtree();
    Quadtree(std::vector<Particle> Particles, float x1, float x2, float y1, float y2, int maxSubTree);

    /*****constants*****/

    /*****variables*****/
    float mass;
    float cm_x;
    float cm_y;
    float cm_z;

    float x1;
    float x2; 
    float y1;
    float y2;

    static int subNodes;

    std::vector<Quadtree> Quadrants;

    /*****core functions*****/
    void makeQuadtree(std::vector<Particle> Particles, float x1, float x2, float y1, float y2, int maxSubTree);
    void computeForce(Particle &p, float G, float dt);
    void computeCollision(Particle &p);
    void reset();
private:
    std::vector<Particle> Particles;
};
#endif