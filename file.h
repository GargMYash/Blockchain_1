void file_trans(char *str)
{
char src[50]="~/Desktop/orignalcode/";
  char dest[50]="~/Desktop/approved";
  char cmd[100];
  strcat(src,str);
  //cout<<"\nENTER FULL PATH OF FILE TO BE MOVED : ";
  //gets(src);
  //cout<<"ENTER FULL PATH WHERE FILE IS TO BE MOVED : ";
  //gets(dest);
  strcpy(cmd,"mv ");
  strcat(cmd,src);
  strcat(cmd," ");
  strcat(cmd,dest);
  system(cmd);


}
