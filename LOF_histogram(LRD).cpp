#include<bits/stdc++.h>
#define pb push_back
using namespace std;

const int xv = 11;//x is max dimention
const int k = 8;//k is selected max neighbor

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

vector< point > points[1<<xv];
vector< int > kNNs[1007];
vector<int> maskidx;

double ar[12][1007];
int n;
bool chk(int pos, int x){
        return (x &(1 << pos));
}

void build_maskid(int mask){
        for(int i = 0; i < xv; i++){
                if( chk(i,mask) ){
                        maskidx.pb(i);
                }
        }
}
int qq;
double dist( vector<double> point_a, vector<double> point_b ){
        int sz = point_a.size();
        double distance = 0;
        for(int i = 0; i < sz; i++){
                double vc = point_a[i]-point_b[i];
                //if(qq) cout<<"i = "<<i<<" vc = "<<vc<<endl;
                distance += ( vc*vc );
        }
        distance = sqrt(distance);
        return distance;
}

vector< double > k_dis;

//building k_distance for every data point

void make_k_dis(int mask){
        vector<double> a, b;
        double mmmx = 0.0;
        int iid;
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
//                if(mask == 3 && i == 13){
//                        a.clear();b.clear();
//                        qq = 1;
//                        for(int j = 0; j < maskidx.size(); j++ ){
//                                a.push_back( points[mask][13].ar[ maskidx[j] ] );
//                                cout<<points[mask][13].ar[ maskidx[j] ]<<" ";
//                                //b.push_back( points[mask][62].ar[ maskidx[j] ] );
//                        }
//                        cout<<endl;
//                        for(int j = 0; j < maskidx.size(); j++ ){
//                                b.push_back( points[mask][224].ar[ maskidx[j] ] );
//                                cout<<points[mask][224].ar[ maskidx[j] ]<<" ";
//                        }
//                        double xcx = dist(a,b);
//                        cout<<endl;
//                        qq = 0;
//                        cout<<"dds => "<<xcx<<endl;
//                }
//                if(i == 92 && mask == 3) cout<<"d92-> "<<tdis[0].dis<<endl;
//                if(i == 62 && mask == 3) cout<<"d62-> "<<tdis[0].dis<<endl;
//                if(i == 13 && mask == 3) cout<<"d13-> "<<tdis[k-1].dis<<endl;
                k_dis.pb( tdis[k-1].dis );
//                if(mmmx < tdis[k-1].dis ){
//                        mmmx = tdis[k-1].dis;
//                        iid = i;
//                }
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
                double zz = (double)k;
                sum /= zz;
                lrd.pb( 1.0/sum );
        }
}

vector<data1> lof;

void build_lof(int mask){
        for(int i = 0; i < n; i++){
                double x = lrd[i];
                double sum = 0.0;
                for(int j = 0; j < kNNs[i].size(); j++){
                        sum += (x/lrd[ kNNs[i][j] ]);
                }
                double zz = (double)k;
                sum /= zz;
                //cout<<"i = "<<i<<" sum = "<<sum<<endl;
//                if(i == 92 && mask == 3) cout<<"d92-> "<<sum<<endl;
//                if(i == 62 && mask == 3) cout<<"d62-> "<<sum<<endl;
//                if(i == 16 && mask == 3) cout<<"d16-> "<<sum<<endl;
                sum = 1.0/sum;
                data1 temp;
                temp.dis = sum;
                temp.idx = i;
                lof.pb(temp);
        }
}

vector<data1> norma;
map< pair<double,double> , vector<int> > histogram;

void build_norm(vector<double> v){
        double mx = -1e9,mn = 1e9;
        int i;
        for(i = 0; i < v.size(); i++){
                mx = max(mx,v[i]);
                mn = min(mn,v[i]);
        }
        for(i = 0; i < v.size(); i++){
                data1 temp;
                temp.dis = (v[i]-mn)/(mx-mn);
                temp.idx = i;
               norma.push_back(temp);
        }
}

pair<double, double> arr[1007];
int vx;

void make_arr(){
                double zx = sqrt(n)+1;
                vx = (int)zx;
                double l = 0.0,r = 1.0/zx,c = 0.000000001,d = r;
                bool xy = 0;
                for(int i = 0 ; i < vx; i++){
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
        for(int i = 0; i < 1024; i++){
                points[i].clear();
        }
}

void work(){
        int i,j,mask;
        n = _I();//number of points
        make_arr();
        mask = _I();
        for(i = 0; i < n; i++){
                for(j = 0; j < 4; j++){
                        ar[j][i] = _D();
                }
        }
        vector<int> zz;
        for(mask = 1; mask < 16; mask++){
                _new();
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
                build_lof(mask);
                int cnt = 0;
                double av= 0.0;
                sort(lof.begin(),lof.end(),cmp);
                if(mask == 3){
                        for(i = n-1; i > n-11; i-- ) cout<<lof[i].idx<<endl;
                }
                vector<double> test_o_l;
                for(i = n-1; i > 0; i--){
                        //printf("%.3f\n",lof[i]);
                        av += lof[i].dis;
                        //if(mask == 5)
                        //cout<<"lof = "<<lof[i].idx<<endl;
                        if(lof[i].dis < 1.0) break;
                        test_o_l.push_back(lof[i].dis);
                }
                build_norm(test_o_l);
                sort(norma.begin(),norma.end(),cmp);
                j = 0;
                for(i = 0; i < norma.size() && j < vx; i++){
                        if(arr[j].first <= norma[i].dis && norma[i].dis <= arr[j].second){
                                histogram[ arr[j] ].push_back(norma[i].idx);
                        }
                        else {
                                j++;
                                i--;
                        }
                }
                vector<int> ddq;
                int vv = 1;
                while(1){
                        ddq = histogram[ arr[vx-vv] ];
                        if(histogram[ arr[vx-vv] ].size() > 0) break;
                        vv++;
                }
                double quality_fac = 0;
                for(i = 0; i < ddq.size(); i++){
                        quality_fac += ddq.size()*lrd[ lof[ ddq[i] ].idx ];
                }
                zz.push_back(quality_fac);
                //zz.push_back(it->second);
        }

        for(i = 0;i < zz.size(); i++){
                cout<<zz[i]<<endl;
        }
        //av/=5.0;
        //cout<<av<<endl;
}


int main(){
        freopen("data1.txt","r",stdin);
        //freopen("out.txt","w",stdout);
        work();
        return 0;
}
