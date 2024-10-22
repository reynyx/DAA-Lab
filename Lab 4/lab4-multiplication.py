import random

def multiply(A, B):
    
    #to check for type errors:
    if not isinstance(A, int) or not isinstance(B, int):
        raise ValueError("Both inputs must be integers.")
    
    # to convert integers to strings to handle each digit
    A_str = str(A)
    B_str = str(B)

    
    n = max(len(A_str), len(B_str))  
    
    # result array
    C = [0] * (2 * n)  

    #for each digit in multiplicant, iteratively perform multiplication and store carry
    for i in range(len(B_str)):
        carry = 0
        b_digit = int(B_str[len(B_str) - 1 - i])  

        for j in range(len(A_str)):
            a_digit = int(A_str[len(A_str) - 1 - j])  

            # Multiply and add to the result
            product = a_digit * b_digit + C[i + j] + carry
            C[i + j] = product % 10  # store the last digit of the product
            carry = product // 10  # update the carry

        C[i + len(A_str)] += carry  # add any remaining carry

    result = ""
    for k in range(2 * n - 1, -1, -1):
        if result or C[k] != 0:  
            result += str(C[k])

    return result if result else "0"  


def karatsuba(X, Y):
     
    if not isinstance(X, int) or not isinstance(Y, int):
        raise ValueError("Both inputs must be integers.")
     
    # base case for recursion: when x or y is a single digit
    if X < 10 or Y < 10:
        return X * Y

    # calculate the no. of digits in the bigger number, 
    n = max(len(str(X)), len(str(Y)))
    m = n // 2  # Split position

    # split the numbers into halves for recursion
    X1 = X // 10**m
    X0 = X % 10**m
    Y1 = Y // 10**m
    Y0 = Y % 10**m

    # 3 recursive calls instead of 4 in regular divide and conquer multiplication
    Z2 = karatsuba(X1, Y1)  
    Z0 = karatsuba(X0, Y0)  
    Z1 = karatsuba(X1 + X0, Y1 + Y0) - Z2 - Z0 

    # Combine the results
    return Z2 * 10**(2 * m) + Z1 * 10**m + Z0

def generate_random_number(num_digits):
    # Ensure the first digit is non-zero to get the desired number of digits
    first_digit = random.randint(1, 9)
    remaining_digits = [random.randint(0, 9) for _ in range(num_digits - 1)]
    number = int(str(first_digit) + ''.join(map(str, remaining_digits)))
    return number


# A = generate_random_number(10)
# B = generate_random_number(10)

# A = generate_random_number(50)
# B = generate_random_number(50)

# A= generate_random_number(100)
# B= generate_random_number(100)

# A = generate_random_number(500)
# B= generate_random_number(500)

A = generate_random_number(1000)
B= generate_random_number(1000)


print("A =")
print(A)
print("B =")
print(B)
try:
    print("Brute Force Multiplication Result:", multiply(A, B))
except ValueError as e:
    print("Error in Brute Force Multiplication:", e)

try:
    print("Karatsuba Multiplication Result:", karatsuba(A, B))
except ValueError as e:
    print("Error in Karatsuba Multiplication:", e)
