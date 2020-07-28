import cs50
import sys
import csv

# check the number of arguments
if len(sys.argv) != 2:
    print('Usage: python import.py data.csv')
    quit()

# open the database
db = cs50.SQL("sqlite:///students.db")

# open the csv file
with open(sys.argv[1], "r") as file:

    # create DictReader
    reader = csv.DictReader(file)

    # iterate through the data
    for row in reader:

        # get the fullname
        fullname = row['name'].split()
        house = row['house']
        birth = row['birth']

        # add data to database
        if len(fullname) == 2:
            db.execute("INSERT INTO students (first, last, house, birth) VALUES(?,?,?,?)",
                       fullname[0], fullname[1], house, birth)

        else:
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?,?,?,?,?)",
                       fullname[0], fullname[1], fullname[2], house, birth)
