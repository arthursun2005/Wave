//
//  World.cpp
//  Wave
//
//  Created by Arthur Sun on 6/8/19.
//  Copyright © 2019 Arthur Sun. All rights reserved.
//

#include "World.hpp"

void World::draw(GLuint target, const Frame& frame) {
    weights[1].bind();
    
    drawer.bind();
    drawer.uniform1i("T", weights[1].id);
    drawer.uniform2f("invSize", 1.0f/(float)frame.w, 1.0f/(float)frame.h);
    
    blit0(target, frame.x, frame.y, frame.w, frame.h);
    
    reset_texture_count;
}

void World::splat(const vec2& p, float power) {
    weights[0].bind();
    weights[1].bind();
    
    splatter.bind();
    splatter.uniform1i("T", weights[1].id);
    splatter.uniform2f("p", (p.x * 0.5f + 0.5f) * width, (p.y * 0.5f + 0.5f) * height);
    splatter.uniform1f("power", power);
    splatter.uniform1f("dir", 0.0f);
    
    blit0(weights[0].fbo);
    
    weights.swap();
    
    reset_texture_count;
    
    velocities[0].bind();
    velocities[1].bind();
    
    splatter.uniform1i("T", velocities[1].id);
    splatter.uniform1f("dir", 1.0f);
    splatter.uniform1f("power", power);
    
    blit0(velocities[0].fbo);
    
    velocities.swap();
    
    reset_texture_count;
}

void World::solve() {
}

void World::advect(float dt) {
    glPointSize(1.0f);
    
    glEnable(GL_BLEND);
    
    weights[0].bind();
    weights[1].bind();
    velocities[1].bind();
    
    advector.bind();
    advector.uniform1i("T", weights[1].id);
    advector.uniform1i("V", velocities[1].id);
    advector.uniform2f("size", width, height);
    advector.uniform1f("dt", dt);
    
    weights[0].clear();
    advect(weights[0].fbo);
    
    weights.swap();
    
    reset_texture_count;
    
    
    
    velocities[0].bind();
    velocities[1].bind();
    
    advector.bind();
    advector.uniform1i("T", velocities[1].id);
    advector.uniform1i("V", velocities[1].id);
    
    velocities[0].clear();
    advect(velocities[0].fbo);
    
    velocities.swap();
    
    reset_texture_count;
    
    glDisable(GL_BLEND);
}

void World::advect2(float dt) {
    weights[0].bind();
    weights[1].bind();
    velocities[1].bind();
    
    advector2.bind();
    advector2.uniform1i("T", weights[1].id);
    advector2.uniform1i("V", velocities[1].id);
    advector2.uniform2f("invSize", 1.0f/(float)width, 1.0f/(float)height);
    advector2.uniform1f("dt", dt);
    
    advect2(weights[0].fbo);
    
    weights.swap();
    
    reset_texture_count;
    
    
    
    velocities[0].bind();
    velocities[1].bind();
    
    advector2.bind();
    advector2.uniform1i("T", velocities[1].id);
    advector2.uniform1i("V", velocities[1].id);
    
    advect2(velocities[0].fbo);
    
    velocities.swap();
    
    reset_texture_count;
}
