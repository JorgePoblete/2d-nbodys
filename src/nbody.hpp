#ifndef N_BODY_H_
#define N_BODY_H_

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <omp.h>
#include "particle.hpp"
#include "quadtree.hpp"

class N_Body
{
public:
    /*****constructor*****/
    N_Body(int x, int y);

    /*****constants*****/
    static const float DT;
    static const float G;

    /*****variables*****/
    Quadtree quadtree;

    /*****core functions*****/
    void addParticle(float x, float y, int id);
    void addParticle(float x, float y, float m, float r, int id);
    void stepBruteForce();
    void stepQuadtree();
    void detectCollision();
    void mirrorContainer();
    void bounceContainer();
    void topSpeed(float speed);
    void useGravitationalConstant(bool use);
    void setTimeConstant(float dt);
    std::vector<Particle> getParticles();
    
private:
    int x;
    int y;
    float g;
    float dt;
    std::vector<Particle> Particles;
};
#endif