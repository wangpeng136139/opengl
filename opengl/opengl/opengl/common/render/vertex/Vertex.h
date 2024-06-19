#ifndef UNTITLED_VERTEX_VERTEX_H
#define UNTITLED_VERTEX_VERTEX_H
#include <glm/glm.hpp>
struct Vertex
{
    glm::vec3 pos_;
    glm::vec4 color_;
    glm::vec2 uv_;
    glm::vec3 normal_;
    Vertex()
    {

    }
    // ¹¹Ôìº¯Êý
    Vertex(glm::vec3 pos, glm::vec4 color, glm::vec2 uv, glm::vec3 normal)
        : pos_(pos), color_(color), uv_(uv), normal_(normal) {}

    Vertex(glm::vec3 pos, glm::vec4 color, glm::vec2 uv)
        : pos_(pos), color_(color), uv_(uv) {
        normal_ = glm::vec3(0,0,0);
    }
};
#endif