
// warning this code in it is curent form dosen't work on many data sets.


#include<iostream>
#include<fstream>
void pathFind(int pos, int direction, char world[], int score[], int startScore, int with, bool* endHorzontaly = NULL, int end = -1){
    int directions[] = {1, -with, -1, with};
    if(startScore <= score[pos] || score[pos] == -1){
        score[pos] = startScore;

        if(end != -1 && pos == end){
            *endHorzontaly = (direction + 1) % 2;
        }

        if(world[pos + directions[direction]] != '#'){
            pathFind(pos + directions[direction], direction, world, score, startScore + 1, with, endHorzontaly, end);
        }
        if(world[pos + directions[(direction + 1) % 4]] != '#'){
            pathFind(pos + directions[(direction + 1) % 4], (direction + 1) % 4, world, score, startScore + 1001, with, endHorzontaly, end);
        }
        if(world[pos + directions[(direction + 3) % 4]] != '#'){
            pathFind(pos + directions[(direction + 3) % 4], (direction + 3) % 4, world, score, startScore + 1001, with, endHorzontaly, end);
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
    char world[with * hieght];
    int score[with * hieght];
    int backScore[with * hieght];

    int start, end;

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

    score[start] = 0;
    bool endedHorizontaly = 0;

    pathFind(start, 0, world, score, 0, with, &endedHorizontaly, end);

    if(endedHorizontaly){
        pathFind(end, 2, world, backScore, 0, with);
    }
    else{
        pathFind(end, 3, world, backScore, 0, with);
    }

    int bestPathScoreStart = backScore[start];
    int bestPathScoreEnd = score[end];

    if(backScore[start] == score[end]){
        bestPathScoreStart -= 1000;
    }

    bestPathScoreStart -= 0;
    unsigned long long total = 0;

    for(int i = 0; i < with * hieght; i++){

        if(backScore[i] + score[i] == bestPathScoreStart || backScore[i] + score[i] == bestPathScoreEnd){
            std::cout << 'O';
            total++;
        }
        else{
            std::cout << world[i];
        }
        if(i % with == with - 1){
            std::cout << std::endl;
        }
    }

    std::cout << total;
    return 0;
}