#include<bits/stdc++.h>
#define pb push_back
using namespace std;

const int x = 11;//x is max dimention
const int k = 5;//k is selected max neighbor

int _I(){ int x; scanf("%d",&x); return x;}
double _D(){ double x; scanf("%lf",&x); return x; }

struct point {
        double ar[12];
};

struct data1 {
        double dis;
        int idx;
};

bool cmp(data1 &x, data1 &y){
        return x.dis < y.dis;
}

vector< point > points[1<<x];
vector< int > kNNs[1007];
vector<int> maskidx;

double ar[12][1007];
int n;
bool chk(int pos, int x){
        return (x &(1 << pos));
}

void build_maskid(int mask){
        for(int i = 0; i < x; i++){
                if( chk(i,mask) ){
                        maskidx.pb(i);
                }
        }
}

double dist( vector<double> point_a, vector<double> point_b ){
        int sz = point_a.size();
        double distance = 0;
        for(int i = 0; i < sz; i++){
                double vc = point_a[i]-point_b[i];
                distance += ( vc*vc );
        }
        distance = sqrt(distance);
        return distance;
}

vector< double > k_dis;

//building k_distance for every data point

void make_k_dis(int mask){
        vector<double> a, b;
        for(int i = 0; i < n; i++){
                a.clear();
                vector < data1 > tdis;
                for(int j = 0; j < maskidx.size(); j++ ){
                        a.push_back( points[mask][i].ar[ maskidx[j] ] );
                }
                for(int l = 0; l < n; l++){
                        b.clear();
                        if(i == l) continue;
                        for(int j = 0; j < maskidx.size(); j++){
                                b.push_back( points[mask][l].ar[ maskidx[j] ] );
                        }
                        double diss = dist(a,b);
                        data1 tt;
                        tt.dis = diss;
                        tt.idx = l;
                        tdis.pb(tt);
                }
                sort(tdis.begin(),tdis.end(),cmp);
                k_dis.pb( tdis[k-1].dis );
                for(int j = 0; j < k; j++ ){
                        kNNs[i].pb( tdis[j].idx );
                }
        }
}

//calculating Reachability distance

double rich_dist( int idx_a, int idx_b,int mask ){
        vector<double> a,b;
        for(int i = 0; i < maskidx.size(); i++){
                a.pb( points[mask][idx_a].ar[ maskidx[i] ] );
                b.pb( points[mask][idx_b].ar[ maskidx[i] ] );
        }
        double z = dist(a,b);
        double q = max( k_dis[idx_b] , z );
        return q;
}
// calculating Local reachability density
vector<double> lrd;
void build_lrd( int mask){
        for(int j = 0; j < n; j++){
                double sum = 0.0;
                for(int i = 0; i < kNNs[j].size(); i++){
                        sum += rich_dist(j, kNNs[j][i], mask);
                }
                double zz = k;
                sum /= zz;
                lrd.pb( 1.0/sum );
        }
}

vector<data1> lof;

void build_lof(){
        for(int i = 0; i < n; i++){
                double x = lrd[i];
                double sum = 0.0;
                for(int j = 0; j < kNNs[i].size(); j++){
                        sum += (x/lrd[ kNNs[i][j] ]);
                }
                double zz = k;
                sum /= zz;
                //cout<<"i = "<<i<<" sum = "<<sum<<endl;
                sum = 1.0/sum;
                data1 temp;
                temp.dis = sum;
                temp.idx = i;
                lof.pb(temp);
        }
}

vector<double> norma;
map< pair<double,double> , int > histogram;

void build_norm(vector<double> v){
        double mx = -1e9,mn = 1e9;
        int i;
        for(i = 0; i < v.size(); i++){
                mx = max(mx,v[i]);
                mn = min(mn,v[i]);
        }
        double normalize;
        for(i = 0; i < v.size(); i++){
               normalize = (v[i]-mn)/(mx-mn);
               norma.push_back(normalize);
        }
}

pair<double, double> arr[12];

void make_arr(){
                double l = 0.0,r = 0.01,c = 0.000000001,d = 0.01;
                bool xy = 0;
                for(int i = 0 ; i < 10; i++){
                        arr[i] = make_pair(l,r);
                        if(!xy) {
                                l += d+c;
                                xy = 1;
                        }
                        else l += d;
                        r += d;
                }
}

void _new(){
        histogram.clear();
        norma.clear();
        lof.clear();
        lrd.clear();
        k_dis.clear();
        maskidx.clear();
        for(int i = 0; i < 1007; i++){
                kNNs[i].clear();
        }
}

void work(){
        int i,j,mask;
        n = _I();//number of points
        mask = _I();
        for(i = 0; i < n; i++){
                for(j = 0; j < 4; j++){
                        ar[j][i] = _D();
                }
        }

        //for(mask = 1; mask < 16; mask++){
                //_new();
                build_maskid(mask);//building relevent indexes
                for(i = 0; i < n; i++){
                    point temp;
                    for(j = 0; j < maskidx.size(); j++){
                        temp.ar[ maskidx[j] ] = ar[ maskidx[j] ][i];
                    }
                    points[mask].push_back(temp);
                }
                make_k_dis(mask);
                build_lrd(mask);
                build_lof();
                int cnt = 0;
                double av= 0.0;
                sort(lof.begin(),lof.end(),cmp);
                vector<double> test_o_l;
                for(i = n-1; i > 0; i--){
                        //printf("%.3f\n",lof[i]);
                        av += lof[i].dis;
                        cout<<"lof = "<<lof[i].idx<<endl;
                        if(lof[i].dis < 1.4) break;
                        test_o_l.push_back(lof[i].dis);
                }
                build_norm(test_o_l);
                sort(norma.begin(),norma.end());
                j = 0;
                for(i = 0; i < norma.size(); i++){
                        if(arr[j].first <= norma[i] && norma[i] <= arr[j].second){
                                histogram[ arr[j] ]++;
                        }
                        else {
                                j++;
                                i--;
                        }
                }
                for(auto it : histogram){
                        cout<<it.second<<endl;
                }
        //}

        //av/=5.0;
        //cout<<av<<endl;
}


int main(){
        make_arr();
        freopen("data1.txt","r",stdin);
        //freopen("out.txt","w",stdout);
        work();
        return 0;
}
