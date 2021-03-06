/*
# This file is Copyright 2003 Dean Hall.
#
# This file is part of the Python-on-a-Chip program.
# Python-on-a-Chip is free software: you can redistribute it and/or modify
# it under the terms of the GNU LESSER GENERAL PUBLIC LICENSE Version 2.1.
#
# Python-on-a-Chip is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# A copy of the GNU LESSER GENERAL PUBLIC LICENSE Version 2.1
# is seen in the file COPYING up one directory from this.
*/


/**
 * Function Object Unit Tests
 * Tests the Function Object implementation.
 */


#include "CuTest.h"
#include "pm.h"


#define HEAP_SIZE 0x2000


/* BEGIN unit tests ported from Snarf */
/**
 * The following source code was compiled to an image using pmImgCreator.py
 * from svn revision [193] using this command line:
 *
 *      ../../tools/pmImgCreator.py  -c -s -o utco.img.c utco.py
 *

def main():

    s = 0
    A = (0,1,2,3)
    B = (3,2,1,0)

    for i in A:
        s += i

    for i in B:
        s -= i

    for i in A:
        for j in B:
            s += i*j

    return s

main()

 */
extern uint8_t test_code_image0[];


/**
 * Tests func_new():
 *      retval is OK
 *      pimg points to one byte past the end of the image after image is loaded
 */
void
ut_func_new_000(CuTest *tc)
{
    uint8_t heap[HEAP_SIZE];
    PmReturn_t retval;
    uint8_t const *pimg = test_code_image0;
    pPmObj_t pcodeobject;
    pPmObj_t pfuncobject;
    pPmObj_t pglobals;

    pm_init(heap, HEAP_SIZE, MEMSPACE_RAM, C_NULL);
    retval = obj_loadFromImg(MEMSPACE_PROG, &pimg, &pcodeobject);
    retval = dict_new(&pglobals);

    /* Check the return value of the function */
    retval = func_new(pcodeobject, pglobals, &pfuncobject);
    CuAssertTrue(tc, retval == PM_RET_OK);
}
/* END unit tests ported from Snarf */


/** Make a suite from all tests in this file */
CuSuite *getSuite_testFuncObj(void)
{
    CuSuite* suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, ut_func_new_000);

    return suite;
}
