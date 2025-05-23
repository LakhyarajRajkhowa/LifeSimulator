#include "Simulator.h"
#include "Random.h"
#include <iostream>
#include <set>

Simulator::Simulator() {}
Simulator::~Simulator() {}

void Simulator::run() {
    particles.resize(NUM_PARTICLES);
    initialize();
	render.create("LIFE SIMULATOR", SCREEN_WIDTH, SCREEEN_HEIGHT, 0);
    loop();
}

void Simulator::loop() {
    bool running = true;
    Color color;
    color.r = 255;
    color.g = 0;
    color.b = 0;

    while (running) {
        handleInputs(running);

        update();
        render.render();
        for (int i = 0; i < NUM_PARTICLES; i++) {
            render.renderParticle(particles[i].x, particles[i].y, particles[i].color);
        } 
        render.present();
    }
    render.destroy();
}
void Simulator::handleInputs(bool& running)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            running = false;
       
    }
}
void Simulator::update() {
    //update velocities
    for (int i = 0; i < NUM_PARTICLES; i++) {
        float totalForceX = 0;
        float totalForceY = 0;
        float totalForceZ = 0;


        for (int j = 0; j < NUM_PARTICLES; j++) {
            if (j == 1) continue;
            const float rx = (particles[j].x - particles[i].x) / SCREEN_WIDTH;
            const float ry = (particles[j].y - particles[i].y) / SCREEEN_HEIGHT;
            const float rz = (particles[j].y - particles[i].y) / SCREEEN_HEIGHT;

            const float r = pow((rx * rx + ry * ry + rz * rz), 0.5);
           
            if (r > 0 && r <= rMax) {
                const float f = force(r / rMax, matrix[particles[i].type][particles[j].type]);
               // std::cout << f << " ";
                totalForceX += rx / r * f;
                totalForceY += ry / r * f;
                totalForceZ += rz / r * f;


            }
        }

        totalForceX *= rMax * forceFactor;
        totalForceY *= rMax * forceFactor;
        totalForceZ *= rMax * forceFactor;


        particles[i].vx *= frictionFactor;
        particles[i].vy *= frictionFactor;
        particles[i].vz *= frictionFactor;


        particles[i].vx += totalForceX * dt;
        particles[i].vy += totalForceY * dt;
        particles[i].vz += totalForceY * dt;



        //update positions
        for (int i = 0; i < NUM_PARTICLES; i++) {
            particles[i].x += particles[i].vx * dt;
            particles[i].y += particles[i].vy * dt;
            particles[i].z += particles[i].vz * dt;


            //boundary collision
            if (particles[i].x < 0 || particles[i].x > SCREEN_WIDTH) particles[i].vx = -particles[i].vx;   
            if (particles[i].y < 0 || particles[i].y > SCREEEN_HEIGHT) particles[i].vy = -particles[i].vy;

           
        }

    }
}
void Simulator::initialize() {

    for (int i = 0; i < NUM_PARTICLES; i++) {
        particles[i].x = Random::getRandomInt(0, SCREEN_WIDTH);
        particles[i].y = Random::getRandomInt(0, SCREEEN_HEIGHT);
        particles[i].z = Random::getRandomInt(0, SCREEEN_HEIGHT);

        particles[i].vx = 0;
        particles[i].vy = 0;
        particles[i].vz = 0;


        Uint8 colors = (Random::getRandomInt(100, 255) / (255/m)) ;
       

        particles[i].type = (int)colors;
        
        particles[i].color.r = colors * 3 * (255 / m);
        particles[i].color.g = colors * 2 * (255 / m);
        particles[i].color.b = colors * 1 * (255 / m);


    }
    matrix.resize(m);
    matrix = Random::makeRandomMatrix(m + 1);
    /*for (int i = 0; i < NUM_PARTICLES; i++) {
        std::cout << particles[i].type << std::endl;
    }*/
    
}

float Simulator::force(float r, int a) {

    if (r < beta)
        return (r / beta) - 1;
    else if (beta <= r && r < 1)
        return a * (1 - (abs(2 * r - 1 - beta) / (1 - beta)));
    else
        return 0;
    }

