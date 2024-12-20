#include<iostream>
#include<fstream>

void pathfind(int pos, int score, int with, int size, bool world[], int scores[]){
    if(score < scores[pos]){
        scores[pos] = score;

        if(pos % with != with -1 && !world[pos + 1]){
            pathfind(pos + 1, score + 1, with, size, world, scores);
        }

        if(pos + with < size && !world[pos + with]){
            pathfind(pos + with, score + 1, with, size, world, scores);
        }

        if(pos - with >= 0 && !world[pos - with]){
            pathfind(pos - with, score + 1, with, size, world, scores);
        }

        if(pos % with != 0 && !world[pos - 1]){
            pathfind(pos - 1, score + 1, with, size, world, scores);
        }
    }
}

int readint(char string[], int * position, int lenght){
    bool writing = 0;
    int read = 0,i = *position;

    for(i ; i < lenght; i++){
        if(string[i] =='\000'){
            break;
        }
        if(string[i] < '0' || string[i] > '9'){
            if(writing){
                break;
            }
        }
        else{
            writing = true;
            read = read * 10 + string[i]- '0';
        }
    }
    *position = i;
    if(!writing){
        read = -1;
    }
    return read;
}

int main(){

    std::ifstream input;
    input.open("input.txt", std::ofstream::in );
    if (input.fail()) {
		std::cout << "Error happend with inFile.";
		exit(1);
	}

    const int with = 71;
    const int hieght = 71;
    const int read = 1024;

    bool corupted[with*hieght] = {0};
    int scores[with*hieght] = {0};

    for(int i = 0; i < with * hieght; i++){
        scores[i] = with * hieght;
    }

    char line[32];
    
    for(int i = 0; i < read; i++){

        int pos = 0;
        input.getline(line, 32);

        int x = readint(line, &pos, 32);
        int y = readint(line, &pos, 32);

        corupted[x + y * with] = 1;
    }

    //prints the world
    for(int i = 0; i < with * hieght; i++){

        if(i % with == 0){
            std::cout << std::endl;
        }
        if(corupted[i]){
            std::cout << '#';
        }
        else{
            std::cout << '.';
        }
    }

    pathfind(0, 0, with, with * hieght, corupted, scores);

    std::cout << std::endl <<scores[(with * hieght) - 1];
    return 0;
}