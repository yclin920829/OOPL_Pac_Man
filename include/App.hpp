#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export
#include "Fruit.hpp"
#include "Pacman.hpp"
#include "Util/Root.hpp"
#include "ghost/Ghost.hpp"
#include "ghost/GhostDeadState.hpp"
#include "ghost/GhostNormalState.hpp"
#include "ghost/GhostVulnerableState.hpp"

class App {
public:
    enum class State {
        START,
        UPDATE,
        END,
    };

    State GetCurrentState() const { return m_CurrentState; }

    void Start();

    void Update();

    void End(); // NOLINT(readability-convert-member-functions-to-static)

private:
    void ValidTask();

private:
    State m_CurrentState = State::START;

    Util::Root root;

    std::shared_ptr<Ghost> blinky;
    std::shared_ptr<Ghost> pinky;
    std::shared_ptr<Ghost> inky;
    std::shared_ptr<Ghost> clyde;

    GhostNormalState * normalBlinky = new GhostNormalState();
    GhostNormalState * normalPinky = new GhostNormalState();
    GhostNormalState * normalInky = new GhostNormalState();
    GhostNormalState * normalClyde = new GhostNormalState();
    GhostDeadState * deadGhost = new GhostDeadState();
    GhostVulnerableState * vulnerableGhost = new GhostVulnerableState();

    std::shared_ptr<Pacman> pacman;

    std::shared_ptr<Fruit> cherry;

    std::vector<std::string> VulnerableGhostsImages;

protected:
    std::shared_ptr<Ghost> CreateGhost(const std::string& dir, float posX, float posY, const std::string& name, GhostState * normalGhost) {
        std::shared_ptr<Ghost> ghost = std::make_shared<Ghost>();
        ghost->SetState(normalGhost);
        ghost->SetUpImages({dir + "/Image/Character/" + name + "/" + name + "_U_01.png", dir + "/Image/Character/" + name + "/" + name + "_U_02.png"});
        ghost->SetDownImages({dir + "/Image/Character/" + name + "/" + name + "_D_01.png", dir + "/Image/Character/" + name + "/" + name + "_D_02.png"});
        ghost->SetRightImages({dir + "/Image/Character/" + name + "/" + name + "_R_01.png", dir + "/Image/Character/" + name + "/" + name + "_R_02.png"});
        ghost->SetLeftImages({dir + "/Image/Character/" + name + "/" + name + "_L_01.png", dir + "/Image/Character/" + name + "/" + name + "_L_02.png"});

        ghost->SetState(deadGhost);
        ghost->SetUpImages({RESOURCE_DIR"/Image/Character/Ghost_dead/Ghost_dead_U.png"});
        ghost->SetDownImages({RESOURCE_DIR"/Image/Character/Ghost_dead/Ghost_dead_D.png"});
        ghost->SetRightImages({RESOURCE_DIR"/Image/Character/Ghost_dead/Ghost_dead_R.png"});
        ghost->SetLeftImages({RESOURCE_DIR"/Image/Character/Ghost_dead/Ghost_dead_L.png"});

        ghost->SetState(vulnerableGhost);
        ghost->SetUpImages(VulnerableGhostsImages);
        ghost->SetDownImages(VulnerableGhostsImages);
        ghost->SetRightImages(VulnerableGhostsImages);
        ghost->SetLeftImages(VulnerableGhostsImages);

        ghost->SetState(normalGhost);
        ghost->SetZIndex(5);
        ghost->SetVisible(true);
        ghost->SetPosition({posX, posY});
        ghost->Draw();

        return ghost;
    }
};

#endif
