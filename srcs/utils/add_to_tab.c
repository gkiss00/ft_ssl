#include "./../include/ft_ssl.h"

static int	add_last(uint8_t **new_tab, uint8_t *str, int i)
{
	new_tab[i] = ft_strdup(str);
	return (1);
}

uint8_t		**add_to_tab(uint8_t **tab, uint8_t *str)
{
	int		i;
	uint8_t	**new_tab;

	i = 0;
	new_tab = malloc(sizeof(uint8_t*) * (ft_tablen(tab) + 2));
    if (new_tab == NULL)
		return (NULL);
	while (tab && tab[i])
	{
		new_tab[i] = ft_strdup(tab[i]);
		++i;
	}
	add_last(new_tab, str, i);
	new_tab[i + 1] = NULL;
	//free_tab(tab);
	return (new_tab);
}