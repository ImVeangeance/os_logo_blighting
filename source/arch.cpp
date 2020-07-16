#include <iostream>
#include <ctime>
#include <string>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <sys/stat.h>

enum colors 
{RED = 1, BLUE = 33,/*33, 20*/ PURPLE = 55, GREEN = 22, WHITE = 255, PINK = 207, BLACK = 16};

struct termios stored_settings;

void arch_logo_print();
int mt_setscreensize(int rows, int cols);
__int32_t mt_setfgcolor(enum colors color);

__int32_t main()
{
	rk_mytermregime(1, 0, 1, 1, 1); // BE CAREFULL
	mt_setscreensize(55, 20);
	system("clear");
	char buf[8] = {0};
	read(STDIN_FILENO, buf, 8);
	arch_logo_print();
	while(true)
	{}
	return 0;
}

int rk_readkey(enum keys *key) // perevod knopki v klu4
{

	rk_mytermregime(1, 0, 1, 1, 1);
	char buf[8] = { 0 };
	read(STDIN_FILENO, buf, 8);
	if (buf[0] == 'q')
		*key = key_q;
	else
		*key = key_other;
	rk_mytermrestore();
	return 0;
}

__int32_t mt_setscreensize(__int32_t rows, __int32_t cols)
{
	std::cout << "\E[8;" << cols << ";" << rows << ";t";
	return 0;
}

__int32_t mt_setfgcolor(enum colors color) // menyaet cvet texta
{
	std::cout << "\E[38;5;" << color << "m";
	return 0;
}

__int32_t rk_mytermsave(void)
{
	if (tcgetattr(0, &stored_settings)) {
		return 1;
	}

	return 0;
}

__int32_t rk_mytermrestore(void)
{
	if (tcsetattr(0, TCSANOW, &stored_settings)){
		return 1;
	}

	return 0;
}

__int32_t rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint)
{
	struct termios new_settings;
	rk_mytermsave();
	new_settings = stored_settings;

	if (regime == 1) {
		new_settings.c_lflag &= (~ICANON);

		if (sigint == 1) {
			new_settings.c_lflag &= (~ISIG);
		} else if (sigint == 0) {
			new_settings.c_lflag |= ISIG;
		}

		if (echo == 1) {
			new_settings.c_lflag &= (~ECHO);
		} else if (echo == 0) {
			new_settings.c_lflag |= ECHO;
		}

		new_settings.c_cc[VMIN] = vmin;
		new_settings.c_cc[VTIME] = vtime;
	} else if (regime == 0) {
		new_settings.c_lflag |= ICANON;
	}

	tcsetattr(0, TCSANOW, &new_settings);
	return 0;
}

void arch_logo_print()
{
	mt_setfgcolor(BLUE);
	std::cout << "\n\n\n";
	std::cout << "\t                  .o+`\n";
	std::cout << "\t                 `ooo/\n";
	std::cout << "\t                `+oooo:\n";
	std::cout << "\t               `+oooooo:\n";
	std::cout << "\t               -+oooooo+:\n";
	std::cout << "\t             `/:-:++oooo+:\n";
	std::cout << "\t            `/++++/+++++++:\n";
	std::cout << "\t           `/++++++++++++++:\n";
	std::cout << "\t          `/+++ooooooooooooo/`\n";
	std::cout << "\t         ./ooosssso++osssssso+`\n";
	std::cout << "\t        .oossssso-````/ossssss+`\n";
	std::cout << "\t       -osssssso.      :ssssssso.\n";
	std::cout << "\t      :osssssss/        osssso+++.\n";
	std::cout << "\t     /ossssssss/        +ssssooo/-\n";
	std::cout << "\t   `/ossssso+/:-        -:/+osssso+-\n";
	std::cout << "\t  `+sso+:-`                 `.-/+oso:\n";
	std::cout << "\t `++:.                           `-/+/\n";
	std::cout << "\t .`                                 `/\n";
	/* TODO */ // mt_setfgcolor(DEFAULT);
}
