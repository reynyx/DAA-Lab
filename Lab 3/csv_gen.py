
import csv
import random
from faker import Faker

# Initialize Faker instance
fake = Faker()

# Define the number of records to generate
num_records = 2000

# Define the field names for the CSV file
fieldnames = [
    'ID', 
    'First Name', 
    'Last Name', 
    'Basic Salary', 
    'Housing Allowance', 
    'Transportation Allowance', 
    'Medical Allowance'
]

# Generate random employee data
data = []
for i in range(1, num_records + 1):
    first_name = fake.first_name()
    last_name = fake.last_name()
    basic_salary = random.randint(30000, 150000)
    housing_allowance = random.randint(5000, 20000)
    transportation_allowance = random.randint(2000, 10000)
    medical_allowance = random.randint(1000, 5000)
    
    # Append the employee data to the list
    data.append({
        'ID': i,
        'First Name': first_name,
        'Last Name': last_name,
        'Basic Salary': basic_salary,
        'Housing Allowance': housing_allowance,
        'Transportation Allowance': transportation_allowance,
        'Medical Allowance': medical_allowance,
    })

# Write the data to a CSV file
with open('employees.csv', mode='w', newline='') as file:
    writer = csv.DictWriter(file, fieldnames=fieldnames)
    writer.writeheader()
    writer.writerows(data)
