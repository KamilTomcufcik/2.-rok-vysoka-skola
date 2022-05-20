#include "a_train.h"
#include <stdio.h>

// Testovaci subor pre vlak
int main(){
    struct car* train = NULL;
    train = add_car(train,"Presov");
    train = add_car(train,"Bratislava");
    train = add_car(train,"Levoca");
    train = add_car(train,"Spiska Nova Ves");
    printf("\n\n\n");
    print_train(train);
    clear_train(train,"Levoca");
    // printf("zo\n");
    print_train(train);
    // printf("asda\n");
    // cancel_train(train);
    print_train(train);

    return 0;
}
