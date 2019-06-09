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
    
    DoubleTexture2D grid;
    
    glProgram solver;
    glProgram splatter;
    glProgram drawer;
    
    int width;
    int height;
    
    GLuint vao[1];
    GLuint vbo[1];
    
    void solve();
    
    int points;
    
public:
        
    inline void clear() {
        grid.clear();
    }
    
    void initialize(int w, int h) {
        width = w;
        height = h;
        
        points = width * height;
        
        grid.initialize(GL_LINEAR);
        grid.image(GL_RG32F, GL_RG, width, height, GL_FLOAT, 0);
        
        clear();
        
        splatter.initialize_with_header("pass.vs", "splat.fs", "common.glsl");
        drawer.initialize_with_header("pass.vs", "draw.fs", "common.glsl");
        solver.initialize_with_header("pass.vs", "solver.fs", "common.glsl");
        
        glGenVertexArrays(1, vao);
        glGenBuffers(1, vbo);
        
        glBindVertexArray(vao[0]);
        
        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(baseQuad), baseQuad, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);
    }
    
    void destory() {
        grid.destory();

        destoryPrograms({&splatter, &drawer, &solver});
        
        glDeleteVertexArrays(2, vao);
        glDeleteBuffers(2, vbo);
    }
    
    inline void blit(GLuint fbo, int x, int y, int w, int h) {
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glBindVertexArray(vao[0]);
        glViewport(x, y, w, h);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    
    inline void blit(GLuint fbo) {
        blit(fbo, 0, 0, width, height);
    }
    
    void splat(const vec2& p, float power);
    
    void step(float dt) {
        grid[0].bind();
        grid[1].bind();
        
        solver.bind();
        solver.uniform1i("T", grid[1].id);
        solver.uniform2f("invSize", 1.0f/(float)width, 1.0f/(float)height);
        solver.uniform1f("dt", dt);
        
        blit(grid[0].fbo);
        
        grid.swap();
        
        reset_texture_count;
    }
    
    inline void step(float dt, int its) {
        float _dt = dt / (float) its;
        for(int i = 0; i < its; ++i)
            step(_dt);
    }
    
    void draw(GLuint target, const Frame& frame);
};

#endif /* World_hpp */
