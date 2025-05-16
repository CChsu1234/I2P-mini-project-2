#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>
#include <string>
#include <cstdio>
#include <iostream>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "PlayScene.hpp"
#include "Scene/ScoreBoardScene.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"

void ScoreBoardScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    Engine::ImageButton *btn;

    table.Update();
    table.Sort();
    total_line = table.size();

    for (int i = 0; i < PAGE_LINE && i < total_line; i++) {
        AddNewObject(scoreboard[i][0] = new Engine::Label(std::to_string(i + 1) + ". "+ table[i].name, "pirulen.ttf", 28, halfW * 2 / 3, halfH +  50 * (i - PAGE_LINE / 2), 255, 255, 255, 255, 0, 0.5, 0));
        AddNewObject(scoreboard[i][1] = new Engine::Label(std::to_string(table[i].score), "pirulen.ttf", 28, halfW * 4 / 3, halfH +  50 * (i - PAGE_LINE / 2), 255, 255, 255, 255, 0.5, 0, 0));
    }
    current_head_line = 0;

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, halfH * 3 / 2 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreBoardScene::BackOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 3 / 2, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW * 1 / 2 - 250, halfH * 3 / 2 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreBoardScene::DownOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("PAGE DOWN", "pirulen.ttf", 48, halfW * 1 / 2 - 50, halfH * 3 / 2, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW  * 3 / 2 - 150, halfH * 3 / 2 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreBoardScene::UpOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("PAGE UP", "pirulen.ttf", 48, halfW * 3 / 2 + 50, halfH * 3 / 2, 0, 0, 0, 255, 0.5, 0.5));
    /*
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, halfH * 3 / 2 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreBoardScene::BackOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 3 / 2, 0, 0, 0, 255, 0.5, 0.5));
    */

    // Not safe if release resource while playing, however we only free while change scene, so it's fine.
    bgmInstance = AudioHelper::PlaySample("select.ogg", true, AudioHelper::BGMVolume);
}
void ScoreBoardScene::Terminate() {
    AudioHelper::StopSample(bgmInstance);
    bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
    IScene::Terminate();
}
void ScoreBoardScene::BackOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("start");
}
void ScoreBoardScene::UpOnClick(int line) {
    if (current_head_line  + line >= total_line - 1) {
        current_head_line = total_line - 2;
    }
    current_head_line++;
    for (int i = 0; i < PAGE_LINE; i++) {
        scoreboard[i][0]->Text = (i + current_head_line < total_line) ? (std::to_string(i + current_head_line + 1) + ". " + table[i + current_head_line].name) : "" ;
        scoreboard[i][1]->Text = (i + current_head_line < total_line) ? std::to_string(table[i + current_head_line].score) : "" ;
    }
}
void ScoreBoardScene::DownOnClick(int line) {
    if (current_head_line - line <= 0) {
        current_head_line = 0;
    }
    current_head_line--;
    for (int i = 0; i < PAGE_LINE && i + current_head_line < total_line; i++) {
        scoreboard[i][0]->Text = (i + current_head_line < total_line) ? (std::to_string(i + current_head_line + 1) + ". " + table[i + current_head_line].name) : "" ;
        scoreboard[i][1]->Text = (i + current_head_line < total_line) ? std::to_string(table[i + current_head_line].score) : "" ;
    }
}
