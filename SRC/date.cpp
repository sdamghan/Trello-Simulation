#include "../headers/date.h"

bool Date::is_leap_year ( int year ) {
  
  int r= year % 33;
  return r==1 || r==5 || r==9 || r==13 || r==17 || r==22 || r==26 || r==30;
}


int Date::day_of_month ( int m, int y ) {
  
  if ( m<7 )
    return 31;
  else if( m<12 )
    return 30;
  else if ( m==12 )
    return is_leap_year ( y ) ? 30: 29;
  else 
    abort();
}


Date::Date ( int d, int m, int y ) {
  set_date ( d, m, y );
}


void Date::inc_one_day () {
  
  day++;
  if ( day > day_of_month ( month, year ) ) {
    day=1;
    month++;
    if ( month>12 ) {
      month=1;
      year++;
    }
  }
}


bool Date::equals ( Date d ) {
  
  return day == d.day && month == d.month && year == d.year;
}


void Date::set_date ( int d, int m, int y ) {
  
  if ( y<0 || m<0 || m>12 || d<1 || d>day_of_month ( m, y ) )
    abort();
  
  day = d;
  month = m;
  year = y;
}


int Date::days_between ( Date d1, Date d2 ) {
  
  int count=0;
 
  while ( !d1.equals( d2 ) ) {
    d1.inc_one_day();
    count++;
    
  }

  return count;
}


void Date::print_date () {
  
  cout << day << "/" << month << "/" << year << endl;
}


void Date::str_to_date( string s ) {

  int slash_pos = s.find("/");
  int d = atoi ( s.substr( 0, slash_pos ).c_str() );
  s = s.substr( slash_pos+1 );
  slash_pos = s.find("/");
  int m = atoi ( s.substr( 0, slash_pos ).c_str() );
  int y = atoi ( s.substr( slash_pos+1 ).c_str() );
  
   set_date( d, m, y );
} 

string Date::show_date() {
  stringstream ss("");
  ss << day << "/" << month << "/" << year; 
  string x;
  ss >> x;
  return x;
}
  
