//
//  common.h
//  Wave
//
//  Created by Arthur Sun on 6/8/19.
//  Copyright © 2019 Arthur Sun. All rights reserved.
//

#ifndef common_h
#define common_h

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>

struct vec2
{
    float x;
    float y;
    
    inline vec2() {}
    
    inline vec2(float x, float y) : x(x), y(y) {}
    
    inline vec2& operator -= (const vec2& v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }
    
    inline vec2& operator += (const vec2& v) {
        x += v.x;
        y += v.y;
        return *this;
    }
    
    inline vec2 operator - () const {
        return vec2(-x, -y);
    }
    
    inline vec2 T () const {
        return vec2(x, -y);
    }
    
    inline vec2 I () const {
        return vec2(y, -x);
    }
    
    inline vec2 norm () const {
        float l = sqrtf(lengthSq());
        return vec2(x/l, y/l);
    }
    
    inline float lengthSq() const {
        return x * x + y * y;
    }
};

inline vec2 operator + (const vec2& a, const vec2& b) {
    return vec2(a.x + b.x, a.y + b.y);
}

inline vec2 operator - (const vec2& a, const vec2& b) {
    return vec2(a.x - b.x, a.y - b.y);
}

inline vec2 operator * (float a, const vec2& b) {
    return vec2(a * b.x, a * b.y);
}

inline vec2 operator * (const vec2& a, const vec2& b) {
    return vec2(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
}

inline float dot (const vec2& a, const vec2& b) {
    return a.x * b.x + a.y * b.y;
}

struct Frame
{
    int x;
    int y;
    int w;
    int h;
    
    float scl;
    vec2 offset;
    
    inline Frame() {}
    
    inline Frame(int x, int y, int w, int h, float scl, const vec2& offset) : x(x), y(y), w(w), h(h), scl(scl), offset(offset) {}
};

inline int fstr(const char* file_name, std::string* str) {
    std::ifstream file;
    file.open(file_name);
    
    if(!file.is_open()) {
        printf("%s cannot be opened\n", file_name);
        return -1;
    }
    
    std::stringstream ss;
    ss << file.rdbuf();
    str->assign(ss.str());
    return 0;
}

#endif /* common_h */
