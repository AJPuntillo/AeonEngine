#ifndef BOARD_H
#define BOARD_H

#include "../3D/Entity.h"
#include "Tile.h"

namespace AEON_ENGINE {

	class Board : Entity
	{
	public:
		Board();
		Board(int width_, int height_, std::string modelPath_);
		~Board();

		//Updating and rendering
		void update(const float deltaTime_) override;
		void render(Shader* shader_) override;

		//Getters
		std::vector<Tile*> getTiles() { return m_board; }

		//Special Translate
		void translateBoard(float x, float y, float z);
		Transform transform;

	private:
		void initBoard();

		//Container of tiles
		std::vector<Tile*> m_board;

		//Board size
		int m_width = 0;
		int m_height = 0;

		//Board layout

		//Unused
		std::string m_modelPath;
	};

}

#endif
