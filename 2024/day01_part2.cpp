#include<iostream>
#include<fstream>

int main(){
    std::ifstream startFile;
    // uses presorted data from excel, part 1 was done by excel
    startFile.open("sort.txt", std::ofstream::in );
    int temp;
    int left[1000];
    int right[1000];

    if (startFile.fail()) {
		std::cout << "Error happend with inFile.";
		exit(1);
	}
    for(int i = 0; i <1000; i++){
        startFile >> temp;
        left[i]= temp;
    }
    for(int i = 0; i <1000; i++){
        startFile >> temp;
        right[i]= temp;
    }
    unsigned long int total;
    for(int i = 0; i <1000; i++){
        temp = left[i];
        for(int p = 0; p <1000; p++){
            if(temp < right[p]){
                break;
            }
            if(temp == right[p]){
                total += temp;
            }
        
        }
    }
    std::cout << total;
    return 0;
}