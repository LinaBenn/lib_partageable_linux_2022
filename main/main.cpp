
#include <iostream>
#include <dlfcn.h>


int main(int argc, char ** argv)
{
	int num1=3;
	int num2=10;
	int valeur;
	
	int choix=0;
	
	while (choix != 1 && choix != 2) {
		std::cout << "Choisir un composant 1 ou 2" << std::endl;
		std::cin >> choix;
	}
	void* hndl = nullptr;
	
	if (choix == 1) {
		hndl = dlopen("./libComposant1.so", RTLD_LAZY);
	} else {
		hndl = dlopen("./libComposant2.so", RTLD_LAZY);
	}
	
	if (!hndl) {
		std::cerr << "dlopen : " << dlerror() << std::endl;
		exit(EXIT_FAILURE);
	}

	int (*fct) (int, int);

	if (choix == 1) {
		fct = (int (*) (int, int)) dlsym(hndl, "composant1");
	} else {
		fct = (int (*) (int, int)) dlsym(hndl, "composant2");
	}


	if (!fct) {
		std::cerr << "dlsym : " << dlerror() << std::endl;
		exit(EXIT_FAILURE);
	}

	std::cout << "Valeur : " << fct(num1, num2) << std::endl;
	
	dlclose(hndl);
	exit(EXIT_SUCCESS);

}
