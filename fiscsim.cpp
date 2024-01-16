#include<iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

vector<string> output;
vector<string> cycle_op;
//int R0 = 0, R1 = 0, R2 = 0, R3 = 0;
string R0 = "00", R1 = "00", R2 = "00", R3 = "00";
//int Rfinal = 0;
string Rfinal = "00";
int counter = 0;
int z = 0;

int conversion(char k){
 
 if(k == 'A')
  return 10;
 else if(k == 'B')
  return 11;
 else if(k == 'C')
  return 12;
 else if(k == 'D')
  return 13;
 else if(k == 'E')
  return 14;
 else if(k == 'F')
  return 15;

 int f = k - '0';
 return f; 

}

char alphaconversion(int k){
 if (k == 10)
  return 'A';
 else if(k == 11)
  return 'B';
 else if(k == 12)
  return 'C';
 else if(k == 13)
  return 'D';
 else if(k == 14)
  return 'E';
 else if(k == 15)
  return 'F';
 return '\0';
}

string hexconvertor(string bstr){
 int k;
 int m = 3;
 int sum1 = 0, sum2 = 0;
 char first, second;

 string hexrep;    

 for(unsigned i = 0; i < 4; i++){
  k = bstr[i] - '0';
  k = k*pow(2,m);
  sum1 += k;
  m--;
 }

 if(sum1 > 9){
  first = alphaconversion(sum1);
 }
 else{
  first = sum1 + '0';
 }

 m = 3;

 for(unsigned i = 4; i < 8; i++){
  k = bstr[i] - '0';
  k = k*pow(2,m);
  sum2 += k;
  m--;
 }

 if(sum2 > 9){
  second = alphaconversion(sum2);
 }
 else{
  second = sum2 + '0';
 }

 hexrep += first;
 hexrep += second;

 return hexrep;

}

string bit_convertor(char inside){
    
 int count;
 char k;
 string retstr;
 int i = 0;

 int x = conversion(inside);

 while(x != 0){
  count = x % 2;
  k = count + '0';
  retstr += k;
  x/=2;
  i++;  
 }

 while(i < 4){
  retstr += '0';
  i++;
 }

 reverse(retstr.begin(), retstr.end());

 return retstr;

}

string value(string s){

 if(s == "00"){
  return R0;
 }
 else if(s == "01"){
  return R1;
 }
 else if(s == "10"){
  return R2;
 }
 else{
  return R3;
 }

}

string lineFormation(string s){
 
 if(s == "00"){
  return "r0";
 }
 else if(s == "01"){
  return "r1";
 }
 else if(s == "10"){
  return "r2";
 }
 else{
  return "r3";
 }

}

int decconvertor(string bstr){
 
 int k;
 int sum1 = 0;
 int m = (int) bstr.size() - 1;    

 for(unsigned i = 0; i < bstr.size(); i++){
  k = bstr[i] - '0';
  k = k*pow(2,m);
  sum1 += k;
  m--;
 }

 return sum1;

}

void update(string s, string insert){
 
 if(s == "00"){
  R0 = insert;
 }
 else if(s == "01"){
  R1 = insert;
 }
 else if(s == "10"){
  R2 = insert;
 }
 else{
  R3 = insert;
 }

}

string add(string fir, string sec){
 
 char change = '0';
 string final;
 
 for(int i = 7; i >= 0; i--){
  
  int fir1 = fir[i] - '0';
  int sec1 = sec[i] - '0';
  int cha = change - '0';
  
  if((fir1 + sec1 + cha) == 0){
   final += "0";
   change = '0';   
  }
  else if((fir1 + sec1 + cha) == 1){
   final += "1";
   change = '0';   
  }
  else if((fir1 + sec1 + cha) == 2){
   final += "0";
   change = '1';   
  }
  else if((fir1 + sec1 + cha) == 3){
   final += "1";
   change = '1';   
  }
 }

 reverse(final.begin(), final.end()); 

 return final;

}

string an(string fir, string sec){

 string final;
 for(unsigned i = 0; i < fir.size(); i++){
  if(fir[i] == '1' && sec[i] == '1'){
   final += "1";
  }
  else{
   final += "0";
  }
 }

 return final;

}

string no(string fir){
 
 string final;
 for(unsigned i = 0; i < fir.size(); i++){
  if(fir[i] == '0'){
   final += "1";
  }
  else{
   final += "0";
  }
 }

 return final;

}

void checker(string s){

 string st1 = s.substr(0,2);
 string st2 = s.substr(2,2);
 string st3 = s.substr(4,2);
 string st4 = s.substr(6,2);
 
 int checker;
 string line,ans;
 string first, second; //both are 8 bits
 string v1,v2,v3;

 v1 = value(st2);
 v2 = value(st3);
 for(int k = 0; k < 2; k++){
  first += bit_convertor(v1[k]);
  second += bit_convertor(v2[k]);
 }

 if(st1 == "00"){ //add
  v3 = add(first,second);
  ans = hexconvertor(v3);
  update(st4, ans);
  Rfinal = ans;
  line = "add " + lineFormation(st4) + " " + lineFormation(st2) + " " + lineFormation(st3);
  output.push_back(line);
 }
 else if(st1 == "01"){ //and
  v3 = an(first,second);
  ans = hexconvertor(v3);
  update(st4, ans);
  Rfinal = ans;
  line = "and " + lineFormation(st4) + " " + lineFormation(st2) + " " + lineFormation(st3);
  output.push_back(line); 
 }
 else if(st1 == "10"){ //not
  v3 = no(first);
  ans = hexconvertor(v3);
  update(st4, ans);
  Rfinal = ans;
  line = "not " + lineFormation(st4) + " " + lineFormation(st2);
  output.push_back(line);
 }
 else if(st1 == "11"){ //bnz
  string k = st2+st3+st4;
  checker = decconvertor(k); 
  line = "bnz " + to_string(checker);
  output.push_back(line);
 }

 if(Rfinal == "00"){
  z = 1;
 }
 else{
  z = 0;
 }

 if(Rfinal != "00" && st1 == "11"){
  counter = checker;
 }
 else{
  counter++;
 }

}

void assembly_convertor(vector<string> input, int real){

 vector<string> bit_strings;
 for(unsigned i = 1; i < input.size(); i++){
  
  string s;
  string line = input.at(i);
  for(int k = 0; k < 2; k++){
   s += bit_convertor(line[k]);
  }

  bit_strings.push_back(s);
 }

 if(real > 100){
  real = 100;
 }

 int q = 0;
 while(((unsigned)counter <= bit_strings.size()) && (q < real)){
  
  if((unsigned)counter == bit_strings.size()){
   counter--;
  }
  checker(bit_strings.at(counter));
  string fri;
  string were = to_string(counter);

  if(counter < 10){
   fri = "PC:0" + were + " " + "Z:" + to_string(z); 
  }
  else{
   fri = "PC:" + were + " " + "Z:" + to_string(z);
  }
  fri = fri + " " + "R0: " + R0 + " " + "R1: " + R1;
  fri = fri + " " + "R2: " + R2 + " " + "R3: " + R3;
  cycle_op.push_back(fri); 
  q++;  
 
 }

}

int main(int argc, char ** argv){
 
 if(argc < 2){
  cout<<"USAGE: fiscsim <object file> [cycles] [-l]\n";
  return 0;
 }

 int k;

 vector<string> fl;
 string input;

 ifstream F_input;

 F_input.open(argv[1]);

 if(!F_input){
  std::cerr<<"Error: Uanble to open or read source file " << "\'" << argv[1] <<"\'" << '\n';
  return 0;
 }

 while(std::getline(F_input,input)){
  fl.push_back(input); 
 }

 F_input.close();

 if(argc < 4){
  k = 20;
 }
 else{
  if(strcmp(argv[2] ,"-d") == 0){
    k = stoi(argv[3]);
  }
  else{
   k = stoi(argv[2]);
  }
 }

 assembly_convertor(fl, k);

 //cout<<"Cycle_op: "<<cycle_op.size()<<" output: " << output.size() <<'\n';

 if(argc < 4){
  for(unsigned i = 0; i < cycle_op.size(); i++){
   cout<<"Cycle:"<<i+1<<" State:"<<cycle_op.at(i)<<'\n';
  }
 }
 else{
  for(unsigned i = 0; i < cycle_op.size(); i++){
   cout<<"Cycle:"<<i+1<<" State:"<<cycle_op.at(i)<<'\n';
   cout<<"Disassembly: "<< output.at(i)<<'\n';
   cout<<'\n';
  }
 }
 

}