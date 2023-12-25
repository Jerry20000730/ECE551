#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
}; 
typedef struct _retire_info retire_info;

double balance(int startAge, double initial, retire_info info) {
  int month = info.months;
  double balance = initial;

  while (month > 0) {
    printf("Age %3d month %2d you have $%.2f\n",
           (startAge + info.months - month) / 12,
           (startAge + info.months - month) % 12,
           balance);
    balance += balance * info.rate_of_return + info.contribution;
    month--;
  }

  return balance;
}

void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  double balance_left = balance(startAge, initial, working);
  balance(startAge + working.months, balance_left, retired);
}

int main(void) {
  retire_info working = {489, 1000, 0.045 / 12};
  retire_info retired = {384, -4000, 0.01 / 12};
  retirement(327, 21345, working, retired);
  return EXIT_SUCCESS;
}
