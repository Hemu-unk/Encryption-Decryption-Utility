#include <stdio.h>      
#include <string.h>     
#include <stdlib.h> 

FILE *in_file;          
FILE *out_file;        
char inName[15], outName[15], temp[2], inChar1[121], inChar2[120], outChar1[255], outChar2[255], hexdec[2];

// Start of Encryption Function
int Encrypt(char *argv[], int x) {
    strcpy(inName, argv[x]); 
    in_file = fopen(inName, "r");        
    if (in_file == NULL) {            
        printf("Error! Can't open file");     
        exit(1);
    }
    printf("\n%s file is being encrypted", inName); 
    int i, len;
    len = strlen(inName);  
    for (i = 0; i < len; i++) {          
        temp[0] = inName[i];            
        if (inName[i] != '.')  
            strcat(outName, temp);    
        else                         
            break;                 
    }
    strcat(outName, ".crp"); 
    out_file = fopen(outName, "w"); 
    while (!feof(in_file)) {             
        fgets(inChar1, 120, in_file);   
        inChar1[strlen(inChar1)] = '\0';       
        for (i = 0; i < strlen(inChar1); i++) {  
            if (inChar1[i] == '\n') {       
            }
            if (inChar1[i] == 9) {               
                char tempString[] = "TT";       
                fputs(tempString, out_file);   
            }
            if (inChar1[i] - 16 < 32) {                       
                inChar1[i] -= 16;                              
                int little = (inChar1[i] - 32) + 144;          
                fprintf(out_file, "%02X", little);            
            } else {                                         
                fprintf(out_file, "%02X", (inChar1[i] - 16));
            }
        }
        fprintf(out_file, "%c", '\n');
    }
    if (feof(in_file)) { 
        printf("\nFile Scan: 100 percent completed.");
    } else {
        printf("Error! encountered an unexpected issue");
    }
    return 0;
}//___________________________________________________________________________End of Encrypt Function

// Start of Decryption Function
int Decrypt(char *argv[], int x) {
    strcpy(inName, argv[x]);  
    in_file = fopen(inName, "r");  
    if (in_file == NULL) { 
        printf("Error! Can't open file");
        exit(1);
    }
    printf("\n%s is being decrypted...");
    int i, len, mid;
    len = strlen(inName);
    for (i = 0; i < len; i++) {
        temp[0] = inName[i];
        if (inName[i] != '.')
            strcat(outName, temp);
        else
            break;
    }
    strcat(outName, ".txt"); 
    out_file = fopen(outName, "w"); 
  while (!feof(in_file)) {  
      fgets(outChar1, 255, in_file); 
      if (strcmp(outChar1, outChar2) == 0 && feof(in_file))  
          break;
      strcpy(outChar2, outChar1); 
      for (i = 0; i < 255; i = i + 2) {  
          hexdec[0] = outChar1[i];
          hexdec[1] = outChar1[i + 1];  
          if (hexdec[0] == 0) 
              break;
          if (hexdec[0] == '\n') {  
              fputc('\n', out_file);
              break;
          } else if (hexdec[0] == 'T' && hexdec[1] == 'T') {  
              fprintf(out_file, "\t");
          } else {
              sscanf(hexdec, "%X", &mid); 
              mid += 16; 

              if (mid > 127)
                  mid = (mid - 144) + 32;
              fprintf(out_file, "%c", mid);
          }
      }
  }
    if (feof(in_file))
        printf("\nFile Scan: 100 percent completed.");
    else {
        printf("\nError! encountered an unexpected issue");
        return 1;
    }
    return 0;
}//___________________________________________________________________________End of Decrypt Function

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Error! Cannot process request");
        exit(1);
    }
    if (strcmp(argv[1], "-E") == 0) {
        printf("Encrypting...");
        Encrypt(argv, 2);
    } else if (strcmp(argv[1], "-D") == 0) {
        printf("Decrypting..");
        Decrypt(argv, 2);
    } else {
        Encrypt(argv, 2);
        printf("Not specified, encryption is assumed");
    }

    fclose(in_file);
    fclose(out_file);
    return 0;
}
