#!/bin/bash
for ((i = 100; i <=30000;i += 100))
	do 
		gcc gerador.c -o gerador -D N=$i
		./gerador > entrada.txt
		gcc trabalhoISEQUENCIALENCADEADA.c -o trabalhoISEQUENCIALENCADEADA -D NUM_MAX_ALUNOS=$i
		./trabalhoISEQUENCIALENCADEADA < entrada.txt
		echo "$i"
	done
