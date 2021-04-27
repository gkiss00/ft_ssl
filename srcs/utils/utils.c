#include "./../include/ft_ssl.h"

uint32_t    ft_strlen(uint8_t *str)
{
    uint32_t i;

    i = 0;
    while (str && str[i] != '\0')
        ++i;
    return (i);
}

uint32_t    ft_strcmp(uint8_t *s1, uint8_t *s2)
{
    uint32_t    i;

    i = 0;
    while(s1[i] && s2[i])
    {
        if (s1[i] != s2[i])
            return (s1[i] - s2[i]);
        ++i;
    }
    return (s1[i] - s2[i]);
}

uint8_t     *ft_strdup(uint8_t *s1)
{
    uint32_t    i;
    uint8_t     *str;

    i = -1;
    if (s1 == NULL)
        return (NULL);
    str = malloc(ft_strlen(s1) + 1);
    if (str == NULL)
        return NULL;
    while(s1 && s1[++i])
        str[i] = s1[i];
    str[i] = '\0';
    return (str);
}

uint8_t     *ft_strjoin(uint8_t *s1, uint8_t *s2)
{
    uint32_t    i;
    uint32_t    j;
    uint8_t     *str;

    i = 0;
    j = 0;

    str = malloc(sizeof(uint8_t) * (ft_strlen(s1) + ft_strlen(s2) + 1));
    if (str == NULL)
        return NULL;
    while(s1 && s1[i])
    {
        str[i] = s1[i];
        ++i;
    }
    while(s2 && s2[j]){
        str[i + j] = s2[j];
        ++j;
    }
    str[i + j] = '\0';
    free(s1);
    return (str);
}

char *to_upper(char * temp) {
    char *name = malloc(strlen(temp));
	int	i = 0;

    while (temp[i]) {
		name[i] = toupper((unsigned char) temp[i]);
        ++i;
    }
	return name;
}