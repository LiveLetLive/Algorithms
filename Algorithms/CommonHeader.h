
#define _CRT_SECURE_NO_DEPRECATE // suppress some compilation warning messages (for VC++ users)
#define _CRT_SECURE_NO_WARNINGS
#define  _SCL_SECURE_NO_WARNINGS
 
#include "ConsoleColor.h"

/**************************************ad-hoc Algorithm*************************************************/
//UVA

//#define UVA_103_STACKING_BOXES
//#define UVA_10285_LONGEST_RUN_ON_SNOWBOARD
//#define UVA_11450_WEDDING_SHOPPING
//#define UVA_1056_DEGREE_OF_SEPERATION
//#define UVA_11951_AREA
//#define UVA_1203_ARGUS
//#define UVA_11367_FULLTANK
//#define UVA_11906_KNIGHT_IN_WAR_GRID
//#define UVA_481_WHATGOESUP
//#define UVA_108_MAXIMUM_SUM
//#define UVA_469_WETLANDS_OF_FLORIDA
//#define UVA_11456_TRAINSORTING
//#define UVA_100_3NPLUS1
//#define UVA_11790_MURCIA_SKYLINE
//#define UVA_10213_HOW_MANY_PIECES_OF_LAND
#define UVA_436_ARBITRAGEII
/*******************************************************************************************************/
#include <iostream>
#include <string>
#include <direct.h>

#define CAT(A, B)   A##B
#define FILE_NAME1(A, B) CAT(A, B)
#define FILE_NAME(A, B) FILE_NAME1(A, B)

#define READ_INPUT(A)													\
	int before_main1()													\
{																		\
	std::string path_dir = _getcwd(NULL, 0);							\
	std::string st = FILE_NAME1(#A, ".txt");							\
	std::string input_file = path_dir + "\\..\\input\\" + st;			\
	freopen(input_file.c_str(), "r", stdin);							\
	return 0;															\
}																		\
	int nn = before_main1();											\
	/*******************************************************************************************************/


