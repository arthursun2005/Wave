//
//  World.hpp
//  Wave
//
//  Created by Arthur Sun on 6/8/19.
//  Copyright © 2019 Arthur Sun. All rights reserved.
//

#ifndef World_hpp
#define World_hpp

#include "utils.h"

static const GLfloat baseQuad[] = {
    -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f
};

class World
{
    
    DoubleTexture2D weights;
    DoubleTexture2D velocities;
    
    glProgram solver;
    glProgram splatter;
    glProgram drawer;
    glProgram advector;
    glProgram advector2;
    
    int width;
    int height;
    
    GLuint vao[2];
    GLuint vbo[2];
    
    void solve();
    
    int points;
    
    void advect(GLuint target) {
        advector.uniform1i("x", 0);
        advector.uniform1i("y", 0);
        blit1(target);
        
        advector.uniform1i("x", 1);
        advector.uniform1i("y", 0);
        blit1(target);
        
        advector.uniform1i("x", 0);
        advector.uniform1i("y", 1);
        blit1(target);
        
        advector.uniform1i("x", 1);
        advector.uniform1i("y", 1);
        blit1(target);
    }
    
    void advect2(GLuint target) {
        blit0(target);
    }
    
    void advect(float dt);
    
    void advect2(float dt);
    
public:
        
    inline void clear() {
        weights.clear();
        velocities.clear();
    }
    
    void initialize(int w, int h) {
        width = w;
        height = h;
        
        points = width * height;
        
        weights.initialize(GL_LINEAR);
        weights.image(GL_R32F, GL_RED, width, height, GL_FLOAT, 0);
        
        velocities.initialize(GL_LINEAR);
        velocities.image(GL_RG32F, GL_RG, width, height, GL_FLOAT, 0);
        
        clear();
        
        splatter.initialize_with_header("pass.vs", "splat.fs", "common.glsl");
        drawer.initialize_with_header("pass.vs", "draw.fs", "common.glsl");
        advector.initialize_with_header("advect.vs", "advect.fs", "common.glsl");
        advector2.initialize_with_header("pass.vs", "advect2.fs", "common.glsl");
        
        glGenVertexArrays(2, vao);
        glGenBuffers(2, vbo);
        
        glBindVertexArray(vao[0]);
        
        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(baseQuad), baseQuad, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(0);
        
        glBindVertexArray(vao[1]);
        
        std::vector<vec2> uvs(points);
        
        for(int y = 0; y < height; ++y) {
            for(int x = 0; x < width; ++x) {
                int i = x + y * width;
                uvs[i].x = (x + 0.5f) / (float)width;
                uvs[i].y = (y + 0.5f) / (float)height;
            }
        }
        
        glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
        glBufferData(GL_ARRAY_BUFFER, points * sizeof(vec2), uvs.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);
    }
    
    void destory() {
        weights.destory();
        velocities.destory();
        
        destoryPrograms({&splatter, &drawer, &advector, &advector2});
        
        glDeleteVertexArrays(2, vao);
        glDeleteBuffers(2, vbo);
    }
    
    inline void blit0(GLuint fbo, int x, int y, int w, int h) {
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glBindVertexArray(vao[0]);
        glViewport(x, y, w, h);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    
    inline void blit0(GLuint fbo) {
        blit0(fbo, 0, 0, width, height);
    }
    
    inline void blit1(GLuint fbo) {
        blit1(fbo, 0, 0, width, height);
    }
    
    inline void blit1(GLuint fbo, int x, int y, int w, int h) {
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glBindVertexArray(vao[1]);
        glViewport(x, y, w, h);
        glDrawArrays(GL_POINTS, 0, points);
        glBindVertexArray(0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    
    void splat(const vec2& p, float power);
    
    inline void step(float dt) {
        advect(dt);
    }
    
    inline void step(float dt, int its) {
        float _dt = dt / (float) its;
        for(int i = 0; i < its; ++i)
            step(_dt);
    }
    
    void draw(GLuint target, const Frame& frame);
};

#endif /* World_hpp */
