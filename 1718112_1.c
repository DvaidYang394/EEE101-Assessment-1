/*
Name: EEE101 C Programming and Software Engineering 1 - Assignment 1
File Name: 1718112_1.c
Copyright: Free

Author: Ziqi Yang
Description: Input full name, phone number, 2-digit decimal number and temperature in degrees Celsius,
             and do operate for the input data, which will print on the screen at last.
*/

/* Include header files Start. */
#include <stdio.h>				/* Include standard library stdio.h for use of printf(), gets() and fflush(). */
#include <stdlib.h>				/* Include standard library stdlib.h for use of atof(), atoi() and itoa(). */
#include <string.h>				/* Include standard library string.h for use of strlen(). */
#include <ctype.h>				/* Include standard library ctype.h for use of isalpha() and isdigit(). */
/* Include header files End. */

/* Define Start. */
#define ERR_ATTEMPT 3			/* Define the total input attempts for each function. */
#define NAME_LENGTH 50			/* Define the max name length. */
#define PHONE_LENGTH 11			/* Define the phone number length. */
#define NUMBER_LENGTH 2			/* Define the 2 digit number length. */
#define TEMPER_LENGTH 10		/* Define the max temperature length. */
/* Define End. */

/* Define struct type Start. */
typedef struct					/* Define a new type to store data about name. */
{
	char	full[256];			/* An array up to store full name as string. */
	int		length;				/* The length of name. */
	int		sum;				/* The sum of character values of the name. */
	int		err_reason;			/* The reason of error occurs. */
	int		result;				/* The run result of the name read function. result_OK: run successfully. result_Error: run failed. */
} Name_Struct;					/* The type to store name information is Name_Struct. */

typedef struct					/* Define a new type to store data about phone. */
{
	char	number[256];		/* An array to store phone number as string. */
	int		length;				/* The length of phone number. */
	char	numerator[7];		/* An array to store first 6 digits of the phone number. */
	char	denominator[6];		/* An array to store last 5 digits of the phone number. */
	float	value;				/* The value which divide the first 6 figures of the telephone number by the last 5. */
	int		err_reason;			/* The reason of error occurs. */
	int		result;				/* The run result of the phone read function. result_OK: run successfully. result_Error: run failed. */
} Phone_Struct;					/* The type to store phone information is Phone_Struct. */

typedef struct					/* Define a new type to store data about the 2 digit number. */
{
	char	decimal[256];		/* An array to store the 2 digit number as string. */
	int		length;				/* The length of the number. */
	int		binary;				/* The number in binary. */
	int		err_reason;			/* The reason of error occurs. */
	int		result;				/* The run result of the number read function. result_OK: run successfully. result_Error: run failed. */
} Number_Struct;				/* The type to store number information is Number_Struct. */

typedef struct					/* Define a new type to store data about the temperature. */
{
	char	celsius[256];		/* An array to store temperature in degrees Celsius as string. */
	int		length;				/* The length of the temperature in degrees Celsius. */
	int		fahrenheit;			/* The temperature in degrees Fahrenheit. */
	int		kelvin;				/* The temperature in degrees Kelvin. */
	int		err_reason;			/* The reason of error occurs. */
	int		result;				/* The run result of the temperature read function. result_OK: run successfully. result_Error: run failed. */
} Temper_Struct;				/* The type to store temperature information is Temper_Struct. */
/* Define struct type End. */

/* Define enumeration type Start. */
typedef enum					/* Define a new enum type to show result of get functions clearly. */
{
	result_Error = 0,			/* If get functions run failed, return result_Error. */
	result_OK					/* If get functions run successfully, return result_OK. */
} General_Result;				/* The type to show result of get functions is General_Result. */

typedef enum					/* Define a new enum type to show the reason of error occurs. */
{
	err_none = 0,				/* If no error occurs, the err_reason is err_none. */
	err_long,					/* If the input is too long, the err_reason is err_long. */
	err_short,					/* If the input is too short, the err_reason is err_short. */
	err_illegal,				/* If there are illegal characters in the input, the err_reason is err_illegal. */
	err_nofull					/* If the name is not full name, the err_reason is err_nofull. */
} Error_Reason;
/* Define enumeration type End. */

/* Function declaration Start. */

/* Declear get functions. */
Name_Struct name_get(Name_Struct name);						/* Declare a function name_get to get and verify name from user. */
Phone_Struct phone_get(Phone_Struct phone);					/* Declare a function phone_get to get and verify phone number from user. */
Number_Struct number_get(Number_Struct number);				/* Declare a function number_get to get and verify 2 digits number from user. */
Temper_Struct temper_get(Temper_Struct temper);				/* Declare a function temper_get to get and verify temperature from user. */

/* Declear operator functions. */
Name_Struct name_operator(Name_Struct name);				/* Declare a function name_operator to operate for the name. */
Phone_Struct phone_operator(Phone_Struct phone);			/* Declare a function phone_operator to operate for the phone number. */
Number_Struct number_operator(Number_Struct number);		/* Declare a function number_operator to operate for the 2 digits number. */
Temper_Struct temper_operator(Temper_Struct temper);		/* Declare a function temper_operator to operate for the temperature. */

/* Declare print functions. */
void name_err_print(Name_Struct name);						/* Declare a function name_err_print to print name error reason. */
void phone_err_print(Phone_Struct phone);					/* Declare a function phone_err_print to print phone number error reason. */
void number_err_print(Number_Struct number);				/* Declare a function number_err_print to print 2 digits number error reason. */
void temper_err_print(Temper_Struct temper);				/* Declare a function temper_err_print to print temperature error reason. */
/* Function declaration End. */

/* Main function Start. */

/* Define a function named main. */
int main()
{
	Name_Struct name = { "00", NAME_LENGTH, 0, err_none, result_Error };							/* Declare name as Name_Struct and initialize name. */
	Phone_Struct phone = { "00", PHONE_LENGTH , "00", "00", 0, err_none, result_Error };			/* Declare phone as Phone_Struct and initialize phone. */
	Number_Struct number = { "00", NUMBER_LENGTH, 0, err_none, result_Error };						/* Declare number as Number_Struct and initialize number. */
	Temper_Struct temper = { "00", TEMPER_LENGTH, 0, 0, err_none, result_Error };					/* Declare temper as Temper_Struct and initialize temper. */
	int attempt = ERR_ATTEMPT;																		/* Declare attempt to store the rest attempts. */

	while (name.result == result_Error)										/* Read name from user input until the result type is correct. */
	{
		name = name_get(name);												/* Read name. */
		if (name.result == result_Error && attempt >= 0)					/* If the name inputed is incorrect and has attempts. */
		{
			name_err_print(name);											/* Print name error reason. */
			if (attempt > 0)												/* Have attempts. */
			{
				printf("You have %d attempts to try again!", attempt);		/* Notice the user the rest of attempts. */
				attempt--;													/* Reduce attempts. */
			}
			else															/* No attempts. */
			{
				printf("You have no attempts to try again, it will go to next function.\n\n");			/* Notice the user no attempts and go to next function. */
				break;
			}
		}
	}
	if (name.result == result_OK)															/* If the name input correctly. */
	{
		name = name_operator(name);															/* Operate for name. */
		printf("The sum of the chapter values of %s is %d.\n\n", name.full, name.sum);		/* Print the result. */
	}

	attempt = ERR_ATTEMPT;																	/* Reset the attempt. */
	while (phone.result == result_Error)													/* Read phone number from user input until the result type is correct. */
	{
		phone = phone_get(phone);															/* Read phone number. */
		if (phone.result == result_Error && attempt >= 0)									/* If the phone number inputed is incorrect and has attempts. */
		{
			phone_err_print(phone);															/* Print phone number error reason. */
			if (attempt > 0)
			{
				printf("You have %d attempts to try again!", attempt);						/* Notice the user the rest of attempts. */
				attempt--;
			}
			else
			{
				printf("You have no attempts to try again, it will go to next function.\n\n");			/* Notice the user no attempts and go to next function. */
				break;
			}
		}
	}
	if (phone.result == result_OK)																				/* If the phone number input correctly. */
	{
		phone = phone_operator(phone);																			/* Operate for phone number. */
		printf("The value of %s / %s is %.2f.\n\n", phone.numerator, phone.denominator, phone.value);			/* Print the result. */
	}

	attempt = ERR_ATTEMPT;																						/* Reset the attempt. */
	while (number.result == result_Error)																		/* Read 2 digits number from user input until the result type is correct. */
	{
		number = number_get(number);																			/* Read 2 digits number. */
		if (number.result == result_Error && attempt >= 0)														/* If the 2 digits number inputed is incorrect and has attempts. */
		{
			number_err_print(number);																			/* Print 2 digits number error reason. */
			if (attempt > 0)
			{
				printf("You have %d attempts to try again!", attempt);											/* Notice the user the rest of attempts. */
				attempt--;
			}
			else
			{
				printf("You have no attempts to try again, it will go to next function.\n\n");			/* Notice the user no attempts and go to next function. */
				break;
			}
		}
	}
	if (number.result == result_OK)													/* If the 2 digits number input correctly. */
	{
		number = number_operator(number);											/* Operate for 2 digits number. */
		printf("The binary of %s is %d.\n\n", number.decimal, number.binary);		/* Print the result. */
	}

	attempt = ERR_ATTEMPT;															/* Reset the attempt. */
	while (temper.result == result_Error)											/* Read the temperature from user input until the result type is correct. */
	{
		temper = temper_get(temper);												/* Read the temperature. */
		if (temper.result == result_Error && attempt >= 0)							/* If the temperature inputed is incorrect and has attempts. */
		{
			temper_err_print(temper);												/* Print temperature error reason. */
			if (attempt > 0)
			{
				printf("You have %d attempts to try again!", attempt);				/* Notice the user the rest of attempts. */
				attempt--;
			}
			else
			{
				printf("You have no attempts to try again, the programme will exit.\n\n");			/* Notice the user no attempts and exit the program. */
				break;
			}
		}
	}
	if (temper.result == result_OK)																	/* If the temperature input correctly. */
	{
		temper = temper_operator(temper);															/* Operate for the temperature. */
		printf("The temperture in degrees Celsius is %d¡ãC.\n", (int)(atof(temper.celsius) + 0.5));	/* Print the result. */
		printf("The temperture in degrees Fahrenheit is %d¡ãF.\n", temper.fahrenheit);				/* Print the result. */
		printf("The temperture in degrees Kelvin is %d¡ãK.\n", temper.kelvin);						/* Print the result. */
	}

	system("pause");																				/* Pause for the program. */
	return 0;																						/* Return value for the main. */
}
/* Main function End. */

/* Custom functions define Start. */

/* Define a function named name_get. */
Name_Struct name_get(Name_Struct name)
{
	int name_space = 0;												/* Declare the variable to record if there is space in the name. */
	int i = 0, j = 0, k = 0;										/* Declare 3 variables for run times of the for loop. */

	printf("Please input your full name:");							/* Ask user to input the name. */
	gets(name.full);												/* Read string from user. */
	fflush(stdin);													/* Clear buffer. */

	name.err_reason = err_none;										/* Initialize the value of err_reason as err_none. */
	name.result = result_OK;										/* Initizlize the value of result as result_OK. */
	name.length = strlen(name.full);								/* Get the length of name. */

	if (name.length > NAME_LENGTH)									/* If the name is too long. */
	{
		name.result = result_Error;									/* Record error and error_reason. */
		name.err_reason = err_long;
	}
	else															/* If the length of name is correct. */
	{
		for (i = 0; i < name.length; i++)							/* Check each character in the string. */
		{
			if (name.full[i] == 32)									/* There is space in name. */
			{
				if (name_space == 0)
				{
					name_space = 1;									/* Record there is space in the name. */
					j = i;											/* Record the position of space in the string. */
				}
			}
			if (!(isalpha(name.full[i]) || name.full[i] == 32))		/* If there is illegal character(not alpha or space). */
			{
				name.result = result_Error;
				name.err_reason = err_illegal;
				break;
			}
		}
	}

	if (name.result == result_OK)
	{
		if (name_space == 0)										/* If no space in the name. */
		{
			name.result = result_Error;
			name.err_reason = err_nofull;
		}
		else
		{
			name.result = result_Error;								/* Suppose the name is error here. */
			name.err_reason = err_nofull;							/* Suppose the name is not full name. */
			for (i = j - 1; i >= 0; i--)							/* Check if there is character on the left of space. */
				if (isalpha(name.full[i]))
				{
					for (k = j + 1; k < strlen(name.full); k++)		/* Check if there is character on the right of space. */
					{
						if (isalpha(name.full[k]))					/* Both have character on the left and right of the name space. */
						{
							name.result = result_OK;				/* Record no error in the name. */
							name.err_reason = err_none;
							break;
						}
					}
					if (name.result == result_OK) break;			/* Leave the loop once there is no error. */
				}
		}
	}

	return name;													/* Return name to the main function. */
}

/* Define a function named phone_get. */
Phone_Struct phone_get(Phone_Struct phone)
{
	int i = 0, zero_state = 0;										/* Declare i to for run time of for loop. zero_state for record if the denominator is zero. */
	char input_again[2];											/* Declare input_again to record if user needs to re-enter when the denominator is zero. */

	printf("Please input your 11 digit phone number:");				/* Ask user to input the phone number. */
	gets(phone.number);
	fflush(stdin);

	phone.err_reason = err_none;
	phone.result = result_OK;										
	phone.length = strlen(phone.number);							/* Get length of phone number. */

	if (phone.length != PHONE_LENGTH)								/* If the length of phone number is incorrect. */
	{
		phone.result = result_Error;								/* Record error. */
		if (strlen(phone.number) > PHONE_LENGTH) phone.err_reason = err_long;		/* Judge and record error reason. */
		else phone.err_reason = err_short;
	}
	else
	{
		for (i = 0; i < PHONE_LENGTH; i++)							/* Check each character in the string. */
		{
			if (!isdigit(phone.number[i]))							/* If there is illegal character(not digit). */
			{
				phone.result = result_Error;
				phone.err_reason = err_illegal;
				break;
			}
		}
	}

	if (phone.result == result_OK)
	{
		for (i = 6; i < PHONE_LENGTH; i++)							/* Check if the denominator is 0. */
		{
			if (phone.number[i] != 48)								/* The denominator is not 0. */
			{
				zero_state = 0;
				break;
			}
			else zero_state = 1;									/* The denominator is 0 this time. */
		}
		if (zero_state == 1)										/* The denominator is 0. */
		{
			printf("The denominator is 0, would you like to input the phone number again(y/n)?");			/* Ask user whether to try again or not(input y/n). */
			while (1)
			{
				gets(input_again);									/* Get the user choice. */
				fflush(stdin);
				switch (input_again[0])								/* Switch the user input answer. */
				{
				case 'y':											/* Try again. */
				case 'Y':
					phone.result = result_Error;
					phone.err_reason = err_none;
					break;
				case 'n':											/* Do not try again. */
				case 'N':
					break;
				default:
					printf("Please input y or n(y/n):");			/* Input illegal. */
					continue;										/* Restart from the begin of whlie and re-enter the user choice. */
				}
				printf("\n");
				break;
			}
		}
	}

	return phone;													/* Return phone to the main function. */
}

/* Define a function named number_get. */
Number_Struct number_get(Number_Struct number)
{
	int i = 0;														/* Declare i for run times of for loop. */

	printf("Please input a 2 digit decimal number:");				/* Ask user to input the 2-digit decimal number. */
	gets(number.decimal);
	fflush(stdin);

	number.err_reason = err_none;
	number.result = result_OK;
	number.length = strlen(number.decimal);							/* Get the length of number. */

	if (number.length != NUMBER_LENGTH)								/* If the length of number is incorrect. */
	{
		number.result = result_Error;								/* Record error. */
		if (strlen(number.decimal) > NUMBER_LENGTH) number.err_reason = err_long;		/* Judge the error reason. */
		else number.err_reason = err_short;
	}
	else
	{
		for (i = 0; i < NUMBER_LENGTH; i++)							/* Check each character of the string. */
		{
			if (!isdigit(number.decimal[i]))						/* If there is illegal character(not digit). */
			{
				number.result = result_Error;
				number.err_reason = err_illegal;
				break;
			}
		}
	}

	return number;													/* Return number to the main function. */
}

/* Define a function named temper_get. */
Temper_Struct temper_get(Temper_Struct temper)
{
	int temper_del = 0, i = 0;										/* Declare temper_del to record the '.', i for run times of for loop.  */

	printf("Please input a temperature in degrees Celsius:");		/* Ask user to input the temperature in Celsius. */
	gets(temper.celsius);
	fflush(stdin);

	temper.err_reason = err_none;
	temper.result = result_OK;
	temper.length = strlen(temper.celsius);							/* Get the length of temperature. */

	if (temper.length > TEMPER_LENGTH)								/* If the length of temperature is too long. */
	{
		temper.result = result_Error;								/* Record error and error reason. */
		temper.err_reason = err_long;
	}
	else
	{
		for (i = 0; i < temper.length; i++)							/* Check each character in the string. */
		{
			if (temper.celsius[i] == 46) temper_del++;				/* If the character is '.', temper_del++. */
			if (!(isdigit(temper.celsius[i]) || temper.celsius[i] == 46))		/* If there is illegal character(not digit or '.'). */
			{
				temper.result = result_Error;
				temper.err_reason = err_illegal;
				break;
			}
		}
	}

	if (temper.result == result_OK)
		if (temper_del > 1 || temper.celsius[0] == 46)				/* If the number of '.' is more than one or the first digit is '.' */
		{
			temper.result = result_Error;							/* Record error and there is illegal character. */
			temper.err_reason = err_illegal;
		}

	return temper;													/* Return temperature to the main function. */
}

/* Define a function named name_operator. */
Name_Struct name_operator(Name_Struct name)
{
	int i = 0;														/* Declare i for run times of for loop. */
	for (i = 0; i < name.length; i++)
	{
		if (name.full[i] != 32)
			name.sum += name.full[i];								/* Add the character value together. */
	}

	return name;													/* Return name to the main function. */
}

/* Define a function named phone_operator. */
Phone_Struct phone_operator(Phone_Struct phone)
{

	int i = 0;														/* Declare i for run times of for loop. */

	for (i = 0; i < 6; i++)
		phone.numerator[i] = phone.number[i];						/* Assignment the numerator from the phone number. */

	for (i = 0; i < 5; i++)
		phone.denominator[i] = phone.number[i + 6];					/* Assignment the denominator from the phone number. */

	phone.value = (float)(atof(phone.numerator) / atof(phone.denominator));			/* Calculate the value of numerator/denominator. */

	return phone;													/* Return phone to the main function. */
}

/* Define a function named number_operator. */
Number_Struct number_operator(Number_Struct number)
{
	int dec = atoi(number.decimal);									/* Declare dec to store decimal number as integer. */
	char bin[8];													/* Declare bin[8] to store binary number as string. */
	itoa(dec, bin, 2);												/* Output number from integer to string in binary type. */
	number.binary = atoi(bin);										/* Transmit binary number in string to integer. */

	return number;													/* Return number to the main function. */
}

/* Define a function named temper_operator. */
Temper_Struct temper_operator(Temper_Struct temper)
{
	float f_cel = (float)atof(temper.celsius);						/* Declare f_cel to store celsius as float, 
																	use atof to transmit it from string to float. */

	float f_fah = (float)(f_cel * (9 / 5) + 32);					/* Declare f_fah to store fahrenheit as float,
																	and calculate fahrenheit from celsius. */

	float f_kel = (float)(f_cel + 273.15);							/* Declare f_kel to store kelvin as float,
																	and calculate kelvin from celsius. */

	int fah = f_fah + 0.5;											/* Rounded for fahrenheit. */
	int kel = f_kel + 0.5;											/* Rounded for kelvin. */

	temper.fahrenheit = fah;										/* Assignment the value to the temper struct. */
	temper.kelvin = kel;
	
	return temper;													/* Return temper to the main function. */
}

/* Define a function named name_err_print. */
void name_err_print(Name_Struct name)								
{
	switch (name.err_reason)										/* Switch for the error reason. */
	{
	case err_long:													/* If the name is too long. */
		printf("The name is too long.\n\n");						/* Print the error reason. */
		break;
	case err_nofull:												/* If the name is not full name. */
		printf("The name is not full name.\n\n");					/* Print the error reason. */
		break;
	case err_illegal:												/* If the name has illegal character. */
		printf("There are illegal characters in the name.\n\n");	/* Print the error reason. */
		break;
	default:														/* The name is correct. */
		name.err_reason = err_none;
	}
}

/* Define a function named phone_err_print. */
void phone_err_print(Phone_Struct phone)
{
	switch (phone.err_reason)										/* Switch for the error reason. */
	{
	case err_long:													/* If the phone number is too long. */
		printf("The phone number is too long.\n\n");				/* Print the error reason. */
		break;
	case err_short:													/* If the phone number is too short. */
		printf("The phone number is too short.\n\n");				/* Print the error reason. */
		break;
	case err_illegal:												/* If the phone number has illegal character. */
		printf("There are illegal characters in the phone number.\n\n");		/* Print the error reason. */
		break;
	default:														/* The phone number is correct. */
		phone.err_reason = err_none;
	}
}

/* Define a function named number_err_print. */
void number_err_print(Number_Struct number)
{
	switch (number.err_reason)										/* Switch for the error reason. */
	{
	case err_long:													/* If the number is too long. */
		printf("The number is too long.\n\n");						/* Print the error reason. */
		break;
	case err_short:													/* If the number is too short. */
		printf("The number is too short.\n\n");						/* Print the error reason. */
		break;
	case err_illegal:												/* If the number has illegal character. */
		printf("There are illegal characters in the number.\n\n");	/* Print the error reason. */
		break;
	default:														/* The number is correct. */
		number.err_reason = err_none;
	}
}

/* Define a function named temper_err_print. */
void temper_err_print(Temper_Struct temper)
{
	switch (temper.err_reason)										/* Switch for the error reason. */
	{
	case err_long:													/* If the number is too long. */
		printf("The temperature is too long.\n\n");					/* Print the error reason. */
		break;
	case err_illegal:												/* If the number has illegal character. */
		printf("There are illegal characters in the temperature.\n\n");		/* Print the error reason. */
		break;
	default:														/* The number is correct. */
		temper.err_reason = err_none;
	}
}
/* Custom functions define End. */

