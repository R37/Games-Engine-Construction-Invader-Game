#pragma once
#include "Entity.h"
class EnemyEntity :
    public Entity
{
public:
    std::string m_spriteName = "Rock";
    void Update(Visulisation& Viz, Simulation& Sim) override final;
    EnemyEntity();
    Side GetSide() const override { return Side::eEnemy; }
    void setup() override final;

    


private:
    bool InitalSpawn = true;
    bool Toggle = false;
};

