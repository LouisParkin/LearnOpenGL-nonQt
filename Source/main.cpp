#include "Tutorial.h"

#include <iostream>

#include <unistd.h>
#include <term.h>
#include <curses.h>
#include <functional>

using namespace std;

void ClearScreen()
{
  if (!cur_term) {
    int result;
    setupterm(NULL, STDOUT_FILENO, &result);
    if (result <= 0) {
      return;
    }
  }

  putp(tigetstr("clear"));
}

void printMenu()
{
  ClearScreen();
  cout << "Please Make A Selection" << endl;
  cout << "------------------------------------------------------" << endl;
  cout << "... (4 ) ... Tutorial 4  ..." << endl;
  cout << "... (5 ) ... Tutorial 5  ..." << endl;
  cout << "... (6 ) ... Tutorial 6  ..." << endl;
  cout << "... (7 ) ... Tutorial 7  ..." << endl;
  cout << "... (8 ) ... Tutorial 8  ..." << endl;
  cout << "... (9 ) ... Tutorial 9  ..." << endl;
  cout << "... (a ) ... Tutorial 10 ..." << endl;
  cout << "... (b ) ... Tutorial 11 ..." << endl;
  cout << "... (c ) ... Tutorial 12 ..." << endl;
  cout << "... (d ) ... Tutorial 13 ..." << endl;
  cout << "... (e ) ... Tutorial 14 ..." << endl;
  cout << "------------------------------------------------------" << endl;
}

int main(int argc, char* argv[])
{
  Tutorial* tut;

  printMenu();

  char input[10];
  cin.getline(input,2);

  while (1) {

    switch (input[0]) {
    case '4' :
      tut = &Tutorial::getInstance(4, &argc, argv);
      break;
    case '5' :
      tut = &Tutorial::getInstance(5, &argc, argv);
      break;
    case '6' :
      tut = &Tutorial::getInstance(6, &argc, argv);
      break;
    case '7' :
      tut = &Tutorial::getInstance(7, &argc, argv);
      break;
    case '8' :
      tut = &Tutorial::getInstance(8, &argc, argv);
      break;
    case '9' :
      tut = &Tutorial::getInstance(9, &argc, argv);
      break;
    case 'a' :
      tut = &Tutorial::getInstance(10, &argc, argv);
      break;
    case 'b' :
      tut = &Tutorial::getInstance(11, &argc, argv);
      break;
    case 'c' :
      tut = &Tutorial::getInstance(12, &argc, argv);
      break;
    case 'd' :
      tut = &Tutorial::getInstance(13, &argc, argv);
      break;
    case 'e' :
      tut = &Tutorial::getInstance(14, &argc, argv);
      break;
    case '0' :
      return 0;
    default  :
      cout << "Not a valid choice.  Try again." << endl;
      cin.getline(input,2);

      continue;
    }

    // Exec choice here
    tut->run();
    break;
  }

  return 0;
}



