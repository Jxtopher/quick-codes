///
/// @file hexpatch.cpp
/// @author *
/// @date Sat May  1 20:15:15 2010
/// @brief Hello world for a simple exemple code
///
/// @compilation g++ hexpatch.cpp -o hexpatch
/// @execution *
///

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

//Display a help
void help()
{
	cout<<"Usage : hexpatch [OPTION]"<<endl;
	cout<<endl;
	cout<<"\t-i file\t\t\tit's file input"<<endl;
	cout<<"\t-o file\t\t\tit's file output"<<endl;
	cout<<"\t-m stringhex:stringhex\t"<<endl;
	cout<<"\t-v\t\t\tversion"<<endl;
	cout<<endl;
	cout<<"Examples :"<<endl;
	cout<<"hexpatch -i ifile -o ofile -m 747372615f74616d:f4ff"<<endl;
	cout<<endl;
	
}

//Display the version
void version()
{
	cout<<"Version : 1.0"<<endl;
	cout<<"Date de compilation : "<<__DATE__<<endl;
	cout<<"Autor : l32k3"<<endl;
}

//Verify if the string is hex
int checkHex(string hex)
{
	for (unsigned int i = 0 ; i < hex.length() ; i++)
	{
		bool error = true;
		for (int j = 48 ; j <= 57 ; j++)
			if (hex[i] == j)
				error = false;
		for (int j = 65 ; j <= 70 ; j++)
			if (hex[i] == j)
				error = false;
		for (int j = 97 ; j <= 102 ; j++)
			if (hex[i] == j)
				error = false;
		if (error)
			return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

//Conversion hex into decimal
int hexChaine(string hex)
{
	int x = 0;

	istringstream iss(hex.c_str()); 
	iss >> std::hex >> x;
	
	return x;
}
/*
* Chercher le nombre de fois, qu'une chaine de caractere (positionsString) soit présent dans le fichier (inputFile)
* retroune le nombre de fois que la chaine  apparait si le fichier n'exist pas, il retourne -1
*/
int searchNomberString(string inputFile, string positionString)
{
	FILE* iFile = NULL;
	int character = 0, nbString = 0;
	unsigned int i = 0;

	iFile = fopen(inputFile.c_str(), "rb");
 
	if (iFile != NULL)
	{
		// Boucle de lecture des caractères un à un
		do
		{
			character = fgetc(iFile); // On lit le caractère
			//printf("%x ", character); // On l'affiche
			if ( hexChaine(positionString.substr(i,2)) == character)
			{		
				//printf("%x \n", character);
				if (i < positionString.length())
					i += 2;
				else if (i == positionString.length())
				{
					nbString++;
					i = 0;
				}
			}
			else
			{
				if (i == positionString.length())
					nbString++;
				long int calc = i / 2;
				fseek(iFile, calc*-1, SEEK_CUR);
				i = 0;
			}		

		} while (character != EOF); // On continue tant que fgetc n'a pas retourné EOF (fin de fichier)
 
		fclose(iFile);
	}
	else
		return -1;
	return nbString;
}
long searchPositionString(string inputFile, string positionString)
{
	FILE* iFile = NULL;
	int character = 0, position = 0;
	unsigned int i = 0;
 
	iFile = fopen(inputFile.c_str(), "rb");
 
	if (iFile != NULL)
	{
		// Boucle de lecture des caractères un à un
		do
		{
			character = fgetc(iFile); // On lit le caractère
			//printf("%x ", character); // On l'affiche
			if ( hexChaine(positionString.substr(i,2)) == character)
			{		
				//printf("%x \n", character);
				if (i < positionString.length())
					i += 2;
				else if (i == positionString.length())
				{
					position = ftell(iFile);
					i = 0;
				}
			}
			else
			{
				if (i == positionString.length())
					position = ftell(iFile);
				long int calc = i / 2;
				fseek(iFile, calc*-1, SEEK_CUR);
				i = 0;
			}		

		} while (character != EOF); // On continue tant que fgetc n'a pas retourné EOF (fin de fichier)
 
		fclose(iFile);
	}
	else
		return -1;
	return position;
}
int replaceString(string inputFile, string outputFile, long position, string newString)
{
	FILE* iFile = NULL;
	FILE* oFile = NULL;
	int character = 0;

	iFile = fopen(inputFile.c_str(), "rb");
	oFile = fopen(outputFile.c_str(), "wb");

	if (iFile != NULL && oFile != NULL)
	{
		// Boucle de lecture des caractères un à un
		do
		{
			character = fgetc(iFile); // On lit le caractère
			//printf("%x ", character); // On l'affiche
			fprintf(oFile,"%c", character);
			if (ftell(iFile) >= position-1 && ftell(iFile) < (position+(newString.length()/2)))
			{
				for (unsigned int i = 0 ; i < (newString.length()) ; i +=2)
				{
					character = fgetc(iFile);
					//printf("->%x ", character);
					//printf("<>%x\n",hexChaine(newString.substr(i,2)));
					fprintf(oFile,"%c", hexChaine(newString.substr(i,2)));
				}
			}
		} while (character != EOF); // On continue tant que fgetc n'a pas retourné EOF (fin de fichier)

		fclose(iFile);
		fclose(oFile);
	}
	else
		return -1;
		
	return EXIT_SUCCESS;
}
int main(int argc, char **argv)
{
	string inputFile, outputFile, positionString, newString;

	for (int i = 0 ; i < argc ; i++)
	{
		if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help" ))
		{
			help();
			return EXIT_SUCCESS;
		}
		else if (!strcmp(argv[i], "-v"))
		{
			version();
			return EXIT_SUCCESS;
		}
		else if (!strcmp(argv[i], "-i") && argc > i+1)
			if (argv[i+1][0] != '-')
				inputFile = argv[++i];
		
		if (!strcmp(argv[i], "-o") && argc > i+1)
                	if (argv[i+1][0] != '-')	
				outputFile = argv[++i];
		
		if (!strcmp(argv[i], "-m") && argc > i+1)	
		{
			while (argc > ++i)
			{
				if (argv[i][0] == '-')	
				{	
					i--;
					break;
				}
				positionString += argv[i];
			}
		}	
	}
	
	if (inputFile.length() == 0 || outputFile.length() == 0 || positionString.length() == 0)
	{
		help();
		return EXIT_SUCCESS;
	}
	if (positionString.find(":") != string::npos)
	{
			newString = positionString.substr(positionString.find(":")+1,positionString.length()-positionString.find(":")+1);	
			positionString = positionString.erase(positionString.find(":"),positionString.length()-positionString.find(":"));
	}
	if (positionString.length() % 2 != 0 || newString.length() % 2 != 0)
	{
		cerr<<"Error : L'option -m doit doit avoir un nombre caractere paire"<<endl;
		return EXIT_SUCCESS;
	}	
	if (checkHex(positionString) == EXIT_FAILURE || checkHex(newString) == EXIT_FAILURE)
	{
		cerr<<"Error : L'option -m doit contenir que de Hexadecimal"<<endl;
		return EXIT_SUCCESS;
	}
		
	cout<<"Input file : "<<inputFile<<endl;
	cout<<"Output file : "<<outputFile<<endl;
	cout<<"Find string : "<<positionString<<endl;
	cout<<"New string : "<<newString<<endl;

	int tmp = searchNomberString(inputFile, positionString);

	if (tmp == -1)
		cerr<<"Error : file : \""<<inputFile<<"\" is not exist !"<<endl;
	else if (tmp > 1 )
		cerr<<"Error : The string is not single. It's : "<<tmp<<" times"<<endl;
	else if (tmp == 0)
		cerr<<"Error : The string is not found"<<endl;
	else
	{
		int position = searchPositionString(inputFile, positionString);
		if (newString.length() != 0)
			replaceString(inputFile, outputFile, position, newString);
		cout<<"The create file is full success !"<<endl;
	}
	
	return EXIT_SUCCESS;
}
