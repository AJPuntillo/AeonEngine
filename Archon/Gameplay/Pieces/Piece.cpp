#include "Piece.h"
#include <glm/gtx/compatibility.hpp>

Piece::Piece(int pieceType_)
{
	switch (pieceType_) {
	//**Team 1 Pieces**
	//Earth
	case 1:
		m_playerSide = PlayerSide::Player1;
		m_model = new Model("Resources/Models/Piece/piece_p1_earth.obj");
		//transform.rotateBy(90.0f, 0.0f, 1.0f, 0.0f);
		m_pieceType = PieceType::EARTH;
		health = 200;
		movement = 1;
		attackDamage = 60;
		attackRange = 1;
		walkSpeed = 2.0f;
		advType = "Water";
		weakType = "Fire";
		break;
	//Water
	case 2:
		m_playerSide = PlayerSide::Player1;
		m_model = new Model("Resources/Models/Piece/piece_p1_ice.obj");
		transform.scaleBy(0.5f, 0.5f, 0.5f);
		//transform.rotateBy(90.0f, 0.0f, 1.0f, 0.0f);
		m_pieceType = PieceType::WATER;
		health = 100;
		movement = 2;
		attackDamage = 80;
		attackRange = 2;
		walkSpeed = 1.0f;
		advType = "Fire";
		weakType = "Earth";
		break;
	//Fire
	case 3:
		m_playerSide = PlayerSide::Player1;
		m_model = new Model("Resources/Models/Piece/piece_p1_fire.obj");
		transform.scaleBy(0.8f, 0.8f, 0.8f);
		//transform.rotateBy(90.0f, 0.0f, 1.0f, 0.0f);
		m_pieceType = PieceType::FIRE;
		health = 150;
		movement = 2;
		attackDamage = 50;
		attackRange = 1;
		walkSpeed = 1.5f;
		advType = "Earth";
		weakType = "Water";
		break;
	//**Team 2 Pieces**
	//Earth
	case 4:
		m_playerSide = PlayerSide::Player2;
		m_model = new Model("Resources/Models/Piece/piece_p2_earth.obj");
		transform.rotateBy(-180.0f, 0.0f, 1.0f, 0.0f);
		m_pieceType = PieceType::EARTH;
		health = 200;
		movement = 1;
		attackDamage = 60;
		attackRange = 1;
		walkSpeed = 2.0f;
		advType = "Water";
		weakType = "Fire";
		break;
	//Water
	case 5:
		m_playerSide = PlayerSide::Player2;
		m_model = new Model("Resources/Models/Piece/piece_p2_ice.obj");
		transform.rotateBy(-180.0f, 0.0f, 1.0f, 0.0f);
		transform.scaleBy(0.5f, 0.5f, 0.5f);
		m_pieceType = PieceType::WATER;
		health = 100;
		movement = 2;
		attackDamage = 80;
		attackRange = 2;
		walkSpeed = 1.0f;
		advType = "Fire";
		weakType = "Earth";
		break;
	//Fire
	case 6:
		m_playerSide = PlayerSide::Player2;
		m_model = new Model("Resources/Models/Piece/piece_p2_fire.obj");
		transform.scaleBy(0.8f, 0.8f, 0.8f);
		transform.rotateBy(-180.0f, 0.0f, 1.0f, 0.0f);
		m_pieceType = PieceType::FIRE;
		health = 150;
		movement = 2;
		attackDamage = 50;
		attackRange = 1;
		walkSpeed = 1.5f;
		advType = "Earth";
		weakType = "Water";
		break;
	case 0:
		break;
	}

	m_animTimer = new Stopwatch();
}

Piece::~Piece()
{

}

void Piece::update(const float deltaTime_)
{
	m_animTimer->Update(deltaTime_);
	if (isAnimating) {
		if (m_animTimer->getAlphaValue() < 1.0f) {
			//transform.setPosition(m_animTimer->LerpTo(transform.position, m_destination));
			glm::vec3 tmp = glm::lerp(transform.position, m_destination, m_animTimer->getAlphaValue());
			transform.setPosition(tmp);
		}
		else {
			isAnimating = false;
		}
	}
	//if (isAnimating) {
	//	if (animTimer < 1.0) {
	//		//transform.translateBy(dir * 0.5f * deltaTime_);
	//		animTimer += 0.01f;
	//		glm::vec3 test = glm::lerp(transform.position, m_destination, animTimer);
	//		transform.setPosition(test);
	//	}
	//	else {
	//		isAnimating = false;
	//		animTimer = 0.0f;
	//	}
	//}
}

void Piece::render(Shader* shader_)
{
	//Set the Model matrix
	transform.updateModelMatrix();

	shader_->setMat4("model", transform.modelMatrix);
	shader_->setBool("hasAction", hasAction);
	shader_->setVec3("colour", glm::vec3(0.0f, 0.0f, 0.0f));
	
	m_model->render(shader_);
}

void Piece::movePiece(Tile* moveTo_, float timer_)
{
	currentTile = moveTo_;
	m_destination = moveTo_->m_centerPos;
	isAnimating = true;
	m_animTimer->StartTimer(5.0f);
}

void Piece::movePiece(Tile* moveTo_)
{
	currentTile = moveTo_;
	m_destination = moveTo_->m_centerPos;
	transform.setPosition(moveTo_->m_centerPos);
}

float Piece::attackPiece(Piece* target_)
{
	float damage = attackDamage;

	//Triangle Modifiers
	//FIRE >> EARTH >> WATER >> FIRE
	switch (target_->getPieceType()) {
		case PieceType::EARTH:
			if (m_pieceType == PieceType::FIRE) {
				damage *= 1.5f;
			}
			else if (m_pieceType == PieceType::WATER) {
				damage = glm::floor(damage / 1.5);
			}
			break;

		case PieceType::FIRE:
			if (m_pieceType == PieceType::WATER) {
				damage *= 1.5f;
			}
			else if (m_pieceType == PieceType::EARTH) {
				damage = glm::floor(damage / 1.5);
			}
			break;

		case PieceType::WATER:
			if (m_pieceType == PieceType::EARTH) {
				damage *= 1.5f;
			}
			else if (m_pieceType == PieceType::FIRE) {
				damage = glm::floor(damage / 1.5);
			}
			break;
	}

	//Tile Modifiers
	if (target_->currentTile->getTileType() == Tile::TileType::MOUNTAIN && target_->getPieceType() == PieceType::EARTH) {
		damage = glm::floor(damage / 1.5);
	}

	if (currentTile->getTileType() == Tile::TileType::LAVA && m_pieceType == PieceType::FIRE) {
		damage *= 1.5f;
	}

	return target_->takeDamage(damage);
}

bool Piece::isEnemy(Piece* piece_)
{
	if (m_playerSide == piece_->getPlayerSide())
		return false;
	else
		return true;
}

float Piece::takeDamage(float damage_)
{
	health -= damage_;

	if (health <= 0) {
		health = 0;
	}
	return health;
}