#include<iostream>
#include<fstream>
#include<cmath>

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

int main(){
    std::ifstream input;
    input.open("input.txt", std::ofstream::in );
    if (input.fail()) {
		std::cout << "Error happend with inFile.";
		exit(1);
	}

    const int with = 141;
    const int hieght = 141;
    int end, start;

    bool world[with * hieght] = {0};
    int score[with * hieght];
    int backScore[with * hieght];
    short visited[with * hieght] = {0};

    unsigned long long total = 0;

    for(int i = 0; i < with * hieght; i++){
        char temp ;
        input >> temp;

        if(temp == 'E'){
            end = i;
        }
        if(temp == 'S'){
            start = i;
        }
        if(temp == '#'){
            world[i] = 1;
        }
        score[i] = with * hieght;
        backScore[i] = with * hieght;
    }

    pathfind(end, 0, with, with * hieght, world, score);
    pathfind(start, 0, with, with * hieght, world, backScore);

    for(int i = 0; i < with * hieght; i++){
        if(backScore[i] + score[i] == score[start]){
            int x = (i % with);
            int y = (i / with);

            for(int p = 0; p < with * hieght; p++){
                if(!world[p] && p != i){
                    int tempx = (p % with);
                    int tempy = (p / with);

                    int distance = abs(x - tempx) + abs(y - tempy);

                    if(distance <= 20){
                        
                        if((score[i] - distance) - score[p] >= 100){
                            visited[i] += 1;
                            total++;
                        }
                    }
                }   
            }
        }
    }
    //prints the world
    for(int i = 0; i < with * hieght; i++){
        if(visited[i] > 0){
            std::cout << visited[i] % 10;
        }
        else if(world[i] == 1){
            std::cout << '#';
        }
        else{
            std::cout << ' ';
        }
        if(i % with == with - 1){
            std::cout << std::endl;
        }
    }
    
    std::cout << total;
    return 0;
}