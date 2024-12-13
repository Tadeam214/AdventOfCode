#include<iostream>
#include<fstream>


int main(){
    std::ifstream input;
    input.open("input.txt", std::ofstream::in );
    if (input.fail()) {
		std::cout << "Error happend with inFile.";
		exit(1);
	}
    // in later days i will make it easier to edit world size
    char world[140*141];
    int total = 0;

    for(int i = 0; i < 140*141; i++){
        //safety strip rather them using more logic in code, I will use more memory.
        if(i % 141 == 0){
           world[i] = 0; 
        }
        else{
            input >> world[i];
        }
        
    }

    for(int i = 0; i < 140*141; i++){
        
        if(world[i] == 'A'){
            bool found = 1;
            int pos;
            for(int p = 0; p < 2; p++){
                
                pos = (i + 141) + ((p == 0) ?  1 : -1);
                if(pos > 140 *141 || pos < 0){
                    found = 0;
                    break;
                } 
                bool M =0;
                if(world[pos] == 'M'){
                    M = 1;
                }
                else if (world[pos] != 'S'){
                    found = 0;
                    break;
                }
                pos = (i - 141) + ((p == 0) ?  -1 : 1);

                if(pos > 140 *141 || pos < 0){
                    found = 0;
                    break;
                }
                if(world[pos] == 'M'){
                    if(M){
                        found = 0;
                        break;
                    }
                }
                else if (world[pos] == 'S'){
                    if(!M){
                        found = 0;
                        break; 
                    }
                }
                else{
                    found = 0;
                    break;
                }
            
            }
            if(found){
                total++;
            }
        }
    }
    std::cout << total;
    return 0;
}