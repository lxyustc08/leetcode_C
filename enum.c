#include <stdio.h>

int main(int argc, char const *argv[])
{
    enum  {Mon=1, Tues, Wen, Thu, Fri, Sat, Sun} day;
    scanf("%d", &day);
    Tues;
    switch(day)
    {
        case Mon: printf("Monday"); break;
        case Tues: printf("Tuesday"); break;
        case Wen: printf("Wensday"); break;
        case Thu: printf("Thuday"); break;
        case Fri: printf("Friday"); break;
        case Sat: printf("Saturday"); break;
        case Sun: printf("Sunday"); break;
        default: printf("Error!"); break;
    }
    printf("\n");
    return 0;
}
