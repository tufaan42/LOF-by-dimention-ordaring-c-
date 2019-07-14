#include<bits/stdc++.h>
using namespace std;

int dim,n;

string itos(int x){
        string ans;
        if(!x) ans += '0';
        while(x){
                int v = x%10;
                ans += v+'0';
                x /=10;
        }
        reverse(ans.begin(),ans.end());
        return ans;
}

vector<int> maskidx;
bool chk(int pos, int x){
        return (x &(1 << pos));
}

void build_maskid(int mask){
        for(int i = 0; i < 4; i++){
                if( chk(i,mask) ){
                        maskidx.push_back(i);
                }
        }
}

double ar[4][1007];

int main()
{
        //freopen("data1.txt","r",stdin);
        //srand(time(0));
        int j = 0,i = 0,k,v;
        string msk;
        cin>>n;
        for(i = 0; i < n; i++){
                for(j = 0; j < 4; j++){
                        cin>>ar[i][j];
                }
        }
        for(i = 1; i < (1<<4); i++){
                int mask = i;
                msk += itos(i);
                string vv = ".txt";
                msk += vv;

                freopen(msk,"w",stdout);
                printf("%d\n",i);
                maskidx.clear();
                build_maskid(i);
                for(j = 0; j < n; j++){
                        for(k = 0; k < maskidx.size(); k++){
                                printf("%d ",ar[ maskidx[k] ][j]);
                        }
                        putchar(10);
                }
                msk.clear();
        }
        //double Start = clock();
        //double End = clock();
        //printf("%lf",End-Start);
        return 0;
}
