from cs50 import get_int


while True:
    n = get_int('Height: ')

    # Wait for corret input
    if n in range(1, 9):
        # Print the pyramid
        for x in range(1, n + 1):
            print((' ' * (n - x)) + ('#' * x) + '  ' + ('#' * x))
        quit()
