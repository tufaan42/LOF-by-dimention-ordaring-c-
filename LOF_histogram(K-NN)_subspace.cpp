#include<bits/stdc++.h>
#define pb push_back
using namespace std;

int xv;//x is max dimention
const int k = 7;//k is selected max neighbor

int _I(){ int x; scanf("%d",&x); return x;}
double _D(){ double x; scanf("%lf",&x); return x; }

struct point {
        double ar[23];
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

vector< point > points;
vector< int > kNNs[1800];
vector<int> maskidx;
vector<int> final_order;

double ar[23][1800];
int n;
bool chk(int pos, int x){
        return (x &(1 << pos));
}

int setm(int x, int pos){
        x = (x| (1<<pos) );
        return x;
}

void build_maskid(int mask){
        for(int i = 0; i < xv; i++){
                if( chk(i,mask) ){
                        maskidx.pb(i);
                }
        }
}
int qq;
bool vis_p[2500][2500];
double dpp[2500][2500];

double dist( vector<double> point_a, vector<double> point_b, int i, int j){//euclidean distance
        int sz = point_a.size();
        if(i > j) swap(i,j);
        if(vis_p[i][j]) return dpp[i][j];
        vis_p[i][j] = 1;
        double distance = 0;
        for(int i = 0; i < sz; i++){
                double vc = point_a[i]-point_b[i];
                //if(qq) cout<<"i = "<<i<<" vc = "<<vc<<endl;
                distance += ( vc*vc );
        }
        distance = sqrt(distance);
        return dpp[i][j] = distance;
}

vector< double > k_dis;

//building k_distance for every data point
vector < data1 > tdis;
void make_k_dis(){
        vector<double> a, b;
        double mmmx = 0.0;
        int iid;

        for(int i = 0; i < n; i++){
                a.clear();
                tdis.clear();
                for(int j = 0; j < maskidx.size(); j++ ){
                        a.push_back( points[i].ar[ maskidx[j] ] );
                }
                int p,q;
                data1 tt;
                for(int l = 0; l < i; l++){
                        tt.dis = dpp[l][i];
                        tt.idx = l;
                        tdis.pb(tt);
                }
                for(int l = i+1; l < n; l++){
                        b.clear();
                        for(int j = 0; j < maskidx.size(); j++){
                                b.push_back( points[l].ar[ maskidx[j] ] );
                        }
                        double diss = dist(a,b,i,l);
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
        //cout<<"dd6"<<endl;
}

//calculating Reachability distance

double rich_dist( int idx_a, int idx_b){
        vector<double> a,b;
        for(int i = 0; i < maskidx.size(); i++){
                a.pb( points[idx_a].ar[ maskidx[i] ] );
                b.pb( points[idx_b].ar[ maskidx[i] ] );
        }
        double z = dist(a,b,idx_a,idx_b);
        double q = max( k_dis[idx_b] , z );
        return q;
}
// calculating Local reachability density
vector<double> lrd;
void build_lrd(){
        for(int j = 0; j < n; j++){
                double sum = 0.0;
                for(int i = 0; i < kNNs[j].size(); i++){
                        sum += rich_dist(j, kNNs[j][i]);
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
                sum /= zz;//average
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
        for(int i = 0; i < 1057; i++){
                kNNs[i].clear();
        }
        points.clear();
        memset(vis_p,0,sizeof vis_p);
}

bool dim_vis[50];

int retrive_mask(vector<int> vc){
        int mask = 0;
        for(int i = 0; i < vc.size(); i++){
                mask = setm(mask,vc[i]);
        }
        return mask;
}

void build(int mask){
        int i,j;
        build_maskid(mask);//building relevent indexes
        for(i = 0; i < n; i++){
                point temp;
                for(j = 0; j < maskidx.size(); j++)
                        temp.ar[ maskidx[j] ] = ar[ maskidx[j] ][i];
                points.push_back(temp);
        }
        make_k_dis();
        build_lrd();
        build_lof(mask);
        sort(lof.begin(),lof.end(),cmp2);
}

void work(){
        int i,j,mask,dim;
        n = _I();//number of points
        make_arr();
        dim = _I();
        xv = dim;
        for(i = 0; i < n; i++){
                for(j = 0; j < dim; j++){
                        ar[j][i] = _D();
                }
        }
        vector<double> zz;
        int m_it,itd;
        //cout<<ar[j-1][i-1]<<endl;
        mask = 0;
        int t_mask = 0,mx_mask;
        double mx_max_quality = 0.0;
        for(itd = 0; itd < dim; itd++){
                t_mask = mask;
                double mx_quality = 0.0;
                int m_id;
                bool f = 0;
                for(m_it = 0; m_it < dim; m_it++){
                        _new();
                        mask = t_mask;
                        if( chk(m_it,t_mask) ) continue;
                        mask = setm(mask,m_it);
                        //cout<<"m = "<<mask<<endl;
                        build(mask);
                        vector<double> test_o_l;
                        for(i = 0; i < n; i++){
                                //cout<<"lof = "<<lof[i].idx<<endl;
                                if(lof[i].dis < 1.0) break;
                                test_o_l.push_back(lof[i].dis);
                        }
                        if(test_o_l.size() < 2) {
                                t_mask = setm(t_mask,m_it);
                                final_order.push_back(m_it);
                                continue;
                        }
                        //cout<<"m_it = "<<m_it<<" tsz = "<<test_o_l.size()<<endl;
                        build_norm(test_o_l);
                        sort(norma.begin(),norma.end(),cmp);
                        j = 0;
                        for(i = 0; i < norma.size() && j < vx; i++){
                                if(arr[j].first <= norma[i].dis && norma[i].dis <= arr[j].second){
                                        histogram[ arr[j] ].push_back(norma[i].idx);
                                }
                                else {
                                        j++;
                                        if(i) i--;
                                }
                        }
                        vector<int> ddq;//highest bin's points
                        int vv = 1;
                        while(1){
                                ddq = histogram[ arr[vx-vv] ];
                                if(histogram[ arr[vx-vv] ].size() > 0) break;
                                vv++;
                                if(vx <= vv) break;
                        }
                        double quality_fac = 0;// quality factor 3
                        for(i = 0; i < ddq.size(); i++){
                                quality_fac += lof[ ddq[i] ].dis*k_dis[ lof[ ddq[i] ].idx ];
                        }
                        //cout<<"qf = "<<quality_fac<<endl;
                        if(quality_fac > mx_quality){
                                mx_quality = quality_fac;
                                m_id = m_it;
                                f = 1;
                        }
                }
                if(!f){
                        break;
//                        for(int dd = 0; dd < dim; dd++){
//                                bool ff = 0;
//                                for(int kk = 0; kk < final_order.size(); kk++){
//                                        if(final_order[kk] == dd){
//                                                ff = 1;
//                                                break;
//                                        }
//                                }
//                                if(!ff){
//                                        t_mask = setm(t_mask,dd);
//                                        final_order.push_back(dd);
//                                        mask = t_mask;
//                                        break;
//                                }
//                        }
//
//                        continue;
                }
                mask = t_mask;
                if(!chk(m_id,mask))
                final_order.push_back(m_id);
                mask = setm(mask,m_id);
                if(mx_quality > 0.0 && mx_quality > mx_max_quality){
                        mx_max_quality = mx_quality;
                        mx_mask = mask;
                }
                else break;
        }
        cout<<"Final order --> ";
        for(i = 0; i < final_order.size(); i++){
                cout<<final_order[i]+1<<" ";
        }
        putchar(10);
        _new();
        build(mx_mask);
        //build( (1<<dim)-1 );
        cout<<"Top 20 outliers:\n";
        for(i = 0; i < 20; i++){
                cout<<"#"<<i+1<<": "<<lof[i].idx<<endl;
        }
        //av/=5.0;
        //cout<<av<<endl;
}


int main(){
        freopen("rdata1.txt","r",stdin);
        //freopen("lof_knn_subspacev2.txt","w",stdout);
        work();
        return 0;
}
