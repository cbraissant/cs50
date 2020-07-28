from cs50 import get_string, get_int


#    AMERICAN EXPRESS:
#        starts with:    34 or 37
#        length:         15 digits
#
#    MASTER CARD:
#        starts with:    51 to 55
#        length:         16 digits
#
#    VISA:
#        starts with:    4
#        length:         13 or 16 digits
#
#    CHECKSUM:
#        multiply every other digit starting from the second-to-last
#        add the products' digits together (ex: 2*6 = 12 -> 1+2 = 3)
#        add those numbers
#        add to remaining numbers
#        if last digit is 0, the number is valid

n = get_string('Number: ')

size = len(n)
sum_number = 0

# start from the second last digit
for i in range(size - 2, -1, -2):

    # multiply by 2 every other digit
    product = int(n[i]) * 2

    # add the products' digits together
    if product >= 10:
        sum_number += product % 10 + 1
    else:
        sum_number += product

#  add the remaining numbers
for i in range(size - 1, -1, -2):
    sum_number += int(n[i])

# check if the number is valid
if sum_number % 10 == 0:

    # AMEX
    if (n[0] == '3' and (n[1] == '4' or n[1] == '7') and size == 15):
        print('AMEX')

    # MASTER CARD
    if (n[0] == '5' and (int(n[1]) in range(1, 6)) and size == 16):
        print('MASTERCARD')

    # VISA
    if (n[0] == '4' and size in [13, 16]):
        print('VISA')

else:
    print('INVALID')
