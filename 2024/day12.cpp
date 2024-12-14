#include<iostream>
#include<fstream>
void check(int i, int index, char world[], int claim[], int perimetr[], int area[], const int lenght, const int with){
    claim[i] = index;
    area[index] += 1;
    if(i + lenght < lenght * with && world[i + lenght] == world[i]){
        if(claim[i+lenght] == 0){
            check(i + lenght, index, world, claim, perimetr, area, lenght, with);
        }
    }
    else{
        perimetr[i] = perimetr[i] | 1;
    }
    if(i - lenght >= 0 && world[i - lenght] == world[i]){
        if(claim[i-lenght] == 0){
            check(i - lenght, index, world, claim, perimetr, area, lenght, with);
        }
    }
    else{
        perimetr[i] = perimetr[i] | 2;
    }
    if(!(i % lenght == lenght - 1)  && world[i + 1 ] == world[i]){
        if(claim[i + 1] == 0){
            check(i + 1, index, world, claim, perimetr, area, lenght, with);
        }
    }
    else{
        perimetr[i] = perimetr[i] | 4;
    }
    if((!(i % lenght == 0))  && world[i - 1 ] == world[i]){
        if(claim[i - 1] == 0){
            check(i - 1, index, world, claim, perimetr, area, lenght, with);
        }
    }
    else{
        perimetr[i] = perimetr[i] | 8;
    }
}


int main(){
    const int lenght = 140;
    const int with = 140;
    unsigned long long total = 0;
    std::ifstream input;
    input.open("input.txt", std::ofstream::in );
    if (input.fail()) {
		std::cout << "Error happend with inFile.";
		exit(1);
	}
    char world[lenght* with];
    int claim[lenght* with] = {0};
    int perimetr[lenght* with] = {0};
    int area[lenght* with] = {0};
    for(int i = 0; i < lenght * with; i++){
        char temp;
        input >> temp;
        world[i] = temp;
    }
    int index = 0;
    for(int i = 0; i < lenght * with; i++){
        if(claim[i] == 0){
            index++;
            check(i , index, world, claim, perimetr, area, lenght, with);
        }
    }
    
    for(int i = 1; i < index + 1; i++){
        int edges = 0;
        for(int x = 0; x < lenght; x++){
            bool left = 0, right = 0;
            for(int y = 0; y < with; y++){
                if(claim[y * lenght + x] == i){
                    if(perimetr[y * lenght + x] & 4){
                        left = 1;
                    }
                    else{
                        edges += left;
                        left = 0;
                    }
                    if(perimetr[y * lenght + x] & 8){
                        right = 1;
                    }
                    else{
                        edges += right;
                        right = 0;
                    }
                }
                else{
                    edges += left;
                    left = 0;
                    edges += right;
                    right = 0;
                }
            }
            edges += left;
            edges += right;
        }
        for(int x = 0; x < lenght; x++){
            bool left = 0, right = 0;
            for(int y = 0; y < with; y++){
                if(claim[x * lenght + y] == i){
                    if(perimetr[x * lenght + y] & 1){
                        left = 1;
                    }
                    else{
                        edges += left;
                        left = 0;
                    }
                    if(perimetr[x * lenght + y] & 2){
                        right = 1;
                    }
                    else{
                        edges += right;
                        right = 0;
                    }
                }
                else{
                    edges += left;
                    left = 0;
                    edges += right;
                    right = 0;
                }
            }
            edges += left;
            edges += right;
        }
        total += area[i] * edges;
    }
    for(int i = 0; i < lenght * with; i++){
        if(i % lenght == 0){
            std::cout << std::endl;
        }
        if(perimetr[i] != 0){
            std::cout << (char)('a' + perimetr[i] - 1);
        }
        else{
            std::cout << ' ';
        }
    }
    
    std::cout << std::endl << total ;
    return 0;
}