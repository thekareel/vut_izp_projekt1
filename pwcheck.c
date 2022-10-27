/**
 * Project1
 * 
 * Author:	Karel Körner
 * xlogin:	xkorne02
 *
 **/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define PW_MAX 102

bool equality_of_str(char str[], char strForCompare[]);
bool contains_lowercase(char str[]);
bool contains_uppercase(char str[]);
bool contains_digit(char str[]);
bool contains_special(char str[]);
bool contains_upper_lower(char str[]);
bool contains_sequence_of_chars(char str[], int sequenceLength);
bool contains_two_substr(char str[], int substrLength);
bool is_digit(char str[]);
int password_length(char str[]);

int main(int argc, char* argv[])
{
	if (argc >= 3 && argc <= 4)
	{
		// check the first two arguments for positive numbers
		int level, param;
		long int longLevel, longParam;
		if (is_digit(argv[1]) && is_digit(argv[2]))
		{
			longLevel = strtol(argv[1], NULL, 10);
			longParam = strtol(argv[2], NULL, 10);
			if (longLevel <= 0 || longParam <= 0)
			{
				fprintf(stderr, "Argumenty LEVEL a PARAM musi byt vetsi nez 0!\n");
				return EXIT_FAILURE;
			}
			else
			{
				if (longLevel <= INT_MAX)
				{
					level = longLevel;
				}
				else
				{
					level = INT_MAX;
				}
				if (longParam <= INT_MAX)
				{
					param = longParam;
				}
				else
				{
					param = INT_MAX;
				}
			}
		}
		else
		{
			fprintf(stderr, "Argumenty LEVEL a PARAM nebyly zadane jako cislo!\n");
			return EXIT_FAILURE;
		}

		if (level >= 1 && level <= 4)
		{
			// check the correctness of the optional parameter --stats
			bool stats = false;
			if (argc == 4)
			{
				int countStats;
				for (countStats = 0; argv[3][countStats] != '\0'; ++countStats);
				if (countStats == 7)
				{
					if (equality_of_str(argv[3], "--stats"))
					{
						stats = true;
					}
					else
					{
						fprintf(stderr, "Chybna syntaxe prikazu!\n");
						return EXIT_FAILURE;
					}
				}
				else
				{
					fprintf(stderr, "Chybna syntaxe prikazu!\n");
					return EXIT_FAILURE;
				}
			}

			bool requirements, containsNewLine;
			int minLength = INT_MAX, countOfPasswords = 0, totalLength = 0, countOfChars = 0;
			bool charsArray[128] = { false };
			double averageLenght = 0;
			char password[PW_MAX];
			while (fgets(password, PW_MAX, stdin) != NULL)
			{
				// check if the password is no longer than 100 chars
				containsNewLine = false;
				for (int i = 0; i <= 100; ++i)
				{
					if (password[i] == '\n')
					{
						containsNewLine = true;
					}
				}
				if (!containsNewLine)
				{
					fprintf(stderr, "Prilis dlouhe heslo!\n");
					return EXIT_FAILURE;
				}

				// STATISTICS:
				int passwordLength = password_length(password);
				if (passwordLength < minLength)
				{
					minLength = passwordLength;
				}
				totalLength += passwordLength;
				++countOfPasswords;
				for (int i = 0; i < passwordLength; ++i)
				{
					int index = password[i];
					charsArray[index] = true;
				}

				requirements = true;
				switch (level)
				{
				case 4: // 4. RULE: the password does not contain two identical substrings of length at least param
					if (contains_two_substr(password, param))
					{
						requirements = false;
					}
					// fall through
				case 3: // 3. RULE: the password does not contain a sequence of the same characters of length at least param
					if (contains_sequence_of_chars(password, param))
					{
						requirements = false;
					}
					// fall through
				case 2: // 2. RULE: the password contains chars from at least param of the following groups
					if (param >= 1) // lowercase(a-z)
					{
						if (!contains_lowercase(password))
						{
							requirements = false;
						}
					}
					if (param >= 2) // uppercase(A-Z)
					{
						if (!contains_uppercase(password))
						{
							requirements = false;
						}
					}
					if (param >= 3) // numbers(0-9) 
					{
						if (!contains_digit(password))
						{
							requirements = false;
						}
					}
					if (param >= 4) // special characters from the ASCII table in positions 32-126 
					{
						if (!contains_special(password))
						{
							requirements = false;
						}
					}
					// fall through
				case 1: // 1. RULE: the password contains at least 1 uppercase and 1 lowercase.
					if (!contains_upper_lower(password))
					{
						requirements = false;
					}
					// fall through
					break;
				}
				if (requirements)
				{
					printf("%s", password);
				}
			}
			if (stats)
			{
				if (countOfPasswords > 0)
				{
					averageLenght = (double)totalLength / countOfPasswords;
					for (int i = 0; i < 128; ++i)
					{
						countOfChars += charsArray[i];
					}
				}
				else
				{
					minLength = 0;
				}
				printf("Statistika:\n");
				printf("Ruznych znaku: %d\n", countOfChars);
				printf("Minimalni delka: %d\n", minLength);
				printf("Prumerna delka: %0.1lf\n", averageLenght);
			}
		}
		else
		{
			fprintf(stderr, "Byl zadan neexistujici bezpecnostni LEVEL!\n");
			return EXIT_FAILURE;
		}
	}
	else
	{
		fprintf(stderr, "Byl zadan chybny pocet argumentu!\n");
		return EXIT_FAILURE;
	}

	return 0;
}

/*
 * Function: equality_of_str
 * -------------------------
 * check if two strings are identical
 *
 *  returns:
 *			true = strings are identical
 *			false = strings are not identical
 */
bool equality_of_str(char str[], char strForCompare[])
{
	for (int i = 0; str[i] != '\0'; ++i)
	{
		if (str[i] != strForCompare[i])
		{
			return false;
		}
	}
	return true;
}
/*
 * Function: contains_lowercase
 * ----------------------------
 * check if string contains lowercase
 *
 *  returns:
 *			true = string contains lowercase
 *			false = string does not contain lowercase
 */
bool contains_lowercase(char str[])
{
	for (int i = 0; str[i] != '\0'; ++i)
	{
		if (str[i] >= 'a' && str[i] <= 'z')
		{
			return true;
		}
	}
	return false;
}
/*
 * Function: contains_uppercase
 * ----------------------------
 * check if string contains uppercase
 *
 *  returns:
 *			true = string contains uppercase
 *			false = string does not contain uppercase
 */
bool contains_uppercase(char str[])
{
	for (int i = 0; str[i] != '\0'; ++i)
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
		{
			return true;
		}
	}
	return false;
}
/*
 * Function: contains_digit
 * ------------------------
 * check if string contains digits
 *
 *  returns:
 *			true = string contains digits
 *			false = string does not contain digits
 */
bool contains_digit(char str[])
{
	for (int i = 0; str[i] != '\0'; ++i)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			return true;
		}
	}
	return false;
}
/*
 * Function: contains_special
 * --------------------------
 * check if string contains special characters
 *
 *  returns:
 *			true = string contains special characters
 *			false = string does not contain special characters
 */
bool contains_special(char str[])
{
	for (int i = 0; str[i] != '\0'; ++i)
	{
		if (str[i] >= 32 && str[i] <= 126) // printable chars only
		{
			if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9'))
			{
				continue;
			}
			return true;
		}
	}
	return false;
}
/*
 * Function: contains_upper_lower
 * ------------------------------
 * check if string contains uppercase and lowercase letters
 *
 *  returns:
 *			true = string contains uppercase and lowercase
 *			false = string does not contain uppercase or lowercase
 */
bool contains_upper_lower(char str[])
{
	if (contains_lowercase(str) && contains_uppercase(str))
	{
		return true;
	}
	return false;
}
/*
 * Function: contains_sequence_of_chars
 * ------------------------------------
 * check if string contains a sequence of characters of length sequenceLength
 *
 *  returns:
 *			true = string contains a sequence of characters of length sequenceLength
 *			false = string does not contain a sequence of characters of length sequenceLength
 */
bool contains_sequence_of_chars(char str[], int sequenceLength)
{
	if (!(sequenceLength > password_length(str)))
	{
		int count;
		int passwordLength = password_length(str);
		for (int i = 0; i <= (passwordLength - sequenceLength); ++i)
		{
			count = 0;
			for (int j = i; j < (i + sequenceLength); ++j)
			{
				if (str[i] == str[j])
				{
					++count;
					if (count == sequenceLength)
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}
/*
 * Function: contains_two_substr
 * -----------------------------
 * check if string contains 2 identical substrings of length substrLength
 *
 *  returns:
 *			true = string contains 2 identical substrings of length substrLength
 *			false = string does not contain 2 identical substrings of length substrLength
 */
bool contains_two_substr(char str[], int substrLength)
{
	if (!(substrLength > password_length(str) / 2))
	{
		char substr[100] = { '\0' };
		int count = 0, countOfMatches = 0;
		int index;
		int passwordLength = password_length(str);
		for (int i = 0; i <= passwordLength - substrLength; ++i)
		{
			index = 0;
			for (int j = i; j < i + substrLength; ++j)
			{
				substr[index] = str[j];
				++index;
			}
			for (int k = 0; k <= passwordLength - substrLength; ++k)
			{
				index = 0;
				for (int l = 0; l < substrLength; ++l)
				{
					if (substr[index] == str[k + l])
					{
						++count;
						if (count == substrLength)
						{
							++countOfMatches;
							if (countOfMatches == 2)
							{
								return true;
							}
						}
					}
					++index;
				}
				count = 0;
			}
			countOfMatches = 0;
		}
	}
	return false;
}
/*
 * Function: is_digit
 * ------------------
 * check if char is a number
 *
 *  returns: 
 *			true = char is a number
 *			false = char is not a number
 */
bool is_digit(char str[])
{
	for (int i = 0; str[i] != '\0'; ++i)
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
		{
			return false;
		}
	}
	return true;
}
/*
 * Function: password_length
 * -------------------------
 * calculates the length of the string terminated by \n
 * 
 *  returns: length of string
 */
int password_length(char str[])
{
	int i;
	for (i = 0; str[i] != '\n'; ++i);
	return i;
}