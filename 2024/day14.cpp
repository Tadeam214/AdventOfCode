#include<iostream>
#include<fstream>
#include<vector>

//read int got a minus upgrade

int readint(char string[], int * position, int lenght){
    bool writing = 0, minus = 0;
    int read =0,i = *position;

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

        if(string[i] =='-' && !writing){
            minus = true;
        }
    }
    *position = i;
    return read * (minus ? -1 : 1);
}

int main(){
    std::ifstream input;
    input.open("input.txt", std::ofstream::in );
    if (input.fail()) {
		std::cout << "Error happend with inFile.";
		exit(1);
	}

    const unsigned int with = 101;
    const unsigned int hieght = 103;
    const unsigned int look =  103*63+4;
    bool world[with * hieght] = {0};
    unsigned long long total = 0;
    int qwadrant[4];

    std::vector <long long> posX;
    std::vector <long long> posY;
    std::vector <int> velocityX;
    std::vector <int> velocityY;

    char line[256];

    while(!input.eof()){
        input.getline(line, 256);

        int pos = 0;
        posX.push_back( readint(line, &pos, 256) + look * with);
        posY.push_back( readint(line, &pos, 256) + look * hieght);
        velocityX.push_back( readint(line, &pos, 256));
        velocityY.push_back( readint(line, &pos, 256));
        

    }

    posX.shrink_to_fit();
    posY.shrink_to_fit();
    velocityX.shrink_to_fit();
    velocityY.shrink_to_fit();

    for(int i = 0; i < posX.size(); i++){
        posX[i] = (posX[i] + (velocityX[i] * (long long)look)) % ((long long)with) ;
        posY[i] = (posY[i] + (velocityY[i] * (long long)look)) % ((long long)hieght);
        world[(posX[i]) + ((posY[i] ) * with)] = 1;
    }

    for(int i = 0; i < posX.size(); i++){
        if(posX[i] != with/2 && posY[i] != hieght/2){
            int index = 0;
            if(posX[i] > with/2){
                index +=1;
            }
            if(posY[i] > hieght/2){
                index +=2;
            }
            qwadrant[index] += 1;
        }
    }

    for(int i = 0; i < with*hieght; i++){
        if(i % with == 0){
            std::cout << std::endl;
        }
        if(world[i]){
            std::cout << '#';
        }
        else{
            std::cout <<'.';
        }
    }
    total = qwadrant[0] * qwadrant[1] * qwadrant[2] * qwadrant[3];
    std::cout << std::endl << total;
    return 0;
}

