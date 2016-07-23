# 2D N-Bodys Simulator 

This is a 2D Simulator of the N-Bodys problem.
It uses the [Barnes-Hut](https://en.wikipedia.org/wiki/Barnes%E2%80%93Hut_simulation) [Quadtree](https://en.wikipedia.org/wiki/Quadtree) to compute the position of the particles on each iteration with O(n log(n)) complexity and its parallelized using the OpenMP Library.

![Image of simulator](https://raw.githubusercontent.com/JorgePoblete/2d-nbodys/master/img/img2.png)

### Installation ###

This simulator uses [Allegro](http://liballeg.org/) to render the particles, so it must be installed in order to use this simulator.

Just clone or download and in a terminal run "make"

### Use ###

An example of the use of this simulator is:

> ./nbody_simulator -n 1000 -steps 2000 -dt 0.05f -drawtree < inputs/in1

### Accepted Parameters ###

This simulator also uses the **[ProgramOptions](https://github.com/JorgePoblete/program_options)** project to read the parameters through the console.

The accepted parameters are:

* "-n x"  this specifies the number of x bodies that will be readed.
* "-steps x"  this specifies the number of iterations that will be simulated.
* "-dt x"  this specifies the time between iterations, it can be used to make time faster or slower.
* "-topspeed x"  this specifies the maxium speed that a particle can reach.
*"-w x"  this specifies the width of the simulator window.
*"-h x"  this specifies the heigth of the simulator window.
* "-drawtree"  this is a flag parameter, if its used the simulator will draw the quadtree boxes around the particles.
* "-collision"  this is a flag parameter, if its used the simulator will detect and compute collisions.
* "-mirror"  this is a flag parameter, if its used the simulator will detect when a particle leaves the visible window and makes that particle to apear at the opposite site of the window.
* "-bounce"  this is a flag parameter, if its used the simulator will detect when a particle touches the borders of the simulator window and makes that particle to bounce to the opposite side.
* "-G"  this flag will set the use of the Gravitational constant in the compute of the force.
