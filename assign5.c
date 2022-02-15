#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct {
  char name [80];
  char schedule [4];
  unsigned hours ;
  unsigned size ;
  unsigned padding ; // unused but required
} COURSE;

int main(){
  
  //char input;
  //FILE *fileIn;
  //file in
  //#define COURSE_FILE "courses.dat"
do{
  char input = ' ';
  FILE *fileIn;
  //file in
  #define COURSE_FILE "courses.dat"
  fileIn = fopen(COURSE_FILE, "rb+");
  if (fileIn == NULL)
     fprintf(stderr, "could not find course file: '%s'\n", COURSE_FILE);
  
  //file out
  //FILE *fileOUT;
  //fileOUT = fopen(COURSE_FILE, "wb");
  //if (fileOUT == NULL)
  //   errExit("could not find course file: '%s'\n", COURSE_FILE);
     
     
  printf("\nAssignment 5 created by Alex Olivarez (ejl483)\n");
  printf("Enter one of the following actions or type CTRL-D to exit.\n");
  printf("C - create a new course record\n");
  printf("R - read an existing course record\n");
  printf("U - update an existing course record\n");
  printf("D - delete an existing course record\n");
  scanf(" %c", &input);

  if (input == 'c'){
    
    COURSE courseC;
    
    int courseNum;
    char courseName [80];
    char courseSchedule [4];
    unsigned courseHours;
    unsigned courseSize;

    int seekResult;
    
    
    printf("\nEnter a course number: 1114\n");
    scanf("%d", &courseNum); 
    
    long lRelativeByteAddress = (sizeof(COURSE) * courseNum);
    seekResult = fseek (fileIn, lRelativeByteAddress , SEEK_SET);
    
    if (seekResult != 0){
       printf("ERROR: course already exists\n");  
       break;
    }
    else{
    printf("Enter a course name: Test Course Name\n");
    scanf(" %[^\n]%*c", courseName);
    strcpy(courseC.name, courseName);
    //courseC.name = courseName;
    
    printf("Enter a course schedule (MWF or TR): \n");
    scanf("%s", courseSchedule);
    strcpy(courseC.schedule, courseSchedule);
    //courseC.schedule = courseSchedule;
    
    printf("Enter course credit hours: 4\n");
    scanf("%d", &courseHours); 
    courseC.hours = courseHours;
    
    printf("Enter student enrollment: 56\n");
    scanf("%d", &courseSize); 
    courseC.size = courseSize;
    
    fclose (fileIn);
    //write
    fileIn = fopen(COURSE_FILE, "wb+");
    fseek (fileIn, 0L, SEEK_END);
    fwrite(&courseC, sizeof(COURSE), 1L, fileIn);
    fclose (fileIn);
    }
  }
  else if (input == 'r'){
    
    int courseNum;
    COURSE courseR;
    
    printf("\nEnter a course number: \n");
    scanf("%d", &courseNum);
    
    //Search for the specified course using the provided course number (e.g., “3424”).
    int seekResult;
    long lRelativeByteAddress = (sizeof(COURSE) * courseNum);
    seekResult = fseek (fileIn, lRelativeByteAddress , SEEK_SET);
    //print
    if(seekResult == 0){
      fread(&courseR, sizeof(COURSE), 1L, fileIn);
      printf("Course number: %d\n", courseNum);
      printf("Course name: %s\n", courseR.name);
      printf("Scheduled days: %s\n", courseR.schedule);
      printf("Credit hours: %d\n", courseR.hours);
      printf("Enrolled Students: %d\n", courseR.size);
      fclose (fileIn);
    }
    else if (seekResult != 0){
        break;
        fclose (fileIn);
    }
  }
  else if (input == 'u'){
  
    int courseNum;
    COURSE courseU;
    
    char courseName [50];
    char courseSchedule [4];
    unsigned courseHours;
    unsigned courseSize;
    
    int seekResult;
    
    printf("\nEnter a course number: 1114\n");
    scanf("%d", &courseNum);
    
    long lRelativeByteAddress = (sizeof(COURSE) * courseNum);
    seekResult = fseek (fileIn, lRelativeByteAddress , SEEK_SET);
    if (seekResult != 0){
       printf("ERROR: course not found\n"); 
       break;
    }
    else{   
    fread(&courseU, sizeof(COURSE), 1L, fileIn); 
      
    printf("Enter a course name: Test Course Name\n");
    scanf(" %[^\n]%*c", courseName);
    if(courseName != NULL) 
      strcpy(courseU.name, courseName);
    
    printf("Enter a course schedule (MWF or TR): \n");
    scanf("%s", courseSchedule);
    if(courseSchedule != NULL)
      strcpy(courseU.schedule, courseSchedule);
    
    printf("Enter course credit hours: 4\n");
    scanf("%d", &courseHours);
    if(courseHours > 0)
      courseU.hours = courseHours;
    
    printf("Enter student enrollment: 56\n");
    scanf("%d", &courseSize); 
    if(courseSize > 0)
      courseU.size = courseSize;
    fclose (fileIn);
    
    //write
    fileIn = fopen(COURSE_FILE, "wb+");
    fseek (fileIn, lRelativeByteAddress , SEEK_SET);
    fwrite(&courseU, sizeof(COURSE), 1L, fileIn);
    fclose (fileIn);
    
    }
  }
  else if (input == 'd'){
  
    int courseNum;
    COURSE courseD;
    int seekResult;
    
    printf("\nEnter a course number: \n");
    scanf("%d", &courseNum);
    //Delete the specified course’s record.
    long lRelativeByteAddress = (sizeof(COURSE) * courseNum);
    seekResult = fseek (fileIn, lRelativeByteAddress , SEEK_SET);
    
    if (seekResult == 0){
      fileIn = fopen(COURSE_FILE, "wb+");
      fwrite(&courseD, sizeof(COURSE), 1L, fileIn);
      fclose (fileIn);
    }
    else{
      fclose (fileIn);
      break;
    }
  }
  else{
    return 0;
  }
  
}while(1);

return 0;
}