#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static bool	is_built_in(char *cmd)
{
	const char	*built_in[] = {"pwd", "cd", NULL};

	for (int i = 0; built_in[i]; i++) {
		if (!strcmp(built_in[i], cmd))
			return (true);
	}
	return (false);
}

static void	exec_built_in(char **built_in)
{
	if (!strcmp(built_in[0], "pwd"))
		built_in_pwd();
	else if (!strcmp(built_in[0], "cd"))
		built_in_cd(built_in[1]);
}

int	main()
{
	char	*buffer = NULL;
	size_t	buf_size = 2048;
	char	**cmd = NULL;

	// alloc buffer qui stockera la commande entree par l'user
	buffer = (char *)calloc(sizeof(char), buf_size);
	if (buffer == NULL) {
		perror("Malloc failure");
		return (EXIT_FAILURE);
	}

	// ecriture d'un prompt
	write(1, "$> ", 3);

	// lecture de STDIN en boucle
	while (getline(&buffer, &buf_size, stdin) > 0) {
		cmd = split(buffer, " \n\t");

		if (cmd[0] == NULL)
			printf("Command not found\n");
		else if (is_built_in(cmd[0]) == false) {
			get_absolute_path(cmd);
			exec_cmd(cmd);
		} else
			exec_built_in(cmd);

		write(1, "$> ", 3);
		free_array(cmd);

	}

	printf("Bye \n");
	free(buffer);
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

static char	**split(char *raw_cmd, char *limit)
{
	char	*ptr = NULL;
	char	**cmd = NULL;
	size_t	idx = 0;

	// split sur les espaces
	ptr = strtok(raw_cmd, limit);

	while (ptr) {
		cmd = (char **)realloc(cmd, ((idx + 1) * sizeof(char *)));
		cmd[idx] = strdup(ptr);
		ptr = strtok(NULL, limit);
		++idx;
	}
	// On alloue un element qu'on met a NULL a la fin du tableau
	cmd = (char **)realloc(cmd, ((idx + 1) * sizeof(char *)));
	cmd[idx] = NULL;
	return (cmd);
}

static void	free_array(char **array)
{
	for (int i = 0; array[i]; i++) {
		free(array[i]);
		array[i] = NULL;
	}
	free(array);
	array = NULL;
}

static void	exec_cmd(char **cmd)
{
	pid_t	pid = 0;
	int		status = 0;

	// On fork
	pid = fork();
	if (pid == -1)
		perror("fork");
	// Si le fork a reussit, le processus pere attend l'enfant (process fork)
	else if (pid > 0) {
		// On block le processus parent jusqu'a ce que l'enfant termine puis
		// on kill le processus enfant
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	} else {
		// Le processus enfant execute la commande ou exit si execve echoue
		if (execve(cmd[0], cmd, NULL) == -1)
			perror("shell");
		exit(EXIT_FAILURE);
	}
}

tatic void	get_absolute_path(char **cmd)
{
	char	*path = strdup(getenv("PATH"));
	char	*bin = NULL;
	char	**path_split = NULL;

	if (path == NULL) // si le path est null, on cree un path
		path = strdup("/bin:/usr/local/bin:/usr/bin:/bin:/usr/local/sbin");

	// si cmd n'est pas le chemin absolue, on cherche le chemin absolue du
	// binaire grace a la variable d'environment PATH
	if (cmd[0][0] != '/' && strncmp(cmd[0], "./", 2) != 0) {

		// On split le path pour verifier ou ce trouve le binaire
		path_split = split(path, ":");
		free(path);
		path = NULL;

		// On boucle sur chaque dossier du path pour trouver l'emplacement du binaire
		for (int i = 0; path_split[i]; i++) {
			// alloc len du path + '/' + len du binaire + 1 pour le '\0'
			bin = (char *)calloc(sizeof(char), (strlen(path_split[i]) + 1 + strlen(cmd[0]) + 1));
			if (bin == NULL)
				break ;

			// On concat le path , le '/' et le nom du binaire
			strcat(bin, path_split[i]);
			strcat(bin, "/");
			strcat(bin, cmd[0]);

			// On verfie l'existence du fichier et on quitte la boucle si access
			// renvoi 0
			if (access(bin, F_OK) == 0)
				break ;

			// Nous sommes des gens propre :D
			free(bin);
			bin = NULL;
		}
		free_array(path_split);

		// On remplace le binaire par le path absolue ou NULL si le binaire
		// n'existe pas
		free(cmd[0]);
		cmd[0] = bin;
	} else {
		free(path);
		path = NULL;
	}
}

void	built_in_cd(char *path)
{
	if (chdir(path) == -1) {
		perror("chdir()");
	}
}
static char	*built_in_pwd(void)
{
	char	*cwd = NULL;

	// On alloue la longueur de PWD= + PATH_MAX + 1 pour le \0
	cwd = (char *)calloc(sizeof(char), PATH_MAX + strlen("PWD=") + 1);
	if (cwd == NULL)
		return (NULL);

	// On concatene le nom de la variable
	strcat(cwd, "PWD=");

	// et on stock le path actuelle apres le = de PATH=
	if (getcwd(&cwd[4], PATH_MAX) == NULL) {
		perror("getcwd()");
	}

	return (cwd);
}

static void	built_in_env(void)
{
	t_env	*tmp = first;

	while (tmp) {
		printf("%s\n", tmp->var);
		tmp = tmp->next;
	}
}

static void	add_env_var(char *var)
{
	struct passwd	*pw = getpwuid(getuid());
	char			*alloc = NULL;

	if (!strcmp(var, "HOME")) {
		alloc = (char *)calloc(sizeof(char), strlen(pw->pw_dir) + strlen("HOME=") + 1);
		if (alloc == NULL) {
			fprintf(stderr, "Cannot add HOME\n");
			return ;
		}
		strcat(alloc, "HOME=");
		strcat(alloc, pw->pw_dir);
	} else if (!strcmp(var, "PATH")) {
		alloc = strdup("PATH=/bin:/usr/bin");
		if (alloc == NULL) {
			fprintf(stderr, "Cannot add PATH\n");
			return ;
		}
	} else if (!strcmp(var, "OLDPWD")) {
		alloc = strdup("OLDPWD=");
		if (alloc == NULL) {
			fprintf(stderr, "Cannot add OLDPWD\n");
			return ;
		}
	} else if (!strcmp(var, "PWD")) {
		alloc = built_in_pwd();
		if (alloc == NULL) {
			fprintf(stderr, "Cannot add PWD\n");
			return ;
		}
	} else if (!strcmp(var, "SHLVL")) {
		alloc = strdup("SHLVL=1");
		if (alloc == NULL) {
			fprintf(stderr, "Cannot add OLDPWD\n");
			return ;
		}
	}

	add_tail(alloc);
}

static void	dup_env(char **envp)
{
	char	*var_lst[] = {"PATH", "HOME", "OLDPWD", "PWD", "SHLVL", NULL};
	ssize_t	nb_elem = 5; // nombre d'element dasn var_lst

	// boucle sur l'env et stock les variables dans la liste
	for (int i = 0; envp[i]; i++) {
		add_tail(strdup(envp[i]));

		// On verifie que l'on a les variables d'environment minimal
		if (!strncmp(envp[i], "PATH", 4)) var_lst[0] = NULL;
		else if (!strncmp(envp[i], "HOME", 4)) var_lst[1] = NULL;
		else if (!strncmp(envp[i], "OLDPWD", 6)) var_lst[2] = NULL;
		else if (!strncmp(envp[i], "PWD", 3)) var_lst[3] = NULL;
		else if (!strncmp(envp[i], "SHLVL", 5)) var_lst[4] = NULL;
	}

	// On verifie qu l'on a les varaibles PATH, HOME, OLD_PWD et SHLVL
	// sinon on l'ajoute
	for (int i = 0; i < 5; i++) {
		if (var_lst[i] != NULL)
			add_env_var(var_lst[i]);
	}
}
