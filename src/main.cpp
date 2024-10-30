#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>

const int scale = 10;

void setpixel(int x, int y) {
    glBegin(GL_QUADS);
    glVertex2i(x * scale, y * scale);
    glVertex2i(x * scale + scale, y * scale);
    glVertex2i(x * scale + scale, y * scale + scale);
    glVertex2i(x * scale, y * scale + scale);
    glEnd();
}

void LineDDA(int xa, int ya, int xb, int yb) {
    int dx = xb - xa, dy = yb - ya;
    int step;

    float x = xa, y = ya;
    float xIncr, yIncr;

    if (abs(dx) > abs(dy))
        step = abs(dx);
    else 
        step = abs(dy);

    xIncr = dx / (float)step;
    yIncr = dy / (float)step;

    setpixel(round(x), round(y));

    for (int i = 0; i < step; ++i) {
        x += xIncr;
        y += yIncr;
        setpixel(round(x), round(y));
    }
}

void Bresenham(int xa, int ya, int xb, int yb) {
    int x0 = xa, y0 = ya;

    int dx = xb - xa, dy = yb - ya;
    int constant1 = 2 * dy, constant2 = constant1 - 2 * dx;
    int p0 = constant1 - dx;

    setpixel(round(x0), round(y0));

    for (int i = 0; i < dx; ++i) {
        x0 += 1;

        if (p0 < 0) {
            p0 += constant1;
        } else {
            y0 += 1;
            p0 += constant2;
        }
        setpixel(round(x0), round(y0));
    }
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(1.0, 0.0, 0.0);
}

// Display 
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    Bresenham(10, 10, 40, 30);
    // LineDDA(10, 10, 40, 30);
    glfwSwapBuffers(glfwGetCurrentContext());
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Set window 
    GLFWwindow* window = glfwCreateWindow(1000, 1000, "Bresenham Line Drawing (Zoomed)", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    init();

    glViewport(0, 0, 500, 500);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 500, 0, 500, -1, 1);

    while (!glfwWindowShouldClose(window)) {
        display();
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
