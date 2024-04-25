//main.cpp
extern int draw_base();
extern int draw_triangle();
extern int draw_quad();
extern int draw_cube();
extern int draw_load_image();
extern int draw_cube_vertex();
extern int draw_cube_vertex3_3();
extern int draw_load_mesh_file();
int main(void)
{
    return draw_load_mesh_file();
}    