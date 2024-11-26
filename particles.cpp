#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <thread>

// Particle structure
struct Particle {
    float x, y;       // Position
    float vx, vy;     // Velocity
    float ax, ay;     // Acceleration
};

// Screen dimensions
const int WIDTH = 80;
const int HEIGHT = 20;

// Gravity constant
const float GRAVITY = 0.1f;

// Time step
const float DELTA_TIME = 0.1f;

// Function to clear the screen
void clearScreen() {
    std::cout << "\033[2J\033[1;1H"; // ANSI escape code to clear the console
}

// Function to render the particles on the screen
void render(const std::vector<Particle>& particles) {
    // Create a blank screen
    std::vector<std::string> screen(HEIGHT, std::string(WIDTH, ' '));

    for (const auto& particle : particles) {
        int px = static_cast<int>(particle.x);
        int py = static_cast<int>(particle.y);

        if (px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT) {
            screen[py][px] = '*';
        }
    }

    for (const auto& line : screen) {
        std::cout << line << std::endl;
    }
}

// Function to update the particles' positions
void update(std::vector<Particle>& particles) {
    for (auto& particle : particles) {
        // Apply gravity
        particle.ay = GRAVITY;

        // Update velocity
        particle.vx += particle.ax * DELTA_TIME;
        particle.vy += particle.ay * DELTA_TIME;

        // Update position
        particle.x += particle.vx * DELTA_TIME;
        particle.y += particle.vy * DELTA_TIME;

        // Bounce off the edges
        if (particle.x < 0 || particle.x >= WIDTH) {
            particle.vx *= -0.9f; // Lose some energy on collision
            particle.x = std::clamp(particle.x, 0.0f, static_cast<float>(WIDTH - 1));
        }

        if (particle.y < 0 || particle.y >= HEIGHT) {
            particle.vy *= -0.9f; // Lose some energy on collision
            particle.y = std::clamp(particle.y, 0.0f, static_cast<float>(HEIGHT - 1));
        }
    }
}

// Main function
int main() {
    std::vector<Particle> particles = {
        {10, 5, 1, 0, 0, 0},   // Particle 1
        {20, 5, -1, 0, 0, 0},  // Particle 2
        {40, 10, 0, -1, 0, 0}, // Particle 3
    };

    while (true) {
        clearScreen();
        render(particles);
        update(particles);
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Control frame rate
    }

    return 0;
}

