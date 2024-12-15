#include<iostream>
#include<fstream>
#include<vector>

void movePlayer(int * playerPos, int direction, char world[]){
    bool canPush = 1;
    int i = 0;
    int pos = *playerPos;

    while(true){
        i++;
        pos += direction;
        if(world[pos] == '#'){
            canPush = 0;
            break;
        }
        else if(world[pos] == '.'){
            break;
        }
    }

    if(canPush){
        for(int p = 0; p < i; p++){
            world[pos] = world[pos - direction];
            pos -= direction;
        }
        world[pos] = '.';
        *playerPos += direction; 
    }
}

int main(){
    std::ifstream input;
    input.open("input.txt", std::ofstream::in );
    if (input.fail()) {
		std::cout << "Error happend with inFile.";
		exit(1);
	}

    
    const int with = 50;
    const int hieght = 50;
    char world[with * hieght] = {'.'};

    std::vector <int> commands;
    int playerPos;

    for(int i = 0; i < with * hieght; i++){
        char temp;
        input >> temp;
        world[i] = temp;

        if(temp == '@'){
            playerPos = i;
        }
    }

    while(!input.eof()){
        char temp;
        input >> temp;

        switch (temp){
        case '<':
            commands.push_back(-1);
            break;
        case '>':
            commands.push_back(1);
            break;
        case '^':
            commands.push_back(-with);
            break;
        case 'v':
            commands.push_back(with);
            break;
        }
        
    }

    commands.shrink_to_fit();

    for(int i = 0; i < commands.size(); i++){
        movePlayer(&playerPos, commands[i], world);
    }

    //print the world
    for(int p = 0; p < with * hieght; p++){
        if(p % with == 0){
            std::cout << std::endl;
        }
        std::cout << world[p];
    }
    unsigned long long total = 0;

    for(int i = 0; i < with * hieght; i++){
        if(world[i] == 'O'){
            total += i % with + i / with * 100;
        }
    }
    std::cout << std::endl << total;
    return 0;
}