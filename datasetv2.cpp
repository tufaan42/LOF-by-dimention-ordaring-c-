#include<bits/stdc++.h>
using namespace std;
double ar[507][6];
int main()
{
        char name[32];
//        int cont ;
//        for(cont = 1; cont < 10; cont++){
//                sprintf(name, "lista%d.txt", cont);
//                freopen(name,"w",stdout);
//        }
        freopen("data1.txt","r",stdin);
        int n;
        cin>>n;
        int i,j;
        for(i = 0; i < n; i++){
                for(j = 0;  j < 4; j++){
                        cin>>ar[i][j];
                }
        }
        for(i = 1; i < 16; i++){
                int t = i;
                int x = 3;
                vector<int> idxs;
                while(t){
                        if(t&1){
                                idxs.push_back(x);
                        }
                        t >>= 1;
                        x--;
                }
                sprintf(name, "list%d.txt", i);
                freopen(name,"w",stdout);
                for(int k = 0; k < n; k++){
                        for(j = 0; j < idxs.size(); j++){
                               printf("%.12f ",ar[ k ][ idxs[j] ]);
                        }
                        putchar(10);
                }
        }
        //double Start = clock();
        //double End = clock();
        //printf("%lf",End-Start);
        return 0;
}
