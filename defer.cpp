#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char buf[100001], cmd[1000];
int output = 0, ok = 0, valgrind = 0, err=0;
FILE *F;

main(int argc, char **argv){
   F = fopen(argv[1],"w");
   while (gets(buf)) {
      if (strstr(buf,"Process terminating with default action of signal")) err=1;
      if (strstr(buf,"== Memcheck, a memory error detector")) continue;
      if (strstr(buf,"== Copyright")) continue;
      if (strstr(buf,"== Using Valgrind")) continue;
      if (strstr(buf,"== Using valgrind")) continue;
      if (strstr(buf,"== Using LibVEX")) continue;
      if (strstr(buf,"== For more details")) continue;
      if (strstr(buf,"== Command: ")) continue;
      if (strstr(buf," Memcheck, a memory error detector")) continue;
      if (!strcmp("== ",buf+strlen(buf)-3)) continue;
      if (strstr(buf,"== HEAP SUMMARY:")) {valgrind=1; break;}
      if (strstr(buf,"== ERROR SUMMARY: 0")) {ok=1; break;}
      if (!output++) {
         sprintf(cmd,"%s %s &",argv[2],argv[1]);
         system (cmd);
      }
      if (strstr(buf,"== ")) {
         fprintf(F,"%s\n",1 + strstr(buf,"== ")); fflush(F);
      }else{
         fprintf(F,"%s\n",buf); fflush(F);
      }
   }
   int n = fread(buf,1,100000,stdin);
   buf[n] = 0;
   if (strstr(buf,"LEAK SUMMARY")) err = 1;
   if (!err && (ok || (n == 0 && !output) || strstr(buf," ERROR SUMMARY: 0 errors"))) {
      fprintf(stderr,"Program has finished.  No runtime errors.\n");
      return 0;
   }
   if (valgrind) fprintf(F,"HEAP SUMMARY:\n");
   if (!output++) {
      sprintf(cmd,"%s %s",argv[2],argv[1]);
      system (cmd);
   }
   fprintf(F,buf);
   if (ok && !err) fprintf(stderr,"Program finished without error.\n");
   else fprintf(stderr,"Program finished with errors -- see %s \n",argv[1]);
   fflush(stdout);
   fclose(F);
   return 1;
}
