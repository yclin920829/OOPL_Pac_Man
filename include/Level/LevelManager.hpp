#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_LEVELMANAGER_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_LEVELMANAGER_HPP

#include "Level.hpp"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

class LevelManager : public Util::GameObject {
public:
    explicit LevelManager(){//暫定存有20個關卡的vector且都只有資訊而無產生實體物件，以防不好換關卡的時候刪除

    };

    void ConstructLevel(int nowLevel, std::string player){
        this -> nowLevel = nowLevel;
        this -> nowPlayer = player;
        NowLevel = std::make_shared<Level>(player);
        NowLevel -> Initialized(nowLevel);
        this -> AddChild(NowLevel);
    }

    void NextLevel(){//導出需儲存的data然後刪除
        this -> RemoveChild(NowLevel);
        nowLevel += 1;
        ConstructLevel(nowLevel, nowPlayer);
    }

    int Update(){
        int nowState = NowLevel -> Update();
        if(nowState != 3){
            return nowState;
        }
        if(nowLevel == maxLevel){
            return 2;
        }else{
            NextLevel();
        }
    }




private:

    int maxLevel = 5;
    std::string nowPlayer;
    int nowLevel = 0;
    std::shared_ptr<Level> NowLevel;
    //std::vector<std::shared_ptr<Level>> Levels;
};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_LEVELMANAGER_HPP
