#include "Simulation.h"
#include "Visulisation.h"
#include "PlayerEntity.h"
#include "EnemyEntity.h"
#include "Rectangle.h"
#include "Bullet.h"
#include <time.h>

float volume = 0.1f;
void Simulation::LoadLevel()
{

	HAPI.PlaySound("Data\\BGMusic.wav", volume);
	//Create Sprites
	if (!Viz.CreateSprite("Background", "data\\background.tga"))
		return;
	if (!Viz.CreateSprite("Player", "data\\playerSprite.tga"))
		return;
	if (!Viz.CreateSprite("Bullet", "data\\Bullet.png"))
		return;
	if (!Viz.CreateSprite("SpaceStation", "data\\spacestation.png"))
		return;
	if (!Viz.CreateSprite("Ship", "data\\Ship.png"))
		return;
	if (!Viz.CreateSprite("Stars", "data\\stars.jpg"))
		return;
	//Create Player 1 Entity
	PlayerEntity* newPlayer = new PlayerEntity;
	m_entityVector.push_back(newPlayer);
	newPlayer->Setup();
	
	StartOfBullets = int (m_entityVector.size() + 1);
	//Create all bullets
	float TotalBullets = 25;
	for (int x = 0; x <= TotalBullets; x++)
	{
		Bullet* newBullet = new Bullet;
		m_entityVector.push_back(newBullet);
	}
	int EndOfBullets = int(m_entityVector.size());

	//Spawn Boss
	EnemyEntity* newEnemy = new EnemyEntity("SpaceStation");
	m_entityVector.push_back(newEnemy);
	newEnemy->SetupBoss();

	float TotalEnemies = 5;
	for (int x = 0; x <= TotalEnemies; x++)
	{
		EnemyEntity* newEnemy = new EnemyEntity("Ship");
		m_entityVector.push_back(newEnemy);
		newEnemy->Setup();
	}

}

float FireDelayTick = 120;

void Simulation::SpawnBullet(float PlayerX, float PlayerY)
{
	for (int z = StartOfBullets; z < m_entityVector.size(); z++)
	{
		if (m_entityVector[z]->GetIsAlive() == false && m_entityVector[z]->GetIsBullet() == true && FireDelayTick >= 50 )
		{
		m_entityVector[z]->SetIsAlive(true);
		m_entityVector[z]->SetPos(PlayerX + 28, PlayerY);
		m_entityVector[z]->Update(Viz, *this);
		HAPI.PlaySound("Data\\laser.wav", volume);
		FireDelayTick = 0;
		break;
		
		}
		
	}
}

void Simulation::RestartGame()
{
	for (Entity* p : m_entityVector)
		p->Setup();
	m_entityVector[0]->SetHealth();
	m_entityVector[0]->SetScore();


}

void Simulation::Run()
{
	Viz.Initialise();
	LoadLevel();
	//const HAPI_TKeyboardData& KeyData = HAPI.GetKeyboardData();
	while (HAPI.Update())
	{
		//DeltaTime
		float time = float (clock());
		DeltaTime = time - OldTime;
		OldTime = time;
		FireDelayTick += (1 * DeltaTime);

		Viz.ClearScreen();
		//Scrolling Background
		Viz.RenderClippedSprite("Stars", 0, BGy);
		Viz.RenderClippedSprite("Stars", 0, BG2y);

		BGy = BGy + (0.5f* DeltaTime);
		BG2y = BG2y + (0.5f * DeltaTime);
		if (BGy >= 768)
			BGy = 0;
		if (BG2y >= 0)
			BG2y = -768;
		//UI
		int score = m_entityVector[0]->GetScore();
		HAPI.RenderText(25, 82, textcol, outcol, 1, "Score: " + std::to_string(score), 32);
		int health = m_entityVector[0]->GetHealth();
		HAPI.RenderText(25, 50, textcol, outcol, 1, "Health: " + std::to_string(health), 32);

		//Update all entitys
		for (Entity* p : m_entityVector)
			p->Update(Viz,*this);

		//None working collision code
		for (int i = 0; i < m_entityVector.size(); i++)
		{
			for (int j = i + 1; j < m_entityVector.size(); j++)
			{
				if ((m_entityVector[i]->GetSide() == Side::ePlayer && m_entityVector[j]->GetSide() == Side::ePlayer) || (m_entityVector[i]->GetSide() == Side::eEnemy && m_entityVector[j]->GetSide() == Side::eEnemy))
				{

				}
				else
				{
					if (m_entityVector[i]->CheckCollision(Viz, *m_entityVector[j]))
					{
						
					}
				}
			}
		}




	}

}

Simulation::~Simulation()
{
	for (auto& p : m_entityVector)
		delete p;
}
