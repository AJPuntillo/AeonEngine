#ifndef PIECE_H
#define PIECE_H

#include <AeonEngine/Engine/Rendering/3D/Model.h>
#include <AeonEngine/Engine/Rendering/3D/Transform.h>
#include <AeonEngine/Engine/Physics/Stopwatch.h>
#include "../Grid/Tile.h"

using namespace AEON_ENGINE;

class Piece : public Entity
{
public:
	enum PlayerSide
	{
		Player1,
		Player2
	};

	enum PieceType
	{
		EARTH,
		WATER,
		FIRE
	};

	Piece(int pieceType_);
	~Piece();

	//Updating and rendering
	void update(const float deltaTime_) override;
	void render(Shader* shader_) override;

	Transform transform;

	void movePiece(Tile* moveTo_, float timer_); //With animation
	void movePiece(Tile* moveTo_);
	float attackPiece(Piece* target_);
	bool isEnemy(Piece* piece_);
	float takeDamage(float damage_);

	Tile* currentTile;

	bool hasAction;
	bool isAnimating = false;

	//Getters
	PlayerSide getPlayerSide() { return m_playerSide; }
	PieceType getPieceType() { return m_pieceType; }
	float getWalkSpeed() { return walkSpeed; }
	int getMovement() { return movement; }
	int getAttackRange() { return attackRange; }
	int getHealth() { return health; }
	int getAttackDamage() { return attackDamage; }
	std::string getAdv() { return advType; }
	std::string getWeakness() { return weakType; }

private:
	Model* m_model;
	PlayerSide m_playerSide;
	PieceType m_pieceType;
	glm::vec3 m_destination;

	//For Anim
	float animTimer = 0.0f;
	Stopwatch* m_animTimer;

	//Piece Stats
	float health;
	int movement;
	int attackDamage;
	int attackRange;
	float walkSpeed; //For animation
	std::string advType;
	std::string weakType;
};

#endif