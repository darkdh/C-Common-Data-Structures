#include "heap/binary_heap.h"
#include "CUnit/Util.h"
#include "CUnit/Basic.h"


#define SIZE_MID_TEST       (1000)
#define MASK_YEAR           (100)
#define MASK_LEVEL          (200)

typedef struct Employ_ {
    int8_t cYear;
    int8_t cLevel;
    int32_t iId;
} Employ;

int32_t aPrim[SIZE_MID_TEST];
Employ* aNoPrim[SIZE_MID_TEST];


/* The functions to prepare and release test data. */
int32_t PrepareTestData();
void ReleaseTestData();


/* The item comparison methods. */
int32_t CompPrimMax(Item, Item);
int32_t CompNoPrimMin(Item, Item);


/* The item clean methods. */
void CleanNoPrim(Item);


/* The functions to register simple and advanced test suites. */
int32_t AddSimpleSuite();
int32_t AddAdvancedSuit();
void TestSimpleManipulate();
void TestAdvancedManipulate();


int32_t main()
{
    int32_t iRtnCode = SUCC;

    iRtnCode = PrepareTestData();
    if (iRtnCode != SUCC)
        goto EXIT;

    if (CU_initialize_registry() != CUE_SUCCESS) {
        iRtnCode = CU_get_error();
        goto EXIT;
    }

    /* Prepare the test suite for primitive item manipulation. */
    iRtnCode = AddSimpleSuite();
    if (iRtnCode != SUCC)
        goto CLEAN;

    /* Prepare the test suite for non-primitive item manipulation. */
    iRtnCode = AddAdvancedSuit();
    if (iRtnCode != SUCC)
        goto CLEAN;

    /* Launch all the tests. */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

CLEAN:
    CU_cleanup_registry();
EXIT:
    ReleaseTestData();
    return iRtnCode;
}


int32_t PrepareTestData()
{
    int32_t iRtnCode = SUCC;

    int32_t idx = 0;
    while (idx < SIZE_MID_TEST)
        aPrim[idx++] = idx;

    while (idx < SIZE_MID_TEST)
        aNoPrim[idx++] = NULL;

    int32_t idxRev;
    idx = 0;
    while (idx < SIZE_MID_TEST) {
        aNoPrim[idx] = (Employ*)malloc(sizeof(Employ));
        if (!(aNoPrim[idx])) {
            iRtnCode = ERR_NOMEM;
            break;
        }
        idxRev = SIZE_MID_TEST - idx;
        aNoPrim[idx]->iId = idxRev;
        aNoPrim[idx]->cYear = idxRev;
        aNoPrim[idx]->cLevel = idxRev;
        idx++;
    }

    return iRtnCode;
}


void ReleaseTestData()
{
    int32_t idx = 0;
    while (idx < SIZE_MID_TEST)
        free(aNoPrim[idx++]);
}


int32_t AddSimpleSuite()
{
    CU_pSuite pSuite = CU_add_suite("Simple Test Suite", NULL, NULL);
    if (!pSuite)
        return ERR_NOMEM;

    CU_pTest pTest = CU_add_test(pSuite, "Primitive item manipulation",
                     TestSimpleManipulate);
    if (!pTest)
        return ERR_NOMEM;

    return SUCC;
}


int32_t AddAdvancedSuit()
{
    CU_pSuite pSuite = CU_add_suite("Advanced Test Suite", NULL, NULL);
    if (!pSuite)
        return ERR_NOMEM;

    CU_pTest pTest = CU_add_test(pSuite, "Non-primitive item manipulation",
                     TestAdvancedManipulate);
    if (!pTest)
        return ERR_NOMEM;

    return SUCC;
}


void TestSimpleManipulate()
{
    BinHeap *pHeap;
    CU_ASSERT(BinHeapInit(&pHeap) == SUCC);

    /* Build the maximum heap. */
    CU_ASSERT(pHeap->set_compare(pHeap, CompPrimMax) == SUCC);

    /* Push items into the heap. */
    int32_t idx = 0;
    Item item;
    while (idx < SIZE_MID_TEST) {
        #if __x86_64__
        CU_ASSERT(pHeap->push(pHeap, (Item)(int64_t)aPrim[idx]) == SUCC);
        CU_ASSERT(pHeap->top(pHeap, &item) == SUCC);
        CU_ASSERT_EQUAL(item, (Item)(int64_t)aPrim[idx]);
        #else
        CU_ASSERT(pHeap->push(pHeap, (Item)aPrim[idx]) == SUCC);
        CU_ASSERT(pHeap->top(pHeap, &item) == SUCC);
        CU_ASSERT_EQUAL(item, aPrim[idx]);
        #endif
        idx++;
    }

    /* Pop half of the items from the heap. */
    idx = 1;
    while (idx <= SIZE_MID_TEST / 2) {
        CU_ASSERT(pHeap->pop(pHeap) == SUCC);
        CU_ASSERT(pHeap->top(pHeap, &item) == SUCC);
        #if __x86_64__
        CU_ASSERT_EQUAL(item, (Item)(int64_t)aPrim[SIZE_MID_TEST - idx - 1]);
        #else
        CU_ASSERT_EQUAL(item, (Item)aPrim[SIZE_MID_TEST - idx - 1]);
        #endif
        idx++;
    }

    /* Check the heap size. */
    int32_t iSize = pHeap->size(pHeap);
    CU_ASSERT_EQUAL(iSize, SIZE_MID_TEST / 2);

    /* Push the poped items into the heap again. */
    idx = SIZE_MID_TEST / 2;
    while (idx < SIZE_MID_TEST) {
        #if __x86_64__
        CU_ASSERT(pHeap->push(pHeap, (Item)(int64_t)aPrim[idx]) == SUCC);
        CU_ASSERT(pHeap->top(pHeap, &item) == SUCC);
        CU_ASSERT_EQUAL(item, (Item)(int64_t)aPrim[idx]);
        #else
        CU_ASSERT(pHeap->push(pHeap, (Item)aPrim[idx]) == SUCC);
        CU_ASSERT(pHeap->top(pHeap, &item) == SUCC);
        CU_ASSERT_EQUAL(item, aPrim[idx]);
        #endif
        idx++;
    }

    /* Pop all the items from the heap. */
    idx = 1;
    while (idx < SIZE_MID_TEST) {
        CU_ASSERT(pHeap->pop(pHeap) == SUCC);
        CU_ASSERT(pHeap->top(pHeap, &item) == SUCC);
        #if __x86_64__
        CU_ASSERT_EQUAL(item, (Item)(int64_t)aPrim[SIZE_MID_TEST - idx - 1]);
        #else
        CU_ASSERT_EQUAL(item, (Item)aPrim[SIZE_MID_TEST - idx - 1]);
        #endif
        idx++;
    }

    BinHeapDeinit(&pHeap);
}


void TestAdvancedManipulate()
{
    BinHeap *pHeap;
    CU_ASSERT(BinHeapInit(&pHeap) == SUCC);

    /* Build the minimum heap. */
    CU_ASSERT(pHeap->set_compare(pHeap, CompNoPrimMin) == SUCC);

    /* Push items into the heap. */
    int32_t idx = 0;
    Item item;
    while (idx < SIZE_MID_TEST) {
        CU_ASSERT(pHeap->push(pHeap, (Item)aNoPrim[idx]) == SUCC);
        CU_ASSERT(pHeap->top(pHeap, &item) == SUCC);
        CU_ASSERT_EQUAL(((Employ*)item)->iId, aNoPrim[idx]->iId);
        idx++;
    }

    /* Pop half of the items from the heap. */
    idx = 1;
    while (idx <= SIZE_MID_TEST / 2) {
        CU_ASSERT(pHeap->pop(pHeap) == SUCC);
        CU_ASSERT(pHeap->top(pHeap, &item) == SUCC);
        CU_ASSERT_EQUAL(((Employ*)item)->iId, aNoPrim[SIZE_MID_TEST - idx - 1]->iId);
        idx++;
    }

    /* Check the heap size. */
    int32_t iSize = pHeap->size(pHeap);
    CU_ASSERT_EQUAL(iSize, SIZE_MID_TEST / 2);

    /* Push the poped items into the heap again. */
    idx = SIZE_MID_TEST / 2;
    while (idx < SIZE_MID_TEST) {
        CU_ASSERT(pHeap->push(pHeap, (Item)aNoPrim[idx]) == SUCC);
        CU_ASSERT(pHeap->top(pHeap, &item) == SUCC);
        CU_ASSERT_EQUAL(((Employ*)item)->iId, aNoPrim[idx]->iId);
        idx++;
    }

    /* Pop all the items from the heap. */
    idx = 1;
    while (idx < SIZE_MID_TEST) {
        CU_ASSERT(pHeap->pop(pHeap) == SUCC);
        CU_ASSERT(pHeap->top(pHeap, &item) == SUCC);
        CU_ASSERT_EQUAL(((Employ*)item)->iId, aNoPrim[SIZE_MID_TEST - idx - 1]->iId);
        idx++;
    }

    BinHeapDeinit(&pHeap);
}


int32_t CompPrimMax(Item itemSrc, Item itemTge)
{
    if (itemSrc == itemTge)
        return 0;
    return (itemSrc > itemTge)? 1 : (-1);
}


int32_t CompNoPrimMin(Item itemSrc, Item itemTge)
{
    Employ *pEmpSrc = (Employ*)itemSrc;
    Employ *pEmpTge = (Employ*)itemTge;

    if (pEmpSrc->iId == pEmpTge->iId)
        return 0;
    return (pEmpSrc->iId < pEmpTge->iId)? 1 : (-1);
}


void CleanNoPrim(Item item)
{
    free((Employ*)item);
}