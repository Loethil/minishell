

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int	quotes(char *str, int *i, int j)
{
	if (str[(*i)] == '\'')
	{
		while (str[++(*i)] != '\'' && str[(*i)])
			;
		j++;	
	}
	else if (str[(*i)] == '"')
	{
		while (str[++(*i)] != '"' && str[(*i)])
			;
		j++;	
	}
	return (j);
}

int	countnbr(char *str)
{
	int	i = 0;
	int	j = 0;

	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			j = quotes(str, &i, j);
		else if (str[i] != ' ')
		{
			while (str[i] != ' ' && str[i])
			{
				if (str[i] == '|')
				{
					j++;
				}
				i++;
			}
			j++;
		}
		else if (str[i] == '|')
			j += 2;
		i++;
	}
	return (j);
}

int	main(int argc, char **argv)
{
	char *line;

	(void)argc;
	(void)argv;
	while (1)
	{
		line = readline("minishell:");
		if (line[0] == '\0')
			continue ;
		add_history(line);
		free(line);
	}
}
