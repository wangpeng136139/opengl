#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
int draw_base()
{
    GLFWwindow* window;
    /* ��ʼ��glfw */
    if (!glfwInit())
        return -1;
    /* ����һ��Window �� OpenGL������ */
    window = glfwCreateWindow(960, 640, "Hello World", NULL, NULL);
    if (!window)
    {
        //����ʧ�ܾ��˳�
        glfwTerminate();
        return -1;
    }
    /* �������洴����OpenGL������ */
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    /* ������Ϸ������ѭ�� */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(49.f / 255, 77.f / 255, 121.f / 255, 1.f);
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* ������� �����¼� */
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}