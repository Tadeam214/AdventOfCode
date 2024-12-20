#include<iostream>
#include<fstream>
void pathFind(int pos, int direction, char world[], int score[], int startScore, int with){
    int directions[] = {1, -with, -1, with};
    if(startScore <= score[pos] || score[pos] == -1){
        score[pos] = startScore;

        if(world[pos + directions[direction]] != '#'){
            pathFind(pos + directions[direction], direction, world, score, startScore + 1, with);
        }
        if(world[pos + directions[(direction + 1) % 4]] != '#'){
            pathFind(pos + directions[(direction + 1) % 4], (direction + 1) % 4, world, score, startScore + 1001, with);
        }
        if(world[pos + directions[(direction + 3) % 4]] != '#'){
            pathFind(pos + directions[(direction + 3) % 4], (direction + 3) % 4, world, score, startScore + 1001, with);
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
    int start, end;

    char world[with * hieght];
    int score[with * hieght];
    int backScore[with * hieght];

    for(int i = 0; i < with * hieght; i++){
        char temp ;
        input >> temp;
        world[i] = temp;
        if(temp == 'E'){
            end = i;
        }
        if(temp == 'S'){
            start = i;
        }

        score[i] = -1;
        backScore[i] = -1;
    }
    
    pathFind(start, 0, world, score, 0, with);

    std::cout << score[end];

    return 0;
}