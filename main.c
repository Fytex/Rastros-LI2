#include <stdio.h>
#include "data/state.h"
#include "interface/interface.h"

int main() {

    State *state = initialize_state();
    interpreter(state);

    return 0;
}