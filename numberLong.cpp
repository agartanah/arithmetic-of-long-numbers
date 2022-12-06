/********************************************************
 * Атвор: Вяткин Владислав                              *
 * Название: Арифметика                                 *
 *  длинных чисел                                       *
 * Дата: 06.12.2022                                     *
 * Ссылка на OnlineGDB: https://onlinegdb.com/pHjZcqPCz *
 ********************************************************/

#include <iostream>
#include <cmath>
#include <stdio.h>
#include <string>
#include <typeinfo>

using namespace std;

bool signMinus(string number) {
  if (number[0] == '-') {
    return true;
  } else {
    return false;
  }
} // true — число с минусом, false — без

void destroyMinus(string &number) {
  string numberNew = "";
  
  for (int numeralIndex = 1; numeralIndex < number.length(); ++numeralIndex) {
    numberNew = numberNew + number[numeralIndex];
  }
  
  number = numberNew;
} // Модуль числа (убираем минус)

void numbersSwap(string &number1, string &number2) {
  string veriableAuxiliary = number1; // меняем числа местами;
  number1 = number2;
  number2 = veriableAuxiliary;
} // Меняет числа местами

char comparison(string number1, string number2) {
  if (signMinus(number1) == 0 && signMinus(number2) == 0) {
    if (number1.length() == number2.length()) {
      for (int numeralIndex = 0; numeralIndex < number1.length();
      ++numeralIndex) {
        if (number1[numeralIndex] > number2[numeralIndex]) {
          return '>';
        } else if (number1[numeralIndex] < number2[numeralIndex]) {
          return '<';
        }
      }
      return '=';
    } else if (number1.length() > number2.length()) {
      return '>';
    } else if (number1.length() < number2.length()) {
      return '<';
    }
  } else if (signMinus(number1) == 1 && signMinus(number2) == 1) {
    if (number1.length() == number2.length()) {
      for (int numeralIndex = 1; numeralIndex < number1.length();
      ++numeralIndex) {
        if (number1[numeralIndex] > number2[numeralIndex]) {
          return '<';
        } else if (number1[numeralIndex] < number2[numeralIndex]) {
          return '>';
        }
      }
      return '=';
    } else if (number1.length() > number2.length()) {
      return '<';
    } else if (number1.length() < number2.length()) {
      return '>';
    }
  } else {
    if (signMinus(number1) == 0) {
      return '>';
    } else {
      return '<';
    }
  }
} // Сравнение чисел между собой, возвращает знак сравнения (=, >, <)

string subtraction(string number1, string number2, bool flagMinus);

string sum(string number1, string number2, bool flagMinus) {
  enum sign { NEG, POS } numberSign;
  
  /*******************************************************
   *                a и b целые числа                    *
   *******************************************************
   *                abs(a) > abs(b)                      *
   * (1) -a + (-b) = -(a + b) ->       NEG, sum;         *
   * (2) -a +   b  = -(a - b) ->       NEG, subtraction; *
   * (3)  a + (-b) =   a - b  ->       POS, subtraction; *
   * (4)  a +   b  =   a + b  ->       POS, sum;         *
   ******************************************************* 
   *                abs(a) < abs(b)                      *
   * (1) -a + (-b) = -(a + b) -> swap, NEG, sum;         *
   * (2) -a +   b  =   a - b  -> swap, POS, subtraction; *
   * (3)  a + (-b) = -(a - b) -> swap, NEG, subtraction; *
   * (4)  a +   b  =   a + b  -> swap, POS, sum;         *
   *******************************************************/
  
  if (signMinus(number1) == 1 && signMinus(number2) == 1) {
    destroyMinus(number1);
    destroyMinus(number2);
    
    if (comparison(number1, number2) == '<') {
      numbersSwap(number1, number2);
    }
    
    return sum(number1, number2, true);
  } else if (signMinus(number1) == 1) {
    destroyMinus(number1);
    
    if (comparison(number1, number2) == '>') {
      return subtraction(number1, number2, true);
    } else if (comparison(number1, number2) == '<' || comparison(number1, number2) == '=') {
      numbersSwap(number1, number2);
      return subtraction(number1, number2, false);
    }
  } else if (signMinus(number2) == 1) {
    destroyMinus(number2);
    
    if (comparison(number1, number2) == '>') {
      return subtraction(number1, number2, false);
    } else if (comparison(number1, number2) == '<') {
      numbersSwap(number1, number2);
      return subtraction(number1, number2, true);
    }
  } else {
    if (flagMinus == true) {
      numberSign = NEG;
    } else {
      numberSign = POS;
    }
    
    if (comparison(number1, number2) == '<') {
      numbersSwap(number1, number2);
      
      numberSign = POS;
    }
    
    int number1Length = number1.length(), number2Length = number2.length();
    
    string numberAdd = "", numberResponse = "";
    int numeralIntegerDiv = 0;
    
    for (int numeralIndex = number2Length - 1; numeralIndex >= 0; --numeralIndex) {
      int number1Index = numeralIndex + (number1Length - number2Length),
      numeralsSum = (number2[numeralIndex] - '0') + (number1[number1Index] - '0') + numeralIntegerDiv,
      numeralRemainderDiv = (numeralsSum % 10);
      
      numberAdd = to_string(numeralRemainderDiv) + numberAdd;
      numeralIntegerDiv = numeralsSum / 10;
      --number1Index;
    }
    
    int index = (number1Length - number2Length) - 1;
    
    if (index >= 0) {
      while (numeralIntegerDiv != 0 && index >= 0) {
        int numeralsSum = (number1[index] - '0') + numeralIntegerDiv;
          
        int numeralRemainderDiv = (numeralsSum % 10);
          
        numberAdd = to_string(numeralRemainderDiv) + numberAdd;
        numeralIntegerDiv = numeralsSum / 10;
          
        --index;
      }
    } 
    
    if (numeralIntegerDiv != 0) {
        numberAdd = to_string(numeralIntegerDiv) + numberAdd;
    }
    
    for (int numeralIndex = 0; numeralIndex <= index; ++numeralIndex) {
      numberResponse = numberResponse + number1[numeralIndex];
    }
    
    numberResponse = numberResponse + numberAdd;
    
    if (numberSign == NEG) {
      return '-' + numberResponse;
    } else {
      return numberResponse;
    }
  }
} // Сумма

string subtraction(string number1, string number2, bool flagMinus) {
  enum sign { NEG, POS } numberSign = POS;
  
  /*******************************************************
   *                a и b целые числа                    *
   *******************************************************
   *                abs(a) > abs(b)                      *
   * (1) -a - (-b) = -(a - b) ->       NEG, subtraction; *
   * (2) -a -   b  = -(a + b) ->       NEG, sum;         *
   * (3)  a - (-b) =   a + b  ->       POS, sum;         *
   * (4)  a -   b  =   a - b  ->       POS, subtraction; *
   ******************************************************* 
   *                abs(a) < abs(b)                      *
   * (1) -a - (-b) =   a - b  -> swap, POS, subtraction; *
   * (2) -a -   b  = -(a + b) -> swap, NEG, sum;         *
   * (3)  a - (-b) =   a + b  -> swap, POS, sum;         *
   * (4)  a -   b  = -(a - b) -> swap, NEG, subtraction; *
   *******************************************************/
  
  string numberAdd = "", numberResponse = "";
  
  if (comparison(number1, number2) == '=') {
    return "0";
  } else if (signMinus(number1) == 1 && signMinus(number2) == 1) { // (1)
    destroyMinus(number1);
    destroyMinus(number2);
    
    if (comparison(number1, number2) == '>') {
      return subtraction(number1, number2, true);
    } else {
      numbersSwap(number1, number2);
      
      return subtraction(number1, number2, false);
    }
  } else if (signMinus(number1) == 1) { // (2)
    destroyMinus(number1);
    
    if (comparison(number1, number2) == '<') {
      numbersSwap(number1, number2);
    }
    
    return sum(number1, number2, true);
  } else if (signMinus(number2) == 1) { // (3)
    destroyMinus(number2);
    
    if (comparison(number1, number2) == '<') {
      numbersSwap(number1, number2);
    }
    
    return sum(number1, number2, false);
  } else { // (4)
    if (flagMinus == true) {
      numberSign = NEG;
    } else {
      numberSign = POS;
    }
    
    if (comparison(number1, number2) == '<') {
      numbersSwap(number1, number2);
      numberSign = NEG;
    }
    
    int number1Length = number1.length(), number2Length = number2.length();
    
    for (int numeralIndex = number2Length - 1; numeralIndex >= 0; --numeralIndex) {
      int number1Index = numeralIndex + (number1Length - number2Length),
      numeralsSub = (number1[number1Index] - '0') - (number2[numeralIndex] - '0');
      
      if (numeralsSub < 0) {
        numeralsSub = 10 + numeralsSub;
        numberAdd = to_string(numeralsSub) + numberAdd;
        
        if (number1[number1Index - 1] == '0') {
          int number1IndexZero = number1Index - 1;
          
          while (number1[number1IndexZero] == '0') {
            number1[number1IndexZero] = '9';
            
            --number1IndexZero;
          }
          
          number1[number1IndexZero] = char(number1[number1IndexZero] - 1);
        } else {
          number1[number1Index - 1] = char(number1[number1Index - 1] - 1);
        }
      } else {
        numberAdd = to_string(numeralsSub) + numberAdd;
      }
      
      --number1Index;
    }
    
    for (int numeralIndex = 0; 
    numeralIndex < (number1Length - number2Length); ++numeralIndex) {
      numberResponse = numberResponse + number1[numeralIndex];
    }
    
    numberResponse = numberResponse + numberAdd;
    
    string numberResponseNew = "";
    
    if (numberResponse[0] == '0') {
      int numeralIndex = 0;
      
      while (numberResponse[numeralIndex] == '0') {
        ++numeralIndex;
      }
      
      while (numeralIndex < numberResponse.length()) {
        numberResponseNew = numberResponseNew + numberResponse[numeralIndex];
        
        ++numeralIndex;
      }
      
      numberResponse = numberResponseNew;
    }
    
    if (numberSign == NEG) {
      return '-' + numberResponse;
    } else {
      return numberResponse;
    }
  }
  
  return "Ошибка! Введите числа в нужной форме.";
} // Вычитание

string multiplication(string number1, string number2) {
  enum sign { NEG, POS } numberSign = POS;
  
  if (number1 == "0" || number2 == "0") {
    return "0";
  }
  
  if (signMinus(number1) == 1 && signMinus(number2) == 0) {
    destroyMinus(number1);
    numberSign = NEG;
  } else if (signMinus(number1) == 0 && signMinus(number2) == 1) {
    destroyMinus(number2);
    numberSign = NEG;
  } else if (signMinus(number1) == 1 && signMinus(number2) == 1) {
    destroyMinus(number1);
    destroyMinus(number2);
  }
  
  //cout << numberSign << endl;
  
  if (comparison(number1, number2) == '<') {
    numbersSwap(number1, number2);
  }
  
  int number1Length = number1.length(), number2Length = number2.length();
  
  string sumOfMultiplacation[number2Length], numeralMultiplication, resultMultiplication = "";
  int sumOfMultiplacationIndex = 0;
  
  for (int numeralIndex = number2Length - 1; numeralIndex >= 0; --numeralIndex) {
    string sumAdditional = "0", numeral2 = "";
    numeral2 = number2[numeralIndex];
    resultMultiplication = "";
    
    for (int number1Index = number1Length - 1; number1Index >= 0; --number1Index) {
      string numeralMultiplication = "0", numeral1 = "";
      numeral1 = number1[number1Index];
      int numeral1Int = stoi(numeral1);
      
      for (int sumCount = 0; sumCount < numeral1Int; ++sumCount) {
        numeralMultiplication = sum(numeralMultiplication, numeral2, false);
      }
      
      numeralMultiplication = sum(numeralMultiplication, sumAdditional, false);
      
      if (comparison(numeralMultiplication, "9") == '>') {
        resultMultiplication = numeralMultiplication[numeralMultiplication.length() - 1]
        + resultMultiplication;
        sumAdditional = numeralMultiplication[numeralMultiplication.length() - 2];
      } else {
        resultMultiplication = numeralMultiplication + resultMultiplication;
        sumAdditional = "0";
      }
    }
    
    if (comparison(sumAdditional, "0") == '>') {
      resultMultiplication = sumAdditional + resultMultiplication;
    }
    
    for (int index = 0; index < sumOfMultiplacationIndex; ++index) {
      resultMultiplication = resultMultiplication + '0';
    }
    
    sumOfMultiplacation[sumOfMultiplacationIndex] = resultMultiplication;
    ++sumOfMultiplacationIndex;
  }
  
  resultMultiplication = sumOfMultiplacation[0];
  
  for (int index = 0; index <= sumOfMultiplacationIndex - 2; ++index) {
    resultMultiplication = sum(resultMultiplication,
                               sumOfMultiplacation[index + 1], false);
  }
  
  if (numberSign == NEG) {
    return '-' + resultMultiplication;
  } else {
    return resultMultiplication;
  }
} //  Умножение

string division(string number1, string number2) { // Деление
  enum sign { NEG, POS } numberSign = POS;
  
  if (signMinus(number1) == 1 && signMinus(number2) == 0) {
    destroyMinus(number1);
    numberSign = NEG;
  } else if (signMinus(number1) == 0 && signMinus(number2) == 1) {
    destroyMinus(number2);
    numberSign = NEG;
  } else if (signMinus(number1) == 1 && signMinus(number2) == 1) {
    destroyMinus(number1);
    destroyMinus(number2);
  }
  
  if (comparison(number1, number2) == '<') {
    return "0";
  } else if (comparison(number1, number2) == '=') {
    if (numberSign == NEG) {  
      return "-1";
    } else {
      return "1";
    }
  }
  
  string number1Copy = number1, numberResponse = "0";
  
  while (comparison(number1Copy, "0") == '>' || comparison(number1Copy, "0") == '=') {
    number1Copy = subtraction(number1Copy, number2, false);
    numberResponse = sum(numberResponse, "1", false);
  }
  
  if (comparison(number1Copy, "0") == '<') {
    numberResponse = subtraction(numberResponse, "1", false);
  }
  
  if (numberSign = NEG) {
    return '-' + numberResponse;
  } else {
    return numberResponse;
  }
  
}

int main() {
  string number1, number2;
  
  cout << "Введите два числа: " << endl;
  cin >> number1 >> number2;
  cout << "Сравнение чисел: \n"
   << number1 << " "   << comparison(number1, number2) << " " << number2 << endl
       << "Сложение чисел: \n"
   << number1 << " + " << number2 << " = " << sum(number1, number2, false)         << endl
       << "Вычитание чисел: \n"
   << number1 << " - " << number2 << " = " << subtraction(number1, number2, false) << endl
       << "Произведение чисел: \n"
   << number1 << " * " << number2 << " = " << multiplication(number1, number2)     << endl 
       << "Деление чисел: \n"
   << number1 << " / " << number2 << " = " << division(number1, number2)           << endl;
}



