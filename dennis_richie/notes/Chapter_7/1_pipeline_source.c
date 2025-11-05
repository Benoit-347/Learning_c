// To Run: 1. compiler source and destination c programs, then run BOTH the compiled files simantaneously along with this syn <source> | <destination> 
    // Runs program <source> first then forward the output obtained as input to stdio of next program and runs program <destination>.
# include <stdio.h>

int main(){
    printf("This is the source text. If this appears into ur other progarm, pipelinining succesfull\n");
    printf("1 2 3 4 5");

    return 0;
}