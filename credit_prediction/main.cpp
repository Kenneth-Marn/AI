#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <math.h>
using namespace std;


vector<string> header;
vector < vector <string> > A;
vector <string> B;
vector <string> result;
vector <string> up;
vector <string> down;
float best_split=0;
float best_gain=0;
int best_attribute=0;
float split_value=0;
int sz=0;
class StringCompare
{
public:
    explicit StringCompare(int column) : m_column(column) {}
    bool operator()(const vector<string>& lhs, const vector<string>& rhs)
    {
        string str1 = lhs[m_column];
        float left=atof(str1.c_str());
        string str2 = rhs[m_column];
        float right=atof(str2.c_str());
        return left < right;
    }
private:
    int m_column;
};

class box
{
public:
    float split_value;   // Length of a box
    int attribute_value;
    
}b1,b2;

struct node
{
    float splitval;
    int attr;
    string label;
    node* Left;
    node* Right;
};




float probability(int no,int total)
{
    float pro=(float)no/(float)total;
    if( isinf(pro) )
    {
        pro = 0;
    }
    else if( isnan(pro) )
    {
        pro = 0;
    }
    return  pro;
}

float cal_set(float pro)
{
    float t=log2 (pro);
    if(isinf(t)==1)
    {
        //printf( "cal_set:%f \n", pro );
        t=0;
    }
    else if( isnan(t))
    {
        t = 0;
    }
    
    float nRet = pro*t;
    
    if(isinf(t)==1)
    {
        nRet=0;
    }
    else if( isnan(nRet))
    {
        nRet = 0;
    }
    
    return nRet;
}

float Info_gain(int cur_row,int cur_column,int size_row,int size_column,float split_value,vector < vector <string> > s)
{
    int sz=size_column-1;
    int no_AAA_up=0,no_AA_up=0,no_A_up=0,no_AAA_down=0,no_AA_down=0,no_A_down=0,no_BBB_up=0,no_BB_up=0,no_B_up=0,no_BBB_down=0,no_BB_down=0,no_B_down=0,no_CCC_up=0,no_CCC_down=0;
    float check;
    int total_up=0;
    int total_down=0;
    int total=0;
    int total_AAA=0;
    int total_AA=0;
    int total_A=0;
    int total_BBB=0;
    int total_BB=0;
    int total_B=0;
    int total_CCC=0;
    
    
    float Pro_AAA_up=0;
    float Pro_AA_up=0;
    float Pro_A_up=0;
    float Pro_BBB_up=0;
    float Pro_BB_up=0;
    float Pro_B_up=0;
    float Pro_CCC_up=0;
    float Pro_AAA_down=0;
    float Pro_AA_down=0;
    float Pro_A_down=0;
    float Pro_BBB_down =0;
    float Pro_BB_down=0;
    float Pro_B_down=0;
    float Pro_CCC_down=0;
    float Pro_r_AAA=0;
    float Pro_r_AA=0;
    float Pro_r_A=0;
    float Pro_r_BBB=0;
    float Pro_r_BB=0;
    float Pro_r_B=0;
    float Pro_r_CCC=0;
    float Pro_UP=0;
    float Pro_Down=0;
    
    float set_AAA_up=0;
    float set_AA_up=0;
    float set_A_up=0;
    float set_BBB_up=0;
    float set_BB_up=0;
    float set_B_up=0;
    float set_CCC_up=0;
    float set_AAA_down=0;
    float set_AA_down=0;
    float set_A_down=0;
    float set_BBB_down=0;;
    float set_BB_down=0;
    float set_B_down=0;;
    float set_CCC_down=0;;
    float set_AAA_r=0;
    float set_AA_r=0;
    float set_A_r=0;
    float set_BBB_r=0;
    float set_BB_r=0;
    float set_B_r=0;
    float set_CCC_r=0;
    
    for(int c=0;c<=size_row-1;c++)
    {
        check=atof ( s[c][cur_column].c_str());
        if(check<=split_value)
        {
            if(s[c][sz]=="AAA")
                no_AAA_up=no_AAA_up+1;
            
            if(s[c][sz]=="AA")
                no_AA_up=no_AA_up+1;
            
            if(s[c][sz]=="A")
                no_A_up=no_A_up+1;
            
            if(s[c][sz]=="BBB")
                no_BBB_up=no_BBB_up+1;
            
            if(s[c][sz]=="BB")
                no_BB_up=no_BB_up+1;
            
            if(s[c][sz]=="B")
                no_B_up=no_B_up+1;
            
            if(s[c][sz]=="CCC")
                no_CCC_up=no_CCC_up+1;
            
            
        }
        if(check>split_value)
        {
            if(s[c][sz]=="AAA")
                no_AAA_down=no_AAA_down+1;
            
            if(s[c][sz]=="AA")
                no_AA_down=no_AA_down+1;
            //cout<<"AA";
            if(s[c][sz]=="A")
                no_A_down=no_A_down+1;
            //cout<<"A";
            if(s[c][sz]=="BBB")
                no_BBB_down=no_BBB_down+1;
            //cout<<"BBB";
            if(s[c][sz]=="BB")
                no_BB_down=no_BB_down+1;
            //cout<<"BB";
            if(s[c][sz]=="B")
                no_B_down=no_B_down+1;
            //cout<<"B";
            if(s[c][sz]=="CCC")
                no_CCC_down=no_CCC_down+1;
        }
        
    }
    
    
    //cout<<no_AAA_up<<" + "<<no_AA_up<<" + "<<no_A_up<<" + "<<no_BBB_up<<" + "<<no_BB_up<<" + "<<no_B_up<<" + "<<no_CCC_up<<endl;
    total_up=no_AAA_up+no_AA_up+no_A_up+no_BBB_up+no_BB_up+no_B_up+no_CCC_up;//total numbers of types at left
    total_down=no_AAA_down+no_AA_down+no_A_down+no_BBB_down+no_BB_down+no_B_down+no_CCC_down;//total numbers of types at right
    total=total_up+total_down;//total numbers of types at root
    total_AAA=no_AAA_up+no_AAA_down;//
    total_AA=no_AA_up+no_AA_down;
    total_A=no_A_up+no_A_down;
    total_BBB=no_BBB_up+no_BBB_down;
    total_BB=no_BB_up+no_BB_down;
    total_B=no_B_up+no_B_down;
    total_CCC=no_CCC_up+no_CCC_down;
    
    
    Pro_AAA_up=probability(no_AAA_up,total_up);
    Pro_AA_up=probability(no_AA_up,total_up);
    Pro_A_up=probability(no_A_up,total_up);
    Pro_BBB_up=probability(no_BBB_up,total_up);
    Pro_BB_up=probability(no_BB_up,total_up);
    Pro_B_up=probability(no_B_up,total_up);
    
    Pro_CCC_up=probability(no_CCC_up,total_up);
    
    Pro_AAA_down=probability(no_AAA_down,total_down);
    Pro_AA_down=probability(no_AA_down,total_down);
    Pro_A_down=probability(no_A_down,total_down);
    Pro_BBB_down =probability(no_BBB_down,total_down);
    Pro_BB_down=probability(no_BB_down,total_down);
    Pro_B_down=probability(no_B_down,total_down);
    Pro_CCC_down=probability(no_CCC_down,total_down);
    Pro_r_AAA=probability(total_AAA,total);
    Pro_r_AA=probability(total_AA,total);
    Pro_r_A=probability(total_A,total);
    Pro_r_BBB=probability(total_BBB,total);
    Pro_r_BB=probability(total_BB,total);
    Pro_r_B=probability(total_B,total);
    Pro_r_CCC=probability(total_CCC,total);
    
    Pro_UP=probability(total_up,total);
    Pro_Down=probability(total_down,total);
    
    set_AAA_up=cal_set(Pro_AAA_up);
    set_AA_up=cal_set(Pro_AA_up);
    set_A_up=cal_set(Pro_A_up);
    set_BBB_up=cal_set(Pro_BBB_up);
    set_BB_up=cal_set(Pro_BB_up);
    set_B_up=cal_set(Pro_B_up);
    set_CCC_up=cal_set(Pro_CCC_up);
    set_AAA_down=cal_set(Pro_AAA_down);
    set_AA_down=cal_set(Pro_AA_down);
    set_A_down=cal_set(Pro_A_down);
    set_BBB_down=cal_set(Pro_BBB_down);
    set_BB_down=cal_set(Pro_BB_down);
    set_B_down=cal_set(Pro_B_down);
    set_CCC_down=cal_set(Pro_CCC_down);
    set_AAA_r=cal_set(Pro_r_AAA);
    set_AA_r=cal_set(Pro_r_AA);
    set_A_r=cal_set(Pro_r_A);
    set_BBB_r=cal_set(Pro_r_BBB);
    set_BB_r=cal_set(Pro_r_BB);
    set_B_r=cal_set(Pro_r_B);
    set_CCC_r=cal_set(Pro_r_CCC);
    
    
    float I_up = -set_AAA_up - set_AA_up - set_A_up - set_BBB_up - set_BB_up - set_B_up - set_CCC_up;
    
    float I_down = -set_AAA_down - set_AA_down - set_A_down - set_BBB_down - set_BB_down - set_B_down - set_CCC_down;
    
    float I_root = -set_AAA_r - set_AA_r - set_A_r - set_BBB_r - set_BB_r - set_B_r - set_CCC_r;
    
    float Info_gain = I_root - (Pro_UP*I_up) - (Pro_Down*I_down);
    
    /* if( 0 == Info_gain )
     {
     printf( "%f %f %f %f %f ==> no_CCC_up:%d total_up:%d \n",I_root, Pro_UP, I_up, Pro_Down, I_down, no_CCC_up,total_up );
     printf( "--- %f %f %f %f %f %f %f\n",set_AAA_up,set_AA_up,set_A_up,set_BBB_up,set_BB_up,set_B_up, set_CCC_up );
     printf( "--- %f %f %f %f %f %f %f\n",Pro_AAA_up,Pro_AA_up,Pro_A_up,Pro_BBB_up,Pro_BB_up,Pro_B_up, Pro_CCC_up );
     
     int a = 0;
     a = 3;
     }*/
    
    return Info_gain;
    
}


//B is column , A is row
box choose_split(vector < vector <string> > v)
{
    
    float a=0;float b=0;float split_value=0;float gain=0;
    best_split=0;best_gain=0;
    
    for(int j=0;j<v[0].size()-1;j++)
    {
        
        sort(v.begin(), v.end(), StringCompare(j));
        
        for(int i=0;i<v.size()-1;i++)        {
            a=atof(v[i][j].c_str());
            b=atof(v[i+1][j].c_str());
            split_value=0.5*(a+b);
            gain=Info_gain(i,j,v.size(),v.size()>0?v[0].size():0,split_value,v);
            
            if(best_gain<gain & gain>0)
            {
                best_gain=gain;
                best_split=split_value;
                best_attribute=j;
            }
            
        }
        
    }
    b1.split_value=best_split;
    b1.attribute_value=best_attribute;
    //cout<<best_split<<endl;
    
    return b1;
}

string count_function(vector<vector<string> >x,int size_row,int size_column)
{
    string result;
    int count_AAA=0,count_AA=0,count_A=0,count_BBB=0,count_BB=0,count_B=0,count_CCC=0;
    for(int i=0;i<x.size();i++)
    {
        result=x[i][size_column-1];
        
        if(result=="AAA")
        {
            count_AAA=count_AAA+1;
        }
        if(result=="AA")
        {
            count_AA=count_AA+1;
        }
        if(result=="A")
        {
            count_A=count_A+1;
        }
        if(result=="BBB")
        {
            count_BBB=count_BBB+1;
        }
        if(result=="BB")
        {
            count_BB=count_BB+1;
        }
        if(result=="B")
        {
            count_B=count_B+1;
        }
        if(result=="CCC")
        {
            count_CCC=count_CCC+1;
        }
    }
    if(count_AAA>count_AA && count_AAA>count_A && count_AAA>count_BBB && count_AAA>count_BB && count_AAA>count_B && count_AAA>count_CCC)
        return "AAA";
    else if(count_AA>count_AAA && count_AA>count_A && count_AA>count_BBB && count_AA>count_BB && count_AA>count_B && count_AA>count_CCC)
        return "AA";
    else if(count_A>count_AA && count_A>count_AAA && count_A>count_BBB && count_A>count_BB && count_A>count_B && count_A>count_CCC)
        return "A";
    else if(count_BBB>count_AA && count_BBB>count_A && count_BBB>count_AAA && count_BBB>count_BB && count_BBB>count_B && count_BBB>count_CCC)
        return "BBB";
    else if(count_BB>count_AA && count_BB>count_A && count_BB>count_AAA && count_BB>count_BBB && count_BB>count_B && count_BB>count_CCC)
        return "BB";
    else if(count_B>count_AA && count_B>count_A && count_B>count_AAA && count_B>count_BBB && count_B>count_BB && count_B>count_CCC)
        return "B";
    else if(count_CCC>count_AA && count_CCC>count_A && count_CCC>count_AAA && count_CCC>count_BB && count_CCC>count_BBB && count_CCC>count_B)
        return "CCC";
    else{
        return "unknown";
    }
}
node* DTL(vector<vector<string> > x,int minleaf,int size_row,int size_column)
{
    
    int a1 = x.size();
    int a2 = x.size()>0?x[0].size():0;
    
    
    vector <vector <string> >left_v;
    vector<string> left_in;
    vector<vector<string> >right_v;
    vector<string> right_in;
    vector<vector<string> >temp1;
    vector<vector<string> >temp2;
    float current = 0.0,initial_value = 0.0;
    string initial,current_str;
    int size_L=0,size_R=0;
    
    //if(sign==0)
    // {
    //left_v.clear();
    //left_in.clear();
    //}
    //if(sign==1)
    //{
    // right_in.clear();
    //right_v.clear();
    //}
    bool c0 = false,c1 = false,c2 = false,c3 = false,c4 = false,c5 = false,check;
    for(int c=0;c<size_column;c++)
    {
        
        if(c==(size_column-1))
        {
            initial=x[0][c];
            for(int d=0;d<size_row;d++)
            {
                current_str=x[d][c];
                if(current_str == initial)
                {
                    c5=true;
                }
                else
                {
                    c5=false;
                    break;
                }
            }
        }
        else
        {
            string str1 = x[0][c];
            initial_value=atof(str1.c_str());
            //initial_value=atof(x[0][c]);
            
            for(int d=1;d<size_row;d++)
            {
                string str2 = x[d][c];
                current=atof( str2.c_str() );
                
                if(current == initial_value)
                {
                    if(c==0)
                    {
                        c0=true;
                    }
                    if(c==1)
                    {
                        c1=true;
                    }
                    if(c==2)
                    {
                        c2=true;
                    }
                    if(c==3)
                    {
                        c3=true;
                    }
                    if(c==4)
                    {
                        c4=true;
                    }
                }
                else
                {
                    
                    if(c==0)
                    {
                        c0=false;
                        break;
                    }
                    if(c==1)
                    {
                        c1=false;
                        break;
                    }
                    if(c==2)
                    {
                        c2=false;
                        break;
                    }
                    if(c==3)
                    {
                        c3=false;
                        break;
                    }
                    if(c==4)
                    {
                        c4=false;
                        break;
                    }
                }
            }
            
            
        }
    }
    
    if( (c0 && c1 && c2 && c3 && c4 ) || c5 )
    {
        check=true;
    }
    else
        check=false;
    
    if(size_row<=minleaf || check==true)
    {
        node* n=new node;
        n->Left = 0;
        n->Right = 0;
        n->label=count_function(x,size_row,size_column);
        return n;
    }
    
    /*for(int j=0;j<x.size();j++)
     {
     for(int k=0;k<x[0].size();k++)
     {
     cout<<x[j][k]<<" ";
     }
     cout<<endl;
     }*/
    b2=choose_split(x);
    node* n=new node;
    n->splitval=b2.split_value;
    n->attr=b2.attribute_value;
    
    int nCountLeft = 0;
    int nCountRight = 0;
    for(int y=0;y<size_row;y++)
    {
        float test=atof(x[y][n->attr].c_str());
        if(test<=n->splitval)
        {
            
            for(int j=0;j<size_column;j++)
            {
                
                
                left_in.push_back(x[y][j]);
                nCountLeft++;
                
            }
            left_v.push_back(left_in);
            left_in.clear();
            
        }
        if(test>n->splitval)
        {
            
            for(int k=0;k<size_column;k++)
            {
                
                right_in.push_back(x[y][k]);
                nCountRight++;
            }
            
            right_v.push_back(right_in);
            right_in.clear();
            
            
        }
        
    }
    
    
    //cout<<"split = "<<n->splitval<<endl;
    temp1=left_v;
    temp2=right_v;
    //cout<<"the left row & column "<<temp1.size()<<" & " <<temp1[0].size()<<endl;
    //cout<<"The right row & column "<<temp2.size()<<" & "<<temp2[0].size()<<endl;
    //cout<<"I IS THE ONE : SIGN "<<b2.split_value<<", "<<sign<<endl;
    n->Left=DTL(temp1,minleaf,temp1.size(),temp1.size()>0?temp1[0].size():0);
    n->Right=DTL(temp2,minleaf,temp2.size(),temp2.size()>0?temp2[0].size():0);
    //n->Left=DTL(temp1,minleaf,temp1.size(),temp1[0].size());
    
    
    //cout<<"REACH : "<<pp<<endl;
    
    return n;
}

vector<vector <string >  > read_train(string x)
{
    A.clear();
    
    ifstream myfile;
    string input;
    int a=0;
    int b=0;
    myfile.open(x.c_str());
    while(!myfile.eof())
    {
        myfile>>input;
        
        if(a<6)
        {
            header.push_back(input);
            a++;
        }
        else
        {
            if(b>(a-1))
            {
                A.push_back(B);
                B.clear();
                b=0;
                
            }
            B.push_back(input);
            b++;
            
            
        }
        if(myfile.eof())
        {
            if( B.size() >=5 )
            {
                A.push_back(B);
            }
            b=0;
            break;
        }
        
    }
    return A;
    
}

vector<vector <string >  > read_test(string x)
{
    ifstream myfile;
    string input;
    int a=0;
    int b=0;
    
    A.clear();
    
    myfile.open(x.c_str());
    while(!myfile.eof())
    {
        myfile>>input;
        
        if(a<5)
        {
            header.push_back(input);
            a++;
        }
        else
        {
            if(b>(a-1))
            {
                A.push_back(B);
                B.clear();
                b=0;
                
            }
            B.push_back(input);
            b++;
            
            
        }
        if(myfile.eof())
        {
            if( B.size() >=5 )
            {
                A.push_back(B);
            }
            b=0;
            break;
        }
        
    }
    myfile.close();
    return A;
    
    
}
void predict(node *n1,vector<string> x)
{
    
    while(n1->Right!=NULL || n1->Left!=NULL)
    {
        int nTemp =  n1->attr;
        string strV = x[nTemp];
        float data= atof (strV.c_str());
        if(data<=n1->splitval)
        {
            n1=n1->Left;
        }
        else
        {
            n1=n1->Right;
        }
    }
    cout<<n1->label<<endl;
}

int main(int argc, char *argv[])
{
    vector<vector< string > > trained;
    vector<vector< string > > tested;
    
    //string test="/Users/zwekhaingmarn/desktop/ai/creditrating/creditrating/test.txt";
    // string  train="/Users/zwekhaingmarn/desktop/ai/creditrating/creditrating/train.txt";
    //string minleaf_string="20";
    string test=argv[2];
    string  train=argv[1];
    string minleaf_string=argv[3];
    float minleaf=atof (minleaf_string.c_str());
    trained=read_train(train);
    tested=read_test(test);
    
    /*for(int j=0;j<tested.size();j++)
     {
     for(int k=0;k<tested[0].size();k++)
     {
     cout<<tested[j][k]<<" ";
     }
     cout<<endl;
     }*/
    node * n2=DTL(trained,minleaf, trained.size(), trained.size()>0?trained[0].size():0);
    for(int f=0;f<tested.size();f++)
    {
        predict(n2,tested[f]);
    }
    
    return 0;
}