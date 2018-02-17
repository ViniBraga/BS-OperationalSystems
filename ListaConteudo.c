/**
Lista conteúdo do diretório
**/

#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>

int main(int argc, char *argv[]){
	DIR *dp;
	struct dirent *ep;

	if(argc!=2){
		printf("Usar: %s <nome diretorio>\n", argv[0]);
		return (1);
	}

	dp=opendir(argv[1]);
	if(dp!=NULL){
		while(ep=readdir(dp)){
			switch (ep->d_type){
				case DT_UNKNOWN:printf("?");break;
				case DT_REG:	printf("f");break;
				case DT_DIR:	printf("d");break;
				default:	printf("o");break;
			}
			printf("%20s\n",ep->d_name);
		}
	closedir(dp);
	}else printf("Não foi possivel abrir o direório %s", argv[1]);
	return 0;
}
