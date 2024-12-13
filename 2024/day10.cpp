#include<iostream>
#include<fstream>

int readint(char string[], int * position, int lenght){
    bool writing = 0;
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
    }
    *position = i;
    if(!writing){
        read = -1;
    }
    return read;
}
int travel(int hieght ,int Index, int world[],const int move[], bool checked[], const int lenght, const int with){
    int add = 0;
    if(hieght == 9 && world[Index] == 9){
        if(checked[Index]){
            return 0;
        }
        else{
            return 1;
        }
        
    
    }
    else{
        for(int p = 0; p < 4; p++){
            int temp = Index + move[p];
            if(temp < (lenght*(with + 1)) && temp > 0){
                if(world[temp] == hieght + 1){
                    add += travel(hieght + 1, temp, world, move, checked, lenght, with);
                }
            }
        }
    }
    return add;
}

int main(){
    const int lenght = 52;
    const int with = 52;
    const int move[] = {1, with + 1, -1, -(with + 1)};
    int world[lenght * (with + 1)];
    unsigned long long total = 0;
    bool checked[lenght * (with + 1)] = {0};
    int write[lenght * (with + 1)] = {0};
    
    std::ifstream input;
    input.open("input.txt", std::ofstream::in );
    if (input.fail()) {
		std::cout << "Error happend with inFile.";
		exit(1);
	}
    
    for(int i = 0; i < lenght * (with + 1); i++){
        if(i % (with + 1) == 0){
            world[i] = -1;
        }
        else{
            char temp;
            input >> temp;
            world[i] = temp - '0';
        }
    }
    for(int i = 0; i < lenght * (with + 1); i++){

        if(world[i] == 0){
            for(int w = 0; w < lenght * (with + 1); w++){
                if(checked[w]){
                    write[w] += 1;
                }
                checked[w] = 0;
            }
            
            int temp = travel(0, i, world, move, checked, lenght, with);
            std::cout << temp << std::endl;
            total += temp;
        }
        
    }
    for(int w = 0; w < lenght * (with + 1); w++){
        if(checked[w]){
            write[w] += 1;
        }
        checked[w] = 0;
    }
    for(int i = 0; i < lenght * (with + 1); i++){
        if(i % (with + 1) == 0){
            std::cout << std::endl;
            std::cout << write[i];
        }
        else if(write[i]> 0){
            std::cout << write[i];
        }
        else{
            std::cout << ' ';
        }
    }
    std::cout << total;
    return 0;
}