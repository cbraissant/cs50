import cs50
import sys
import csv

# check the number of arguments
if len(sys.argv) != 2:
    print('Usage: python roster.py housename')
    quit()

# open the database
db = cs50.SQL("sqlite:///students.db")

# get the house from the argument
house = sys.argv[1]

people = db.execute(
    "SELECT * FROM students WHERE house = ? ORDER BY last, first", house)

for person in people:
    fullname = person['first']
    if person['middle'] != None:
        fullname = fullname + ' ' + person['middle']
    fullname = fullname + ' ' + person['last']
    birth = person['birth']

    print(f"{fullname}, born {birth}")
