#include<iostream>
#include<fstream>
#include<vector>

int readint(char string[], int * position, int lenght){
    bool writing = 0;
    int read = 0, i = *position;
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
int ifEvenHowMany(unsigned long long value){
    int i = 0;
    unsigned long long temp = 1;
    while(value >= temp){
        temp *= 10;
        i++;
    }
    if(i % 2 == 0){
        return i / 2;
    }
    else{
        return 0;
    }
}

int main(){

    std::ifstream input;
    input.open("input.txt", std::ofstream::in );
    if (input.fail()) {
		std::cout << "Error happend with inFile.";
		exit(1);
	}

    std::vector <unsigned long long> stones;
    std::vector <unsigned long long> amount;
    
    unsigned long long pow[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000, 10000000000, 100000000000};
    int look = 75;
    unsigned long long total = 0;

    int pos = 0;
    char line[256] = {0};
    input.getline(line, 256);
    int temp = readint(line, &pos, 256);

    while (temp >= 0){
        stones.push_back(temp);
        amount.push_back(1);
        temp = readint(line, &pos, 256);
    }
    input.close();
    
    for(int p = 0; p < look; p++){
        temp = stones.size();
        std::cout << temp << ", " ;

        for(int i = 0; i < temp; i++){
            
            if(stones[i] == 0){
                stones[i] = 1;
            }
            else{
                int nubearEven = ifEvenHowMany(stones[i]);
                if(nubearEven > 0){
                    unsigned long long prev = stones[i];
                    stones[i] = stones[i] / pow[nubearEven];
                    amount.push_back(amount[i]);
                    stones.push_back(prev % pow[nubearEven]);
                }
                else{
                    stones[i] *= 2024;
                }
            }
        }
        //merge
        for(unsigned int i = 0; i < stones.size()-1; i++){
            for(unsigned int p = i + 1; p < stones.size(); p++){
                if(stones[i] == stones[p]){
                    amount[i] += amount[p];
                    stones.erase(stones.begin() + p);
                    amount.erase(amount.begin() + p);
                }
            }
        }
    }

    for(int i = 0; i < amount.size(); i++){
        total += amount[i];
    }
    
    std::cout<< std::endl << stones.size() << " : " << total - stones.size() << std::endl << total;

    return 0;
}
