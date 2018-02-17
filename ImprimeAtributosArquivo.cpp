/**
Imprime os atributos de um determinado arquivo
**/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){
	struct stat buf;

	if(argc!=2){
		printf("Usar: %s <nome arquivo>\n", argv[0]);
		return 1;
	}

	if(!stat(argv[1], &buf)){ //Se nome de arquivo válido

		//Imprime atributos de acesso do proprietário do arquivo
		printf("%ls",((buf.st_mode & S_IRUSR) ? "r" : "-"));
		printf("%ls",((buf.st_mode & S_IWUSR) ? "w" : "-"));
		printf("%ls",((buf.st_mode & S_IXUSR) ? "x" : "-"));

		//Imprime atributos de acesso para membros do grupo
		printf("%ls",((buf.st_mode & S_IRGRP) ? "r" : "-"));
		printf("%ls",((buf.st_mode & S_IWGRP) ? "w" : "-"));
		printf("%ls",((buf.st_mode & S_IXGRP) ? "x" : "-"));

		//Imprime atributos de acesso para outros
		printf("%ls",((buf.st_mode & S_IROTH) ? "r" : "-"));
		printf("%ls",((buf.st_mode & S_IWOTH) ? "w" : "-"));
		printf("%ls",((buf.st_mode & S_IXOTH) ? "x" : "-"));

		printf("%7d %s\n", (unsigned int) buf.st_size, argv[1]);
	}else	printf("Arquivo não existe!\n");
	return 0;
}
