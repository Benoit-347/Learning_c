extern int get_char();
extern int ungetchar(char);

// used to get a single entity here, being either number (neg or postive) or other.
// if its a number, create a repition custom to it alone, such that until the getchar in not int, it keeps taking num.
int get_element(){
    int ch;
    extern double number;
    int neg_flag = 1;
    number = 0;

    ch = get_char();
    while (ch == ' ')
            ch = get_char();
    
    if (ch == '-'){
        ch = get_char();
        if (ch >= '0' && ch <='9')
            neg_flag = -1;
        else{
            ungetchar(ch);
            ch = '-';
        }
    }
    if (ch >= '0' && ch <='9'){
        while(ch >= '0' && ch <='9'){
            number = number*10 + ch - '0';
            ch = get_char();
        }
        if (ch == '.'){
            int power = 1;
            ch = get_char();
            while(ch >= '0' && ch <='9'){
                number = number*10 + ch - '0';
                power *=10;
                ch = get_char();
            }
            number = number/power;
        }
        ungetchar(ch);
        number *= neg_flag;
        return '0';
    }
    else {
        return ch;
    }
}