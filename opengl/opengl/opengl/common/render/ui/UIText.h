#pragma once
#include "../../component/Component.h"
#include <string>
#include <glm/glm.hpp>

class Font;
class MeshRenderer;

class UIText : public Component {
public:
    UIText();
    ~UIText();
    void set_font(Font* font) { font_ = font; }
    Font* font() { return font_; }
    void set_text(std::string text);
    std::string text() { return text_; }
    void set_color(glm::vec4 color) { color_ = color; }
    glm::vec4 color() { return color_; }
public:
    void Update() override;
    /// ��Ⱦ֮ǰ
    void OnPreRender() override;
    void OnPostRender() override;
private:
    Font* font_;
    std::string text_;
    bool dirty_;//�Ƿ�仯��Ҫ��������Mesh
    glm::vec4 color_;//������ɫ
};
