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

// Digital Differential Analyzer
// Time complexity: O(max(dx, dy)) 
// Space complexity: 0(1)  
void LineDDA(int xa, int ya, int xb, int yb) {
    int dx = xb - xa;
    int dy = yb - ya;

    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float xIncr = dx / (float)steps;
    float yIncr = dy / (float)steps;

    float x = xa;
    float y = ya;
    for (int i = 0; i <= steps; ++i) {
        setpixel(round(x), round(y));
        x += xIncr;
        y += yIncr;
    }
}

void Bresenham(int xa, int ya, int xb, int yb) {
    int dx = xb - xa;
    int dy = yb - ya;

    float m = dy / (float)dx;

    if (m < 1) {
        int parameter = 2*dy - dx;
        int x = xa;
        int y = ya;

        if (dx < 0) {
            x = xb;
            y = yb;
            xb = xa;
        }
        setpixel(x, y);
        
        while (x < xb) {
            if (parameter >= 0) {
                x += 1;
                y += 1;
                parameter = parameter + 2*dy - 2*dx;
            }
            else {
                x += 1;
                parameter = parameter + 2*dy;
            }
            setpixel(x, y);
        }
    }
    else if (m > 1) {
        int parameter = 2*dx - dy;
        int x = xa;
        int y = ya;

        if (dy < 0) {
            x = xb;
            y = yb;
            yb = ya;
        }
        setpixel(x, y);

        while (y < yb) {
            if (parameter >= 0) {
                x += 1;
                y += 1;
                parameter = parameter + 2*dx - 2*dy;
            }
            else {
                y += 1;
                parameter = parameter + 2*dx;
            }
            setpixel(x, y);
        }
    }
    else {
        int x = xa;
        int y = ya;
        setpixel(x, y);

        while (x < xb) {
            x += 1;
            y += 1;
            setpixel(x, y);
        }
    }
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(1.0, 0.0, 0.0);
}

// Display 
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    Bresenham(10, 10, 40, 80);
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
