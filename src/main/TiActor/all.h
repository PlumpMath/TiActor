
#ifndef TIACTOR_ALL_H
#define TIACTOR_ALL_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <stdio.h>

#include "TiActor/basic/stddef.h"
#include "TiActor/basic/stdint.h"

TIACTOR_API
int only_test_for_api_export() {
    // Do nothing!!
    printf("Only test for api export.\n");
    return 0;
}

#endif  /* TIACTOR_ALL_H */
