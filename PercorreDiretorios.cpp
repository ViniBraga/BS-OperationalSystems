#include <ftw.h>
#include <stdio.h>
#include <sys/stat.h>
#include <vector>
#include <string.h>
#include <iostream>
#include <sys/types.h>
#include<dirent.h>
#include <sstream>
#include <time.h>
using namespace std;

int percorre(const char *name, const struct stat *status, int type);//Método que percorre diretórios de forma recursiva e armazena seus nomes em um vetor
bool listaConteudo(int argc,string argv);//Método que lista detalhadamente o conteúdo dos diretórios (chamando imprime atributos)
bool imprimeAtrib(int argc,string argv,char *relatName);//Método que imprime atributos de diretório
vector<string> vetorDir;//vetor que armazena métodos

int main(int argc, char *argv[]) {
	if(argc == 1) ftw(".", percorre, 1);//Percorrer pastas recursivamente usando método ftw
	else ftw(argv[1], percorre, 1);
	
	for(int i=0; i<vetorDir.size();i++){//percorrer vetor preenchido
		DIR *dp;
		struct dirent *ep;
		const char *arg =vetorDir[i].c_str();
		dp=opendir(arg);
		if(dp!=NULL){//Lógica para verificar se o arquivo é um diretório para dar título à listagem
			ep=readdir(dp);
			switch (ep->d_type){
				case DT_DIR: cout<<vetorDir[i]<<":\n"<<endl;break;
			}
		}
		listaConteudo(argc,vetorDir[i]);//chama método lista conteúdo
		printf("\n\n");
	}
	return 0;
}

int percorre(const char *name, const struct stat *status, int type) {
	string message=name;
	//if(type == FTW_NS) return 0;
	if(type == FTW_F)vetorDir.push_back(message);
	if(type == FTW_D && strcmp(".", name) != 0) vetorDir.push_back(message);
	return 0;
}

bool listaConteudo(int argc,string argv){
	DIR *dp;
	struct dirent *ep;

	const char *arg =argv.c_str();

	dp=opendir(arg);
	if(dp!=NULL){
		while(ep=readdir(dp)){
				/*switch (ep->d_type){
				case DT_UNKNOWN:printf("-");break;
				case DT_REG:	printf("-");break;
				case DT_DIR:	printf("");break;
				default:	printf("-");break;
			}*/
			char *name=ep->d_name;
			//--concatenação
			char result[100];
			strcpy(result,arg);
			strcat(result,"/"); 
			strcat(result,ep->d_name); 
			stringstream ss;
			string s;
			ss << result;
			ss >> s;
			//--------
			string aux = ep->d_name;
			if(aux!=".." && aux!=".")
			imprimeAtrib(argc,s,ep->d_name);
		}
	closedir(dp);
	}
}

bool imprimeAtrib(int argc,string argv,char *relatName){
	struct stat buf;
	struct tm *ts; 
	const char *arg =argv.c_str();
	char buf2[100];
	if(!stat(arg, &buf)){ //Se nome de arquivo válido
	string n = relatName;
	DIR *dp;
	struct dirent *ep;
	const char *arg =argv.c_str();
	dp=opendir(arg);
	

		if(n!=".." && n!="."){	
			if(dp!=NULL){//Lógica para verificar se o arquivo é um diretório para dar título à listagem
				ep=readdir(dp);
				if(ep->d_type==DT_DIR)printf("d");
				else printf("-");
			}

			//Imprime atributos de acesso do proprietário do arquivo
			printf("%1s",((buf.st_mode & S_IRUSR) ? "r" : "-"));
			printf("%1s",((buf.st_mode & S_IWUSR) ? "w" : "-"));
			printf("%1s",((buf.st_mode & S_IXUSR) ? "x" : "-"));

			//Imprime atributos de acesso para membros do grupo
			printf("%1s",((buf.st_mode & S_IRGRP) ? "r" : "-"));
			printf("%1s",((buf.st_mode & S_IWGRP) ? "w" : "-"));
			printf("%1s",((buf.st_mode & S_IXGRP) ? "x" : "-"));

			//Imprime atributos de acesso para outros
			printf("%1s",((buf.st_mode & S_IROTH) ? "r" : "-"));
			printf("%1s",((buf.st_mode & S_IWOTH) ? "w" : "-"));
			printf("%1s",((buf.st_mode & S_IXOTH) ? "x" : "-"));

			ts=localtime(&buf.st_mtime);
			strftime(buf2, sizeof(buf2), "%a %d-%m-%Y- %H:%M:%S", ts);
			printf("\t%20s", buf2);
			cout<<"\t"<<(unsigned int) buf.st_size<<"\t"<<relatName<<endl;
		}

	}else	printf("Arquivo não existe!\n");
}



// FTW_F    The object is a  file
// FTW_D    ,,    ,,   ,, ,, directory
// FTW_DNR  ,,    ,,   ,, ,, directory that could not be read
// FTW_SL   ,,    ,,   ,, ,, symbolic link
// FTW_NS   The object is NOT a symbolic link and is one for 
//          which stat() could not be executed

