# Minishell

![minishell](https://raw.githubusercontent.com/ayogun/42-project-badges/main/badges/minishellm.png)

## Description
Minishell est un projet de l'École 42 visant à créer un shell basique en C, similaire à bash.

## Objectif
Développer un interpréteur de commandes capable de parser, exécuter des commandes et gérer l'environnement.

## Fonctionnalités

- Affichage d'un prompt
- Historique des commandes
- Exécution de commandes avec leurs paramètres
- Gestion des redirections (<, >, <<, >>)
- Gestion des pipes (|)
- Variables d'environnement ($ suivi de caractères)
- Gestion des signaux (ctrl-C, ctrl-D, ctrl-\)
- Builtins : echo, cd, pwd, export, unset, env, exit

## Spécifications techniques

- Langage : C
- Fonctions autorisées : readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history, printf, malloc, free, write, access, open, read, close, fork, wait, waitpid, wait3, wait4, signal, sigaction, sigemptyset, sigaddset, kill, exit, getcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, perror, isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

## Installation
Make

## Utilisation
./minishell
