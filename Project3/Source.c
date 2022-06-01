#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//Structura cu informatia unui angajat
typedef struct Employee
{
    short code;
    char* name;
    char* department;
    double salary;
}Employee;

//Structura ce tine evidenta afisarii in functie de prioritatea unui angajat
typedef struct PriorityQueue
{
    Employee** items;
    int size;
    int index;
}PriorityQueue;

Employee* createInfo(short code, char* name, char* department, double salary);
void printInfo(Employee* info);

void ReHeapUp(PriorityQueue* queue, int childIndex);
void putPriority(PriorityQueue* queue, Employee* info);

void main()
{
    FILE* file = fopen("Data.txt", "r");
    char buffer[128];
    char sep_list[] = ",\n";
    char* token;

    PriorityQueue queue = { .items = NULL, .size = 0, .index = 0 };
    Employee* emp = NULL;


    if (file)
    {
        while (fgets(buffer, sizeof(buffer), file))
        {
            emp = (Employee*)malloc(sizeof(Employee));

            token = strtok(buffer, sep_list);
            emp->code = atoi(token);

            token = strtok(NULL, sep_list);
            emp->name = (char*)malloc(strlen(token) + 1);
            strcpy(emp->name, token);

            token = strtok(NULL, sep_list);
            emp->department = (char*)malloc(strlen(token) + 1);
            strcpy(emp->department, token);

            token = strtok(NULL, sep_list);
            emp->salary = atof(token);

            //insert
            putPriority(&queue, emp);
            printf("\n*****************\n");
            for (int i = 0; i < queue.index; i++)
            {
                printInfo(queue.items[i]);
            }
        }

    }
}

//FUNCTIE DE SWAP INTRE CHILD SI PARENT
void ReHeapUp(PriorityQueue* queue, int childIndex)
{
    if (childIndex > 0)
    {
        int parentIndex = (childIndex - 1) / 2;
        if (queue->items[childIndex]->code > queue->items[parentIndex]->code)   //if child > parent
        {
            Employee* aux = queue->items[childIndex];                         // aux = child
            queue->items[childIndex] = queue->items[parentIndex];            // child = parent
            queue->items[parentIndex] = aux;                                 // parent = aux
            ReHeapUp(queue, parentIndex);   //recursive function
        }
    }
}


void putPriority(PriorityQueue* queue, Employee* info)
{
    //ALOCAREA MEMORIEI INITIALE
    if (queue->items == NULL)
    {
        queue->items = (Employee**)malloc(sizeof(Employee*) * 5);  //vom avea 5 angajati
        for (int i = 0; i < 5; i++)
        {
            memcpy(queue->items, queue, sizeof(Employee*) * 5);
        }

        queue->size = 5;
    }

    //RESIZE 
    if (queue->index >= queue->size)
    {
        Employee** aux = queue->items;
        queue->items = (Employee**)malloc(sizeof(Employee*) * queue->size * 2);
        for (int i = 0; i < 2; i++)
        {
            memcpy(queue->items, queue, sizeof(Employee*) * queue->size * 2);
        }

        memcpy(queue->items, aux, sizeof(Employee*) * queue->size);

        queue->size = queue->size * 2;
    }

    queue->items[queue->index] = info;
    ReHeapUp(queue, queue->index);
    queue->index++;

}

void printInfo(Employee* info)
{
    if (info)
    {
        printf("Code: %d, Name: %s, Department: %s, Salary: %f \n",
            info->code, info->name, info->department, info->salary);
    }
}

Employee* createInfo(short code, char* name, char* department, double salary)
{
    Employee* emp = (Employee*)malloc(sizeof(Employee));
    emp->code = code;
    emp->name = (char*)malloc(strlen(name) + 1);
    strcpy(emp->name, name);
    emp->department = (char*)malloc(strlen(department) + 1);
    strcpy(emp->department, department);
    emp->salary = salary;
    return emp;
}





