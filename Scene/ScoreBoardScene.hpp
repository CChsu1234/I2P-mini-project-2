#ifndef ScoreBoardScene_HPP
#define ScoreBoardScene_HPP

#include <allegro5/allegro_audio.h>
#include <memory>

#include "Engine/IScene.hpp"
#include "UI/Component/Label.hpp"

#define PAGE_LINE 6

typedef struct _User {
    std::string name;
    int score;
} User;

class ScoreBoardScene final : public Engine::IScene {
private:
    int current_head_line;
    int total_line;
    std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
    User *table;
    Engine::Label *scoreboard[PAGE_LINE][2];

public:
    explicit ScoreBoardScene() = default;
    void Initialize() override;
    void Terminate() override;
    void BackOnClick(int stage);
    void PageUpOnClick(int line);
    void PageDownOnClick(int line);
};

#endif   // ScoreBoardScene_HPP

