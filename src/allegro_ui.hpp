#ifndef ALLEGRO_UI_H_
#define ALLEGRO_UI_H_

#include <iostream>
#include <vector>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "particle.hpp"
#include "quadtree.hpp"

class Allegro_ui
{
public:
    /*****constructor*****/
    Allegro_ui();
    Allegro_ui(int w, int h);
    Allegro_ui(int w, int h, int FPS);

    /*****constants*****/
    

    /*****core functions*****/
    void drawParticles(std::vector<Particle> particles, Quadtree Q, bool drawQuadtree);
    void drawQuadtreeBoxes(Quadtree Q);
    void waitUserKeyDown();

private:
	int width;
	int height;
    int FPS;
	ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *queue;
    ALLEGRO_TIMER *timer;
    ALLEGRO_FONT *Font;
    ALLEGRO_COLOR BLANCO;
	ALLEGRO_COLOR NEGRO;
    ALLEGRO_COLOR VERDE;
    ALLEGRO_COLOR ROJO;

    void Allegro_init();
};
#endif
