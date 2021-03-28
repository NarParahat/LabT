#include "Stack.h"



const int MaxLength = 255;          // максимальный размер входной строки
class TFormula {

private:
	char Formula[MaxLength];      // входная строка
	char PostfixForm[MaxLength]; // постфиксная запись

public:
	TFormula(char form[MaxLength]);
	int FormulaChecker(int Brackets[], int size);// проверка правильности
	int FormulaConverter(void); // перевод в постфиксную форму
	double FormulaCalculator(void); // вычисление результата
};