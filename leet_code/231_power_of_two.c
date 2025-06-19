bool isPowerOfTwo(int n) {
    if (n == 1)
        return 1;
    else{
        
        while (!n%2 && n){
            n = n/2;
        }
        if (n==0)
            return 1;
    }
    return 0;
}