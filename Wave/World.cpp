//
//  World.cpp
//  Wave
//
//  Created by Arthur Sun on 6/8/19.
//  Copyright © 2019 Arthur Sun. All rights reserved.
//

#include "World.hpp"

void World::draw(GLuint target, const Frame& frame) {
    grid[1].bind();
    
    drawer.bind();
    drawer.uniform1i("T", grid[1].id);
    drawer.uniform2f("invSize", 1.0f/(float)frame.w, 1.0f/(float)frame.h);
    
    blit(target, frame.x, frame.y, frame.w, frame.h);
    
    reset_texture_count;
}

void World::splat(const vec2& p, float power) {
    grid[0].bind();
    grid[1].bind();
    
    splatter.bind();
    splatter.uniform1i("T", grid[1].id);
    splatter.uniform2f("p", (p.x * 0.5f + 0.5f) * width, (p.y * 0.5f + 0.5f) * height);
    splatter.uniform1f("power", power);
    
    blit(grid[0].fbo);
    
    grid.swap();
    
    reset_texture_count;
}
