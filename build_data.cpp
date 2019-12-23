#include<bits/stdc++.h>
using namespace std;
//double ar[507][6];
int xv = 11;//mx dimension
bool chk(int pos, int x){
        return (x &(1 << pos));
}

string ar[5050];
int main()
{
        char name[32];
//        int cont ;
//        for(cont = 1; cont < 10; cont++){
//                sprintf(name, "lista%d.txt", cont);
//                freopen(name,"w",stdout);
//        }
        freopen("data0.txt","r",stdin);
        freopen("rdata12.txt","w",stdout);
        int n,dim;
        cin>>n>>dim;
        cout<<n<<" "<<dim<<"\n";
        getchar();
        int i,j;
        for(i = 0; i < n; i++){
                getline(cin,ar[i]);
        }
        for(i = 0; i < n; i++){
                int k = 0;
                string temp;
                for(j = 0; j < ar[i].size(); j++){
                        if(ar[i][j] == ','){
                                cout<<temp;
                                k++;
                                if(k == dim) {
                                        cout<<endl;break;
                                }
                                cout<<" "; temp.clear();
                                continue;
                        }
                        temp += ar[i][j];
                }
        }
        //double Start = clock();
        //double End = clock();
        //printf("%lf",End-Start);
        return 0;
}
