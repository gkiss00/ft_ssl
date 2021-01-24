#include "./../include/ft_ssl.h"

void		ft_putchar_fd(uint8_t c, int fd)
{
	write(fd, &c, 1);
}

void		ft_putstr_fd(uint8_t *str, int fd)
{
	uint32_t    i;

	i = 0;
	if (str != 0)
	{
		while (i < ft_strlen(str))
		{
			ft_putchar_fd(str[i], fd);
			++i;
		}
	}
}

void		ft_putstrendl_fd(uint8_t *str, int fd)
{
	uint32_t    i;

	i = 0;
	if (str != 0)
	{
		while (i < ft_strlen(str))
		{
			ft_putchar_fd(str[i], fd);
			++i;
		}
	}
	ft_putchar_fd((uint8_t)'\n', fd);
}