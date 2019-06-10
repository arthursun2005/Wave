//
//  main.cpp
//  Wave
//
//  Created by Arthur Sun on 6/8/19.
//  Copyright © 2019 Arthur Sun. All rights reserved.
//

#include <iostream>
#include "World.hpp"

GLFWwindow *window;
World world;

double mouseX, mouseY;
double pmouseX = mouseX, pmouseY = mouseY;
int width = 1280;
int height = 840;

Frame frame;

float dMouseX = 0.0f;
float dMouseY = 0.0f;

float timeBtwFrames = 0.016f;

#ifdef DEBUG

int framesPerSecond = 0;
float lastSecondTime = glfwGetTime();

#endif

#define mouse_scale 0.95f

#define scroll_scale 0.001f

void mouseCallback(GLFWwindow* window, int button, int action, int mods) {
}

inline vec2 getMouse() {
    float k = 2.0f / frame.scl;
    vec2 mouse((mouseX * 2.0f - width) * k, (mouseY * 2.0f - height) * -k);
    mouse -= frame.offset;
    return mouse;
}

inline vec2 getMouseN() {
    vec2 mouse = getMouse();
    mouse.x *= 0.5f/(float)width;
    mouse.y *= 0.5f/(float)height;
    return mouse;
}

inline void splat(float radius, float power) {
    vec2 mouse((mouseX * 2.0f - width), -(mouseY * 2.0f - height));
    mouse.x *= 1.0f/(float)width;
    mouse.y *= 1.0f/(float)height;
    world.splat(mouse, radius, power);
}

inline void block(float m, float w, float h) {
    vec2 mouse((mouseX * 2.0f - width), -(mouseY * 2.0f - height));
    mouse.x *= 1.0f/(float)width;
    mouse.y *= 1.0f/(float)height;
    world.set(mouse, w, h, m);
}

inline void level(float e, float w, float h) {
    vec2 mouse((mouseX * 2.0f - width), -(mouseY * 2.0f - height));
    mouse.x *= 1.0f/(float)width;
    mouse.y *= 1.0f/(float)height;
    world.setLevel(mouse, w, h, e);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(action == GLFW_RELEASE) {
        if(key == GLFW_KEY_A) {
            splat(2000.0f, 1000.0f);
        }
        
        if(key == GLFW_KEY_P) {
            splat(0.1f, FLT_MAX);
        }
        
        if(key == GLFW_KEY_R) {
            world.reset();
        }
        
        if(key == GLFW_KEY_C) {
            world.clear();
        }
        
        if(key == GLFW_KEY_M) {
            world.clearMedium();
        }
        
        float gap = 0.01f;
        float off = 0.02f;
        
        if(key == GLFW_KEY_T) {
            for(float x = -1.0f; x <= 1.0f; x += gap * 2.0f) {
                world.set(vec2(x, off), gap * 0.25f, 1.0f, 0.0f);
            }
            
            for(float x = -1.0f; x <= 1.0f; x += gap * 2.0f) {
                world.set(vec2(x, -off), gap * 0.25f, 1.0f, 0.0f);
            }
        }
    }
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    frame.scl *= exp(yoffset * scroll_scale);
}

void resizeCallback(GLFWwindow* window, int w, int h)
{
    width = w;
    height = h;
    frame.w = width * 2;
    frame.h = height * 2;
}

int main(int argc, const char * argv[]) {
    srand((unsigned int)time(0));
    
    if(!glfwInit())
        return EXIT_FAILURE;
    
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    
    window = glfwCreateWindow(width, height, "Wave", NULL, NULL);
    
    glfwMakeContextCurrent(window);
    
    glewInit();
    
    const unsigned char* version = glGetString(GL_VERSION);
    
    printf("%s\n", version);
    
    glfwSetMouseButtonCallback(window, mouseCallback);
    
    GLFWcursor* cursor = glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR);
    
    glfwSetCursor(window, cursor);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetScrollCallback(window, scrollCallback);
    glfwSetWindowSizeCallback(window, resizeCallback);
    
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_ONE, GL_ONE);
    
    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    
    mouseX = width * 0.5f;
    mouseY = height * 0.5f;
    
    frame.x = 0;
    frame.y = 0;
    frame.w = width * 2;
    frame.h = height * 2;
    frame.scl = 1.0f;
    frame.offset = vec2(0.0f, 0.0f);
    
    world.initialize(width, height);

    do {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glfwGetCursorPos(window, &mouseX, &mouseY);
        
        float currentTime = glfwGetTime();
        bool press = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
        
#ifdef DEBUG
        ++framesPerSecond;
        if(currentTime - lastSecondTime >= 1.0f) {
            printf("%f ms/frame \n", 1000.0f * (currentTime - lastSecondTime)/(float)framesPerSecond);
            framesPerSecond = 0;
            lastSecondTime = currentTime;
        }
#endif
        
        if(glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
            block(0.0f, 0.02f, 0.02f);
        }
        
        if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
            block(1.0f, 0.02f, 0.02f);
        }
        
        if(glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
            block(0.5f, 0.05f, 0.05f);
        }
        
        if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            level(0.0f, 0.2f, 0.2f);
        }
        
        if(glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
            block(0.1f, 0.05f, 0.05f);
        }
        
        if(press) {
            dMouseX = (mouseX - pmouseX);
            dMouseY = (pmouseY - mouseY);
            
            splat(60.0f, 60.0f);
        }else{
            dMouseX *= mouse_scale;
            dMouseY *= mouse_scale;
        }
        
        frame.offset.x += dMouseX * 4.0f / frame.scl;
        frame.offset.y += dMouseY * 4.0f / frame.scl;
        
        world.step(10.0f, 20);
        
        world.draw(0, frame);
    
        pmouseX = mouseX;
        pmouseY = mouseY;
        
        glfwPollEvents();
        glfwSwapBuffers(window);
        
        float finish = glfwGetTime();
        
        float ssecs = std::max(timeBtwFrames - (finish - currentTime), 0.0f);
        
        usleep(useconds_t(ssecs * 1000000.0f));
    } while (glfwWindowShouldClose(window) == GL_FALSE && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS);
    world.destory();
    glfwDestroyCursor(cursor);
    glfwTerminate();
    return EXIT_SUCCESS;
}


