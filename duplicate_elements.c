#include<stdio.h>
void read_array( int n,int a[20],FILE *fp);
void display_array(int n,int a[20]);
void check_duplicate(int a[20],int n);
int main() {
    int a[20];
    int n;
    FILE *fp;
    fp=fopen("stack.txt","r");
    scanf("%d",&n);
    read_array( n, a,fp);
    display_array( n,a);
    check_duplicate(a,n);
     /* Enter your code here. Read input from STDIN. Print output to STDOUT */
     fclose(fp);
    return 0;
}
void read_array(int n,int a[20],FILE *fp)
{
    int i;
    for(i=0;i<n;i++)
    {
        fscanf(fp,"%d",&a[i]);
    }
}
void display_array(int n,int a[20])
{
  int i;
    for(i=0;i<n;i++)
    {
        printf("%d ",a[i]);
    }
   printf("\n");
}
void check_duplicate(int a[20],int n)
{
    int i;
    int c=0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(a[i]==a[j])
            c++;
        }
        printf("no of %d are %d\n",a[i],c);
        c=0;
    }
}
