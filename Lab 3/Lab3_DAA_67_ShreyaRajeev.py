import csv
from typing import List, Dict, Tuple


class Employee:
    def __init__(self, data: Dict[str, str]):
        self.id = data['ID']
        self.first_name = data['First Name']
        self.last_name = data['Last Name']
        self.basic_salary = float(data.get('Basic Salary', 0))
        self.housing_allowance = float(data.get('Housing Allowance', 0))
        self.transportation_allowance = float(data.get('Transportation Allowance', 0))
        self.medical_allowance = float(data.get('Medical Allowance', 0))
        self.gross_salary = 0
        self.net_salary = 0

    def calculate_salary(self, income_tax_rate: float, social_security_rate: float):
        if any(value < 0 for value in [
            self.basic_salary,
            self.housing_allowance,
            self.transportation_allowance,
            self.medical_allowance
        ]):
            raise ValueError(f"Error: Negative salary component for employee {self.id}.")

        self.gross_salary = (
            self.basic_salary +
            self.housing_allowance +
            self.transportation_allowance +
            self.medical_allowance
        )
        income_tax = round(self.gross_salary * income_tax_rate, 2)
        social_security = round(self.gross_salary * social_security_rate, 2)
        self.net_salary = round(self.gross_salary - (income_tax + social_security), 2)

    def to_dict(self) -> Dict[str, str]:
        return {
            'ID': self.id,
            'First Name': self.first_name,
            'Last Name': self.last_name,
            'Basic Salary': str(self.basic_salary),
            'Housing Allowance': str(self.housing_allowance),
            'Transportation Allowance': str(self.transportation_allowance),
            'Medical Allowance': str(self.medical_allowance),
            'Gross Salary': str(self.gross_salary),
            'Net Salary': str(self.net_salary)
        }


class EmployeeDataManager:
    @staticmethod
    def read_employee_data(filename: str) -> List[Employee]:
        try:
            with open(filename, 'r', newline='') as emp_file:
                reader = csv.DictReader(emp_file)
                return [
                    Employee(row) for row in reader
                    if all(field in row for field in ['ID', 'First Name', 'Last Name'])
                ]
        except FileNotFoundError:
            raise FileNotFoundError(f"Error: The file {filename} was not found.")

    @staticmethod
    def write_employee_data(employees: List[Employee], output_filename: str):
        if not employees:
            raise ValueError("No data to write.")

        fieldnames = employees[0].to_dict().keys()
        with open(output_filename, 'w', newline='') as file:
            writer = csv.DictWriter(file, fieldnames=fieldnames)
            writer.writeheader()
            writer.writerows(emp.to_dict() for emp in employees)


class SalaryCalculator:
    def __init__(self, income_tax_rate: float, social_security_rate: float):
        self.income_tax_rate = income_tax_rate
        self.social_security_rate = social_security_rate

    def calculate_salaries(self, employees: List[Employee]) -> List[Employee]:
        for emp in employees:
            emp.calculate_salary(self.income_tax_rate, self.social_security_rate)
        return employees


class EmployeeAnalyzer:
    @staticmethod
    def linear_min_max(employees: List[Employee]) -> Tuple[Employee, Employee]:
        if not employees:
            raise ValueError("No employee data available.")

        min_emp = max_emp = employees[0]
        for emp in employees[1:]:
            if emp.net_salary < min_emp.net_salary:
                min_emp = emp
            if emp.net_salary > max_emp.net_salary:
                max_emp = emp

        return min_emp, max_emp

    @staticmethod
    def div_conquer(employees: List[Employee]) -> Tuple[Employee, Employee]:
        if len(employees) == 1:
            return employees[0], employees[0]

        if len(employees) == 2:
            return (employees[0], employees[1]) if employees[0].net_salary < employees[1].net_salary else (employees[1], employees[0])

        mid = len(employees) // 2
        left_min, left_max = EmployeeAnalyzer.div_conquer(employees[:mid])
        right_min, right_max = EmployeeAnalyzer.div_conquer(employees[mid:])

        return (
            left_min if left_min.net_salary < right_min.net_salary else right_min,
            left_max if left_max.net_salary > right_max.net_salary else right_max
        )


def print_min_max_results(method: str, min_emp: Employee, max_emp: Employee):
    print(f"By {method}:")
    print(f"Employee with the Minimum Salary is: {min_emp.first_name} {min_emp.last_name} with a salary of {min_emp.net_salary}")
    print(f"Employee with the Maximum Salary is: {max_emp.first_name} {max_emp.last_name} with a salary of {max_emp.net_salary}")


def main():
    try:
        # Configuration
        input_file = 'employees.csv'
        output_file = 'employees_with_salaries.csv'
        income_tax_rate = 0.1
        social_security_rate = 0.05

        # Read employee data
        employees = EmployeeDataManager.read_employee_data(input_file)

        # Calculate salaries
        calculator = SalaryCalculator(income_tax_rate, social_security_rate)
        employees_with_salaries = calculator.calculate_salaries(employees)

        # Write updated employee data
        EmployeeDataManager.write_employee_data(employees_with_salaries, output_file)

        # Analyze employee data
        analyzer = EmployeeAnalyzer()

        # Linear search
        min_emp_linear, max_emp_linear = analyzer.linear_min_max(employees_with_salaries)
        print_min_max_results("linear scan", min_emp_linear, max_emp_linear)

        # Divide and conquer
        min_emp_dc, max_emp_dc = analyzer.div_conquer(employees_with_salaries)
        print_min_max_results("divide and conquer algorithm", min_emp_dc, max_emp_dc)

    except (ValueError, FileNotFoundError, csv.Error, IOError) as e:
        print(f"An error occurred: {e}")
        exit(1)


if __name__ == "__main__":
    main()