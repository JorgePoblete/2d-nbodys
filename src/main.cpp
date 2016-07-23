#include <iostream>
#include <cstdlib>

#include "nbody.hpp"
#include "allegro_ui.hpp"
#include "program_options.hpp"

int main(int argc, char *argv[])
{
	Program_options po;

	po.add_option("-w","1280",po.type_data);
    po.add_option("-h","600",po.type_data);
    po.add_option("-n","0",po.type_data);
    po.add_option("-steps","10",po.type_data);
    po.add_option("-collision",po.type_flag);
    po.add_option("-mirror",po.type_flag);
    po.add_option("-bounce",po.type_flag);
    po.add_option("-G",po.type_flag);
    po.add_option("-dt","0.01f",po.type_data);
    po.add_option("-topspeed",po.type_data);
    po.add_option("-drawtree",po.type_flag);

    po.parse_args(argc,argv);

	N_Body nb(po.get_option<int>("-w"),po.get_option<int>("-h"));
	Allegro_ui aui(po.get_option<int>("-w"),po.get_option<int>("-h"));

	std::cout << "Reading bodys!" << std::endl;
	for (int i=0; i<po.get_option<int>("-n"); i++)
	{
		float x,y,m,r;
		std::cin >> x;
		std::cin >> y;
		std::cin >> m;
		std::cin >> r;
		nb.addParticle(x,y,m,r,i);
	}

	nb.useGravitationalConstant(po.is_set("-G"));
	nb.setTimeConstant(po.get_option<float>("-dt"));

	std::cout << "Starting simulation!" << std::endl;
	for (int i=0; i<po.get_option<int>("-steps"); i++)
	{
		//nb.stepBruteForce();
		nb.stepQuadtree();
		if (po.is_set("-collision"))
			nb.detectCollision();
		if (po.is_set("-mirror"))
			nb.mirrorContainer();
		if (po.is_set("-bounce"))
			nb.bounceContainer();
		if (po.is_set("-topspeed"))
			nb.topSpeed(po.get_option<float>("-topspeed"));
		aui.drawParticles(nb.getParticles(), nb.quadtree, po.is_set("-drawtree"));
	}
	std::cout << "Done!" << std::endl;
	aui.waitUserKeyDown();
	return 0;
}