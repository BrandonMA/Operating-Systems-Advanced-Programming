#!/bin/bash
echo -e "1- list processes\n2- search for a process\n3- display files in a folder\n4- search for a file (use the find command)\n5- change file permissions\n6- change folder permissions (for all files inside the folder too)\n7- open a file using a text editor (vi, emacs, ...)\n8- exit\n"
read -p "Choose an option: " answer

if [ $answer = "1" ]; then
	ps aux
elif [ $answer = "2" ]; then
	read -p "Name of the process: " process_name
	ps aux | grep $process_name
elif [ $answer = "3" ]; then
	read -p "Name of the folder: " folder_name
	ls $folder_name
elif [ $answer = "4" ]; then
	read -p "Name of the file: " file_name
	find . $file_name
elif [ $answer = "5" ]; then
	read -p "Name of the file: " file_name
	read -p "Write the permissions: " permissions
	chmod $permissions $file_name
elif [ $answer = "6" ]; then
	read -p "Name of the folder: " folder_name
	read -p "Write the permissions: " permissions
	chmod -R $permissions $folder_name
elif [ $answer = "7" ]; then
	read -p "Name of the file: " file_name
	nano $file_name
fi
