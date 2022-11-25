#include <sys/types.h>     /* key_t  */
#include <sys/ipc.h>       /* ftok   */
#include <sys/sem.h>       /* semget, semctl, semop */
#include <sys/stat.h>      /* stat, struct stat  */
#include <stdlib.h>        /* malloc */
#include <stdio.h>         /* perror, printf */
#include <errno.h>         /* errno */
#include <unistd.h> 	   /*sleep*/

// Ce programme doit �tre dupliqu� pour chaque processus voulant �tablir un RDV
// vous pouvez nommer le programme du premier processus RDV1.C et celui du 2nd RDV2.C par exemple
// Les 2 programmes doivent �tre compil�s s�parement et ex�cuter s�parement sur le shell


/* retourne -1 en cas d'erreur           */
int P(int semid, int noSem)
{
	struct sembuf sops[1];
	int ok;
	
	// Q- donner les 3 �l�ments de la structure Ops pour r�aliser l'op�ration (voir le cours)
	// Ops[0].sem_num = ...; ...
	sops[0].sem_num =noSem ;
    sops[0].sem_op =-1;
    sops[0].sem_flg = 0;
	// Q- faire appel � la fonction semop pour r�aliser l'op�ration P, la variable OK r�cup�re la valeur de retour
	ok = semop(semid,sops,1);
	return ok;
  
}

/* retourne -1 en cas d'erreur           */
int V(int semid, int noSem)//semid identifiant de l'ensemble de sémaphore créé, retourné part la fonction semget(),noSem le numéron de sémaphore de l'ensemble sur 
//lequel on veut faire l'opération
{
	struct sembuf sops[1];
	int ok;
	
	// Q- donner les 3 �l�ments de la structure Ops pour r�aliser l'op�ration (voir le cours)
	// Ops[0].sem_num = ...; ...
	sops[0].sem_num =noSem ;
    sops[0].sem_op =+1;
    sops[0].sem_flg = 0;
	// Q- faire appel � la fonction semop pour r�aliser l'op�ration V, la variable OK r�cup�re la valeur de retour
	ok = semop(semid,sops,1);
	return ok;
}

int main (void)
{ // � compl�ter sans oublier de supprimer l'ensemble des s�maphores

	// Q- Il faut d'abord recr�er la cl� (voir sema.c)
	key_t k1;
	k1 = ftok("id1",1);
	
	// Q- il faut ensuite ouvrir le semaphore avec semget, � part la cl�, les autres argument doivent �tre � z�ro
	// car il ne s'agit pas d'une cr�ation mais d'une ouverture
	int semid;
	semid = semget(k1,0,0);
	
	
	// Q- faire l'appel � sleep() afin d'avoir des attentes de diff�rentes dur�es pour les 2 processus
	sleep(1);
	
	// Q- faire appel � P et � V (voir le TD)
	printf("RDV1 BLOQUE\n");
	P(semid,1);
	V(semid,0);
	
	
	
	// appeler la fonction de RDV, un printf est suffisant.
	printf("RDV1\n");
	semctl(semid,0, IPC_RMID);
	return 0;
	
}