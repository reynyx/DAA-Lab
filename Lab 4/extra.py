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