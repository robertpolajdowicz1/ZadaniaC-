#include <iostream>

using namespace std;
//struktura
struct vege{
    string name;
    float z;
    int d;
    int m;
};
//swap podmieniający struktury "vege"
void vege_swap(vege &v,vege &w){
    vege tmp=v;
    v=w;
    w=tmp;
}
//comparatory dla poszczegolnych kolumn
int vege_comp1(vege v1,vege v2){

    if(v1.z>v2.z) return 1;
    if(v1.z==v2.z) return 0;
    else return -1;
}
int vege_comp2(vege v1,vege v2){

    if(v1.d>v2.d) {return 1;}
    if(v1.d==v2.d) {return 0;}
    else {return -1;}
}
int vege_comp3(vege v1,vege v2){
    if(v1.m>v2.m) return 1;
    if(v1.m==v2.m) return 0;
    else return -1;
}
//odpowiednie wersjce funkcji sortujących
void vege_sort312(vege *tablica, int n){
    for(int i=0;i<n-1;++i)
    {
       int j=i+1;
       while(j>0 && (
             (vege_comp3(tablica[j],tablica[j-1]) == 1) ||
             (vege_comp3(tablica[j],tablica[j-1]) == 0 && vege_comp1(tablica[j],tablica[j-1]) == 1) ||
             (vege_comp3(tablica[j],tablica[j-1]) == 0 && vege_comp1(tablica[j],tablica[j-1]) == 0 && vege_comp2(tablica[j],tablica[j-1]) == 1)))
       {         
          vege_swap(tablica[j],tablica[j-1]);
          --j;
       }
    }
}
void vege_sort321(vege *tablica, int n){
    for(int i=0;i<n-1;++i)
    {
       int j=i+1;
       while(j>0 && (
             (vege_comp3(tablica[j],tablica[j-1]) == 1) ||
             (vege_comp3(tablica[j],tablica[j-1]) == 0 && vege_comp2(tablica[j],tablica[j-1]) == 1) ||
             (vege_comp3(tablica[j],tablica[j-1]) == 0 && vege_comp2(tablica[j],tablica[j-1]) == 0 && vege_comp1(tablica[j],tablica[j-1]) == 1)))
       {
          vege_swap(tablica[j],tablica[j-1]);
          --j;
       }
    }
}
void vege_sort213(vege *tablica, int n){
    for(int i=0;i<n-1;++i)
    {
       int j=i+1;
       while(j>0 && (
             (vege_comp2(tablica[j],tablica[j-1]) == 1) ||
             (vege_comp2(tablica[j],tablica[j-1]) == 0 && vege_comp1(tablica[j],tablica[j-1]) == 1) ||
             (vege_comp2(tablica[j],tablica[j-1]) == 0 && vege_comp1(tablica[j],tablica[j-1]) == 0 && vege_comp3(tablica[j],tablica[j-1]) == 1)))
       {
          vege_swap(tablica[j],tablica[j-1]);
          --j;
       }
    }
}
void vege_sort231(vege *tablica, int n){
    for(int i=0;i<n-1;++i)
    {
       int j=i+1;
       while(j>0 && (
             (vege_comp2(tablica[j],tablica[j-1]) == 1) ||
             (vege_comp2(tablica[j],tablica[j-1]) == 0 && vege_comp3(tablica[j],tablica[j-1]) == 1) ||
             (vege_comp2(tablica[j],tablica[j-1]) == 0 && vege_comp3(tablica[j],tablica[j-1]) == 0 && vege_comp1(tablica[j],tablica[j-1]) == 1)))
       {
          vege_swap(tablica[j],tablica[j-1]);
          --j;
       }
    }
}
void vege_sort123(vege *tablica, int n){
    for(int i=0;i<n-1;++i)
    {
       int j=i+1;
       while(j>0 && (
             (vege_comp1(tablica[j],tablica[j-1]) == 1) ||
             (vege_comp1(tablica[j],tablica[j-1]) == 0 && vege_comp2(tablica[j],tablica[j-1]) == 1) ||
             (vege_comp1(tablica[j],tablica[j-1]) == 0 && vege_comp2(tablica[j],tablica[j-1]) == 0 && vege_comp3(tablica[j],tablica[j-1]) == 1)))
       {
          vege_swap(tablica[j],tablica[j-1]);
          --j;
       }
    }
}
void vege_sort132(vege *tablica, int n){
    for(int i=0;i<n-1;++i)
    {
       int j=i+1;
       while(j>0 && (
             (vege_comp1(tablica[j],tablica[j-1]) == 1) ||
             (vege_comp1(tablica[j],tablica[j-1]) == 0 && vege_comp3(tablica[j],tablica[j-1]) == 1) ||
             (vege_comp1(tablica[j],tablica[j-1]) == 0 && vege_comp3(tablica[j],tablica[j-1]) == 0 && vege_comp2(tablica[j],tablica[j-1]) == 1)))
       {
          vege_swap(tablica[j],tablica[j-1]);
          --j;
       }
    }
}
int main()
{
   std::ios_base::sync_with_stdio(false);
   std::cin.tie(nullptr);
   std::cout.tie(nullptr);
    //wczytanie danych
    int n;
    cin>>n;
    vege* korzeniowe = new vege[n];
    vege* niekorzeniowe= new vege[n];
    int tier[3];
    cin>>tier[0]>>tier[1]>>tier[2];
    int kod=100*tier[0]+10*tier[1]+tier[2];
    
    for(int i=0;i<2*n;++i)
    {
        if(i<n){    cin>>korzeniowe[i].name>>korzeniowe[i].z>>korzeniowe[i].d>>korzeniowe[i].m;}
        else{   cin>>niekorzeniowe[i-n].name>>niekorzeniowe[i-n].z>>niekorzeniowe[i-n].d>>niekorzeniowe[i-n].m;}
    }
    //wywolanie odpowiednich sortów na podstawie konkretnego kodu dla dwóch tablic
    if(kod==123){vege_sort123(korzeniowe,n);vege_sort123(niekorzeniowe,n);}
    if(kod==132){vege_sort132(korzeniowe,n);vege_sort132(niekorzeniowe,n);}
    if(kod==213){vege_sort213(korzeniowe,n);vege_sort213(niekorzeniowe,n);}
    if(kod==231){vege_sort231(korzeniowe,n);vege_sort231(niekorzeniowe,n);}
    if(kod==312){vege_sort312(korzeniowe,n);vege_sort312(niekorzeniowe,n);}
    if(kod==321){vege_sort321(korzeniowe,n);vege_sort321(niekorzeniowe,n);}
    //wypisanie na ekran odpowiednich par
    for(int i=0;i<n;++i)
    {
        cout<<korzeniowe[i].name<<"-"<<niekorzeniowe[i].name<<" ";
    }
    //usuniecie tablic dynamicznych
    delete[] korzeniowe;
    delete[] niekorzeniowe;
}