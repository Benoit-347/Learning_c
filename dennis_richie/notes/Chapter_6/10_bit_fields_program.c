# include <stdio.h>

int main(){
    struct bit_fields{
        unsigned int flag_1 : 1;
        unsigned int flag_2 : 1;
        unsigned int flag_3 : 2;
    } bit_field_obj;

    bit_field_obj.flag_1 = 1;
    bit_field_obj.flag_2 = 0;
    bit_field_obj.flag_3 = 0;

    if (bit_field_obj.flag_1 || bit_field_obj.flag_2 || bit_field_obj.flag_3)
        printf("Val exists\n");
    else
        printf("Empty\n");

    return 0;
}