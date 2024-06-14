#include "App.hpp"


void App::Update() {
//    LOG_DEBUG("Update");

    int nowState = levelManager -> Update();
    if(nowState == 1){
        IsBackFromGame = true;
        m_CurrentState = State::END;
    }

    if (nowState == 2) {
        IsBackFromGame = true;
        m_CurrentState = State::UI;
        root.RemoveChild(levelManager);
    }//改到在UI按ESC才有到END，在這按ESC是回UI

    root.Update();
}