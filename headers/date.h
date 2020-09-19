#ifndef DaTe_H__
#define DaTe_H__

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>
using namespace std;


class Date {
  
public :
  Date ( int d, int m, int y );
  Date (){}
  void set_date ( int d, int m, int y );
  bool equals( Date d );
  void print_date ();
  void inc_one_day ();
  void str_to_date( string s );
  int get_day() { return day; }
  int get_month() { return month; }
  int get_year() { return year; }
  int day_of_month ( int m, int y );
  bool is_leap_year ( int year );
  int days_between ( Date d1, Date d2 );
  string show_date();
  
private :
  int day;
  int month;
  int year;
  
};

#endif