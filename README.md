# EDF-Scheduler
This repo contains changes made to freeRTOS source code in order to add an option of using an EDF scheduler 

Thus repo contains all the changes made from the research paper "Implementation and Test of EDF and LLREF
Schedulers in FreeRTOS".

It also contaions extra features missing from the paper that are necessary for the proper functioning of the new scheduler (updating the idle task deadline,
switching context as soon as a task with an earlier deadline is moved to the ready list,and updating the deadline of tasks entering the ready list)

Changes made to freeRTOSconfig.h are also included(ex: switched_in marco and switch_out macros which where used along with the logic analyzer on keil IDE to 
examine the proper functioning of the scheduler and record execution times of different tasks)

an application (main.c) was developed to test the new scheduler.
