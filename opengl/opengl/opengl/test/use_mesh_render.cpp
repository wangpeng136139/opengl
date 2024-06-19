#include "../common/engine_head.h"
using namespace std;


using namespace glm;

//����

//ԭʼ��������
static const Vertex kVertexs_mesh_render[36] = {
    //Front
    {glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 0.0f) },
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
    {glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 1.0f)},
};

static const glm::vec3 kPositions_mesh_render[36] = {
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

static const glm::vec4 kColors_mesh_render[36] = {
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

static const glm::vec2 kUvs_mesh_render[36] =
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

GLFWwindow* window_mesh_render;
GLint mvp_location_mesh_render, vpos_location_mesh_render, vcol_location_mesh_render, u_diffuse_texture_location_mesh_render, a_uv_location_mesh_render;
GLuint kVBO_mesh_render, kEBO_mesh_render, kVAO_mesh_render;
Texture2D* texture2d_mesh_render = nullptr;
MeshFilter* mesh_load_mesh_render = nullptr;
//ȥ�صĶ���Vector
static vector<Vertex> kVertexRemoveDumplicateVectorv_mesh_render;
//��������Vector
static vector<unsigned short> kVertexIndexVector_mesh_render;

//����ȥ��
static void VertexRemoveDumplicate_mesh_render() {
    for (int i = 0; i < 36; ++i) {
        const Vertex& vertex = kVertexs_mesh_render[i];
        //�ж϶����Ƿ����
        int index = -1;
        for (int j = 0; j < kVertexRemoveDumplicateVectorv_mesh_render.size(); ++j) {
            if (vertex.pos_ == kVertexRemoveDumplicateVectorv_mesh_render[j].pos_ && vertex.color_ == kVertexRemoveDumplicateVectorv_mesh_render[j].color_ && vertex.uv_ == kVertexRemoveDumplicateVectorv_mesh_render[j].uv_) {
                index = j;
                break;
            }
        }
        if (index < 0) {
            //û�ҵ��ͽ�Ŀ�궥�����kVertexRemoveDumplicateVector������¼����ΪkVertexRemoveDumplicateVector.size()��
            kVertexRemoveDumplicateVectorv_mesh_render.push_back(vertex);
            kVertexIndexVector_mesh_render.push_back(kVertexRemoveDumplicateVectorv_mesh_render.size() - 1);
        }
        else {
            //�ҵ���Ŀ�궥�㣬��¼����ΪkVertexRemoveDumplicateVector��λ�á�
            kVertexIndexVector_mesh_render.push_back(index);
        }
    }
}
/// ����VAO
void GeneratorVertexArrayObject_mesh_render() {
    glGenVertexArrays(1, &kVAO_mesh_render);
}


//����VBO��EBO
void GeneratorBufferObject_mesh_render()
{
    //��GPU�ϴ�������������
    glGenBuffers(1, &kVBO_mesh_render);
    //������������ָ��Ϊ���㻺��������
    glBindBuffer(GL_ARRAY_BUFFER, kVBO_mesh_render);
    //�ϴ��������ݵ�����������
    glBufferData(GL_ARRAY_BUFFER, mesh_load_mesh_render->GetMesh()->vertex_num_ * sizeof(Vertex), mesh_load_mesh_render->GetMesh()->vertex_data_, GL_STATIC_DRAW);

    //��GPU�ϴ�������������
    glGenBuffers(1, &kEBO_mesh_render);
    //������������ָ��Ϊ������������������
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, kEBO_mesh_render);
    //�ϴ������������ݵ�����������
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh_load_mesh_render->GetMesh()->vertex_index_num_ * sizeof(unsigned short), mesh_load_mesh_render->GetMesh()->vertex_index_data_, GL_STATIC_DRAW);
    //����VAO
    glBindVertexArray(kVAO_mesh_render);
    {
        //ָ����ǰʹ�õ�VBO
        glBindBuffer(GL_ARRAY_BUFFER, kVBO_mesh_render);
        //��Shader����(a_pos)�Ͷ�������VBO������й���������0��ʾ����ƫ������
        glVertexAttribPointer(vpos_location_mesh_render, 3, GL_FLOAT, false, sizeof(Vertex), 0);
        //���ö���Shader����(a_color)��ָ���붥����ɫ���ݽ��й�����
        glVertexAttribPointer(vcol_location_mesh_render, 4, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(float) * 3));
        //��Shader����(a_uv)�Ͷ���UV����VBO������й�����
        glVertexAttribPointer(a_uv_location_mesh_render, 2, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(float) * (3 + 4)));

        glEnableVertexAttribArray(vpos_location_mesh_render);
        glEnableVertexAttribArray(vcol_location_mesh_render);
        glEnableVertexAttribArray(a_uv_location_mesh_render);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, kEBO_mesh_render);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

static void error_callback_mesh_render(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}



void init_opengl_mesh_render()
{
    //���ô���ص�
    glfwSetErrorCallback(error_callback_mesh_render);
    /* ��ʼ��glfw */
    if (!glfwInit())
        exit(EXIT_FAILURE);

    //ָ��opengl�汾��
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    //��������
    window_mesh_render = glfwCreateWindow(960, 640, "Simple example", NULL, NULL);
    if (!window_mesh_render)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window_mesh_render);
    // ����OpenGL ָ��   
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    //���������ʾ����������֮ǰ�ȴ���֡����ͨ����Ϊvsync��
   //Ĭ������£��������Ϊ0������Ϊ��Ļÿ��ֻ����60-75�Σ����Դ󲿷ֵĻ��治�ᱻ��ʾ��
   //���ң��������п�������Ļ���µ��м佻����������Ļ˺�ѵ������
   //���ԣ����Խ��ü����Ϊ1����ÿ֡����һ�Ρ�����������Ϊ���ߵ�ֵ��������ܵ��������ӳ١�
    glfwSwapInterval(1);

}
//
///// ���롢����Shader  
//void compile_shader_mesh_render()
//{
//    Shader * shader = new Shader();
//    shader->Find("resources/shader/Unlit");
//    program_mesh_render = shader->GetProgramId();
//}


//����Texture
void CreateTexturem_mesh_render(std::string image_file_path)
{
    texture2d_mesh_render = Texture2D::LoadFromFileTpc(image_file_path);
}


int draw_mesh_render(void)
{

    //VertexRemoveDumplicate_mesh_render();
   //MeshFilter::ExportMesh("cube.mesh", kVertexRemoveDumplicateVectorv_mesh_render, kVertexIndexVector_mesh_render);
    init_opengl_mesh_render();
    /*CreateTexturem_mesh_render("resources/textures/1.cpt");
      string a = "resources/textures/1.png";
      string b  = "resources/textures/1.cpt";
      Texture2D::CompressImageFile(a,b);
      return 0;*/
    Material* material = new Material();
    material->Parse("resources/material/cube.mat");

    mesh_load_mesh_render = new MeshFilter();
    mesh_load_mesh_render->LoadMesh("resources/mesh/cube.mesh");


    MeshRenderer * meshRender = new MeshRenderer();
    meshRender->SetMaterial(material);
    meshRender->SetMeshFilter(mesh_load_mesh_render);

    while (!glfwWindowShouldClose(window_mesh_render))
    {
        float ratio;
        int width, height;

        glfwGetFramebufferSize(window_mesh_render, &width, &height);
        ratio = width / (float)height;

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(49.f / 255, 77.f / 255, 121.f / 255, 1.f);

        glm::mat4 trans = glm::translate(glm::vec3(0, 0, 0)); //���ƶ���������;

        static float rotate_eulerAngle = 0.f;
        rotate_eulerAngle += 1;
        glm::mat4 rotation = glm::eulerAngleYXZ(glm::radians(rotate_eulerAngle), glm::radians(rotate_eulerAngle), glm::radians(rotate_eulerAngle)); //ʹ��ŷ������ת;

        glm::mat4 scale = glm::scale(glm::vec3(2.0f, 2.0f, 2.0f)); //����;
        glm::mat4 model = trans * scale * rotation;
        glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
        glm::mat4 projection = glm::perspective(glm::radians(60.f), ratio, 1.f, 1000.f);
        glm::mat4 mvp = projection * view * model;

        meshRender->SetMVP(mvp);
        meshRender->Render();


        glfwSwapBuffers(window_mesh_render);
        glfwPollEvents();
    }

    glfwDestroyWindow(window_mesh_render);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}