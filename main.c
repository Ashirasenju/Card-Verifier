#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_help(void) {
  printf("CardCheck - Credit Card Validator\n");
  printf("\n");
  printf("USAGE:\n");
  printf("  cardcheck [OPTIONS] <card_number>\n");
  printf("\n");
  printf("OPTIONS:\n");
  printf("  -h, --help      Show this help message\n");
  printf("\n");
  printf("DESCRIPTION:\n");
  printf("  CardCheck validates credit card numbers using:\n");
  printf("    - Luhn algorithm\n");
  printf("    - IIN (Issuer Identification Number) ranges\n");
  printf("\n");
  printf("SUPPORTED ISSUERS:\n");
  printf("  - Visa\n");
  printf("  - Mastercard\n");
  printf("  - American Express\n");
  printf("\n");
  printf("EXAMPLE:\n");
  printf("  cardcheck 4532015112830366\n");
}

int is_a_number(char c) { return (c >= '0' && c <= '9'); }

int sum_values(int value[], int sum_values) {
  int sum = 0;
  for (int i = 0; i < sum_values; i++) {
    sum = sum + value[i];
  }
  return sum;
}

int luhn_algorithm(char *number, int number_len) {
  int key = number[number_len - 1] - '0';
  int *values = calloc(number_len, sizeof(int));
  for (int i = number_len - 2; i >= 0; i--) {
    char current_char = number[i];
    if (is_a_number(current_char)) {
      if (is_a_number(current_char)) {
        if (i % 2 == 0) {
          int pre_value = (current_char - '0') * 2;

          if (pre_value > 9) {
            pre_value -= 9;
          }
          values[i] = pre_value;
        } else {
          values[i] = current_char - '0';
        }
      } else {
        return EXIT_FAILURE;
      }
    }
  }

  int sum = sum_values(values, number_len) + key;
  printf("Sum : %i\n", sum);
  if (sum % 10 == 0) {
    free(values);
    return EXIT_SUCCESS;

  } else {
    free(values);
    return EXIT_FAILURE;
  }
}

int check_mastercard(char *credit_card_number, int len_credit_card_number) {
  if (len_credit_card_number != 16) {
    return 0;
  }
  int in_first_two_numbers =
      (credit_card_number[0] - '0') * 10 + (credit_card_number[1] - '0');
  int in_first_four_numbers = (credit_card_number[0] - '0') * 1000 +
                              (credit_card_number[1] - '0') * 100 +
                              (credit_card_number[2] - '0') * 10 +
                              credit_card_number[3] - '0';
  if ((in_first_two_numbers >= 51 && in_first_two_numbers <= 55) ||
      (in_first_four_numbers >= 2221 && in_first_four_numbers <= 2720)) {
    puts("🏦Card Issuer : Mastercard");

    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}
int check_amex(char *credit_card_number, int len_credit_card_number) {
  if (len_credit_card_number != 15) {
    return EXIT_FAILURE;
  }
  int in_first_two_numbers =
      (credit_card_number[0] - '0') * 10 + (credit_card_number[1] - '0');
  if (in_first_two_numbers >= 34 && in_first_two_numbers <= 37) {
    puts("🏦Card Issuer :  American Express");
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}
int check_visa(char *credit_card_number, int len_credit_card_number) {
  if ((len_credit_card_number == 13 || len_credit_card_number == 16 ||
       len_credit_card_number == 19) &&
      credit_card_number[0] == '4') {
    puts("🏦Card Issuer :  Visa");
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}
int check_valid_iin(char *credit_card_number, int len_credit_card_number) {
  if (check_visa(credit_card_number, len_credit_card_number) ||
      check_amex(credit_card_number, len_credit_card_number) ||
      check_mastercard(credit_card_number, len_credit_card_number)) {

    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}

int main(int argc, char *argv[]) {
  if (argc <= 1) {
    printf("❌No options given.\n");
    return EXIT_FAILURE;
  }
  if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {

    print_help();
    return EXIT_SUCCESS;
  }
  for (int i = 1; i < argc; i++) {
    char *credit_card_number = argv[i];
    printf("Credit Card numbers : %s\n", credit_card_number);
    int len_credit_card_number = strlen(credit_card_number);
    if (len_credit_card_number < 12 || len_credit_card_number > 20) {
      printf("❌Wrong format.\n\n");
      return EXIT_FAILURE;
    }

    int status = luhn_algorithm(credit_card_number, len_credit_card_number);
    if (status == EXIT_SUCCESS) {
      printf("✅ Passed the Luhn algorithm.\n");

      int iin_status =
          check_valid_iin(credit_card_number, len_credit_card_number);
      if (iin_status == EXIT_SUCCESS) {
        printf("✅Correct Credit card format.\n");
      } else {
        printf("❌Card network not recognized");
      }
    } else {
      printf("❌Number is not valid\n\n");
    }
  }
  return EXIT_SUCCESS;
}
