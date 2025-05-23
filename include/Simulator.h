#pragma once

#include "Render.h"
#include "Particle.h"
#include <cmath>
#include <vector>

const int SCREEN_WIDTH = 800;
const int SCREEEN_HEIGHT = 600;

const int NUM_PARTICLES = 500;
const float dt = 0.015;
const float frictionHalfLife = 0.040;
const float rMax = 0.2;
const int m = 6;
const float beta = 0.3;
const float frictionFactor = pow(0.5, dt / frictionHalfLife);
const float forceFactor = 20;




class Simulator
{
public:
	Simulator();
	~Simulator();

	void run();
	void handleInputs(bool &running);
	void update();
	void loop();
	void initialize();
	float force(float r, int a);

private:
	Render render;
	std::vector<Particle> particles;
	std::vector<std::vector<int>> matrix;

};

