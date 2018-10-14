import os

def listProcesses():
	os.system("ps aux")

def searchForProcess(process_name):
	os.system("ps aux | grep " + process_name)

def showFiles(folder_name):
	os.system("ls " + folder_name)

def find(file_name):
	os.system("find . " + file_name)

def permisions(permisions, file_name):
	os.system("chmod " + permisions + " " + file_name)

def permisionsForFolder(permisions, folder_name):
	os.system("chmod -R " + permisions + " " + folder_name)

def openFile(file_name):
	os.system("nano " + file_name)

answer = input("1- list processes\n2- search for a process\n3- display files in a folder\n4- search for a file (use the find command)\n5- change file permissions\n6- change folder permissions (for all files inside the folder too)\n7- open a file using a text editor (vi, emacs, ...)\n8- exit\n")

if answer == "1":
	listProcesses()

elif answer == "2":
	process_name = input("Write the name of the process you want to search for: ")
	searchForProcess(process_name)

elif answer == "3":
	folder_name = input("Write the name of the folder you want to look: ")
	showFiles(folder_name)

elif answer == "4":
	file_name = input("Write the name of the file: ")
	find(file_name)

elif answer == "5":
	permisions = input("Write the permisions that you want: ")
	file_name = input("Write the file name: ")
	permisions(permisions, file_name)

elif answer == "6":
	permisions = input("Write the permisions that you want: ")
	folder_name = input("Write the folder name: ")
	permisionsForFolder(permisions, folder_name)

elif answer == "7":
	file_name = input("Write the file name: ")
	openFile(file_name)

elif answer == "8":
	exit()