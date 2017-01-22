#include <vector>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class M_object
{
	public:	void  set_var(int _v_size,vector<string> Model_o_titles,vector<vector<int> > _right_matrix,vector<vector<vector<double> > > _Matrix_a);
			vector<string> getNames();
			vector<string> getroot(string M_objectName);
			vector<vector<vector<double> > > getPro();
	private:
		int v_size;
		vector<string> Model_O_names;
		vector<vector<int> > right_matrix;
		vector<vector<vector<double> > > Matrix_a;
	
};

void M_object:: set_var(int _v_size,vector<string> Model_o_titles,vector<vector<int> > _right_matrix,vector<vector<vector<double> > > _Matrix_a)
{
							
	v_size=_v_size;
	Model_O_names=Model_o_titles;	
	right_matrix=_right_matrix;
	Matrix_a=_Matrix_a;					
										
}

vector<string> M_object::getNames()
{
	return Model_O_names;
}
vector<string> M_object::getroot(string M_objectName)
{
	int col=-1;
	for(int i =0; i<Model_O_names.size(); i++)
	{
		if(Model_O_names.at(i)==M_objectName){
			col=i;
			break;
		}							
	}
	vector<string> root;
	for(int i =0; i<Model_O_names.size(); i++)
	{
		if(right_matrix.at(i).at(col)==1){
			root.push_back(Model_O_names.at(i));
		}
		
	}
	return root;
}

vector<vector<vector<double> > > M_object::getPro()
{

	return Matrix_a;
}

class line
{
	public:void  set_var(string _T_variable,vector<string> _K_var,vector<int> _K_varVals,vector<string> _unK_var);
			string T_var();
			vector<string> K_variable();
			vector<string> Un_variable();
			vector<int> K_variableVals();
	private:
		string T_variable;
		vector<string> K_var;
		vector<int> K_varVals;
		vector<string> unK_var;
};


vector<string> line::K_variable()
{
	return K_var;
}
vector<int> line::K_variableVals()
{
	return K_varVals;
}
vector<string> line::Un_variable()
{
	return unK_var;
}

string line::T_var()
{
	return T_variable;
}

void line:: set_var(string _T_variable,vector<string> _K_var,vector<int> _K_varVals,vector<string> _unK_var)
{					
							
	T_variable=_T_variable;	
	K_var=_K_var;
	K_varVals=_K_varVals;	
	unK_var=_unK_var;				
								
}
double StoD(string s)
{
	double n = atof(s.c_str());
	return n;
}

int StoI(string s)
{
	int no = atoi(s.c_str());
	return no;
}


M_object* streamingM_object(char* Name)
{
	string f_row;string call_file;
	fstream OBJECT_Mf(Name);
	vector<vector<int> > right_matrix;
	vector<vector<vector<double> > > Matrix_a;
	vector<vector<double> > Matrix_p;
	vector<double> Matrix_pRow;

	getline(OBJECT_Mf, f_row);
	stringstream signal(f_row);
	signal>>call_file;
	int v_size=StoI(call_file);
	getline(OBJECT_Mf, f_row);	
	getline(OBJECT_Mf, f_row);		
	stringstream signal1(f_row);
	vector<string> Model_O_names;

	while(signal1>>call_file)
	{
		Model_O_names.push_back(call_file);
	}

	getline(OBJECT_Mf, f_row);	
	
	for(int i=0; i<v_size; i++)
	{
		getline(OBJECT_Mf, f_row);
		stringstream signal3(f_row);
		vector<int> right_matrixRow;
		while(signal3>>call_file)
		{
			right_matrixRow.push_back(StoI(call_file));
		}
		right_matrix.push_back(right_matrixRow);
		
	}

	
	getline(OBJECT_Mf, f_row);
	while(!OBJECT_Mf.eof())
	{
		getline(OBJECT_Mf, f_row);
		if( f_row=="\r" || f_row=="" )
		{
			Matrix_a.push_back(Matrix_p);
			Matrix_p.clear();
		}
		else
		{
			stringstream signal4(f_row);
			while(signal4>>call_file)
			{
				Matrix_pRow.push_back(StoD(call_file));
			}
			Matrix_p.push_back(Matrix_pRow);
			Matrix_pRow.clear();
		}
	
	}

	M_object* M_M= new M_object();
	M_M-> set_var(v_size, Model_O_names, right_matrix, Matrix_a);
	return M_M;
}

double randomnize(vector<double> nos, int &tex)
{
	double total_Num=0;
	double r = (double)rand()/RAND_MAX;
	for(int i =0;i<nos.size();i++)
	{
		
		total_Num=total_Num+nos.at(i);
		if(r<=total_Num){
			tex=i;
			return nos.at(i);
		}
	}
}



vector<line*> line_stream(char* Name, M_object* M_M)
{
	string T_variable,f_row;fstream Q_file(Name);vector<line*> Q_list;string SM;bool boolean=false;vector<string> unK_var;
	while(getline(Q_file, f_row))
	{
		vector<string> K_var;vector<int> K_varVals;bool K_variable=false;int i=0;bool P=false;
		while(i<f_row.length())
		{
			if(f_row[i]=='|'|| f_row[i]==')' || f_row[i]=='(' || f_row[i]==',' || (i==0 && P==false) )
			{
				f_row.erase (f_row.begin()+i);
				i=0;
				P=true;
			}
			else if(f_row[i]=='=')
			{
				f_row[i]=' ';
				i++;
			}
			else
			{
				i++;
			}
		}
		stringstream S_s(f_row);
		
		if(f_row!="" )
		{
			while(S_s>>SM) 
			{
				if(K_variable==false)
				{
					K_variable=true;
					T_variable=SM;
				}
				else if(K_variable==true)
				{
					if(boolean==false)
					{
						K_var.push_back(SM);
						boolean=true;
					}
					else
					{
						if(SM=="false")
						{
							K_varVals.push_back(0);
						}
						else
						{
							K_varVals.push_back(1);
						}
						boolean=false;
					}
				}
			}
	
			vector<string> allVars= M_M->getNames();
			for(int k=0;k<allVars.size();k++)
			{
				bool n=true;
				for(int j=0;j<K_var.size();j++)
				{
					if(T_variable==allVars.at(k) || K_var.at(j)==allVars.at(k) )
					{
						n=false;
						break;
					}
				}
				if(n==true){
					unK_var.push_back(allVars.at(k));
				}
			}
			line* qp= new line();
			qp-> set_var(T_variable,K_var,K_varVals,unK_var);
			Q_list.push_back(qp);
		}
	}
	return Q_list;

}

bool Search(string temp, vector<string> c)
{
	for(int a =0;a<c.size();a++)
	{
		if(temp==c.at(a))
		{
			return true;
		}
	
	}
	return false;
}

int give_tex(string temp, vector<string> c)
{
	for(int l =0;l<c.size();l++){
		if(temp==c.at(l)){
			return l;
		}
	
	}
	return -1;

}


void samplingweight(M_object* M_M, line* qp, vector<int> &noofsamples, vector<double> &weight, vector<vector<int> > &b_com)
{
	int numOfSamples=12000;
	int total=0;
	vector<string> Model_O_names=M_M->getNames();
	vector<string> K_vars=qp->K_variable();
	vector<int> K_varVals=qp->K_variableVals();
	vector<string> unK_vars=qp->Un_variable();
	string T_variable = qp->T_var();
	vector<vector<vector<double> > > Matrix_a=M_M->getPro();
	
	for(int h=0;h<numOfSamples;h++)
	{			
		vector<double> pro_all;vector<int> pro_allInx;
		double w=1;
		for(int i =0; i<Model_O_names.size(); i++){	
									
			if (Search(Model_O_names.at(i),K_vars)==false)
			{
				
				
				if(   M_M->getroot(Model_O_names.at(i)).size()>0)
				{	

					vector<string> root=M_M->getroot(Model_O_names.at(i));
					vector<int> root_com;
					for(int j =0; j<root.size(); j++)
					{									
						int inx = give_tex(root.at(j),Model_O_names);
						root_com.push_back(pro_allInx.at(inx));
					}
					
					int lineNum=0;
					for(int j=root_com.size()-1; j>=0; j--)
					{
						if(root_com.at(j)>=1)
						{			
							lineNum=lineNum+(root_com.at(j)*pow(2,root_com.size()-1-j));
						}
					}
					
					
					int tex;													
					double pro= randomnize(Matrix_a.at(i).at(lineNum), tex );
					pro_all.push_back(pro);
					pro_allInx.push_back(tex);
			
				}
				else
				{	
					
					int tex;																								
					double pro= randomnize(Matrix_a.at(i).at(0), tex);
					pro_all.push_back(pro);
					pro_allInx.push_back(tex);
					
				}
			
			}
			else if(Search(Model_O_names.at(i), K_vars)==true)
			{
				
				if(   M_M->getroot(Model_O_names.at(i)).size()>0){	
				
					vector<string> root=M_M->getroot(Model_O_names.at(i));
					vector<int> root_com;
					for(int j =0; j<root.size(); j++)
					{									
						int inx = give_tex(root.at(j),Model_O_names);
						root_com.push_back(pro_allInx.at(inx));
					}
	
					int lineNum=0;
					for(int k=root_com.size()-1; k>=0; k--)
					{
						if(root_com.at(k)>=1)
						{			
							lineNum=lineNum+(root_com.at(k)*pow(2,root_com.size()-1-k));
						}
					}
					
					
					int tex = give_tex(Model_O_names.at(i),K_vars);
					
					double pro= Matrix_a.at(i).at(lineNum).at(K_varVals.at(tex));
					
					w=w*pro;
					pro_all.push_back(pro);
					pro_allInx.push_back(K_varVals.at(tex));
			
				}else
				{	
					
					int texInKnown=give_tex(Model_O_names.at(i), K_vars);	
					int inx=K_varVals.at(texInKnown);	
					double pro=Matrix_a.at(i).at(0).at(inx);
					w=w*pro;
					pro_all.push_back(pro);
					pro_allInx.push_back(inx);
					
				}
			
			}
			
		}
			
			bool taken=false;
			if(b_com.size()>0){
				for(int i =0; i<b_com.size();i++)
				{
					for(int j=0;j<b_com.at(i).size();j++)
					{
						if(b_com.at(i).at(j) == pro_allInx.at(j)){
							taken=true;
						}else{
							taken=false;
							break;
						}
					}
					if(taken==true){
						noofsamples.at(i)++;
						break;
					}
				}
			
			}
					
			if(taken==false)
			{
				b_com.push_back(pro_allInx);
				noofsamples.push_back(1);
				weight.push_back(w);
			}

	
	}
	

	for(int h =0;h<b_com.size();h++){
	
		total=total+noofsamples.at(h);
	}
	bool equal=false;
	
	for(int h =0;h<b_com.size();h++){
		int due=0;
		for(int i =0;i<b_com.size();i++){
			
			for(int j =0;j<b_com.at(h).size();j++){
				if(b_com.at(h).at(j)==b_com.at(i).at(j)){
					equal=true;
				}else{
					equal=false;
					break;
				}
			}
			if(equal==true){
				due++;
			}
		}
	}
	
}

int main(int argc, char* argv[]){		
	srand(time(NULL));																		
	M_object* M_M = streamingM_object(argv[1]);
	vector<line*> Q_list = line_stream(argv[2],M_M);

	ofstream file;
	file.open (argv[3]);
	for(int i =0; i<Q_list.size(); i++){
		
		vector<int> noofsamples;
		vector<double> weight;
		vector<vector<int> > b_com;
		
		samplingweight( M_M, Q_list.at(i), noofsamples, weight, b_com);

		int iof=give_tex(Q_list.at(i)->T_var(), M_M->getNames());
		
		double T_fact=0;double F_fact=0;
		
		for(int j=0; j<b_com.size();j++){
		
			if(b_com.at(j).at(iof)==1){
				T_fact=T_fact+weight.at(j)*noofsamples.at(j);
				
			}else{
				F_fact=F_fact+weight.at(j)*noofsamples.at(j);
			}
		}

 		file << F_fact/(T_fact+F_fact)<<" "<<T_fact/(T_fact+F_fact)<<endl;
  		
	}
	file.close();
	
	return 0;
}