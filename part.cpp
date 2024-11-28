#include<iostream>
#include<vector>
#include<algorithm>
#include<thread>
#include<chrono>

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
        int px = static_cast<int>(particle.x);
        int py = static_cast<int>(particle.y);

        if (px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT){
            screen[py][px] = '*';
        }
    }

    for (const auto& line : screen) {
        cout << line << endl;
    }
}

void update(vector<Particle>& particles){
    for (auto& particle : particles) {
        particle.ay = GRAVITY;

        particle.vx += particle.ax * DELTA_TIME;
        particle.vy += particle.ay * DELTA_TIME;

        particle.x += particle.vx * DELTA_TIME;
        particle.y += particle.vy * DELTA_TIME;

        if (particle.x < 0 || particle.x >= WIDTH){
            particle.vx *= -0.9f;
            particle.x = clamp(particle.x, 0.0f, static_cast<float>(WIDTH - 1));
        }

        if (particle.y < 0 || particle.y >= HEIGHT) {
            particle.vy *= -0.9f;
            particle.y = clamp(particle.y, 0.0f, static_cast<float>(HEIGHT - 1));
        }
    }
}

int main() {
    vector<Particle> particles = {
        {10, 5, 1, 0, 0, 0},   // Particle 1
        {20, 5, -1, 0, 0, 0},  // Particle 2
        {40, 10, 0, -1, 0, 0}, // Particle 3
    };

    while (true) {
        clearScreen();
        render(particles);
        update(particles);
        this_thread::sleep_for(chrono::milliseconds(10));
    }

    return 0;
}