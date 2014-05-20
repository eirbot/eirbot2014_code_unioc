#include "avoidance.hpp"
#include "rds.hpp"
#include "devices.hpp"
#include "trajectory.hpp"

World<WORLD_SIZE, AABB> world;
Astar astar(42, world);

void avoidance_init(void) {
  fill_world(world);
}

bool avoidance_goto(const Vect<2, s32>& target) {
  Vect<2, s32> *path;
  io << "begin avoidance\n";

  check_for_collision();
  path = astar.getTrajectory(pos.getValue(), (Vect<2, s32>)target);

  io << "going from : " << pos.getValue()[0] << " " << pos.getValue()[1] << " to " << target[0] << " " << target[1] << "\n";

  if (! astar.isPathEnded()) {
    io << "failed to find path\n";
    return false;
  }
  io << "path length " << astar.getPathLengh() << "\n";
  for (uint8_t i = astar.getPathLengh(); i>0; i--) {
    io << "goto " << path[i-1].coord(0) << " " << path[i-1].coord(1) << "...\n";
    traj.gotoPosition(path[i-1]);
    while(!traj.isEnded()) {
      if (update_world()) {
	io << "DETECTED !\n";
	// Faire le traitement qu'on a vu avec les doubles segments par trajectoire + cercle robot par rotation.
	//TEST AVEC COLLISION SUR SEGMENTS QUI ENCADRENT LA TRAJECTOIRE /!\ A placer dans un autre fichier ... ?
	// s32 my_x, my_y, x1, y1, x2, y2, dx, dy;
	// Segment seg1, seg2;
	// my_x = pos.getValue().coord(0);
	// my_y = pos.getValue().coord(1);
	// //on teste sur le segment (robot)->(prochain check point)
	// dx = path[i-1].coord(0) - my_x;
	// dy = path[i-1].coord(1) - my_y;
	// x1 = my_x - dy;
	// y1 = my_y + dx;
	// x2 = path[i-1].coord(0) - dy;
	// y2 = path[i-1].coord(1) + dx;
	// seg1 = Segment(x1, y1, x2, y2);
	// world.addShape(&seg1);
	// seg1 = Segment(x1, y1, x2, y2);

       	return false;
      }
    }
  }

  io << "DONE !\n";
  return true;
}
