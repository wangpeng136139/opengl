#ifndef UNTITLED_RENDER_BASE_HEAD_H
#define UNTITLED_RENDER_BASE_HEAD_H

#define GLM_ENABLE_EXPERIMENTAL
#define GLFW_INCLUDE_NONE

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtx/transform2.hpp>
#include<glm/gtx/euler_angles.hpp>
#include <string>
#include <vector>
#include <unordered_map>
#include <spscqueue/include/rigtorp/SPSCQueue.h>
#include <fstream>
#include <functional>
#include "freetype/ftglyph.h"

#include <fstream>
#include <iostream>
#include "timetool/stopwatch.h"
#include "common/Debug.h"
#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_utils.hpp"
#include <rttr/registration>
#include <rttr/type>
#include "render/vertex/Vertex.h"
#include <easy/profiler.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#endif