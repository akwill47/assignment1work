#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct student{
  int id;
  char *lname; 
  float *scores;
  float std_avg;
}student;

typedef struct course{
  char *course_name;
  int num_sections;
  student **sections;
  int *num_students;
  int *num_scores;
}course;
course *read_courses(FILE *fp, int *num_courses);
student **read_sections(FILE *fp, int num_students[], int num_scores[], int num_sections);
void process_courses(course *courses, int num_courses);
void release_courses( course *courses, int num_courses);

int main(void){
  FILE *fp = fopen ("assignment1input.txt","r");
  int t;
  course *courses;
  fscanf(fp,"%d",&t);
  

  for(int i=0;i<t;i++){
    printf("test case %d\n",i+1);
    int num_courses; 
    courses=read_courses(fp,&num_courses);
    process_courses(courses,num_courses);
    release_courses(courses,num_courses);
  }

  fclose(fp);
  return 0;
}

course *read_courses(FILE *fp, int *num_courses){
  fscanf(fp,"%d",num_courses);
  course *temp=(course*)malloc(*num_courses*sizeof(course));
  char cn[50];
  
  for(int i=0;i<*num_courses;i++){

    fscanf(fp,"%s",cn);
    temp[i].course_name = malloc(strlen(cn)+1);
    strcpy(temp[i].course_name,cn);


    fscanf(fp,"%d",&temp[i].num_sections);
    temp[i].num_students = (int*)malloc(temp[i].num_sections*sizeof(int));
    temp[i].num_scores = (int*)malloc(temp[i].num_sections*sizeof(int));
    
    temp[i].sections = read_sections(fp,temp[i].num_students,temp[i].num_scores,temp[i].num_sections);  
    

  }
 
 return temp;
}
student **read_sections(FILE *fp, int num_students[], int num_scores[], int num_sections){
  student **temp = (student**)malloc(num_sections*sizeof(student *));
  char name[50];
  for(int i=0;i<num_sections;i++){
    fscanf(fp,"%d",&num_students[i]);
    fscanf(fp,"%d",&num_scores[i]);

    temp[i]=(student*)malloc(num_students[i]*sizeof(student));
  
    for(int j=0;j<num_students[i];j++){
      fscanf(fp,"%d",&temp[i][j].id);
      fscanf(fp,"%s",name);

      temp[i][j].lname = malloc(strlen(name)+1);
      strcpy(temp[i][j].lname,name);
      temp[i][j].scores =(float *)malloc(num_scores[i]*sizeof(float));

      float sum = 0;
      for(int k=0;k<num_scores[i];k++){
        fscanf(fp,"%f",&temp[i][j].scores[k]);
        sum+=temp[i][j].scores[k];
      }
      temp[i][j].std_avg = sum/num_scores[i];
    }  
  }
  return temp;  
}

void process_courses(course *courses, int num_courses){
  for (int i = 0; i<num_courses; i++){
    printf("%s ", courses[i].course_name);
    float *s_avg = (float *) malloc(courses[i].num_sections * sizeof(float));
    int j_index=0; int k_index=0; int pass=0; float avg=-1;
    for(int j=0;j<courses[i].num_sections;j++){
      float s_sum=0;
      for (int k=0;k<courses[i].num_students[j];k++){
        if(courses[i].sections[j][k].std_avg>=70){
          pass++;
        }
        s_sum+=courses[i].sections[j][k].std_avg;

        if(courses[i].sections[j][k].std_avg>avg){
          avg=courses[i].sections[j][k].std_avg;
          j_index=j;
          k_index=k;
        }
      }
      s_avg[j]=s_sum/courses[i].num_students[j];
    }
  printf("%d ", pass);

  for(int l=0;l<courses[i].num_sections;l++){
    printf("%.2f ",s_avg[l]);
  }

  printf("%d ",courses[i].sections[j_index][k_index].id);
  printf("%s ",courses[i].sections[j_index][k_index].lname);
  printf("%.2f\n",courses[i].sections[j_index][k_index].std_avg);
  free(s_avg);
    
  }
}

void release_courses( course *courses, int num_courses){
  for (int i = 0; i<num_courses; i++){
    free(courses[i].course_name);
    for(int j = 0; j<courses[i].num_sections; j++){
      for(int k = 0; k<courses[i].num_students[j]; k++){
        free(courses[i].sections[j][k].lname);
        free(courses[i].sections[j][k].scores);
      }
    free(courses[i].sections[j]);
    }
    free(courses[i].sections);
    free(courses[i].num_students);
    free(courses[i].num_scores);
  }
  free(courses);
}
