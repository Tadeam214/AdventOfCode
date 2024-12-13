#include<iostream>
#include<fstream>
#include<cmath>
bool canExit(char world[]){
    int dir = 0;
    int X = 41;
    int Y = 73;
    
    for(int i = 0; i < 260*260; i++){
        int oldx = X;
        int oldy = Y;
        switch (dir){
        case 0:
            Y -= 1;
            break;
        case 1:
            X += 1;
            break;
        case 2:
            Y += 1;
            break;
        case 3:
            X -= 1;
            break;
        }
        if(X < 0 || X > 129 || Y < 0 || Y > 129){
            return 1;
        }
        else if(world[X + Y * 130] == '#'){
            X = oldx;
            Y = oldy;
            dir = (dir + 1) % 4;
        }
    }
    return 0;
}

int main(){
    std::ifstream input;
    input.open("input.txt", std::ofstream::in );
    if (input.fail()) {
		std::cout << "Error happend with inFile.";
		exit(1);
	}
    // in later days I will make it easier to changend the world size, but today I have underestimeted it's usefulness in debugging
    char world[130*130] = {'.'};
    bool visted[130*130]= {0};
    int playerX, playerY;
    int total = 0, dir = 0;

    for(int i = 0; i < 130*130; i++){
        char temp;
        input >> temp;
        if(temp == '^'){
            playerX = i % 130;
            playerY = floor(i / 130);
            world[i] = '.';
        }
        else{
        world[i] = temp; 
        }
    }
    visted[playerX + playerY * 130] = 0;

    while(true){
        int olddir = dir;
        int oldx = playerX;
        int oldy = playerY;
        switch (dir){
        case 0:
            playerY -= 1;
            break;
        case 1:
            playerX += 1;
            break;
        case 2:
            playerY += 1;
            break;
        case 3:
            playerX -= 1;
            break;
        }
        if(playerX < 0 || playerX > 129 || playerY < 0 || playerY > 129){
            break;
        }
        else if(world[playerX + playerY * 130] == '#'){
            playerX = oldx;
            playerY = oldy;
            dir = (dir + 1) % 4;
        }
        else{
            visted[playerX + playerY * 130] = 1;
        }
        
    }
    
    for(int i = 0; i < 130 * 130; i++){

        if(visted[i] == 1){
            world[i] = '#';
            if(!canExit(world)){
                total++;
            }
            world[i] = '.';
        }
    }

    for(int i = 0; i < 130*130; i++){
        if(i % 130 == 0){
            std::cout << std::endl;
        }
        
        if(visted[i]){
            
            std::cout << 'O';
        }
        else{
            std::cout << world[i];
        }
    }
    std::cout<< total;
    return 0;
}