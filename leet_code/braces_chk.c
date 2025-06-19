MAINTAIN MEMORY MORE EFFI ELSE 0ms

bool isValid(char* s) {
    char arr[10000];
    int arr_index = 0;
    char ch;
    for (int i = 0; (ch = s[i]); i++){
        switch(s[i]){
            case '(':
            case '[':
            case '{':
                arr[arr_index++] = ch;
                break;
            case ')':
                if (arr_index && arr[arr_index-1] == '(')
                    arr_index--;
                else
                    return 0;
                break;
            case ']':
                if (arr_index && arr[arr_index-1] == '[')
                    arr_index--;
                else
                    return 0;
                break;
            case '}':
                if (arr_index && arr[arr_index-1] == '{')
                    arr_index--;
                else
                    return 0;
                break;
            default:
                return -1;
        }
    }
    if (!arr_index)
        return 1;
    else
        return 0;

}