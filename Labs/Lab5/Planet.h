#ifndef PLANET_H
#define PLANET_H

class Planet {
public:
	bool activated;
	bool flag_deactivate;
	double x, y;
	int mass;

	double vx, vy; // Velocity vector
	double ax, ay; // Acceleration vector

	int uid; // Same as the index in the array.

	Planet() : activated(false),flag_deactivate(false),x(0),y(0),mass(1),vx(0),vy(0),ax(0),ay(0),uid(-1){

	}

	/**
	* If collision occurs, deactivate
	*/
	void determine_collision();

	void update_acceleration();

	void update_velocity();

	void update_displacement();
};

#endif