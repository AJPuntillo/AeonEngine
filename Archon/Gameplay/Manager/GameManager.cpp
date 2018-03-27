#include "GameManager.h"

GameManager::GameManager()
{
	m_playerTurn = PlayerTurn::P2_turn;
	m_turnTimer = new Stopwatch();
	m_turnMaxTime = 45.0f;
	m_emitter = new ParticleEmitter(10, 0);
}

GameManager::~GameManager()
{

}

void GameManager::update(float deltaTime_, Camera* camera_)
{
	if (m_isAnimating) {
		if (m_timer < 1.0) {
			m_timer += deltaTime_;
			if (m_playerTurn == PlayerTurn::P2_turn) {
				glm::vec3 tmp = glm::lerp(camera_->getPos(), glm::vec3(9.75f, 6.75f, 3.5f), m_timer);
				camera_->setPos(tmp);
				camera_->setYaw((180.0f * m_timer) * 2.5f);
				if (camera_->getYaw() > 180.0f)
					camera_->setYaw(180.0f);
			}
			else if (m_playerTurn == PlayerTurn::P1_turn) {
				glm::vec3 tmp = glm::lerp(camera_->getPos(), glm::vec3(-2.75f, 6.75f, 3.5f), m_timer);
				camera_->setPos(tmp);
				camera_->setYaw((180.0f) - (180.0f * m_timer) * 2.5f);
				if (camera_->getYaw() < 0.0f)
					camera_->setYaw(0.0f);
			}
		}
		else {
			m_isAnimating = false;
			m_timer = 0.0f;
			m_turnTimer->StartTimer(45.0f);
		}
	}

	//if (m_isAnimating) {
	//	if (m_turnTimer->getAlphaValue() < 1.0f) {
	//		if (m_playerTurn == PlayerTurn::P2_turn) {
	//			glm::vec3 tmp = glm::lerp(camera_->getPos(), glm::vec3(9.75f, 6.75f, 3.5f), m_turnTimer->getAlphaValue());
	//			camera_->setPos(tmp);
	//			camera_->setYaw((180.0f * m_turnTimer->getAlphaValue()) * 2.0f);
	//			if (camera_->getYaw() > 180.0f)
	//				camera_->setYaw(180.0f);
	//		}
	//		else if (m_playerTurn == PlayerTurn::P1_turn) {
	//			glm::vec3 tmp = glm::lerp(camera_->getPos(), glm::vec3(-2.75f, 6.75f, 3.5f), m_turnTimer->getAlphaValue());
	//			camera_->setPos(tmp);
	//			camera_->setYaw((180.0f) - (180.0f * m_turnTimer->getAlphaValue()) * 2.0f);
	//			if (camera_->getYaw() < 0.0f)
	//				camera_->setYaw(0.0f);
	//		}
	//	}
	//	else {
	//		m_isAnimating = false;
	//		m_turnTimer->StartTimer(45.0f);
	//	}
	//}

	m_emitter->update(deltaTime_);
	m_turnTimer->Update(deltaTime_);
}

void GameManager::updatePieceCount(int p1_, int p2_)
{
	p1_pieceCount = p1_;
	p2_pieceCount = p2_;

	if (p1_pieceCount == 0) {
		std::cout << "Player 2 Wins!" << std::endl;
	}
	else if (p2_pieceCount == 0) {
		std::cout << "Player 1 Wins!" << std::endl;
	}
}

void GameManager::render(Shader* shader_)
{
	m_emitter->render(shader_);
}

void GameManager::nextTurn()
{
	if (m_playerTurn == PlayerTurn::P1_turn)
		m_playerTurn = PlayerTurn::P2_turn;
	else if (m_playerTurn == PlayerTurn::P2_turn)
		m_playerTurn = PlayerTurn::P1_turn;

	turnCount++;

	m_turnTimer->StartTimer(1.0f);
	m_isAnimating = true;
}

void GameManager::playParticles(Piece::PieceType type_, int amount_, float lifeTime_, glm::vec3 pos_)
{
	m_emitter->setParticleAmount(amount_);
	m_emitter->setLifetime(lifeTime_);
	m_emitter->transform.setPosition(pos_);

	switch (type_) {
		case Piece::PieceType::FIRE:
			m_emitter->setColour(glm::vec3(1.4f, 0.5f, 0.5f));
			break;
		case Piece::PieceType::EARTH:
			m_emitter->setColour(glm::vec3(0.5f, 1.4f, 0.5f));
			break;
		case Piece::PieceType::WATER:
			m_emitter->setColour(glm::vec3(0.5f, 0.5f, 1.0f));
			break;
	}

	m_emitter->play();
}