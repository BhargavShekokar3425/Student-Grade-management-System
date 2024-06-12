#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_stud 600
#define MAX_sub 50
#define FILENAME "Student.csv"

struct Student {
    int roll_num;
    char name[100];
    char dept[100];
    int year;
    int no_sem;
    int num_subjects;
    char subjects[MAX_sub][50];
    int credits[MAX_sub];
    int grades[MAX_sub];
    float cgpa;
    int dept_rank;
};

void welcome_to_student_management() {
    printf("Welcome to the Student grade management program.\n");
    printf("Here you can enter details of students, store them, extract them, calculate CGPA, and calculate departmental ranks.\n");
    printf("While entering the department, use the following codes:\n");
    printf("cs: Computer Science\n");
    printf("ee: Electrical Department\n");
    printf("cm: Computational Mathematics\n");
    printf("me: Mechanical Department\n");
    printf("ch: Chemical Department\n");
    printf("ci: Civil Department\n");
    printf("mt: Materials Department\n");
    printf("bb: Bioscience and Bioengineering\n");
    printf("ph: B.S. Physics\n");
    printf("cy: B.S. Chemistry\n");

    printf("While entering the name please enter it without spaces in the format of <first name>_<last name> \n");
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
}

void store_details(struct Student *std) {
    // Code for storing student details
    printf("Enter the details of the student:\n");

    printf("Roll number: ");
    scanf("%d", &std->roll_num);

    printf("Name: ");
    scanf(" %s", &std->name);

    printf("Department: ");
    scanf(" %s", &std->dept);

    printf("Study Year: ");
    scanf("%d", &std->year);

    printf("Number of Semesters completed: ");
    scanf("%d", &std->no_sem);

    printf("Number of subjects: ");
    scanf("%d", &std->num_subjects);

    printf("Enter subject details int the format \n name credits grade (i.e. 3 spaced details): \n");
    for (int i = 0; i < std->num_subjects; i++) {
        printf("Subject %d: ", i + 1);
        scanf(" %s %d %d", &std->subjects[i], &std->credits[i], &std->grades[i]);
    }
}

void cgpa_calculation(struct Student *std) {
    // Code for calculating CGPA
    float sum_grades=0;
    int total_credits=0;
    for(int i=0;i<std->num_subjects;i++)
    {
        sum_grades+= std->grades[i]*std->credits[i];
        total_credits+= std->credits[i];
    }
    std->cgpa=(float) sum_grades/total_credits;
}

void calculate_department_rank(struct Student students[], int num_students) {
    int rank=1;
    // Loop through all students
    for (int i = 0; i <num_students; i++) {
        rank =1;
        // Loop through all students again to compare with current student
        for (int j = 0; j < num_students; j++) {

            // If the student is not the same and is from the same department
            if (i != j && strcmp(students[i].dept, students[j].dept) == 0 && students[i].cgpa < students[j].cgpa) {

                // Check if the CGPA of the current student is less than the CGPA of another student in the same department
                rank=rank+1;
            }
        }
            // Assign the calculated rank to the current student
            students[i].dept_rank = rank;
        }
    }

    void save_students(struct Student students[], int num_students) {
        // Code for saving student details to a file
        //saves details of new students into the given Students file

        FILE *file = fopen(FILENAME, "w+");
        if (file == NULL) {
            printf("Error opening file for writing.\n");
            return;
        }

        for (int i = 0; i < num_students; i++) {
            fprintf(file, "%d,%s,%s,%d,%d,%f,%d\n", students[i].roll_num, students[i].name, students[i].dept,
                    students[i].year, students[i].no_sem, students[i].cgpa, students[i].dept_rank);
        }

        fclose(file);
    }
    int load_students(struct Student **students) {
        FILE *file = fopen(FILENAME, "r");
        if (file == NULL) {
            printf("File not found or unable to open.\n");
            return 0;
        }

        char line[200]; // Adjust the size as needed
        int i = 0;

        // Dynamically allocate memory for the students array
        *students = malloc(MAX_stud * sizeof(struct Student));
        if (*students == NULL) {
            printf("Memory allocation failed.\n");
            fclose(file);
            return 0;
        }

        while (fgets(line, sizeof line, file) != NULL) {
            char *token = strtok(line, ",");
            if (token != NULL) {
                (*students)[i].roll_num = atoi(token);
                token = strtok(NULL, ",");
                if (token != NULL) {
                    strncpy((*students)[i].name, token, sizeof((*students)[i].name) - 1);
                    (*students)[i].name[sizeof((*students)[i].name) - 1] = '\0'; // Ensure null-termination
                    token = strtok(NULL, ",");
                    if (token != NULL) {
                        strncpy((*students)[i].dept, token, sizeof((*students)[i].dept) - 1);
                        (*students)[i].dept[sizeof((*students)[i].dept) - 1] = '\0'; // Ensure null-termination
                        token = strtok(NULL, ",");
                        if (token != NULL) {
                            (*students)[i].year = atoi(token);
                            token = strtok(NULL, ",");
                            if (token != NULL) {
                                (*students)[i].no_sem = atoi(token);
                                token = strtok(NULL, ",");
                                if (token != NULL) {
                                    (*students)[i].cgpa = atof(token);
                                    token = strtok(NULL, ",");
                                    if (token != NULL) {
                                        (*students)[i].dept_rank = atoi(token);
                                    }
                                }
                            }
                        }
                    }
                }
                i++;
            }
        }

        fclose(file);
        return i; // Return the number of students loaded
    }
    void display_details(struct Student *std) {
        // Code for displaying student details
        printf("Student Details:\n");
        printf("Roll number: %d\n", std->roll_num);
        printf("Name: %s\n", std->name);
        printf("Department: %s\n", std->dept);
        printf("Study Year: %d\n", std->year);
        printf("Number of Semesters completed: %d\n", std->no_sem);
        printf("CGPA: %.2f\n", std->cgpa);
    }

    void display_department_rank(struct Student students[], int num_students) {
        // Code for displaying departmental ranks
        printf("Departmental Ranks of the students are as follows :\n");

        for (int i = 0; i < num_students; i++) {
            printf("Roll number: %d, Department: %s, Departmental Rank: %d\n", students[i].roll_num, students[i].dept, students[i].dept_rank);
        }

    }

    int main() {
        welcome_to_student_management();

        int choice;
        //    struct Student students[MAX_stud];
        //    int num_students = 0;
        struct Student *students = NULL;
        int num_students = load_students(&students);
        do {
            printf("\nChoices:\n");
            printf("1: Enter student details\n");
            printf("2: Display student details\n");
            printf("3: Display departmental ranks\n");
            printf("4: Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    if (num_students < MAX_stud) {
                        store_details(&students[num_students]);
                        int count=0;
                        for(int i=0;i<num_students;i++)
                        {
                            for(int j=0;j<num_students;j++)
                            {
                                if(students[i].roll_num==students[j].roll_num)
                                {
                                    count=count+1;
                                }
                            }
                            if(count>1)
                            {
                                printf("Roll numbers can't be same .ENter a roll number that is non repetitive");
                                exit(0);
                            }
                            count = 0;
                        }
                        cgpa_calculation(&students[num_students]);
                        num_students++;
                        calculate_department_rank(students, num_students);
                        //save_students(students, num_students);
                    } else {
                        printf("Maximum number of students reached.\n");
                    }
                    break;
                case 2:
                    printf("Enter student roll number: ");
                    int roll_num;
                    scanf("%d", &roll_num);
                    int found = 0;
                    // Directly use the students array that is already populated
                    for (int i = 0; i < num_students; i++) {
                        if (students[i].roll_num == roll_num) {
                            display_details(&students[i]);
                            found = 1;
                            break;
                        }
                    }
                    if (!found) {
                        printf("Student not found.\n");
                    }
                    break;
                case 3:
                    display_department_rank(students, num_students);
                    break;
                case 4:
                    save_students(students, num_students);
                    //free(students);
                    printf("Exiting program....\n");
                    break;
                default:
                    printf("Invalid choice.....\n");
            }
        } while (choice != 4);

        free(students);
        return 0;
    }
/*
flow of the program -
Welcome to student grade management program-welcome function
Then a choice of what needs to be done by the program
1- Enter the student details
2-Display Student details
3-Calculate and Display Departmental ranks
4-exit..

1- enter the details of a student like Name, roll number, department,
*/