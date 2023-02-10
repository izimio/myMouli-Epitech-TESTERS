#include <dlfcn.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int good = 0;
int nums = 0;

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

int main(int argc, char **argv)
{
    void *handle;
    int (*my_strlen)(const char *);
    char *(*my_strchr)(const char *, int);
    char *(*my_strrchr)(const char *, int);
    void *(*my_memset)(void *, int, size_t);
    void *(*my_memcpy)(void *dest, void *src, size_t n);
    void *(*my_memmove)(void *dest, void *src, size_t n);
    int (*my_strcmp)(const char *, const char *);
    int (*my_strncmp)(const char *, const char *, size_t);
    int (*my_strcasecmp)(const char *, const char *);
    char *(*my_strstr)(const char *, const char *);
    char *(*my_strpbrk)(const char *, const char *);
    size_t (*my_strcspn)(const char *, const char *);
    char *error;

    handle = dlopen("./libasm.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        return 1;
    }

    my_strlen = dlsym(handle, "strlen");
    my_strchr = dlsym(handle, "strchr");
    my_strrchr = dlsym(handle, "strrchr");
    my_memset = dlsym(handle, "memset");
    my_memcpy = dlsym(handle, "memcpy");
    my_strcmp = dlsym(handle, "strcmp");
    my_strncmp = dlsym(handle, "strncmp");
    my_memmove = dlsym(handle, "memmove");
    my_strcasecmp = dlsym(handle, "strcasecmp");
    my_strstr = dlsym(handle, "strstr");
    my_strpbrk = dlsym(handle, "strpbrk");
    my_strcspn = dlsym(handle, "strcspn");
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "%s\n", error);
        return 1;
    }

    printf(" ===== TEST STRLEN =====\n");
    INT_test_printf("strlen(\"a\")", "%ld", "%d", strlen("a"), my_strlen("d"));
    INT_test_printf("strlen(\"\")", "%ld", "%d", strlen(""), my_strlen(""));
    INT_test_printf("strlen(\"0123456789\")", "%ld", "%d",
    strlen("0123456789"), my_strlen("0123456789"));

    printf("\n\n");
    printf(" ===== TEST STRCHR =====\n");
    char *str = "0123456789";
    char *tricky1 = strdup("0123456789");
    STR_test_printf("strrchr(\"0123456789\", '\0')", "%s", "%s",
    strchr(str, '\0'), my_strchr(str, '\0'));

    STR_test_printf("strrchr(\"01234\\056789\", '\0')", "%s", "%s",
    strchr(tricky1, '\0'), my_strchr(tricky1, '\0'));
    STR_test_printf("strchr(\"0123456789\", '4')", "%s", "%s",
    strchr(str, '4'), my_strchr(str, '4'));
    STR_test_printf("strchr(\"0123456789\", 'z')", "%s", "%s",
    strchr(str, 'z'), my_strchr(str, 'z'));
    STR_test_printf(
    "strchr(\"\", 'z')", "%s", "%s", strchr("", 'z'), my_strchr("", 'z'));
    STR_test_printf("strchr(\"joshua\", 'j')", "%s", "%s",
    strchr("joshua", 'j'), my_strchr("joshua", 'j'));
    STR_test_printf("strchr(\"joshua\", 'a')", "%s", "%s",
    strchr("joshua", 'a'), my_strchr("joshua", 'a'));

    printf("\n\n");
    printf(" ===== TEST STRRCHR =====\n");
    char *tricky = strdup("0123456789");
    STR_test_printf("strrchr(\"0123456789\", '\0')", "%s", "%s",
    strrchr(str, '\0'), my_strrchr(str, '\0'));

    STR_test_printf("strrchr(\"01234\\056789\", '\0')", "%s", "%s",
    strrchr(tricky, '\0'), my_strrchr(tricky, '\0'));

    STR_test_printf("strrchr(\"0123456789\", '4')", "%s", "%s",
    strrchr(str, '4'), my_strrchr(str, '4'));
    STR_test_printf("strrchr(\"0123456789\", 'z')", "%s", "%s",
    strrchr(str, 'z'), my_strrchr(str, 'z'));
    STR_test_printf(
    "strrchr(\"\", 'z')", "%s", "%s", strrchr("", 'z'), my_strrchr("", 'z'));
    STR_test_printf("strrchr(\"bobobobobobobobobobobo\", 'b')", "%s", "%s",
    strrchr("bobobobobobobobobobobo", 'b'),
    my_strrchr("bobobobobobobobobobobo", 'b'));
    STR_test_printf("strrchr(\"djbdfbjebfejbewfb\", 'z')", "%s", "%s",
    strrchr("djbdfbjebfejbewfb", 'z'), my_strrchr("djbdfbjebfejbewfb", 'z'));

    printf("\n\n");
    printf(" ===== TEST MEMSET =====\n");
    char *str1 = strdup("0123456789");
    char *str2 = strdup("0123456789");
    char *str3 = strdup("uwu");
    char *str4 = strdup("uwu");
    char *str5 = strdup("ara");
    char *str6 = strdup("ara");
    STR_test_printf("memset(\"0123456789\", 'a', 3)", "%s", "%s",
    memset(str1, 'p', 3), my_memset(str2, 'p', 3));
    STR_test_printf("memset(\"uwu\", 'O', 50)", "%s", "%s",
    memset(str3, 'O', 50), my_memset(str3, 'O', 50));
    STR_test_printf("memset(\"ara\", 'a', 0)", "%s", "%s",
    memset(str5, 'a', 0), my_memset(str6, 'a', 0));

    printf("\n\n");
    printf(" ===== TEST MEMCPY =====\n");
    char *memcpy1 = strdup("123456789");
    char *memcpy2 = strdup("123456789");
    STR_test_printf("memcpy(\"123456789\", \"abc\", 3)", "%s", "%s",
    memcpy(memcpy1, "abc", 3), my_memcpy(memcpy2, "abc", 3));
    STR_test_printf("memcpy(\"123456789\", \"abc\", 0)", "%s", "%s",
    memcpy(memcpy1, "5bc", 0), my_memcpy(memcpy2, "5bc", 0));
    STR_test_printf("memcpy(\"123456789\", \"abc\", 1)", "%s", "%s",
    memcpy(memcpy1, "Lbc", 1), my_memcpy(memcpy2, "Lbc", 1));
    printf("\n\n");
    printf(" ===== TEST STRCMP =====\n");
    STRCMP_test_printf(
    "strcmp(\"a\", \"a\")", "%d", "%d", strcmp("a", "a"), my_strcmp("a", "a"));
    STRCMP_test_printf(
    "strcmp(\"a\", \"b\")", "%d", "%d", strcmp("a", "b"), my_strcmp("a", "b"));
    STRCMP_test_printf(
    "strcmp(\"b\", \"a\")", "%d", "%d", strcmp("b", "a"), my_strcmp("b", "a"));
    STRCMP_test_printf("strcmp(\"a\", \"aa\")", "%d", "%d", strcmp("a", "aa"),
    my_strcmp("a", "aa"));
    STRCMP_test_printf("strcmp(\"aa\", \"a\")", "%d", "%d", strcmp("aa", "a"),
    my_strcmp("aa", "a"));
    STRCMP_test_printf(
    "strcmp(\"\", \"\")", "%d", "%d", strcmp("", ""), my_strcmp("", ""));
    STRCMP_test_printf(
    "strcmp(\"\", \"a\")", "%d", "%d", strcmp("", "a"), my_strcmp("", "a"));
    STRCMP_test_printf(
    "strcmp(\"a\", \"\")", "%d", "%d", strcmp("a", ""), my_strcmp("a", ""));
    STRCMP_test_printf(
    "strcmp(\"a\", \"a\")", "%d", "%d", strcmp("a", "a"), my_strcmp("a", "a"));
    STRCMP_test_printf(
    "strcmp(\"a\", \"b\")", "%d", "%d", strcmp("a", "b"), my_strcmp("a", "b"));
    STRCMP_test_printf(
    "strcmp(\"b\", \"a\")", "%d", "%d", strcmp("b", "a"), my_strcmp("b", "a"));
    STRCMP_test_printf("strcmp(\"a\", \"aa\")", "%d", "%d", strcmp("a", "aa"),
    my_strcmp("a", "aa"));
    STRCMP_test_printf("strcmp(\"aa\", \"a\")", "%d", "%d", strcmp("aa", "a"),
    my_strcmp("aa", "a"));
    STRCMP_test_printf(
    "strcmp(\"\", \"\")", "%d", "%d", strcmp("", ""), my_strcmp("", ""));
    STRCMP_test_printf("strcmp(\"aaaa\", \"aab\")", "%d", "%d",
    strcmp("aaaa", "aab"), my_strcmp("aaaa", "aab"));

    printf("\n\n");
    printf(" ===== TEST STRNCMP =====\n");
    STRCMP_test_printf("strncmp(\"a\", \"a\", 1)", "%d", "%d",
    strncmp("a", "a", 1), my_strncmp("a", "a", 1));
    STRCMP_test_printf("strncmp(\"a\", \"b\", 1)", "%d", "%d",
    strncmp("a", "b", 1), my_strncmp("a", "b", 1));
    STRCMP_test_printf("strncmp(\"b\", \"a\", 1)", "%d", "%d",
    strncmp("b", "a", 1), my_strncmp("b", "a", 1));
    STRCMP_test_printf("strncmp(\"a\", \"aa\", 1)", "%d", "%d",
    strncmp("a", "aa", 1), my_strncmp("a", "aa", 1));
    STRCMP_test_printf("strncmp(\"aa\", \"a\", 1)", "%d", "%d",
    strncmp("aa", "a", 1), my_strncmp("aa", "a", 1));
    STRCMP_test_printf("strncmp(\"aa\", \"ab\", 1)", "%d", "%d",
    strncmp("aa", "ab", 1), my_strncmp("aa", "ab", 1));
    STRCMP_test_printf("strncmp(\"ab\", \"aa\", 100)", "%d", "%d",
    strncmp("ab", "aa", 100), my_strncmp("ab", "aa", 100));
    STRCMP_test_printf(
    "strncmp(\"abqwdwdqwdqdw\", \"abqwdwdqwdqdddddwqw\", 1)", "%d", "%d",
    strncmp("abqwdwdqwdqdw", "abqwdwdqwdqdddddwqw", 1),
    my_strncmp("abqwdwdqwdqdw", "abqwdwdqwdqdddddwqw", 1));
    STRCMP_test_printf(
    "strncmp(\"abqwdwdqwdqdw\", \"abqwdwdqwdqdzdddwqw\", 100)", "%d", "%d",
    strncmp("abqwdwdqwdqdw", "abqwdwdqwdqdzdddwqw", 100),
    my_strncmp("abqwdwdqwdqdw", "abqwdwdqwdqdzdddwqw", 100));
    printf("\n\n");
    printf(" ===== TEST MEMMOVE =====\n");
    char test[100] = "test";
    char test2[100] = "test";
    char copy[100] = "copy";
    char copy2[100] = "copy";

    char empty[100] = "";
    char empty2[100] = "";
    char uwu[500] = "salut les amis, c'est david lafarge pokemon COUCOUU";
    STR_test_printf("memmove(\"test\", \"copy\", 4)", "%s", "%s",
    memmove(test, copy, 4), my_memmove(test2, copy2, 4));
    STR_test_printf("memmove(\"test\", \"copy\", 0)", "%s", "%s",
    memmove(test, copy, 0), my_memmove(test2, copy2, 0));
    STR_test_printf("memmove(\"empty\", \"copy\", 4)", "%s", "%s",
    memmove(empty, copy, 4), my_memmove(empty2, copy2, 4));
    STR_test_printf("memmove(\"test\", \"empty\", 4)", "%s", "%s",
    memmove(test, empty, 4), my_memmove(test2, empty2, 4));
    STR_test_printf("memmove(\"empty\", \"empty\", 4)", "%s", "%s",
    memmove(empty, empty, 4), my_memmove(empty2, empty2, 4));
    STR_test_printf("memmove(\"empty\", \"empty\", 4)", "%s", "%s",
    memmove(uwu + 15, uwu + 10, 40), my_memmove(uwu + 15, uwu + 10, 40));
    STR_test_printf("memmove(\"empty\", \"empty\", 4)", "%s", "%s",
    memmove(uwu + 10, uwu + 15, 40), my_memmove(uwu + 10, uwu + 15, 40));
    printf("\n\n");
    printf(" ===== TEST STRCASECMP =====\n");
    STRCMP_test_printf("strcasecmp(\"a\", \"a\")", "%d", "%d",
    strcasecmp("a", "a"), my_strcasecmp("a", "a"));
    STRCMP_test_printf("strcasecmp(\"a\", \"A\")", "%d", "%d",
    strcasecmp("a", "A"), my_strcasecmp("a", "A"));
    STRCMP_test_printf("strcasecmp(\"A\", \"a\")", "%d", "%d",
    strcasecmp("A", "a"), my_strcasecmp("A", "a"));
    STRCMP_test_printf("strcasecmp(\"a\", \"b\")", "%d", "%d",
    strcasecmp("a", "b"), my_strcasecmp("a", "b"));
    STRCMP_test_printf("strcasecmp(\"b\", \"a\")", "%d", "%d",
    strcasecmp("b", "A"), my_strcasecmp("b", "a"));
    STRCMP_test_printf("strcasecmp(\"a\", \"aa\")", "%d", "%d",
    strcasecmp("a", "aa"), my_strcasecmp("a", "aa"));
    STRCMP_test_printf("strcasecmp(\"aa\", \"a\")", "%d", "%d",
    strcasecmp("aa", "a"), my_strcasecmp("aa", "a"));
    STRCMP_test_printf("strcasecmp(\"aa\", \"ab\")", "%d", "%d",
    strcasecmp("AAAAABb", "AAAAABb"), my_strcasecmp("AAAAABb", "AAAAABb"));
    STRCMP_test_printf("strcasecmp(\"AB\", \"AA\")", "%d", "%d",
    strcasecmp("AB", "AA"), my_strcasecmp("AB", "AA"));
    STRCMP_test_printf("strcasecmp(\"12ABCaBcWdEj\", \"12ABCaBcWdEj\")", "%d",
    "%d", strcasecmp("12ABCaBcWdEj", "12ABCaBcWdEj"),
    my_strcasecmp("12ABCaBcWdEj", "12ABCaBcWdEj"));
    STRCMP_test_printf("strcasecmp(\"12ABCaBc8WdEj\", \"12ABCaBcWdEj\")", "%d",
    "%d", strcasecmp("12ABCaBc8WdEj", "12ABCaBcWdEj"),
    my_strcasecmp("12ABCaBc8WdEj", "12ABCaBcWdEj"));
    STRCMP_test_printf(
    "strcasecmp(\"abqwdwdQWdqdzdddwqw\", \"abqwdwdQWdqdzdddwqw\")", "%d", "%d",
    strcasecmp("abqwdwdQWdqdzdddwqw", "abqwdwdQWdqdzdddwqw"),
    my_strcasecmp("abqwdwdQWdqdzdddwqw", "abqwdwdQWdqdzdddwqw"));
    STRCMP_test_printf(
    "strcasecmp(\"abqwdwdQWdqdzdddwqw\", \"abqwdwdQWdqdzdddwqw\")", "%d", "%d",
    strcasecmp("abqwdwdQWdqdzdddwqw", "abqwdwdQWdqdzdddwqw"),
    my_strcasecmp("abqwdwdQWdqdzdddwqw", "abqwdwdQWdqdzdddwqw"));

    printf("\n\n");
    printf(" ===== TEST STRSTR =====\n");
    STR_test_printf("strstr(\"test\", \"test\")", "%s", "%s",
    strstr("test", "test"), my_strstr("test", "test"));
    STR_test_printf(
    "strstr(\"\", \"\")", "%s", "%s", strstr("", ""), my_strstr("", ""));
    STR_test_printf("strstr(\"test\", \"es\")", "%s", "%s",
    strstr("test", "es"), my_strstr("test", "es"));
    STR_test_printf("strstr(\"test\", \"t\")", "%s", "%s", strstr("test", "t"),
    my_strstr("test", "t"));
    STR_test_printf("strstr(\"test\", \"\")", "%s", "%s", strstr("test", ""),
    my_strstr("test", ""));
    STR_test_printf("strstr(\"test\", \"est\")", "%s", "%s",
    strstr("test", "est"), my_strstr("test", "est"));
    STR_test_printf("strstr(\"test\", \"testtest\")", "%s", "%s",
    strstr("test", "testtest"), my_strstr("test", "testtest"));
    STR_test_printf("strstr(\"blablacar\", \"blacar\")", "%s", "%s",
    strstr("blablacar", "blacar"), my_strstr("blablacar", "blacar"));
    STR_test_printf("strstr(\"blabblablalacar\", \"blacar\")", "%s", "%s",
    strstr("blabblablalacar", "blacar"),
    my_strstr("blabblablalacar", "blacar"));

    printf("\n\n");
    printf(" ===== TEST STRPBRK =====\n");
    STR_test_printf("strpbrk(\"test\", \"test\")", "%s", "%s",
    strpbrk("test", "test"), my_strpbrk("test", "test"));
    STR_test_printf(
    "strpbrk(\"\", \"\")", "%s", "%s", strpbrk("", ""), my_strpbrk("", ""));
    STR_test_printf("strpbrk(\"test\", \"es\")", "%s", "%s",
    strpbrk("test", "es"), my_strpbrk("test", "es"));
    STR_test_printf("strpbrk(\"test\", \"t\")", "%s", "%s",
    strpbrk("test", "t"), my_strpbrk("test", "t"));
    STR_test_printf("strpbrk(\"test\", \"\")", "%s", "%s", strpbrk("test", ""),
    my_strpbrk("test", ""));
    STR_test_printf("strpbrk(\"test\", \"est\")", "%s", "%s",
    strpbrk("test", "est"), my_strpbrk("test", "est"));
    STR_test_printf("strpbrk(\"test\", \"testtest\")", "%s", "%s",
    strpbrk("test", "testtest"), my_strpbrk("test", "testtest"));
    STR_test_printf("strpbrk(\"blablacar\", \"blacar\")", "%s", "%s",
    strpbrk("blablacar", "blacar"), my_strpbrk("blablacar", "blacar"));
    STR_test_printf("strpbrk(\"blabblablalacar\", \"blacar\")", "%s", "%s",
    strpbrk("blabblablalacar", "blacar"),
    my_strpbrk("blabblablalacar", "blacar"));

    printf("\n\n");
    printf(" ===== TEST STRCSPN =====\n");
    INT_test_printf("strcspn(\"test\", \"test\")", "%zu", "%zu",
    strcspn("test", "test"), my_strcspn("test", "test"));
    INT_test_printf(
    "strcspn(\"\", \"\")", "%zu", "%zu", strcspn("", ""), my_strcspn("", ""));
    INT_test_printf("strcspn(\"test\", \"es\")", "%zu", "%zu",
    strcspn("test", "es"), my_strcspn("test", "es"));
    INT_test_printf("strcspn(\"test\", \"t\")", "%zu", "%zu",
    strcspn("test", "t"), my_strcspn("test", "t"));
    INT_test_printf("strcspn(\"test\", \"\")", "%zu", "%zu",
    strcspn("test", ""), my_strcspn("test", ""));
    INT_test_printf("strcspn(\"test\", \"est\")", "%zu", "%zu",
    strcspn("test", "est"), my_strcspn("test", "est"));
    INT_test_printf("strcspn(\"test\", \"testtest\")", "%zu", "%zu",
    strcspn("test", "testtest"), my_strcspn("test", "testtest"));
    INT_test_printf("strcspn(\"blablacar\", \"blacar\")", "%zu", "%zu",
    strcspn("blablacar", "blacar"), my_strcspn("blablacar", "blacar"));
    INT_test_printf("strcspn(\"blablacar\", \"\")", "%zu", "%zu",
    strcspn("blablacar", ""), my_strcspn("blablacar", ""));
    INT_test_printf("strcspn(\"Hello World\", \"cacao\")", "%zu", "%zu",
    strcspn("Hello World", "cacao"), my_strcspn("Hello World", "cacao"));
    INT_test_printf("strcspn(\"Hello World\", \" \")", "%zu", "%zu",
    strcspn("Hello World", " "), my_strcspn("Hello World", " "));
    INT_test_printf("strcspn(\"\", \"cacao\")", "%zu", "%zu",
    strcspn("", "cacao"), my_strcspn("", "cacao"));

    dlclose(handle);
    printf(" ===== RESULT =====\n");
    if (good == nums)
        printf("\033[32m  All tests passed on %d tests\033[0m\n", nums);
    else
        printf("%d / %d tests passed\n", good, nums);
}