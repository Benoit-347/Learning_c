# include <stdio.h>

double atof(char str[]){
    int i = 0;
    double  result = 0;
    char ch;

    // accomodating sign
    char neg_flag = 1;
    neg_flag = (str[i] == '-') ? -1 : 1;

    if (str[i] == '+' || str[i] == '-')
        i++;

    for (; (ch = str[i]) != '\0'; i++){

        if (ch >= '0' && ch <= '9')
            result = result*10 + (ch - '0');
        else
            break;
    }

    // extra computaion for the remaining digits
    if (ch == '.'){
        i++;
        float num2 = 0, power = 1;

        for (; (ch = str[i]) != '\0'; i++){
            power *=10;        
            if (ch >= '0' && ch <= '9')
                num2 = num2*10 + (ch - '0');
            else
                break;
        }
        result =  (result + num2/power); 
        
        if (ch == 'e' || ch == 'E'){
            int temp = str[++i] - '0';
            power  = 1;
            for (int i = 0; i<temp; i++)
                power *= 10;
            result = result * power;
        }
    }
    
    

    return result*neg_flag;
}

int main(){
    char str[] = "-10.547e5";
    printf("The float: %f\n", atof(str));
}