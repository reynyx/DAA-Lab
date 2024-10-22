import random

def count_inversions(arr):
    """
    Counts the number of inversions in the array using a modified merge sort.
    Returns a tuple of (sorted_array, inversion_count).
    """
    if len(arr) <= 1:
        return arr, 0

    mid = len(arr) // 2
    left_half, left_inversions = count_inversions(arr[:mid])
    right_half, right_inversions = count_inversions(arr[mid:])

    merged, cross_inversions = merge_and_count(left_half, right_half)

    total_inversions = left_inversions + right_inversions + cross_inversions
    return merged, total_inversions

def merge_and_count(left, right):
    """
    Merges two sorted lists and counts cross-inversions.
    Returns a tuple of (merged_list, cross_inversions).
    """
    i, j = 0, 0
    cross_inversions = 0
    merged_list = []

    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            merged_list.append(left[i])
            i += 1
        else:
            merged_list.append(right[j])
            cross_inversions += len(left) - i  # Count inversions
            j += 1

    # Append remaining elements
    merged_list.extend(left[i:])
    merged_list.extend(right[j:])
    
    return merged_list, cross_inversions

def analyze_student_choices(student_choices):
    """
    Analyzes the inversion counts of students' course choices.
    Returns a list with the number of students having 0, 1, 2, 3, or more than 3 inversions.
    """

    if not student_choices:  # Check if the input list is empty
        raise ValueError("Student choices cannot be empty.")
    
    available_courses = 10  # Define the maximum number of available courses
    courses_per_student=5

    # Check for each student's choices
    seen_choices = set()  # To track seen choices
    for choices in student_choices:
        if len(choices) == 0:
            raise ValueError("Individual student choices cannot be empty.")
        
        if len(choices) > courses_per_student:  # Check for more courses than available
            raise ValueError("Cannot select more courses than allowed.")

        # Check for duplicates in the student's choice
        if len(choices) != len(set(choices)):  # Check for duplicates
            raise ValueError("Duplicate courses found in student choices.")
        
        # Add choices to seen set to detect identical choices
        choices_tuple = tuple(sorted(choices))  # Use a sorted tuple for consistent comparison
        if choices_tuple in seen_choices:
            raise ValueError("Identical course choices found for multiple students.")
        seen_choices.add(choices_tuple)

        _, inversions = count_inversions(choices)

def generate_random_course_choices(num_students=100, num_courses=10, courses_per_student=5):
    """
    Generates random course-code choices for a given number of students.
    Each student randomly selects a subset of courses from 1001 to 1001 + num_courses - 1.
    """
    if num_courses < courses_per_student:
        raise ValueError("Number of courses must be greater than or equal to courses per student.")

    student_choices = []
    course_codes = list(range(1001, 1001 + num_courses))  # Course codes from 1001 to 1001 + num_courses - 1

    for _ in range(num_students):
        # Randomly select courses from the list of available course codes
        chosen_courses = random.sample(course_codes, courses_per_student)
        student_choices.append(chosen_courses)

    return student_choices
    

if __name__ == "__main__":
   
    try:
        result = analyze_student_choices(student_choices)
        print(result)  # Only prints if no errors occur
    except ValueError as e:
        print("Error:", e)
