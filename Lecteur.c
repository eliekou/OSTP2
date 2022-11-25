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
	sops[0].sem_num =noSem ;//le numéro du sémaphore pris
    sops[0].sem_op =-1;//opération sur le sémaphore:négatif->opération p
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
	sops[0].sem_num =noSem ;
    sops[0].sem_op =+1;//le signe détermine l'opération sur le sémaphore, si le signe est positif l'opération sur le sémaphore est de type V
    sops[0].sem_flg = 0;
	// Q- faire appel � la fonction semop pour r�aliser l'op�ration V, la variable OK r�cup�re la valeur de retour
    ok = semop(semid, sops, 1);
    return ok;
}

int main (void)
{ // � compl�ter sans oublier de supprimer l'ensemble des s�maphores




    //1) Read nb Lecteurs
    FILE *f2 = fopen("nombre.txt", "r");
    int NbLecteur;
    fscanf(f2, "%d", &NbLecteur);
    
    FILE *f1;
    f1 = fopen("test1.txt","r+");
	// Q- Il faut d'abord recr�er la cl� (voir sema.c)
	key_t k1;
	k1 = ftok("id1",1);




    int mutex_I = 1;
    int donnee = 0;

    int semid;
	semid= semget(k1,0,0);
    printf(" LE semaphore est = %d\n",semid);





    P(semid,mutex_I);
    NbLecteur++;
    rewind(f2);
    fprintf(f2, "%d", NbLecteur);

    if (NbLecteur == 1){
        P(semid,donnee);
    }
    V(semid,mutex_I);

    fprintf(f1,"wxwd");
    fclose(f1);

    P(semid,mutex_I);
    NbLecteur--;
    rewind(f2);
    fprintf(f2, "%d", NbLecteur);
    fclose(f2);

    if (NbLecteur==0){
        V(semid,donnee);
    }

    V(semid,mutex_I);

    semctl(semid,mutex_I,IPC_RMID);

    return 0;





}