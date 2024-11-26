#ifndef PIPEX_H
# define PIPEX_H

#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <aio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <aio.h>
#include "libft.h"
//#include <error.h>
#include <stdio.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>

void pipex(char **argv, char **env);
void handle_here_doc(char **argv, char **env);
void execute_command (char *cmd, char  **env);
char  *find_path(char *cmd, char **env);

#endif
