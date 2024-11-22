namespace Event{
	void life_spawn(Field& field){
		int posX = rand() % N;
		int posY = rand() % N;

		for(int i = posX-1; i <= posX+1; i++){
			for(int j = posY-1; j <= posY+1; j++){
				field[i][j] = true;
			}
		}
	} // spawns life.

	void Thanos_fart(Field& field){
		for(int i = 0; i < N; i++){
			for(int j = 0; j < N; j++){
				if(rand() % 2 == 0){field[i][j] = false;}
			}
		}
	} // kills ~50% of all life, do not translate function name.

	void invert(Field& field){
		for(int i = 0; i < N; i++){for(int j = 0; j < N; j++){if(rand()%5==1){field[i][j] = !field[i][j];}}}
	} // inverts some game pixels, most likely not all because that would cause extinction.

	std::vector<void(*)(Field&)> events = {
		Event::life_spawn
	}; // put events that you want to see in-game here, each event from pointer vector has a chance to be called.
}
