#!/bin/bash

FILE=cripto.exe

echo -e "\nCompilando o arquivo $FILE\n"
gcc criptografia.c main.c -o $FILE -lm

if [ "$FILE" ] ; then
	./$FILE
	echo -e "\nExcluindo o arquivo $FILE\n"
	sudo rm $FILE
else
	echo -e "\nErro ao compilar!\n"
fi