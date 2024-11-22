#include <iostream>

#include <thread>
#include <chrono>

#include "life_forms.hpp"
#include "life_definitions.hpp"
#include "life_events.hpp"

const int chance = /* 1:*/3;

using Field = std::array<std::array<bool, N>, N>;

class Game{
	private:
		Field field;
		int last_event = -1;

		int get_neighbours(int x, int y){
			int neighbours = 0;

			for(int i = x-1; i <= x+1; i++){
				if(i < 0 || i > N){continue;}

				for(int j = y - 1; j <= y+1; j++){
					if((i == x && j == y) || (j < 0 || j > N)){continue;}

					if(this->field[i][j]){neighbours++;}
				}
			}

			return neighbours;
		}
	public:
		Game(){
			for(int i = 0; i < N; i++){for(int j = 0; j < N; j++){this->field[i][j] = rand()%chance==1;}}
		}

		void update(){
			Field new_f = this->field;

			for(int i = 0; i < N; i++){
				for(int j = 0; j < N; j++){
					int neighbours = this->get_neighbours(i, j);
					bool* pixel = &this->field[i][j];
					
					if(!*pixel && neighbours == 3){new_f[i][j] = true;}
					else if(*pixel && (neighbours < 2 || neighbours > 3)){new_f[i][j] = false;}
				}
			}

			this->field = new_f;

			this->last_event++;
		}

		void show(){
			for(int i = 0; i < N; i++){
				for(int j = 0; j < N; j++){
					std::cout << (this->field[i][j]?"O":" ") << " ";
				}
				std::cout << std::endl;
			}
		}

		template<class X> void event(X f){
			f(this->field);
			this->last_event = 0;
		}
};

int main(int argc, char** argv){
	srand(time(nullptr));

	Game game;

	int last_update = 0;

	while(1){
		game.update();
		last_update++;

		if(last_update > DISPLAY_FREQUENCY){system("clear"); last_update = 0; game.show();}
	
		if(EVENTS){
			if(rand() % 100 == 0){
				game.event(Event::events[rand() % Event::events.size()]);
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1000 / UPS));
	}
}
