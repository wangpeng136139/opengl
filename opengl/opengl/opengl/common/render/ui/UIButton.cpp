#include "UIButton.h"
#include <rttr/registration>
#include <glm/ext.hpp>
#include "../../component/GameObject.h"
#include "../../component/transform.h"
#include "../../render/textures/Texture2D.h"
#include "../../common/Debug.h"
#include "../../render/mesh/MeshRenderer.h"
#include "../../renderdevice/RenderDevice.h"
#include "../../common/Screen.h"
#include "../../eventstytem/Input.h"
#include "../../eventstytem/key_code.h"
#include "UIImage.h"

using namespace rttr;
RTTR_REGISTRATION{
    registration::class_<UIButton>("UIButton")
            .constructor<>()(rttr::policy::ctor::as_raw_ptr);
}

UIButton::UIButton() :pressed_(false), click_callback_(nullptr) {

}

UIButton::~UIButton() {

}

void UIButton::Update() {
    Component::Update();

    if (image_normal_ == nullptr || image_press_ == nullptr) {
        return;
    }

    Transform* transform = dynamic_cast<Transform*>(game_object()->GetComponent("Transform"));
    //��ť��ͼƬ �� ��ť����ͬ��
    Transform* transform_image_normal = dynamic_cast<Transform*>(image_normal_->game_object()->GetComponent("Transform"));
    Transform* transform_image_press = dynamic_cast<Transform*>(image_press_->game_object()->GetComponent("Transform"));
    transform_image_normal->set_position(transform->position());
    transform_image_press->set_position(transform->position());

    if (Input::GetMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        auto transform_position = transform->position();
        //��ȡ������꣬�������Ͻ���㣬ת��Ϊ��Ļ������㡣
        auto mouse_position = Input::mousePosition();
        mouse_position.x = mouse_position.x - Screen::width() / 2;
        mouse_position.y = Screen::height() / 2 - mouse_position.y;
        //��ȡ��ťͼƬ���
        float image_normal_width = image_normal_->width();
        float image_normal_height = image_normal_->height();
        //����������Ƿ��ڰ�ťͼƬ��Χ��
        if ((mouse_position.x > transform_position.x && mouse_position.x < transform_position.x + image_normal_width) &&
            (mouse_position.y > transform_position.y && mouse_position.y < transform_position.y + image_normal_height)) {
            if (pressed_) {
                return;
            }
            pressed_ = true;
            //������ť����ص�
            if (click_callback_) {
                click_callback_();
            }
        }
        else {
            pressed_ = false;
        }
    }
    else {
        pressed_ = false;
    }
    //��pressΪtrue �ر���ͨ״̬ͼƬ�������״̬ͼƬ.����ת��
    transform_image_normal->game_object()->set_active(!pressed_);
    transform_image_press->game_object()->set_active(pressed_);
}
