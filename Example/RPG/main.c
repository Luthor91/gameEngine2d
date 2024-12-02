#include "../../Core/core.h"

int main(int argc, char* argv[]) {

    if (Init_All() == 0)    
        printf("Main: ERROR INIT\n");
    else                    
        printf("Main: Success\n");



    changeState(STATE_DEBUGGING);
    while (current_state != STATE_EXIT)
        handleState();

    Exit_All();

    return 0;
}
