#include "libft.h"

char *ft_strndup(const char *s, size_t n)
{
    size_t len = 0;
    while (s[len] && len < n)
        len++;
    char *result = (char *)malloc(len + 1);
    if (!result)
        return NULL;
    memcpy(result, s, len);
    result[len] = '\0';
    return result;
}
