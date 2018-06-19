/*
 * nubix-term.c
 *
 *  Created on: 13.06.2018
 *      Author: jan
 */
#include <stdio.h>
#include <stdlib.h>
#include <nubix.h>

int main(int argc, char **argv)
{
	GtkWidget* window;

	nubix_new_window(window, "Nubix-Shell", 80, 25);
	return 0;
}


