#include "allegro_ui.hpp"

Allegro_ui::Allegro_ui()
{
	this->width = 640;
	this->height = 480;
	this->FPS = 60;
	Allegro_init();
}
Allegro_ui::Allegro_ui(int w, int h)
{
	this->width = w;
	this->height = h;
	this->FPS = 60;
	Allegro_init();
}
Allegro_ui::Allegro_ui(int w, int h, int FPS)
{
	this->width = w;
	this->height = h;
	this->FPS = FPS;
	Allegro_init();
}

void Allegro_ui::Allegro_init()
{
	if(!al_init()) {
    	std::cout << "failed to initialize allegro!" << std::endl;
      	exit(0);
   	} 
	al_set_new_display_flags(ALLEGRO_OPENGL); 
	display = al_create_display(this->width, this->height);
	if(!display) {
		std::cout << "failed to create display!" << std::endl;
      	exit(0);
   	}
   	if(!al_init_primitives_addon()) {
   		std::cout << "failed to initialize primitives!" << std::endl;
      	exit(0);
   	}
   	if(!al_init_font_addon()) {
   		std::cout << "failed to initialize fonts!" << std::endl;
      	exit(0);
   	}
   	if(!al_init_ttf_addon()) {
   		std::cout << "failed to initialize ttf!" << std::endl;
      	exit(0);
   	}
   	if(!al_install_keyboard()) {
   		std::cout << "failed to initialize the keyboard!" << std::endl;
      	exit(0);
   	}
   	if(!al_install_mouse()) {
   		std::cout << "failed to initialize the mouse!" << std::endl;
      	exit(0);
   	}
   	queue = al_create_event_queue();
	if(!queue) {
		std::cout << "failed to initialize the event queue!" << std::endl;
      	exit(0);		
	}
	timer = al_create_timer(1.0 / this->FPS);
   	if(!timer) {
      	std::cout << "failed to create timer!" << std::endl;
      	exit(0);
   	}
   	
   	al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));

   	al_start_timer(timer);

	//BLANCO = al_map_rgb(255,255,255);	
	BLANCO = al_map_rgb(153,204,255);	
	NEGRO = al_map_rgb(0,0,0);
	VERDE = al_map_rgb(0,255,0);
	ROJO = al_map_rgb(255,0,0);
	Font = al_load_ttf_font("verdana.ttf",9,0 );
	al_set_window_title(display, "N-Body Simulation");
	al_clear_to_color(NEGRO);
	al_flip_display();
}
void Allegro_ui::drawParticles(std::vector<Particle> particles, Quadtree Q, bool drawQuadtree)
{
	ALLEGRO_EVENT event;
	al_wait_for_event(queue, &event);

	if(event.type == ALLEGRO_EVENT_TIMER) {
		al_clear_to_color(NEGRO);
		for (unsigned i=0; i<particles.size(); i++)
		{
			al_draw_filled_circle(particles[i].x, this->height - particles[i].y, particles[i].r, BLANCO);
		}
		if (drawQuadtree) drawQuadtreeBoxes(Q);
		al_draw_text(Font, BLANCO, 5, 5,ALLEGRO_ALIGN_LEFT, ("Body count: "+std::to_string(particles.size())).c_str());
		al_draw_text(Font, BLANCO, 5, 15,ALLEGRO_ALIGN_LEFT, ("Quadtree nodes: "+std::to_string(Q.subNodes)).c_str());
		al_flip_display();
	}
}

void Allegro_ui::drawQuadtreeBoxes(Quadtree Q)
{
	al_draw_rectangle(Q.x1, this->height - Q.y1, Q.x2, this->height - Q.y2, VERDE, 1.0);
	if (Q.Quadrants.size() == 0)
	{
		return;
	}
	for (unsigned i=0; i<Q.Quadrants.size(); i++)
		drawQuadtreeBoxes(Q.Quadrants[i]);
}

void Allegro_ui::waitUserKeyDown()
{
	ALLEGRO_EVENT event;
	al_register_event_source(queue, al_get_keyboard_event_source());
  	do{
    	al_wait_for_event(queue, &event); 
	}
  	while (event.type != ALLEGRO_EVENT_KEY_DOWN);
}