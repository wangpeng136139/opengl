#ifndef UNTITLED_UI_BUTTON_H
#define UNTITLED_UI_BUTTON_H

#include "include_common.h"

class UIImage;
class UIButton : public Component {
public:
    UIButton();
    ~UIButton();

    void set_image_normal(UIImage* image) { image_normal_ = image; }
    void set_image_press(UIImage* image) { image_press_ = image; }
    /// ���ð�ť����ص�
    /// \param callback
    void set_click_callback(std::function<void()> click_callback) { click_callback_ = click_callback; }
public:
    void Update() override;
private:
    UIImage* image_normal_;//��ͨ״̬��ʾͼƬ
    UIImage* image_press_;//��ѹ״̬��ʾͼƬ
    bool pressed_;//��ǰ��ť״̬�Ƿ���
    std::function<void()> click_callback_;//��ť����ص�
};
#endif