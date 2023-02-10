#include <dlfcn.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int good = 0;
int nums = 0;

int is_anagram(char *str1, char *str2) {
    char buff[256] = {0};
    int i = 0;

    while (str1[i]) {
        buff[str1[i]]++;
        i++;
    }
    i = 0;
    while (str2[i]) {
        buff[str2[i]]--;
        i++;
    }
    i = 0;
    while (i < 256) {
        if (buff[i] != 0) {
            return 0;
        }
        i++;
    }
    return 1;
}

int issamesign(int a, int b)
{
    if (a == 0 && b != 0)
        return 0;
    if (a != 0 && b == 0)
        return 0;
    int ret = (a ^ b) >= 0;
    good += ret;
    return ret;
}

int STRCMP_test_printf(
const char *name, const char *format1, const char *format2, int a, int b)
{
    nums++;
    printf("Test on %s\n", name);

    char str1[700];
    sprintf(str1, format1, a);

    char str2[700];
    sprintf(str2, format2, b);

    printf("Expected: %s\n", str1);
    printf("Got:      %s\n", str2);

    int good = atoi(str1);
    int mine = atoi(str2);

    int result = issamesign(good, mine) ? 1 : 0;

    if (result == 1) {
        printf("Result: \033[32mPASS\033[0m\n\n");
    } else {
        printf("Result: \033[31mFAIL\033[0m\n\n");
    }

    return result;
}

int INT_test_printf(
const char *name, const char *format1, const char *format2, int a, int b)
{
    nums++;

    printf("Test on %s\n", name);

    char str1[700];
    sprintf(str1, format1, a);

    char str2[700];
    sprintf(str2, format2, b);

    printf("Expected: %s\n", str1);
    printf("Got:      %s\n", str2);

    int result = (strcmp(str1, str2) == 0) ? 1 : 0;

    if (result == 1) {
        printf("Result: \033[32mPASS\033[0m\n\n");
    } else {
        printf("Result: \033[31mFAIL\033[0m\n\n");
    }
    good += result;

    return result;
}

int STR_test_printf(
const char *name, const char *format1, const char *format2, char *a, char *b)
{
    nums++;

    printf("Test on %s\n", name);

    char *str1 = calloc(700, 1);
    printf("LA : %s\n", a);
    sprintf(str1, format1, a);
    printf("UWU\n");

    char *str2 = malloc(700);
    sprintf(str2, format2, b);

    printf("Expected: %s\n", str1);
    printf("Got:      %s\n", str2);

    int result = (strcmp(str1, str2) == 0) ? 1 : 0;

    if (result == 1) {
        printf("Result: \033[32mPASS\033[0m\n\n");
    } else {
        printf("Result: \033[31mFAIL\033[0m\n\n");
    }
    good += result;
    free(str1);
    free(str2);
    return result;
}

int main()
{
    void *handle;
    char *error;
    int (*my_ffs)(int i);
    char *(*my_index)(const char *s, int c);
    char *(*my_rindex)(const char *s, int c);
    void *(*my_memfrob)(void *s, size_t n);
    char *(*my_strfry)(char *s);

    handle = dlopen("./libasm.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        return 1;
    }

    my_ffs = dlsym(handle, "ffs");
    my_index = dlsym(handle, "index");
    my_rindex = dlsym(handle, "rindex");
    my_memfrob = dlsym(handle, "memfrob");
    my_strfry = dlsym(handle, "strfry");

    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "%s\n", error);
        return 1;
    }

    printf("\n\n");
    printf("========================================\033[32mBonus\033[0m========================================\n");
    printf(" ===== TEST FFS =====\n");
    INT_test_printf("ffs(0)", "%d", "%d", ffs(0), my_ffs(0));
    INT_test_printf("ffs(1)", "%d", "%d", ffs(1), my_ffs(1));
    INT_test_printf("ffs(2)", "%d", "%d", ffs(2), my_ffs(2));
    INT_test_printf("ffs(3)", "%d", "%d", ffs(3), my_ffs(3));
    INT_test_printf("ffs(4)", "%d", "%d", ffs(4), my_ffs(4));
    INT_test_printf("ffs(5)", "%d", "%d", ffs(5), my_ffs(5));
    INT_test_printf("ffs(6)", "%d", "%d", ffs(6), my_ffs(6));
    INT_test_printf("ffs(7)", "%d", "%d", ffs(7), my_ffs(7));
    INT_test_printf("ffs(8)", "%d", "%d", ffs(8), my_ffs(8));
    INT_test_printf("ffs(9)", "%d", "%d", ffs(9), my_ffs(9));
    INT_test_printf("ffs(10)", "%d", "%d", ffs(10), my_ffs(10));
    INT_test_printf("ffs(-11)", "%d", "%d", ffs(-11), my_ffs(-11));
    INT_test_printf("ffs(-12)", "%d", "%d", ffs(-12), my_ffs(-12));
    INT_test_printf("ffs(-13)", "%d", "%d", ffs(-13), my_ffs(-13));
    INT_test_printf("ffs(-1)", "%d", "%d", ffs(-1), my_ffs(-1));

    printf("\n\n");
    printf(" ===== TEST INDEX =====\n");
    STR_test_printf("index(\"hello\", 'h')", "%s", "%s", index("hello", 'h'), my_index("hello", 'h'));
    STR_test_printf("index(\"hello\", 'e')", "%s", "%s", index("hello", 'e'), my_index("hello", 'e'));
    STR_test_printf("index(\"hello\", 'l')", "%s", "%s", index("hello", 'l'), my_index("hello", 'l'));
    STR_test_printf("index(\"hello\", 'o')", "%s", "%s", index("hello", 'o'), my_index("hello", 'o'));
    STR_test_printf("index(\"hello\", 'a')", "%s", "%s", index("hello", 'a'), my_index("hello", 'a'));
    STR_test_printf("index(\"hello\", 'z')", "%s", "%s", index("hello", 'z'), my_index("hello", 'z'));
    STR_test_printf("index(\"hello\", 0)", "%s", "%s", index("hello", 0), my_index("hello", 0));
    STR_test_printf("index(\"hello\", 1)", "%s", "%s", index("hello", 1), my_index("hello", 1));
    STR_test_printf("index(\"\", 0)", "%s", "%s", index("", 0), my_index("", 0));

    printf("\n\n");
    printf(" ===== TEST Rrindex =====\n");
    STR_test_printf("rindex(\"hello\", 'h')", "%s", "%s", rindex("hello", 'h'), my_rindex("hello", 'h'));
    STR_test_printf("rindex(\"hello\", 'e')", "%s", "%s", rindex("hello", 'e'), my_rindex("hello", 'e'));
    STR_test_printf("rindex(\"hello\", 'l')", "%s", "%s", rindex("hello", 'l'), my_rindex("hello", 'l'));
    STR_test_printf("rindex(\"hello\", 'o')", "%s", "%s", rindex("hello", 'o'), my_rindex("hello", 'o'));
    STR_test_printf("rindex(\"hello\", 'a')", "%s", "%s", rindex("hello", 'a'), my_rindex("hello", 'a'));
    STR_test_printf("rindex(\"hello\", 'z')", "%s", "%s", rindex("hello", 'z'), my_rindex("hello", 'z'));
    STR_test_printf("rindex(\"hello\", 0)", "%s", "%s", rindex("hello", 0), my_rindex("hello", 0));
    STR_test_printf("rindex(\"hello\", 1)", "%s", "%s", rindex("hello", 1), my_rindex("hello", 1));
    STR_test_printf("rindex(\"\", 0)", "%s", "%s", rindex("", 0), my_rindex("", 0));
    STR_test_printf("rindex(\"helllllllllllllllo         l\", 'l')", "%s", "%s", rindex("helllllllllllllllo         l", 'l'), my_rindex("helllllllllllllllo         l", 'l'));

    printf("\n\n");
    printf(" ===== TEST MEMFROB =====\n");
    char *str = strdup("hello");
    char *str2 = strdup("hello");
    memfrob(str, 5);

    STR_test_printf("memfrob(\"hello\", 5)", "%s", "%s", str, my_memfrob(str2, 5));
    memfrob(str, 5);
    STR_test_printf("memfrob(\"hello\", 5)", "%s", "%s", str, my_memfrob(str2, 5));
    memfrob(str, 0);
    STR_test_printf("memfrob(\"hello\", 0)", "%s", "%s", str, my_memfrob(str2, 0));
    memfrob(str, 2);
    STR_test_printf("memfrob(\"hello\", 2)", "%s", "%s", str, my_memfrob(str2, 2));

    printf("\n\n");
    printf(" ===== TEST STRFRY =====\n");
    char *fries = strdup("Hello world");
    char *first_fry = my_strfry(fries);
    fries = strdup("Hello world");
    char *second_fry = my_strfry(fries);

    INT_test_printf("Is anagram #1 ?", "%d", "%d", 1, is_anagram(first_fry, "Hello world"));
    INT_test_printf("Is anagram #2 ?", "%d", "%d", 1, is_anagram(second_fry, "Hello world"));
    INT_test_printf("Is shuffled #1 ?", "%d", "%d", 1, !!strcmp(first_fry, "Hello world"));
    INT_test_printf("Is shuffled #2 ?", "%d", "%d", 1, !!strcmp(second_fry, "Hello world"));
    INT_test_printf("Is random ?", "%d", "%d", 1, !!strcmp(first_fry, second_fry));
    fries = strdup("A");
    first_fry = my_strfry(fries);
    STR_test_printf("strfry(\"A\")", "%s", "%s", "A", my_strfry(fries));
    fries = strdup("");
    first_fry = my_strfry(fries);
    STR_test_printf("strfry(\"\")", "%s", "%s", "", my_strfry(fries));


    dlclose(handle);
    printf(" ===== RESULT =====\n");
    if (good == nums)
        printf("\033[32m  All tests passed on %d tests\033[0m\n", nums);
    else
        printf("%d / %d tests passed\n", good, nums);
}