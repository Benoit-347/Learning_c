# include <stdio.h>
# include <strings.h>
# include <stdlib.h>

# define DAY_MAX 10
# define EVENT_MAX 100
struct diary{
    char name[DAY_MAX];
    int day;
    char event[EVENT_MAX];
};

typedef struct diary Diary;

void initialize_structs(Diary * weekly, int n){
    char * ch_ptr;
    printf("Reached here\n");
    for (int i = 0; i<n; i++){
        ch_ptr = weekly-> name;
        for (int i = 0; i<DAY_MAX; i++)
            *ch_ptr++ = 0;
        ch_ptr = weekly-> event;
        for (int i = 0; i<EVENT_MAX; i++)
            *ch_ptr++ = 0;
        weekly->day = 0;
        weekly++;
    }
}

void read_input(Diary * weekly, int n){

    for (int i = 0; i<n; i++){        
        printf("Enter Name of day: ");
        scanf("%s", weekly->name);
        printf("Enter date (int): ");
        scanf("%d", &weekly->day);
        printf("Enter event name: ");
        scanf(" %s", weekly->event);
        weekly++;
    }
}

void display_struct(Diary * weekly, int n){

    printf("\n=== Weekly Activity Report ===\n");
    printf("%-10s %-6s %-30s\n", "Day", "Date", "Activity");
    for (int i = 0; i<n; i++){        
        printf("%-10s ", weekly->name);
        printf("%-6d ", (weekly->day));
        printf("%-30s\n", weekly->event);
        weekly++;
    }
}

int main(){
    int n;
    printf("Enter number of records u want to enter: ");
    scanf("%d", &n);

    Diary * weekly__obj = (Diary *) malloc(sizeof(Diary)*n);

    printf("n is: %d\n", n);
    initialize_structs(weekly__obj, n);
    read_input(weekly__obj, n);
    display_struct(weekly__obj, n);

    return 0;
}