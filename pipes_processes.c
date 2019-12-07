// C program to demonstrate use of fork() and pipe() 
#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 
  
int main() 
{ 
    // We use two pipes 
    // First pipe to send input string from parent 
    // Second pipe to send concatenated string from child 
  
    int fd1[2];  // Used to store two ends of first pipe 
    int fd2[2];  // Used to store two ends of second pipe 
  
    char fixed_str1[] = "howard.edu"; 
    char fixed_str2[] = "gobison.org";
    char input_str[100]; 
    pid_t p; 
  
    if (pipe(fd1)==-1) 
    { 
        fprintf(stderr, "Pipe Failed" ); 
        return 1; 
    } 
    if (pipe(fd2)==-1) 
    { 
        fprintf(stderr, "Pipe Failed" ); 
        return 1; 
    } 
  
    printf("Enter a string to concatenate:");
    scanf("%s", input_str); 
    p = fork(); 
  
    if (p < 0) 
    { 
        fprintf(stderr, "fork Failed" ); 
        return 1; 
    } 
   
    else if (p > 0) 
    { 
        char join_str[100]; 
  
        close(fd1[0]);   
        write(fd1[1], input_str, strlen(input_str)+1); 
        close(fd1[1]); 
  
        
        wait(NULL); 
  
        close(fd2[1]); // Close writing end of second pipe  
        char string[100];
        read(fd2[0], string, 100); 
        close(fd2[0]);
        printf("Output is: %s\n", string); 
   
    for (int i = 0; i < strlen(string);i++){
      join_str[i] = string[i];
    }
    
    int k = strlen(join_str);
      
    for(int j = 0; j < strlen(fixed_str2); j++){
      join_str[k++] = fixed_str2[j];
    } 
      
    printf("Final Outpt is: %s\n", join_str);
    printf("\n");
    } 

  // child process 
  else
  { 
      // Read string from the first pipe 
      char join_str[100]; 
    
      close(fd1[1]);  // Close writing end of first pipe 
      
      read(fd1[0], join_str, 100);
      close(fd1[0]);
        
      // Concatenate a fixed string with it 
      int k = strlen(join_str); 
    
      for (int i=0; i<strlen(fixed_str1); i++) 
          join_str[k++] = fixed_str1[i]; 
      join_str[k] = '\0';   // string ends with '\0' 

      // Close the reading end
      close(fd2[0]); 
    
      //writing the concatanated string and closing
      write(fd2[1], join_str, strlen(join_str)+1); 
      close(fd2[1]);
    
      exit(0); 
  } 
} 