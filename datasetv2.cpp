#include<bits/stdc++.h>
using namespace std;
double ar[507][6];
int xv = 11;//mx dimension
bool chk(int pos, int x){
        return (x &(1 << pos));
}
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
                int x = 3,y = 0;
                vector<int> idxs;

                for(int j = 0; j < xv; j++){
                        if( chk(j,i) ){
                                idxs.push_back(j);
                        }
                }

                sprintf(name, "list%d.csv", i);
                freopen(name,"w",stdout);
                for(int k = 0; k < idxs.size()-1; k++){
                        cout<<"0.5,";
                }
                cout<<"0.5\n";
                for(int k = 0; k < n; k++){
                        for(j = 0; j < idxs.size(); j++){
                               if(j != idxs.size()-1) printf("%.12f,",ar[ k ][ idxs[j] ]);
                               else printf("%.12f",ar[ k ][ idxs[j] ]);
                        }
                        putchar(10);
                }
        }
        //double Start = clock();
        //double End = clock();
        //printf("%lf",End-Start);
        return 0;
}
