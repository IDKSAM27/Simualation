#include<iostream>
#include<vector>

using namespace std;

struct Particle {
    float x, y;
    float vx, vy;
    float ax, ay;
};

const int WIDTH = 80;
const int HEIGHT = 20;

const float GRAVITY = 0.1f;

const float DELTA_TIME = 0.1f;

void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

void render(const vector<Particle>& particles) {
   vector<string> screen(HEIGHT, string(WIDTH, ' ')); 

   for(const auto& particle : particles) {

}