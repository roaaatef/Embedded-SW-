/*
 * c_projecTT.C
 *
 *  Created on: Aug 11, 2024
 *      Author: hp202
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 struct student_information
 {
	int ID;
	char student_name[50];
	int AGE;
	float GPA;

 } ;

struct node
{
struct student_information data;
struct node*next;


};
struct node*head = NULL;


 void add_new_student(  const struct student_information const *sptr)
{
printf("enter student`s information \n");
fflush(stdout);
scanf(" %d",&sptr->ID);
struct node* current = head;
while (current != NULL) {
    if (current->data.ID == sptr->ID) {
        printf("Error: The ID already exists.\n");
        return;
    }
    current = current->next;
}

	printf("enter the rest of the data \n");
	fflush(stduot);
	scanf(" %s %d %f",&sptr->student_name,&sptr->AGE,&sptr->GPA);
	struct node* pointer2 = NULL;
	struct node*pointer = (struct node*)malloc(sizeof(struct node))	;
	if(pointer==NULL)
	{
		printf("error the allocation  failed \n");
		return;
	}
	else
	{
	pointer->data.AGE=sptr->AGE ;
	pointer->data.GPA=sptr->GPA ;
	pointer->data.ID=sptr->ID;
    strcpy(pointer->data.student_name, sptr->student_name);
    pointer->next = NULL;
    if(head==NULL)
    {
    	head = pointer;
    	return;
    }
    pointer2 = head;
    while(pointer2->next != NULL)
    {
    pointer2 = pointer2->next;
    }


    pointer2->next = pointer;
	}
	}


void display_students_information (void)
{
struct node*pointer3 = head;
int position =0;
if(pointer3==NULL)
	printf("the list is empty \n");
else{
while(pointer3 != NULL)
	{
		printf(" the student number %d  information : ");
		printf(" ID: %d",pointer3-> data.ID);
		printf("  name: %s",pointer3->data.student_name);
		printf(" AGE: %d",pointer3->data.AGE);
		printf("  GPA %d",pointer3->data.GPA);
		pointer3 = pointer3->next;
		position++;
	}

}


}

void searching_for_student(int id)
{
struct node*pointer4 =NULL;

pointer4 = head;
	while(pointer4 != NULL)
	{
		if(pointer4->data.ID == id)
		{
			printf(" student found :");
			printf(" ID:%d \n",pointer4-> data.ID);
					printf("  name: %s \n",pointer4->data.student_name);
					printf(" AGE: %d \n",pointer4->data.AGE);
					printf("  GPA:  %d \n",pointer4->data.GPA);
		}
	pointer4= pointer4->next;

	}
	// ID not found in the list
	printf(" student with ID %d  not found \n");



}

void update_student_information(int id)
{ printf("enter student id to update his information: \n");
fflush(stdout);
scanf(" %d",&id);
	struct node*pointer5 =NULL;

	pointer5 = head;
		while(pointer5 != NULL)
		{
			if(pointer5->data.ID == id)
			{
			printf("enter new information for a student with id %d",id)	;
			printf("enter his name :");
			fflush(stdout);
			scanf(" %s",&pointer5->data.student_name);
			printf("enter his AGE :");
			fflush(stdout);
			scanf(" %s",&pointer5->data.AGE);
			printf("enter his GPA :");
			fflush(stdout);
			scanf(" %s",&pointer5->data.GPA);
			printf("student information updated successfully \n");
			}
			pointer5= pointer5->next;
		}

		printf(" student with ID %d  not found \n");
}

float calculate_avg_gpa (void)
{ int count=0;
float sum =0.0;
float avg_gpa=0.0;
struct node*pointer6=NULL;
if(head==NULL)
{
	return 0.0;
}
pointer6=head;
while(pointer6!=NULL){
 sum+=pointer6->data.GPA;
count++;
	pointer6=pointer6->next;

}
avg_gpa = sum/count;
return avg_gpa;
}
void search_highest_gpa (void)
{
	 float highest_gpa = head->data.GPA;
	 struct node*pointer7=NULL;
	 pointer7=head;
	 if(head==NULL)
	 {
		 printf("there are no students in the list \n");
		 return;
	 }
	 while(pointer7!=NULL)
	 {
		if(pointer7->data.GPA>highest_gpa)
		{
		highest_gpa = pointer7->data.GPA;
		}
		pointer7=pointer7->next;

	 }

	 printf(" student with highest gpa : \n");
	 printf(" ID:%d \n",pointer7-> data.ID);
	 printf("  name: %s \n",pointer7->data.student_name);
	 printf(" AGE: %d \n",pointer7->data.AGE);
	 printf("  GPA:  %d \n",pointer7->data.GPA);

}
void delete_student(int id)
{
	int position = 0;
		// pointer to loop in linked list
		struct node *pointer8 = NULL;
		struct node *previous = NULL;
		// pointer to point the node that will be deleted
		struct node * delete = NULL;



		//check the first node in the linked list
		if(head->data.ID == id)
		{
			delete = head;
			// move head to next node
			head = head->next;

			printf(" student with id %d was deleted successfully \n", id);
			free(delete);
			return;
		}

		//check the rest of nodes in the linked list

		pointer8 = head->next;
		previous = head;
		while(pointer8 != NULL)
		{
			if(pointer8->data.ID == id)
			{
				//element found
				delete = pointer8;
				previous->next = pointer8->next;

				printf(" student with id %d was deleted successfully \n", id);
				free(delete);
				return;
			}
			previous = pointer8;
			pointer8 = pointer8->next;

		}

		//in case the data not found in the linked list
		if(delete == NULL)
		{
			printf(" the student with id %d not found in the List.",id);
		}
	}





int main()
{
int option;
int id;
struct student_information std;
while(1){
printf("enter choice: \n");
fflush(stdout);
scanf(" %d",&option);
switch(option)
{
case 1:
	 add_new_student( std);
	 break;
case 2:

	 display_students_information();
	 break;
case 3:
	 searching_for_student( id)	;
	 break;
case 4:
	 update_student_information( id);
	 break;
case 5:
	 delete_student( id);
	 break;
case 6:
	 calculate_avg_gpa ();
	 break;
case 7:
	 search_highest_gpa ();
	 break;
}
if (strcmp(option, "exit") == 0) { // Check if user typed "exit"
         break;
}

}

printf("Program finished. \n");


	return 0;
}


