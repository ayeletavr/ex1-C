/**
 * @file manageStudents.c
 * @author  Ayelet avraham username ayeletavr <ayelet.avraham@mail.huji.ac.il>
 * @date 10 April 2020
 *
 * @brief this program manage students at university.
 */

// ------------------------------ includes ------------------------------
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

// -------------------------- const definitions -------------------------const int MAX_ARR_LENGTH = 5500;
const int MAX_ARR_LENGTH = 5500;
const int ASCII_SPACE = 32;
const int ASCII_HYPHEN = 45;
const unsigned int MIN_GRADE = 0;
const unsigned int MAX_GRADE = 100;
const unsigned int MIN_AGE = 18;
const unsigned int MAX_AGE = 120;
int ID_FLAG = 0;
char NAME_FLAG[42] = "name_flag";
unsigned int GRADE_FLAG = 1000;
unsigned int AGE_FLAG = 1000;
char COUNTRY_FLAG[42] = "country_flag";
char CITY_FLAG[42] = "city_flag";
struct Student STUDENT_FLAG;

// -------------------------- function declarations -------------------------int isValid(unsigned int id, char name[], unsigned int grade, unsigned int age, char country[], char city[]);
int isValid();
struct Student createStudent();
struct Student findBestStudent();
int noMissingArgs();
int parseIntoStudentArray();
void assignStudent();
void printStudentArray();
void mergeArrays();
void mergeSort();
void swapStudents();
int partition();
void quickSort();


/**
 * This struct represents a student, and contains all fields of student.
 */
struct Student
{
    long id;
    char name[42];
    unsigned int grade;
    unsigned int age;
    char country[42];
    char city[42];
};

/**
 * checks validity of student input.
 * @param id student's ID.
 * @param name student's name.
 * @param grade student's grade.
 * @param age student's age.
 * @param country student's country.
 * @param city student's city.
 * @return 1 (true) if input is valid, 0 (false) otherwise.
 */

int isValid(long id, char name[], unsigned int grade, unsigned int age, char country[], char city[])
{
    //checks validity of ID:
    if ((floor(log10(labs(id)) + 1) != 10) || (id - 1000000000 < 0))
    {
        printf("ERROR: ID can contain exactly 10 characters and first number is not 0\n");
        return 0;
    }
    //check validity of name:
    for (unsigned long i = 0; i < strlen(name); i++)
    {
        int asciiVal = name[i];
        if ((!isalpha(name[i])) && (asciiVal != ASCII_HYPHEN) && (asciiVal != ASCII_SPACE))
        {
            printf("ERROR: name can only contain alphabetic characters, whitespaces or '-'\n");
            return 0;
        }
    }
    // check validity of grade:
    if ((grade < MIN_GRADE) || (grade > MAX_GRADE))
    {
        printf("ERROR: grade is an integer between 0 to 100\n");
        return 0;
    }
    // check age:
    if ((age < MIN_AGE) || (age > MAX_AGE))
    {
        printf("ERROR: age is an integer between 18 to 120\n");
        return 0;
    }
    // check country:
    for (unsigned long i = 0; i < strlen(country); i++)
    {
        int asciiVal = country[i];
        if ((!isalpha(country[i])) && (asciiVal != ASCII_HYPHEN))
        {
            printf("ERROR: country can only contain alphabetic characters or '-'\n");
            return 0;
        }
    }
    // check city:
    for (unsigned long i = 0; i < strlen(city)-1; i++)
    {
        int asciiVal = city[i];
        if ((!isalpha(city[i])) && (asciiVal != ASCII_HYPHEN))
        {
            printf("ERROR: city can only contain alphabetic characters or '-'\n");
            return 0;
        }
    }
    return 1;
}

/**
 * creates a student object. assumes all fields are valid.
 * @param id student's ID.
 * @param name student's name.
 * @param grade student's grade.
 * @param age student's age.
 * @param country student's country.
 * @param city student's city.
 * @return a student object.
 */
struct Student createStudent(long id, char name[], unsigned int grade, unsigned int age, char country[],
        char city[])
{
    struct Student newStudent;
    newStudent.id = id;
    strcpy(newStudent.name, name);
    newStudent.grade = grade;
    newStudent.age = age;
    strcpy(newStudent.country, country);
    strcpy(newStudent.city, city);
    return newStudent;
}

/**
 * Gets an array of students, and returns the student that has the highest quality factor of (grade/age).
 * Assumes that it's not an empty array (size >= 1).
 * @param studentsArr an array on students.
 * @param size size of the array.
 * @return the student with the highest rate of (grade/age).
 */
struct Student findBestStudent(struct Student studentsArr[], int size)
{
    struct Student bestStudent;
    if (size == 1)
    {
        bestStudent = studentsArr[0];
    } else
    {
        double maxVal = (double)studentsArr[0].grade / (double) studentsArr[0].age;
        bestStudent = studentsArr[0];
        for (int i = 1; i < size; i++)
        {
            double iQualityFactor = (double) studentsArr[i].grade / (double) studentsArr[i].age;
            if (iQualityFactor > maxVal)
            {
                maxVal = iQualityFactor;
                bestStudent = studentsArr[i];
            }

        }
    }
    return bestStudent;
}

/**
 * checks if there are no missing args (less than 6) in student's input.
 * @param id
 * @param name
 * @param grade
 * @param age
 * @param country
 * @param city
 * @return 0 if there are missing args, 1 otherwise.
 */
int noMissingArgs(long id, char name[], unsigned int grade, unsigned int age, char country[], char city[])
{
    if (id == ID_FLAG || strcmp(name, NAME_FLAG) == 0 || grade == GRADE_FLAG || age == AGE_FLAG
        || strcmp(country, COUNTRY_FLAG) == 0 || strcmp(city, CITY_FLAG) == 0)
    {
        printf("ERROR: Missing one or more arguments.\n");
        return 0;
    }
    return 1;
}

/**
 * assigning a student object into an array of students.
 * assumes there is no Index out of bounds error.
 * @param student
 * @param studentArr
 */
void assignStudent(struct Student student, struct Student studentArr[], int index)
{
    studentArr[index].id = student.id;
    strcpy(studentArr[index].name, student.name);
    studentArr[index].grade = student.grade;
    studentArr[index].age = student.age;
    strcpy(studentArr[index].country, student.country);
    strcpy(studentArr[index].city, student.city);
}

/**
 * parses user's input into a student array.
 * @param studentsArr a default (empty-flagged) array of students.
 * @param size size of array (equal to the amount of user's inputs).
 * @return studens array last index, or -1 if EOF error.
 */
int parseIntoStudentArray(struct Student studentsArr[], int size)
{
    char buffer[80];
    // setting initial values to student fields.
    long id = ID_FLAG;
    char name[42];
    strcpy(name, NAME_FLAG);
    unsigned int grade = GRADE_FLAG;
    unsigned int age = AGE_FLAG;
    char country[42];
    strcpy(country, COUNTRY_FLAG);
    char city[42];
    strcpy(city, CITY_FLAG);
    int lineCounter = 0;
    // end of initializing student fields.
    printf("Enter student info. To exit press q, then enter\n");
    if (fgets(buffer, 80, stdin) == NULL)
    {
        printf("ERROR: EOF\n");
        printf("in line %d\n", lineCounter);
        return -1;
    }
    while (strncmp(buffer, "q", 1) != 0)
    {
        sscanf(buffer, "%ld,%42[^,],%u,%u,%42[^,],%s", &id, name, &grade, &age, country, city);
        if (noMissingArgs(id, name, grade, age, country, city) > 0 && isValid(id, name, grade, age, country, city) > 0)
        {
            struct Student student = createStudent(id, name, grade, age, country, city);
            assignStudent(student, studentsArr, size);
            size++;
            lineCounter++;
            printf("Enter student info. To exit press q, then enter\n");
            if (fgets(buffer, 80, stdin) == NULL)
            {
                printf("ERROR: EOF\n");
                printf("in line %d\n", lineCounter);
                return -1;
            }
        }
        else
        {
            printf("in line %d\n", lineCounter);
            lineCounter++;
            printf("Enter student info. To exit press q, then enter\n");
            if (fgets(buffer, 80, stdin) == NULL)
            {
                printf("ERROR: EOF\n");
                printf("in line %d\n", lineCounter);
                return -1;
            }
        }
    }
    return size;
}

/**
 * prints a student array.
 * @param array student array.
 * @param size array's size.
 */
void printStudentArray(struct Student array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%ld,%s,%u,%u,%s,%s\n", array[i].id, array[i].name, array[i].grade,
               array[i].age, array[i].country, array[i].city);
    }
}

// ------------------------------ merge sort algorithm ------------------------------

/**
 * merge algorithm. Merges two arrays into one sorted array.
 * @param array array to sort.
 * @param leftIndex most left index of array.
 * @param midIndex middle index of array (floor rounded).
 * @param rightIndex most right index of array.
 */
void mergeArrays(struct Student array[], int leftIndex, int midIndex, int rightIndex)
{
    int i, j, k;
    int firstHalfSize = midIndex - leftIndex + 1;
    int secondHalfSize = rightIndex - midIndex;
    struct Student firstHalf[2750];
    struct Student secondHalf[2750];
    for (i = 0; i < firstHalfSize; i++)
    {
        assignStudent(array[i + leftIndex], firstHalf, i);
    }
    for (j = 0; j < secondHalfSize; j++)
    {
        assignStudent(array[midIndex + 1 + j], secondHalf, j);
    }
    i = 0;
    j = 0;
    k = leftIndex;
    while (i < firstHalfSize && j < secondHalfSize)
    {
        if (firstHalf[i].grade <= secondHalf[j].grade)
        {
            assignStudent(firstHalf[i++], array, k++);
        }
        else
        {
            assignStudent(secondHalf[j++], array, k++);
        }
    }
    while (i < firstHalfSize)
    {
        assignStudent(firstHalf[i++], array, k++);
    }
    while (j < secondHalfSize)
    {
        assignStudent(secondHalf[j++], array, k++);
    }
}

/**
 * merge sort algorithm to sort an array of students.
 * @param unsortedArray array to sort.
 * @param size size of array.
 */
void mergeSort(struct Student unsortedArray[], int leftIndex, int rightIndex)
{
    if (leftIndex < rightIndex)
    {
        int midIndex = leftIndex + (rightIndex - leftIndex) / 2;
        mergeSort(unsortedArray, leftIndex, midIndex);
        mergeSort(unsortedArray, midIndex + 1, rightIndex);
        mergeArrays(unsortedArray, leftIndex, midIndex, rightIndex);
    }
}


// ------------------------------ quick sort algorithm ------------------------------
/**
 * swaps two students.
 * @param firstStudent to swap with secondStudent.
 * @param secondStudent to swap with firstStudent.
 */
void swapStudents(struct Student* firstStudent, struct Student* secondStudent)
{
    struct Student temp = *firstStudent;
    *firstStudent = *secondStudent;
    *secondStudent = temp;
}

/**
 * helper to quickSort. partition picks a pivot element (in this case we pick the last one),
 * and reorder the array so that all the smaller elements than pivot will be in left of it,
 * and all the larger ones will be right of it.
 * @param studentArray
 * @param start
 * @param end
 * @return
 */
int partition(struct Student studentArray[], int start, int end)
{
    struct Student pivot = studentArray[end]; //we take the last element as the pivot.
    int i = (start - 1); //index of the smaller student.
    for (int j = start; j < end; j++)
    {
        if (strcmp(studentArray[j].name, pivot.name) <= 0)
        {
            i++;
            swapStudents(&studentArray[i], &studentArray[j]);
        }
    }
    swapStudents(&studentArray[i + 1], &studentArray[end]);
    return (i + 1);
}

/**
 * quickSort algorithm. Recursively implies partition to sub-arrays of elements with
 * smaller values and separately to the sub-arrays with larger values.
 * @param studentsArray array to sort (alphabetically).
 * @param start start index of sub-array.
 * @param end end index of sub-array.
 */
void quickSort(struct Student studentsArray[], int start, int end)
{
    if (start < end)
    {
        int partitionIndex = partition(studentsArray, start, end);
        quickSort(studentsArray, start, partitionIndex - 1);
        quickSort(studentsArray, partitionIndex + 1, end);
    }
}

/**
 * driver of the program.
 * @param argc number of args.
 * @param argv valid args are: best, merge and quick.
 * @return 0 or 1.
 */
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("USAGE: input includes too many arguments.\n");
        return 1;
    }
    char charInput;
    if (strncmp(argv[1], "best", 4) == 0)
    {
        charInput = 'b';
    }
    else if (strncmp(argv[1], "merge", 5) == 0)
    {
        charInput = 'm';
    }
    else if (strncmp(argv[1], "quick", 5) == 0)
    {
        charInput = 'q';
    }
    else
    {
        printf("USAGE: invalid input.\n");
        return 1;
    }
    struct Student studentsArr[5500];
    int arrLastIndex = 0;
    STUDENT_FLAG = createStudent(ID_FLAG, NAME_FLAG, GRADE_FLAG, AGE_FLAG, COUNTRY_FLAG, CITY_FLAG);
    for (int i = 0; i < MAX_ARR_LENGTH; i++)
    {
        studentsArr[i] = STUDENT_FLAG;
    }
    arrLastIndex = parseIntoStudentArray(studentsArr, arrLastIndex);
    // handling EOF error:
    if (arrLastIndex == -1)
    {
        return 1;
    }
    // case of no students input.
    int counter = 0;
    for (int i = 0; i < MAX_ARR_LENGTH; i++)
    {
        if (studentsArr[i].id == ID_FLAG) // checking only one field is okay because we check for validity.
        {
            counter++;
        }
    }
    if (counter == MAX_ARR_LENGTH)
    {
        return 0;
    }
    struct Student bestStudent = findBestStudent(studentsArr, arrLastIndex);

    switch (charInput)
    {
        case 'b':
            printf("best student info is: %ld,%s,%u,%u,%s,%s\n",
                   bestStudent.id, bestStudent.name, bestStudent.grade, bestStudent.age, bestStudent.country,
                   bestStudent.city);
            return 0;
        case 'm':
            mergeSort(studentsArr, 0, arrLastIndex-1);
            printStudentArray(studentsArr, arrLastIndex);
            return 0;
        case 'q':
            quickSort(studentsArr, 0, arrLastIndex-1);
            printStudentArray(studentsArr, arrLastIndex);
            return 0;

    }
    return 1;
}