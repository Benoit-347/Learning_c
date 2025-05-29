// register variables requests the compiler to store the variable at a certain register at the computer that the compiler is free to ignore.
// the operations therefore on, to and from the register will make the program faster. 
        
        //Syn:
        int main(){
        register int x =10;
        }
        //scope: can only be done on automatic variables (even formal fn parameters)
        //resterictions: type of variable and number of register variables are limited; machine to machine

        /*
        initializing:
        Only automatic variables have storage assigned to them when declared. BUT by default standard declaration like static int x; is considered a definition and allocates storage.
            Exclusively in the case where extern static int x; is applied, only declaration takes place.
        When only declared, automatic variables (even the ones in main fn as it is in main block) are intialized to random value.
        While external and stiatic when only defined (known layman's terms declared) are initialzed to 0
        
        Initializing arrays:
            When initializing arrays with unspecified size at the brackets:
                arr[] = {2, 3, 4, 5, 6, 7} the compiler computes the length by conting the number of initializers.*/