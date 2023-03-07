/*
** EPITECH PROJECT, 2023
** finalMinilibc
** File description:
** main
*/

#include <criterion/criterion.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

int (*_strlen)(const char *);
char *(*_strchr)(const char *, int);
char *(*_strrchr)(const char *, int);
void *(*_memset)(void *, int, size_t);
void *(*_memcpy)(void *dest, void *src, size_t n);
void *(*_memmove)(void *dest, void *src, size_t n);
int (*_strcmp)(const char *, const char *);
int (*_strncmp)(const char *, const char *, size_t);
int (*_strcasecmp)(const char *, const char *);
char *(*_strstr)(const char *, const char *);
char *(*_strpbrk)(const char *, const char *);
size_t (*_strcspn)(const char *, const char *);

void setup(void)
{

    void *handle = dlopen("./libasm.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        return;
    }

    _strlen = dlsym(handle, "strlen");
    _strchr = dlsym(handle, "strchr");
    _strrchr = dlsym(handle, "strrchr");
    _memset = dlsym(handle, "memset");
    _memcpy = dlsym(handle, "memcpy");
    _strcmp = dlsym(handle, "strcmp");
    _strncmp = dlsym(handle, "strncmp");
    _memmove = dlsym(handle, "memmove");
    _strcasecmp = dlsym(handle, "strcasecmp");
    _strstr = dlsym(handle, "strstr");
    _strpbrk = dlsym(handle, "strpbrk");
    _strcspn = dlsym(handle, "strcspn");
    char *error;
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "%s\n", error);
        return;
    }
}

Test(memcpy1, completeCopy, .init = setup)
{
    char *source = strdup("Source");
    char *destination = strdup("Destination");

    cr_assert_str_eq(_memcpy(destination, source, 6), "Sourceation");
    free(source);
    free(destination);
}

Test(memcpy1, overloadCopy, .init = setup)
{
    char *source = strdup("Source");
    char *destination = strdup("Destination");

    cr_assert_str_eq(_memcpy(destination, source, 8), "Source");
    free(source);
    free(destination);
}

Test(memcpy1, firstCharacterCopy, .init = setup)
{
    char *source = strdup("Source");
    char *destination = strdup("Destination");

    cr_assert_str_eq(_memcpy(destination, source, 1), "Sestination");
    free(source);
    free(destination);
}

Test(memcpy1, noneCopy, .init = setup)
{
    char *source = strdup("Source");
    char *destination = strdup("Destination");

    cr_assert_str_eq(_memcpy(destination, source, 0), "Destination");
    free(source);
    free(destination);
}

// ====== TEST MEMMOVE =========== //

Test(memmove, completeCopy, .init = setup)
{
    char *source = strdup("Source");
    char *destination = strdup("Destination");

    cr_assert_str_eq(_memmove(destination, source, 6), "Sourceation");
    free(source);
    free(destination);
}

Test(memmove, overloadCopy, .init = setup)
{
    char *source = strdup("Source");
    char *destination = strdup("Destination");

    cr_assert_str_eq(_memmove(destination, source, 8), "Source");
    free(source);
    free(destination);
}

Test(memmove, firstCharacterCopy, .init = setup)
{
    char *source = strdup("Source");
    char *destination = strdup("Destination");

    cr_assert_str_eq(_memmove(destination, source, 1), "Sestination");
    free(source);
    free(destination);
}

Test(memmove, noneCopy, .init = setup)
{
    char *source = strdup("Source");
    char *destination = strdup("Destination");

    cr_assert_str_eq(_memmove(destination, source, 0), "Destination");
    free(source);
    free(destination);
}

// ========== TEST MEMSET =========== //

Test(memset, setAllCharacters, .init = setup)
{
    char string[10] = "Hello You";

    cr_assert_str_eq(_memset(string, 'A', 10), "AAAAAAAAAA");
}

Test(memset, setFirstCharacter, .init = setup)
{
    char string[10] = "Hello You";

    cr_assert_str_eq(_memset(string, 'A', 1), "Aello You");
}

Test(memset, setTooMuchCharacters, .init = setup)
{
    char *string = malloc(10);

    cr_assert(memset(string, 'A', 11) == _memset(string, 'A', 11));
    free(string);
}

Test(memset, setNoneCharacter, .init = setup)
{
    char string[10] = "Hello You";

    cr_assert_str_eq(_memset(string, 'A', 0), "Hello You");
}

// ========== TEST STRRCHR ======= //

Test(_strrchr, findCharacter, .init = setup)
{
    char *string = "Hello World";

    cr_assert_str_eq(_strrchr(string, 'W'), "World");
}

Test(_strrchr, stringNULL, .init = setup)
{
    char *string = "";

    cr_assert_null(_strrchr(string, 'A'));
}

Test(_strrchr, characterZero, .init = setup)
{
    char *string = "Hello World";

    cr_assert_str_eq(_strrchr(string, '\0'), string + strlen(string));
}

// ========== TEST STRCASECMP ======= //

Test(strcasecmp, sameStrings, .init = setup)
{
    char *s1 = "HeLlO WoRlD";
    char *s2 = "Hello World";

    cr_assert_eq(_strcasecmp(s1, s2), 0);
}

Test(strcasecmp, firstStringNULL, .init = setup)
{
    char *s1 = "";
    char *s2 = "HeLlO WoRlD";

    cr_assert_geq(_strcasecmp(s1, s2), strcasecmp(s1, s2));
}

Test(strcasecmp, secondStringNULL, .init = setup)
{
    char *s1 = "HeLlO WoRlD";
    char *s2 = "";

    cr_assert_leq(_strcasecmp(s1, s2), strcasecmp(s1, s2));
}

Test(strcasecmp, stringsNULL, .init = setup)
{
    char *s1 = "";
    char *s2 = "";

    cr_assert(_strcasecmp(s1, s2) == strcasecmp(s1, s2));
}

Test(strcasecmp, differentStrings, .init = setup)
{
    char *s1 = "HeLlO WoRlD";
    char *s2 = "Hello You";

    cr_assert_eq(_strcasecmp(s1, s2), -2);
}

// ========== TEST STRCHR ======= //

Test(strchr, presentCharacter, .init = setup)
{
    cr_assert(strchr("Hello World", 'l') == _strchr("Hello World", 'l'));
}

Test(strchr, lostCharacter, .init = setup)
{
    cr_assert(strchr("Hello World", 'z') == _strchr("Hello World", 'z'));
}

Test(strchr, emptyString, .init = setup)
{
    cr_assert(strchr("", '\0') == _strchr("", '\0'));
}

// ========== TEST STRCMP ======= //

Test(strcmp, sameStrings, .init = setup)
{
    char *s1 = "Hello World";
    char *s2 = "Hello World";

    cr_assert_eq(_strcmp(s1, s2), 0);
}

Test(strcmp, firstStringNULL, .init = setup)
{
    char *s1 = "";
    char *s2 = "Hello World";

    cr_assert_eq(_strcmp(s1, s2), -72);
}

Test(strcmp, secondStringNULL, .init = setup)
{
    char *s1 = "Hello World";
    char *s2 = "";

    cr_assert_eq(_strcmp(s1, s2), 72);
}

Test(strcmp, differentStrings, .init = setup)
{
    char *s1 = "Hello World";
    char *s2 = "Hello You";

    cr_assert_eq(_strcmp(s1, s2), -2);
}

// ======== TEST STRCSPN ============== //

Test(strcspn, characterOccurrence, .init = setup)
{
    char *string = "Hello World";

    cr_assert_eq(_strcspn(string, " "), 5);
}

Test(strcspn, stringOccurrence, .init = setup)
{
    char *string = "Hello World";

    cr_assert_eq(_strcspn(string, "cacao"), 4);
}

Test(strcspn, nullString, .init = setup)
{
    char *string = "";

    cr_assert(_strcspn(string, "cacao") == strcspn(string, "cacao"));
}

Test(strcspn, nullOccurrence, .init = setup)
{
    char *string = "Hello World";

    cr_assert_eq(_strcspn(string, ""), 11);
}

// =========== TEST STRLEN ========= //

Test(strlen, simpleString, .init = setup)
{
    char *string = "Hello World";

    cr_assert(strlen(string) == _strlen(string));
}

Test(strlen, emptyString, .init = setup)
{
    char *string = "";

    cr_assert(strlen(string) == _strlen(string));
}

// ========== TEST STRNCMP ======== //

Test(strncmp, sameStrings, .init = setup)
{
    char *s1 = "Hello World";
    char *s2 = "Hello World";

    cr_assert_eq(_strncmp(s1, s2, 11), 0);
}

Test(strncmp, firstStringNULL, .init = setup)
{
    char *s1 = "";
    char *s2 = "Hello World";

    cr_assert_eq(_strncmp(s1, s2, 11), -72);
}

Test(strncmp, secondStringNULL, .init = setup)
{
    char *s1 = "Hello World";
    char *s2 = "";

    cr_assert_eq(_strncmp(s1, s2, 11), 72);
}

Test(strncmp, differentStrings, .init = setup)
{
    char *s1 = "Hello World";
    char *s2 = "Hello You";

    cr_assert_eq(_strncmp(s1, s2, 11), -2);
}

Test(strncmp, differentStringsButSize, .init = setup)
{
    char *s1 = "Hello World";
    char *s2 = "Hello You";

    cr_assert_eq(_strncmp(s1, s2, 6), 0);
}

Test(strncmp, sizeZero, .init = setup)
{
    char *s1 = "Hello World";
    char *s2 = "Hello World";

    cr_assert_eq(_strncmp(s1, s2, 0), 0);
}

// ========= TEST STRPBRK ========== //

Test(strpbrk, characterOccurrence, .init = setup)
{
    char *string = "Hello World";

    cr_assert_str_eq(_strpbrk(string, " "), " World");
}

Test(strpbrk, stringOccurrence, .init = setup)
{
    char *string = "Hello World";

    cr_assert_str_eq(_strpbrk(string, "cacao"), "o World");
}

Test(strpbrk, nullString, .init = setup)
{
    char *string = "";

    cr_assert_null(_strpbrk(string, "cacao"));
}

Test(strpbrk, nullOccurrence, .init = setup)
{
    char *string = "Hello World";

    cr_assert_null(_strpbrk(string, ""), "cacao");
}

// ======== TEST STRSTR ========= //

Test(strstr, findNeedleWord, .init = setup)
{
    char *string = "Hello World";

    cr_assert_str_eq(_strstr(string, "World"), "World");
}

Test(strstr, findNeedleCharacters, .init = setup)
{
    char *string = "Hello World";

    cr_assert_str_eq(_strstr(string, "ll"), "llo World");
}

Test(strstr, lostNeedleWord, .init = setup)
{
    char *string = "Hello World";

    cr_assert_null(_strstr(string, "You"));
}

Test(strstr, nullHaystack, .init = setup)
{
    char *string = "";

    cr_assert_null(_strstr(string, "World"));
}