#pragma once


namespace gol {
	class Cell
	{
		bool alive = false;

	public:
		Cell();
		~Cell();
		bool isAlive();
		void kill();
		void revive();
	};
}