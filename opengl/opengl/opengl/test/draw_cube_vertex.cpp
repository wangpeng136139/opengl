#include "../common/render_head.h"


using namespace std;


#ifndef UNTITLED_SHADERSOURCE_H
#define UNTITLED_SHADERSOURCE_H

//������ɫ������
static const char* vertex_shader_text_cube_vertex =
"#version 110\n"

"uniform mat4 u_mvp;\n"

"attribute  vec3 a_pos;\n"
"attribute  vec4 a_color;\n"
"attribute  vec2 a_uv;\n"

"varying vec4 v_color;\n"
"varying vec2 v_uv;\n"
"void main()\n"
"{\n"
"    gl_Position = u_mvp * vec4(a_pos, 1.0);\n"
"    v_color = a_color;\n"
"   v_uv = a_uv;\n"
"}\n";
//Ƭ����ɫ������
static const char* fragment_shader_text_cube_vertex =
"#version 110\n"
"uniform sampler2D u_diffuse_texture;\n"
"varying vec4 v_color;\n"
"varying vec2 v_uv;"
"void main()\n"
"{\n"
"    gl_FragColor = texture2D(u_diffuse_texture,v_uv);\n"
"}\n";

#endif //UNTITLED_SHADERSOURCE_H

using namespace std;



//ԭʼ��������
static const Vertex kVertexs_cube_vertex_cube_vertex[36] = {
    //Front
    {glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 0.0f)},
    {glm::vec3(1.0f, -1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 0.0f)},
    {glm::vec3(1.0f,  1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 1.0f)},

    {glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 0.0f)},
    {glm::vec3(1.0f,  1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 1.0f)},
    {glm::vec3(-1.0f,  1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 1.0f)},

    //back
    {glm::vec3(1.0f,  1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 1.0f)},
    {glm::vec3(1.0f, -1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 0.0f)},
    {glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 0.0f)},

    {glm::vec3(1.0f,  1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 1.0f)},
    {glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 0.0f)},
    {glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 1.0f)},


    //left
    {glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 1.0f)},
    {glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 0.0f)},
    {glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 0.0f)},

    {glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 1.0f)},
    {glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 0.0f)},
    {glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 1.0f)},

    //right
    {glm::vec3(1.0f, -1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 0.0f)},
    {glm::vec3(1.0f, -1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 0.0f)},
    {glm::vec3(1.0f, 1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 1.0f)},

    {glm::vec3(1.0f, -1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 0.0f)},
    {glm::vec3(1.0f, 1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 1.0f)},
    {glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 1.0f)},

    //up
    {glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 0.0f)},
    {glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 0.0f)},
    {glm::vec3(1.0f, 1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 1.0f)},

    {glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 0.0f)},
    {glm::vec3(1.0f, 1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 1.0f)},
    {glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 1.0f)},

    //down
    {glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 0.0f)},
    {glm::vec3(1.0f, -1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 0.0f)},
    {glm::vec3(1.0f, -1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 1.0f)},

    {glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 0.0f)},
    {glm::vec3(1.0f, -1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 1.0f)},
    {glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 1.0f) },
};

static const glm::vec3 kPositions_cube_vertex[36] = {
    //Front
    glm::vec3(-1.0f, -1.0f, 1.0f),
    glm::vec3(1.0f, -1.0f, 1.0f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(-1.0f, -1.0f, 1.0f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(-1.0f, 1.0f, 1.0f),
    //back
    glm::vec3(1.0f, -1.0f, -1.0f),
    glm::vec3(-1.0f, -1.0f, -1.0f),
    glm::vec3(-1.0f, 1.0f, -1.0f),
    glm::vec3(1.0f, -1.0f, -1.0f),
    glm::vec3(-1.0f, 1.0f, -1.0f),
    glm::vec3(1.0f, 1.0f, -1.0f),
    //left
    glm::vec3(-1.0f, -1.0f, -1.0f),
    glm::vec3(-1.0f, -1.0f, 1.0f),
    glm::vec3(-1.0f, 1.0f, 1.0f),
    glm::vec3(-1.0f, -1.0f, -1.0f),
    glm::vec3(-1.0f, 1.0f, 1.0f),
    glm::vec3(-1.0f, 1.0f, -1.0f),
    //right
    glm::vec3(1.0f, -1.0f, 1.0f),
    glm::vec3(1.0f, -1.0f, -1.0f),
    glm::vec3(1.0f, 1.0f, -1.0f),
    glm::vec3(1.0f, -1.0f, 1.0f),
    glm::vec3(1.0f, 1.0f, -1.0f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    //up
    glm::vec3(-1.0f, 1.0f, 1.0f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(1.0f, 1.0f, -1.0f),
    glm::vec3(-1.0f, 1.0f, 1.0f),
    glm::vec3(1.0f, 1.0f, -1.0f),
    glm::vec3(-1.0f, 1.0f, -1.0f),
    //down
    glm::vec3(-1.0f, -1.0f, -1.0f),
    glm::vec3(1.0f, -1.0f, -1.0f),
    glm::vec3(1.0f, -1.0f, 1.0f),
    glm::vec3(-1.0f, -1.0f, -1.0f),
    glm::vec3(1.0f, -1.0f, 1.0f),
    glm::vec3(-1.0f, -1.0f, 1.0f),
};

static const glm::vec4 kColors_cube_vertex[36] = {
    //Front
          glm::vec4(1, 0, 0, 1),
          glm::vec4(1, 0, 0, 1),
          glm::vec4(1, 0, 0, 1),

          glm::vec4(1, 0, 0, 1),
          glm::vec4(1, 0, 0, 1),
          glm::vec4(1, 0, 0, 1),

          //back
          glm::vec4(1, 0, 0, 1),
          glm::vec4(1, 0, 0, 1),
          glm::vec4(1, 0, 0, 1),

          glm::vec4(1, 0, 0, 1),
          glm::vec4(1, 0, 0, 1),
          glm::vec4(1, 0, 0, 1),

          //left
          glm::vec4(0, 1, 0, 1),
          glm::vec4(0, 1, 0, 1),
          glm::vec4(0, 1, 0, 1),

          glm::vec4(0, 1, 0, 1),
          glm::vec4(0, 1, 0, 1),
          glm::vec4(0, 1, 0, 1),

          //right
          glm::vec4(0, 1, 0, 1),
          glm::vec4(0, 1, 0, 1),
          glm::vec4(0, 1, 0, 1),

          glm::vec4(0, 1, 0, 1),
          glm::vec4(0, 1, 0, 1),
          glm::vec4(0, 1, 0, 1),

          //up
          glm::vec4(0, 0, 1, 1),
          glm::vec4(0, 0, 1, 1),
          glm::vec4(0, 0, 1, 1),

          glm::vec4(0, 0, 1, 1),
          glm::vec4(0, 0, 1, 1),
          glm::vec4(0, 0, 1, 1),

          //down
          glm::vec4(0, 0, 1, 1),
          glm::vec4(0, 0, 1, 1),
          glm::vec4(0, 0, 1, 1),

          glm::vec4(0, 0, 1, 1),
          glm::vec4(0, 0, 1, 1),
          glm::vec4(0, 0, 1, 1),
};

static const glm::vec2 kUvs_cube_vertex[36] =
{
    //Front
    glm::vec2(0.0f, 0.0f),
    glm::vec2(1.0f, 0.0f),
    glm::vec2(1.0f, 1.0f),

    glm::vec2(0.0f, 0.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(0.0f, 1.0f),

    //back
    glm::vec2(0.0f, 0.0f),
    glm::vec2(1.0f, 0.0f),
    glm::vec2(1.0f, 1.0f),

    glm::vec2(0.0f, 0.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(0.0f, 1.0f),

    //left
    glm::vec2(0.0f, 0.0f),
    glm::vec2(1.0f, 0.0f),
    glm::vec2(1.0f, 1.0f),

    glm::vec2(0.0f, 0.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(0.0f, 1.0f),

    //right
    glm::vec2(0.0f, 0.0f),
    glm::vec2(1.0f, 0.0f),
    glm::vec2(1.0f, 1.0f),

    glm::vec2(0.0f, 0.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(0.0f, 1.0f),

    //up
    glm::vec2(0.0f, 0.0f),
    glm::vec2(1.0f, 0.0f),
    glm::vec2(1.0f, 1.0f),

    glm::vec2(0.0f, 0.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(0.0f, 1.0f),

    //down
    glm::vec2(0.0f, 0.0f),
    glm::vec2(1.0f, 0.0f),
    glm::vec2(1.0f, 1.0f),

    glm::vec2(0.0f, 0.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(0.0f, 1.0f),
};

GLFWwindow* window_cube_vertex;
GLuint vertex_shader_cube_vertex, fragment_shader_cube_vertex, program_cube_vertex;
GLint mvp_location_cube_vertex, vpos_location_cube_vertex, vcol_location_cube_vertex, u_diffuse_texture_location_cube_vertex, a_uv_location_cube_vertex;
GLuint kVBO_cube_vertex, kEBO_cube_vertex;
Texture2D* texture2d_cube_vertex = nullptr;
//ȥ�صĶ���Vector
static vector<Vertex> kVertexRemoveDumplicateVectorv_cube_vertex;
//��������Vector
static vector<unsigned short> kVertexIndexVector_cube_vertex;

//����ȥ��
static void VertexRemoveDumplicate_cube_vertex() {
    for (int i = 0; i < 36; ++i) {
        const Vertex& vertex = kVertexs_cube_vertex_cube_vertex[i];
        //�ж϶����Ƿ����
        int index = -1;
        for (int j = 0; j < kVertexRemoveDumplicateVectorv_cube_vertex.size(); ++j) {
            if (vertex.pos_ == kVertexRemoveDumplicateVectorv_cube_vertex[j].pos_ && vertex.color_ == kVertexRemoveDumplicateVectorv_cube_vertex[j].color_ && vertex.uv_ == kVertexRemoveDumplicateVectorv_cube_vertex[j].uv_) {
                index = j;
                break;
            }
        }
        if (index < 0) {
            //û�ҵ��ͽ�Ŀ�궥�����kVertexRemoveDumplicateVector������¼����ΪkVertexRemoveDumplicateVector.size()��
            kVertexRemoveDumplicateVectorv_cube_vertex.push_back(vertex);
            kVertexIndexVector_cube_vertex.push_back(kVertexRemoveDumplicateVectorv_cube_vertex.size() - 1);
        }
        else {
            //�ҵ���Ŀ�궥�㣬��¼����ΪkVertexRemoveDumplicateVector��λ�á�
            kVertexIndexVector_cube_vertex.push_back(index);
        }
    }
}

//����VBO��EBO
void GeneratorBufferObject_cube_vertex()
{
    //��GPU�ϴ�������������
    glGenBuffers(1, &kVBO_cube_vertex);
    //������������ָ��Ϊ���㻺��������
    glBindBuffer(GL_ARRAY_BUFFER, kVBO_cube_vertex);
    //�ϴ��������ݵ�����������
    glBufferData(GL_ARRAY_BUFFER, kVertexRemoveDumplicateVectorv_cube_vertex.size() * sizeof(Vertex), &kVertexRemoveDumplicateVectorv_cube_vertex[0], GL_STATIC_DRAW);

    //��GPU�ϴ�������������
    glGenBuffers(1, &kEBO_cube_vertex);
    //������������ָ��Ϊ������������������
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, kEBO_cube_vertex);
    //�ϴ������������ݵ�����������
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, kVertexIndexVector_cube_vertex.size() * sizeof(unsigned short), &kVertexIndexVector_cube_vertex[0], GL_STATIC_DRAW);
}

static void error_callback_cube_vertex(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}



void init_opengl_cube_vertex()
{
    //���ô���ص�
    glfwSetErrorCallback(error_callback_cube_vertex);
    /* ��ʼ��glfw */
    if (!glfwInit())
        exit(EXIT_FAILURE);

    //ָ��opengl�汾��
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //��������
    window_cube_vertex = glfwCreateWindow(960, 640, "Simple example", NULL, NULL);
    if (!window_cube_vertex)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window_cube_vertex);
    // ����OpenGL ָ��   
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    //���������ʾ����������֮ǰ�ȴ���֡����ͨ����Ϊvsync��
   //Ĭ������£��������Ϊ0������Ϊ��Ļÿ��ֻ����60-75�Σ����Դ󲿷ֵĻ��治�ᱻ��ʾ��
   //���ң��������п�������Ļ���µ��м佻����������Ļ˺�ѵ������
   //���ԣ����Խ��ü����Ϊ1����ÿ֡����һ�Ρ�����������Ϊ���ߵ�ֵ��������ܵ��������ӳ١�
    glfwSwapInterval(1);

}

/// ���롢����Shader  
void compile_shader_cube_vertex()
{
    //��������Shader
    vertex_shader_cube_vertex = glCreateShader(GL_VERTEX_SHADER);
    //ָ��ShaderԴ��
    glShaderSource(vertex_shader_cube_vertex, 1, &vertex_shader_text_cube_vertex, NULL);
    //����Shader
    glCompileShader(vertex_shader_cube_vertex);
    //��ȡ������
    GLint compile_status = GL_FALSE;
    glGetShaderiv(vertex_shader_cube_vertex, GL_COMPILE_STATUS, &compile_status);
    if (compile_status == GL_FALSE)
    {
        GLchar message[256];
        glGetShaderInfoLog(vertex_shader_cube_vertex, sizeof(message), 0, message);
        cout << "compile vs error:" << message << endl;
    }

    //����Ƭ��Shader
    fragment_shader_cube_vertex = glCreateShader(GL_FRAGMENT_SHADER);
    //ָ��ShaderԴ��
    glShaderSource(fragment_shader_cube_vertex, 1, &fragment_shader_text_cube_vertex, NULL);
    //����Shader
    glCompileShader(fragment_shader_cube_vertex);
    //��ȡ������
    compile_status = GL_FALSE;
    glGetShaderiv(fragment_shader_cube_vertex, GL_COMPILE_STATUS, &compile_status);
    if (compile_status == GL_FALSE)
    {
        GLchar message[256];
        glGetShaderInfoLog(fragment_shader_cube_vertex, sizeof(message), 0, message);
        cout << "compile fs error:" << message << endl;
    }


    //����GPU����
    program_cube_vertex = glCreateProgram();
    //����Shader
    glAttachShader(program_cube_vertex, vertex_shader_cube_vertex);
    glAttachShader(program_cube_vertex, fragment_shader_cube_vertex);
    //Link
    glLinkProgram(program_cube_vertex);
    //��ȡ������
    GLint link_status = GL_FALSE;
    glGetProgramiv(program_cube_vertex, GL_LINK_STATUS, &link_status);
    if (link_status == GL_FALSE)
    {
        GLchar message[256];
        glGetProgramInfoLog(program_cube_vertex, sizeof(message), 0, message);
        cout << "link error:" << message << endl;
    }
}


//����Texture
void CreateTexturem_cube_vertex(std::string image_file_path)
{
    texture2d_cube_vertex = Texture2D::LoadFromFile(image_file_path);
}


int draw_cube_vertex(void)
{
    VertexRemoveDumplicate_cube_vertex();
    init_opengl_cube_vertex();
    CreateTexturem_cube_vertex("resources/textures/1.png");

    GeneratorBufferObject_cube_vertex();
    compile_shader_cube_vertex();

    //��ȡshader����ID
    mvp_location_cube_vertex = glGetUniformLocation(program_cube_vertex, "u_mvp");
    vpos_location_cube_vertex = glGetAttribLocation(program_cube_vertex, "a_pos");
    vcol_location_cube_vertex = glGetAttribLocation(program_cube_vertex, "a_color");
    a_uv_location_cube_vertex = glGetAttribLocation(program_cube_vertex, "a_uv");
    u_diffuse_texture_location_cube_vertex = glGetUniformLocation(program_cube_vertex, "u_diffuse_texture");

    while (!glfwWindowShouldClose(window_cube_vertex))
    {
        float ratio;
        int width, height;
        glm::mat4 model, view, projection, mvp;

        glfwGetFramebufferSize(window_cube_vertex, &width, &height);
        ratio = width / (float)height;

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(49.f / 255, 77.f / 255, 121.f / 255, 1.f);

        glm::mat4 trans = glm::translate(glm::vec3(0, 0, 0)); //���ƶ���������;

        static float rotate_eulerAngle = 0.f;
        rotate_eulerAngle += 1;
        glm::mat4 rotation = glm::eulerAngleYXZ(glm::radians(rotate_eulerAngle), glm::radians(rotate_eulerAngle), glm::radians(rotate_eulerAngle)); //ʹ��ŷ������ת;

        glm::mat4 scale = glm::scale(glm::vec3(2.0f, 2.0f, 2.0f)); //����;
        model = trans * scale * rotation;

        view = glm::lookAt(glm::vec3(0, 0, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

        projection = glm::perspective(glm::radians(60.f), ratio, 1.f, 1000.f);

        mvp = projection * view * model;

        //ָ��GPU����(����ָ��������ɫ����Ƭ����ɫ��)
        glUseProgram(program_cube_vertex);
        {
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE);//���������޳�

            //ָ����ǰʹ�õ�VBO
            glBindBuffer(GL_ARRAY_BUFFER, kVBO_cube_vertex);
            //��Shader����(a_pos)�Ͷ�������VBO������й���������0��ʾ����ƫ������
            glEnableVertexAttribArray(vpos_location_cube_vertex);
            glVertexAttribPointer(vpos_location_cube_vertex, 3, GL_FLOAT, false, sizeof(Vertex), 0);
            //���ö���Shader����(a_color)��ָ���붥����ɫ���ݽ��й���
            glEnableVertexAttribArray(vcol_location_cube_vertex);
            glVertexAttribPointer(vcol_location_cube_vertex, 4, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(float) * 3));
            //��Shader����(a_uv)�Ͷ���UV����VBO������й���������0��ʾ����ƫ������
            glEnableVertexAttribArray(a_uv_location_cube_vertex);
            glVertexAttribPointer(a_uv_location_cube_vertex, 2, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(float) * (3 + 4)));

            //�ϴ�mvp����
            glUniformMatrix4fv(mvp_location_cube_vertex, 1, GL_FALSE, &mvp[0][0]);

            //��ͼ����
            //��������Ԫ0
            glActiveTexture(GL_TEXTURE0);     
            //�����ص�ͼƬ���������󶨵�����Ԫ0��Texture2D�ϡ�
            glBindTexture(GL_TEXTURE_2D, texture2d_cube_vertex->gl_texture_id_);
            //����Shader���������Ԫ0��ȡ��ɫ����
            glUniform1i(u_diffuse_texture_location_cube_vertex, 0);

            //ָ����ǰʹ�õĶ�����������������
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, kEBO_cube_vertex);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);//ʹ�ö����������л��ƣ�����0��ʾ����ƫ������
        }
        glfwSwapBuffers(window_cube_vertex);
        glfwPollEvents();
    }

    glfwDestroyWindow(window_cube_vertex);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}