# include <stdio.h>

void clear_whitespace(char * s, int * i){   // shift i over whitespaces (skip all ' ')
    while (s[(*i)++] == ' ')   // cond is evaluated at the last causing the last i to incr,
        ;
    (*i)--;
}

// from i index of str1, cmp str1 and str2
char chk_seq_ch(char * expression, int * i, char * expr){
    clear_whitespace(expression, i);
    int temp_i = *i;
    int j = 0;

    while (expression[temp_i++] == expr[j++]){
        if (expr[j] == 0){
            *i = temp_i;
            return 1;
        }
    }
    return 0;
}


int str_to_int(char * arr, int * i){    // pass str arr and the index starting from the str int
    int num = 0;
    char ch;
    while ( (ch = arr[*i]) >= '0' && ch <= '9'){
        num = num*10 + (ch - '0');
        (*i)++; // this fn wven when exit, will keep i val at next element's index
    }
    return num;
}

// Eval to only evaluate the adds and mults
int eval_val_from_exp(char * expression, int *i, char * add, char * multi){   // This can ignore including the lets, but scope of lets may exist b/w them.
    int operand_1, operand_2, result;
    char ch;
    if (expression[*i] == '('){
        (*i)++;
        clear_whitespace(expression, i);

        // todo: adding numbers recurly
        if ( chk_seq_ch(expression, i, add) ){
            clear_whitespace(expression, i);
            if ( (ch = expression[*i]) == '(')
                operand_1 = eval_val_from_exp(expression, i, add, multi);
            else if (ch >= '0' && ch <= '9')
                operand_1 = str_to_int(expression, i);
            else if (ch == ')')
                return result;
            clear_whitespace(expression, i);

        }
    }
    else
        return str_to_int(expression, i);
}

int evaluate(char* expression) {
    char var_names[10][16] = {0};
    char var_names_index = 0;
    int var_values[10];
    char var_value_index = 0;
    char ch;

    char let[4] = "let";
    char add[4] = "add";
    char multi[5] = "mult";

    // when strs of let, add, etc match (endpoint of loop cond being ' ') perform its res ops
        // when let, take the var_name, into a 2D array of chars, the sections of chars divided by 0.
            // Now when taking value, after chk if ch is '(' then store the str of int, as int into the int arr.
                // evaling the ():
                /*current objectives:   1. allow continous evals for every operation of add or multi or..
                                            // just realized, there are no lets inside evals
                                        2. Maintain scope of var values
                                        maybe: eval let exprs properly
                */
    for (int i = 0; expression[i]; i++){

        // chk let
        int j = 0;
        if (chk_seq_ch(expression, &i, let)){
            clear_whitespace(expression, &i);
            char temp_index = 0;
            while (expression[i] != ' ')     
                var_names[var_names_index][temp_index++] = expression[i++];
    
            i++;    // at endpoint of cond, the ending space is skipped.
            var_names[var_names_index][temp_index] = 0;
            var_names_index++;
            
            var_values[var_value_index++] = eval_val_from_exp(expression, &i);
            

        }
    }
    for (int i = 0; i<5; i++){
        printf("Var_name %d: %s\nVar_value %d: %d\n", i, var_names[i], i, var_values[i]);
    }

}


int main(){
    int i = 1;
    char * expression = "alet xyz 124"; // final test case: "(let x0 -1 x1 3 x2 3 x3 2 x4 -4 x5 4 x6 -2 x7 -4 x8 -4 x9 -1 (mult (mult x9 x0) (mult (let x0 1 x4 -1 x8 2 (add -10 -8)) (add (add (add (mult (mult (mult (mult -5 (mult 1 1)) -10) -6) (add x5 (add x6 (add x9 (mult 1 1))))) (let x0 -3 x7 -2 (mult (add (mult (mult 1 1) -2) x0) (let x0 -5 x9 0 (add (mult 1 1) -10))))) (mult (add (let x0 -1 x8 3 (mult (mult (mult 1 1) (mult 1 1)) x7)) (mult (mult (mult (mult 1 1) (mult 1 1)) -5) (add -6 (mult (mult 1 1) x0)))) -7)) -7))))"
    evaluate(expression);
}