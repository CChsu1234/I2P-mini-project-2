#ifndef ENEMY_HPP
#define ENEMY_HPP
#include <list>
#include <string>
#include <vector>

#include "Engine/Point.hpp"
#include "Engine/Sprite.hpp"
#include "UI/Component/Image.hpp"

class Bullet;
class PlayScene;
class Turret;

class Enemy : public Engine::Sprite {
protected:
    Engine::Sprite *Fire;
    std::vector<Engine::Point> path;
    float speed;
    float hp;
    float HitCountDown;
    float BurnCountDown;
    float BurnDamage;
    int money;
    PlayScene *getPlayScene();
    virtual void OnExplode();

public:
    float reachEndTime;
    std::list<Turret *> lockedTurrets;
    std::list<Bullet *> lockedBullets;
    Enemy(std::string img, float x, float y, float radius, float speed, float hp, int money, std::string fire = "play/bullet-6.png");
    void Hit(float damage);
    void Burn(float damage, float Time);
    void UpdatePath(const std::vector<std::vector<int>> &mapDistance);
    void Update(float deltaTime) override;
    void Draw() const override;
};
#endif   // ENEMY_HPP
