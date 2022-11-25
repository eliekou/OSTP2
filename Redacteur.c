#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#include <sys/types.h>     /* key_t  */
#include <sys/ipc.h>       /* ftok   */
#include <sys/sem.h>       /* semget, semctl, semop */
#include <sys/stat.h>      /* stat, struct stat  */
#include <stdlib.h>        /* malloc */
#include <stdio.h>         /* perror, printf */
#include <errno.h>         /* errno */
#include <unistd.h> 	   /*sleep*/


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
  	ok = semop(semid, sops, 1);
    return ok;
}

int V(int semid, int noSem)//semid identifiant de l'ensemble de sémaphore créé, retourné part la fonction semget(),noSem le numéron de sémaphore de l'ensemble sur 
//lequel on veut faire l'opération
{
	struct sembuf sops[1];
	int ok;
	
	// Q- donner les 3 �l�ments de la structure Ops pour r�aliser l'op�ration (voir le cours)
	// Ops[0].sem_num = ...; ...
	sops[0].sem_num =noSem ;//numéro de sémaphore
    sops[0].sem_op =+1;//opération sur le sémaphore
    sops[0].sem_flg = 0;//option
	// Q- faire appel � la fonction semop pour r�aliser l'op�ration V, la variable OK r�cup�re la valeur de retour
  	ok = semop(semid, sops, 1);
	//Par l'intermédiare du semid qui provient de semget, le processus connaissant l'identification d'un e,nsemble de sémaphore, va pouvoir effectuer
	//des opérations sur eux.

    return ok;

}

int main (void)
{ // � compl�ter sans oublier de supprimer l'ensemble des s�maphores


    FILE *f1;
    f1 = fopen("test1.txt","r+");
	// Q- Il faut d'abord recr�er la cl� (voir sema.c)
	key_t k1;
	k1 = ftok("id1",1);
	
	// Q- il faut ensuite ouvrir le semaphore avec semget, � part la cl�, les autres argument doivent �tre � z�ro
	// car il ne s'agit pas d'une cr�ation mais d'une ouverture
	//semget traduit la clé en un identificateur représentant un ensemble de sémaphore
	int semid;
	int donnee;
	donnee = 0;
	semid= semget(k1,0,0);
	printf("Le sema donne est %d\n",semid);//identificateur du groupe de sémaphore


	
	
	// Q- faire l'appel � sleep() afin d'avoir des attentes de diff�rentes dur�es pour les 2 processus
	//sleep(1);
	
	// Q- faire appel � P et � V (voir le TD)
	printf("On s'apprète à écrire");
	P(semid,donnee);
    fprintf(f1,"test");
	printf("On a ecrit dans le fichier test");
	V(semid,donnee);
    fclose(f1);


	semctl(semid,donnee, IPC_RMID);

	return 0;
	
	
	
	
	
}

