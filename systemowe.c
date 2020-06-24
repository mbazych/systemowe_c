#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
	// sprawdza czy został podany argument jako nazwa pliku
	// program ma zawsze jeden pierwszy argument - swoją nazwę
	// stąd argc = 1 jest niepoprawne, argc = 3 to już za dużo argumentów
	// czyli plik wykonujemy ./systemowe.c <nazwa_pliku>
	if (argc != 2)
	{
		printf("\nPass command line argument as your filename.\n");
		return 1;
	}
	// tworzymy zmienną procesa dziecka
	pid_t pid;
	// przypisujemy do zmiennej nowy proces dziecko
	pid = fork();
	// jeśli pid == 0 to jest to proces dziecko, nasz sforkowany proces
	if (pid == 0)
	{
		// tworzymy bufor pliku
		FILE *stream;
		// tworzymy zmienną iteracyjną
		int i;
		// otwieramy plik
		stream = fopen(argv[1], "w");

		// sprawdzamy czy plik się otworzył prawidłowo, jeśli nie, zamyka program
		if (!stream)
		{
			printf("\nError while opening file\n");
			return 1;	
		}
		else
		{
			// iteracja od 1 do 50
			for ( i = 1; i <= 50; i++)
			{	
				// jeśli dzielenie przez 3 nie zwraca reszty
				if(i % 3 == 0)
					// zapisz do pliku zmienną i
					fprintf(stream, "%d\n", i);
			}
			// zamknij plik
			fclose(stream);

		}
	}
	// jeśli pid != 0 to jest to proces rodzica
	if (pid != 0)
	{	
		// czekamy aż proces dziecka zakończy się i odeśle sygnał do rodzica
		int *wstatus;
		wait(wstatus);
		// pokazujemy PID rodzica
		printf("\nPARENT PID: %d", getpid());
		// PID child processu
		printf("\nCHILD PID: %d", pid);

		// CO DO TEGO JESTEM MOCNO NIEPEWNY CZY JEST DOBRZE, WYDAJE MI SIE ZE NIE

		// i informacje że pgrogram się zakończył razem z informacją o kodzie
		printf("\nChild process ended with code ");
		printf("%d\n", WIFEXITED(*wstatus));
	}
	// otwieramy plik niebuforowanymi operacjami I/O
	int fd = open(argv[1], O_RDONLY);
	// mierzymy lseekiem rozmiar pliku, SEEK_END i 0 gwanantują nam że będzie na końcu pliku
	int size = lseek(fd, 0, SEEK_END);

	// no i wyświetlamy rozmiar
	printf("\nSize of the file is ");
	printf("%d\n", size);

	// zamykamy plik
	close(fd);

	// i zamykamy program
	return 0;
}
