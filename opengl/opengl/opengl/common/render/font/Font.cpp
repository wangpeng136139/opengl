#include "Font.h"

#include "../../common/Debug.h";
#include <fstream>
#include "freetype/ftbitmap.h"


using std::ifstream;
using std::ios;

std::unordered_map<std::string, Font*> Font::font_map_;

void Font::LoadCharacter(char ch) {
    if (character_map_[ch] != nullptr) {
        return;
    }
    //��������ֵ�����,���ص� m_FTFace����ȥ;Glyph�����Σ�ͼ���ַ� [glif];
    FT_Load_Glyph(ft_face_, FT_Get_Char_Index(ft_face_, ch), FT_LOAD_DEFAULT);

    //�� FTFace�����ȡ�������  �� ft_glyph ����;
    FT_Glyph ft_glyph;
    FT_Get_Glyph(ft_face_->glyph, &ft_glyph);
    //��ȾΪ256���Ҷ�ͼ
    FT_Glyph_To_Bitmap(&ft_glyph, ft_render_mode_normal, 0, 1);

    FT_BitmapGlyph ft_bitmap_glyph = (FT_BitmapGlyph)ft_glyph;
    FT_Bitmap& ft_bitmap = ft_bitmap_glyph->bitmap;

    //���������ɵ��ַ�����ͼ���е����С�
    if (font_texture_fill_x + ft_bitmap.width >= font_texture_size_) {//�����Ͻ������Ͻ���䣬���˾ͻ�һ�С�
        font_texture_fill_x = 0;
        font_texture_fill_y += font_size_;
    }
    if (font_texture_fill_y + font_size_ >= font_texture_size_) {
        spdlog::error("{} is out of font_texture y", ch);
        return;
    }
    font_texture_->UpdateSubImage(font_texture_fill_x, font_texture_fill_y, ft_bitmap.width, ft_bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, ft_bitmap.buffer);

    //�洢�ַ���Ϣ
    Character* character = new Character(font_texture_fill_x * 1.0f / font_texture_size_, font_texture_fill_y * 1.0f / font_texture_size_, (font_texture_fill_x + ft_bitmap.width) * 1.0f / font_texture_size_, (font_texture_fill_y + ft_bitmap.rows) * 1.0f / font_texture_size_);
    character_map_[ch] = character;

    font_texture_fill_x += ft_bitmap.width;
}

std::vector<Font::Character*> Font::LoadStr(std::string str) {
    //�������е��ַ� bitmap    
    for (auto ch : str) {
        LoadCharacter(ch);
    }
    //���������ַ���Ϣ
    std::vector<Character*> character_vec;
    for (auto ch : str) {
        auto character = character_map_[ch];
        if (character == nullptr) {
            spdlog::error("LoadStr error,no bitmap,ch:{}", ch);
            continue;
        }
        character_vec.push_back(character);
    }
    return character_vec;
}



Font* Font::GetFont(std::string font_file_path) {
    return font_map_[font_file_path];
}

void Texture2D::UpdateSubImage(int x, int y, int width, int height, unsigned int client_format, unsigned int data_type,
    unsigned char* data) {
    if (width <= 0 || height <= 0) {
        return;
    }
    glBindTexture(GL_TEXTURE_2D, gl_texture_id_); __CHECK_GL_ERROR__
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1); __CHECK_GL_ERROR__
        glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height, client_format, data_type, data); __CHECK_GL_ERROR__
}


Font* Font::LoadFromFile(std::string font_file_path, unsigned short font_size) {
    Font* font = GetFont(font_file_path);
    if (font != nullptr) {
        return font;
    }

    //��ȡ ttf �����ļ�
    ifstream input_file_stream(font_file_path, ios::in | ios::binary);
    input_file_stream.seekg(0, std::ios::end);
    int len = input_file_stream.tellg();
    input_file_stream.seekg(0, std::ios::beg);
    char* font_file_buffer = new char[len];
    input_file_stream.read(font_file_buffer, len);

    //��ttf ����FreeType����
    FT_Library ft_library = nullptr;
    FT_Face ft_face = nullptr;
    FT_Init_FreeType(&ft_library);//FreeType��ʼ��;
    FT_Error error = FT_New_Memory_Face(ft_library, (const FT_Byte*)font_file_buffer, len, 0, &ft_face);
    if (error != 0) {
        DEBUG_LOG_ERROR("FT_New_Memory_Face return error {}!", error);
        return nullptr;
    }

    FT_Select_Charmap(ft_face, FT_ENCODING_UNICODE);

    FT_F26Dot6 ft_size = (FT_F26Dot6)(font_size * (1 << 6));

    FT_Set_Char_Size(ft_face, ft_size, 0, 72, 72);

    if (ft_face == nullptr) {
        DEBUG_LOG_ERROR("FT_Set_Char_Size error!");
        return nullptr;
    }

    //����Fontʵ��������Freetype������������
    font = new Font();
    font->font_size_ = font_size;
    font->font_file_buffer_ = font_file_buffer;
    font->ft_library_ = ft_library;
    font->ft_face_ = ft_face;
    font_map_[font_file_path] = font;

    //�����հ׵ġ���Alphaͨ�����������������֡�
    unsigned char* pixels = (unsigned char*)malloc(font->font_texture_size_ * font->font_texture_size_);
    memset(pixels, 0, font->font_texture_size_ * font->font_texture_size_);
    font->font_texture_ = Texture2D::Create(font->font_texture_size_, font->font_texture_size_, GL_RED, GL_RED, GL_UNSIGNED_BYTE, pixels);
    delete pixels;

    return font;
}
