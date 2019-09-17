#include<bits/stdc++.h>
#define pb push_back
using namespace std;

const int xv = 11;//x is max dimention
const int k = 7;//k is selected max neighbor

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

bool cmp2(data1 &x, data1 &y){
        return x.dis > y.dis;
}

vector< point > points[1<<xv];
vector< int > kNNs[5057];
vector<int> maskidx;

double ar[12][5057];
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
        //cout<<"dd6"<<endl;
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
                if(sum > 0.0)
                lrd.pb( 1.0/sum );
                else lrd.pb(0.0);
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
                if(sum > 0.0)
                sum = 1.0/sum;
                else sum = 0;
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
        for(int i = 0; i < 5037; i++){
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
                for(j = 0; j < 10; j++){
                        ar[j][i] = _D();
                }
        }
        vector<double> zz;
        //cout<<ar[j-1][i-1]<<endl;
        for(mask = 511; mask < 512; mask++){
                _new();
                //cout<<"dd1"<<endl;
                build_maskid(mask);//building relevent indexes
                //cout<<"dd2"<<endl;
                for(i = 0; i < n; i++){
                    point temp;
                    for(j = 0; j < maskidx.size(); j++){
                        temp.ar[ maskidx[j] ] = ar[ maskidx[j] ][i];
                    }
                    points[mask].push_back(temp);
                }
                //cout<<"dd3"<<endl;
                make_k_dis(mask);
                //cout<<"dd4"<<endl;
                build_lrd(mask);
                //cout<<"dd5"<<endl;
                build_lof(mask);
                //cout<<"dd6"<<endl;
                int cnt = 0;
                double av= 0.0;
                sort(lof.begin(),lof.end(),cmp2);
                //cout<<"dd7"<<endl;
                cout<<"m = "<<mask<<endl;
                if(mask == 511){
                        for(i = 0; i < 10; i++ ) cout<<lof[i].idx<<endl;
                }
                vector<double> test_o_l;
                for(i = 0; i < n; i++){
                        //printf("%.3f\n",lof[i]);
                        av += lof[i].dis;
                        //if(mask == 5)
                        //cout<<"lof = "<<lof[i].idx<<endl;
                        if(lof[i].dis < 1.0) break;
                        test_o_l.push_back(lof[i].dis);
                }
                //cout<<"dd8"<<endl;
                build_norm(test_o_l);
                //cout<<"dd9"<<endl;
                sort(norma.begin(),norma.end(),cmp);
                //cout<<"dd10"<<endl;
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
//                for(i = 0; i < vx; i++){
//                        cout<<histogram[ arr[i] ].size()<<endl;
//                }
                //cout<<"dd11"<<endl;
                vector<int> ddq;
                int vv = 1;
                while(1){
                        ddq = histogram[ arr[vx-vv] ];
                        if(histogram[ arr[vx-vv] ].size() > 0) break;
                        vv++;
                }
                //cout<<"ddx"<<endl;
                double quality_fac = 0;
                //if(mask == 3) cout<<histogram[ arr[vx-vv] ].size()<<endl;
//                for(i = 0; i < k_dis.size(); i++){
//                        cout<<k_dis[i]<<endl;
//                }
                //cout<<"dd12"<<endl;
                for(i = 0; i < ddq.size(); i++){
                        quality_fac += lof[ ddq[i] ].dis*k_dis[ lof[ ddq[i] ].idx ];
                }
                zz.push_back(quality_fac);
                //cout<<"dd13"<<endl;
                //zz.push_back(it->second);
        }
        double mxxx = 0;
        int mxidx;
        for(i = 0;i < zz.size(); i++){
                if(zz[i] > mxxx){
                        mxxx = zz[i];
                        mxidx = i;
                }
                printf("%.6f\n",zz[i]);
        }
        cout<<mxidx<<endl;
        //av/=5.0;
        //cout<<av<<endl;
}


int main(){
        freopen("rdata1.txt","r",stdin);
        //freopen("out.txt","w",stdout);
        work();
        return 0;
}
