"""This is the simple work calculations module.

This module simply supplies what are your basic revenue options. It will
ask your working hours, along with hourly wage to calculate your revenue over
the format of weekly, monthly, and yearly.
"""

# constant variables
WEEKS_TO_MONTHS = 4.345 
MONTHS_TO_YEAR = 12


# variables to work with
workHours = int(input("Enter the amount of working hours you earned:"))
hourlyWage = float(input("Enter how much you make during those hours:"))
workDays = int(input("Enter how many days you work in a week:"))

# simple workweek + monthly + yearly revenue calculations
workingWage = round(float(workHours * hourlyWage))
weekRev = float(workingWage*workDays)
monthlyRev = round(weekRev*WEEKS_TO_MONTHS, 2) # round number to nearest hundreth
yearlyRev = round(monthlyRev*MONTHS_TO_YEAR, 2)

# print simple revenue stats
# Note: To past me, use + instead of , when you want to concatenate two things
#       in a print statement
print()
print(f"Your weekly revenue = ${weekRev}")
print(f"Your monthly revenue = ${monthlyRev}")
print(f"Your yearly revenue = ${yearlyRev}")


