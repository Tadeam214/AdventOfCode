#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>

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
    unsigned int look;
    bool world[with * hieght] = {0};

    std::vector <long long> startPosX;
    std::vector <long long> startPosY;
    std::vector <long long> posX;
    std::vector <long long> posY;
    std::vector <int> velocityX;
    std::vector <int> velocityY;

    char line[256];

    while(!input.eof()){
        input.getline(line, 256);

        int pos = 0;
        startPosX.push_back( readint(line, &pos, 256) + with * with * hieght);
        startPosY.push_back( readint(line, &pos, 256) + with * hieght * hieght);
        velocityX.push_back( readint(line, &pos, 256));
        velocityY.push_back( readint(line, &pos, 256));
        

    }

    startPosX.shrink_to_fit();
    startPosY.shrink_to_fit();
    posX.resize(startPosX.size());
    posY.resize(startPosX.size());
    velocityX.shrink_to_fit();
    velocityY.shrink_to_fit();

    int score = hieght + 1;
    int fristRoot;

    for(int p = 0; p < hieght; p++){
        look = p;
        int amountOnY[hieght] = {0};

        for(int i = 0; i < posX.size(); i++){

            posY[i] = startPosY[i];
            posY[i] = (posY[i] + (velocityY[i] * (long long)look)) % ((long long)hieght);
            
            amountOnY[posY[i]] += 1;
        }

        double center = 0;

        for(int w = 0; w < hieght; w++){
            center += amountOnY[w] * w / (double)startPosX.size();
        }
        center = round(center);
        int distance = 1;
        int coverd = 0;
        
        for(distance = 1; distance < hieght ; distance += 2){
            coverd += amountOnY[((int) center)+(distance-1) / 2];
            if(distance > 1){
                coverd += amountOnY[((int) center)-(distance-1) / 2];
            }
            // most means 3/4 right
            if(coverd > startPosX.size() * 3 / 4){
                break;
            }
        }
        if(distance < score ){
            score = distance;
            fristRoot = p;
        }
    }
    score = with + 1;
    int secondRoot;

    for(int p = 0; p < with; p++){
        look = fristRoot + p * hieght;
        int amountOnX[with] = {0};

        for(int i = 0; i < posX.size(); i++){
            posX[i] = startPosX[i];
            posX[i] = (posX[i] + (velocityX[i] * (long long)look)) % ((long long)with) ;
            
            amountOnX[posX[i]] += 1;
        }

        double center = 0;

        for(int w = 0; w < with; w++){
            center += amountOnX[w] * w / (double)startPosX.size();
        }
        center = round(center);
        int distance = 1;
        int coverd = 0;
        
        for(distance = 1; distance < with ; distance += 2){
            coverd += amountOnX[((int) center)+(distance-1) / 2];
            if(distance > 1){
                coverd += amountOnX[((int) center)-(distance-1) / 2];
            }
            
            if(coverd > startPosX.size() * 3 / 4){
                break;
            }
        }
        if(distance < score ){
            score = distance;
            secondRoot = p;
        }
    }

    look = fristRoot + secondRoot * hieght;

    for(int i = 0; i < posX.size(); i++){
        posX[i] = startPosX[i];
        posX[i] = (posX[i] + (velocityX[i] * (long long)look)) % ((long long)with) ;

        posY[i] = startPosY[i];
        posY[i] = (posY[i] + (velocityY[i] * (long long)look)) % ((long long)hieght);
        
        world[posX[i] + with * posY[i]] = 1;
    }

    for(int i = 0; i < with*hieght; i++){
        if(i % with == 0){
            std::cout << std::endl;
        }
        if(world[i]){
            std::cout << '#';
        }
        else{
            std::cout <<' ';
        }
    
    }
    std::cout << std::endl << look;
    return 0;
}

