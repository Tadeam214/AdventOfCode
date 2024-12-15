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
bool canBePushed(int position, int direction, char world[], bool pushMap[]){
    pushMap[position] = 1;
    bool can = 1;

    if(world[position + direction] == '#'){
        can = 0;
        return 0;
    }
    else if(world[position + direction] == '.'){
        if(world[position] == '[' || world[position] == ']'){
            if(world[position] == '['){
                if(pushMap[position + 1] == 1){
                    return 1;
                }
                else{
                    return canBePushed(position + 1, direction, world, pushMap);
                }
            }
            else{
                if(pushMap[position - 1] == 1){
                    return 1;
                }
                else{
                    return canBePushed(position - 1, direction, world, pushMap);
                }
            }
        }
        else{
            return 1;
        }
    }
    else{
        if(world[position] == '[' || world[position] == ']'){
            if(world[position] == '['){
                if(!(pushMap[position + 1] == 1)){
                    can = can & canBePushed(position + 1, direction, world, pushMap);
                }
            }
            else{

                if(!(pushMap[position - 1] == 1)){
                    can = can & canBePushed(position - 1, direction, world, pushMap);
                }
                
            }
        }
        can = can & canBePushed(position + direction, direction, world, pushMap);
    }
    return can;
}
void pushVerticaly(int direction, int size, char world[], bool pushMap[]){
    if(direction < 0){
        for(int i = 0; i < size; i++){
            if(pushMap[i]){
                world[i + direction] = world[i];
                world[i] = '.';
                
            }
        }
    }
    else{
        for(int i = size - 1; i >= 0; i--){
            if(pushMap[i]){
                world[i + direction] = world[i];
                world[i] = '.';
                
            }
        }
    }
}
int main(){
    std::ifstream input;
    input.open("input.txt", std::ofstream::in );
    if (input.fail()) {
		std::cout << "Error happend with inFile.";
		exit(1);
	}

    
    const int with = 50 * 2;
    const int hieght = 50;
    char world[with * hieght] = {'.'};
    bool pushMap[with * hieght] = {0};

    std::vector <int> commands;
    int playerPos;
    
    for(int i = 0; i < hieght * with / 2; i++){
        char temp;
        input >> temp;

        if(temp == '@'){
            world[i*2] = '@';
            world[i*2 + 1] = '.';
        }
        else{
            if(temp == 'O'){
                world[i*2] = '[';
                world[i*2 + 1] = ']';
            }
            else{
                world[i*2] = temp;
                world[i*2 + 1] = temp;
            }
        }
    }

    for(int i = 0; i < hieght * with / 2; i++){
        if (world[i] == '@'){
            playerPos = i;
            break;
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
    
    commands.pop_back();
    commands.shrink_to_fit();

    for(int i = 0; i < commands.size(); i++){
        
        if(commands[i] == 1 || commands[i] == -1){
            movePlayer(&playerPos, commands[i], world);
        }
        else{
            if (canBePushed(playerPos, commands[i], world, pushMap)){

                pushVerticaly(commands[i], with * hieght, world, pushMap);
                playerPos += commands[i];
            }

            for(int i = 0; i < with * hieght; i++){
                pushMap[i] = 0;
            }  
        }
    }

    //print the world
    for(int p = 0; p < with * hieght; p++){
        if(p % with == 0){
            std::cout << std::endl;
        }
        std::cout << world[p];
    }
    int total = 0;

    for(int i = 0; i < with * hieght; i++){
        if(world[i] == '['){
            total += i % with + i / with * 100 ;
        }
    }
    std::cout << std::endl << total;
    return 0;
}