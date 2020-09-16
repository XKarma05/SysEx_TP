#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>    //ajout des librairies utiles à l'appel de fonctions diverses

#define KEY 4567
#define PERMS 0660

int main(int argc, char **argv)
{
	int id;
	int i;
	int *ptr;

	system("ipcs -m");   //la fonction system() envoie la commande entre () pour être exécutée 
			     // par le processeur de command 
			     // ipcs() donne des informations sur les communication inter-processeur
			     // et l'argument -m indique les morceaux de mémoire partagés
			     // il n'y en a pas à cet instant là

	id = shmget(KEY, sizeof(int), IPC_CREAT | PERMS); 
	//alloue un segment de mémoiré partagée, avec une clée d'accès, la taille du segment et les droits d'accès
	//id reçoit une adresse 

	system("ipcs -m");
	//on réaffiche les segments de mémoire partagée
	//celui qu'on a crée est affiché

	ptr = (int *) shmat(id, NULL, 0);
	//on attache la variable ptr au segment de mémoire partagée
	//la valeur de ptr est égale à l'adresse de ce segment

	*ptr = 54;
	//on donne la valeur 54 à l'adresse du segment

	i = 54;

	if(fork() == 0)
	{
		(*ptr)++;
		//la valeur de l'adresse du segment est incrémentée (54 + 1)
		i++;
		printf("Value of *ptr = %d\nValue of i = %d\n", *ptr, i);
		exit(0);
	}
	else
	{
		wait(NULL);
		//on attend que le procces fils soit fini

		printf("Value of *ptr = %d\nValue of i = %d\n", *ptr, i);

		shmctl(id, IPC_RMID, NULL);
		//la fonction shmctl() demande à la commande IPC_RMID de libérer l'id, il libère le segment

		system("ipcs -m");
		//visiblement la mémoire n'a pas été libérée
	}
}
