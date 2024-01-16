#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <iomanip>

using namespace std;

vector<string> output;
map<string, int> m;
map<string,int> errm;
vector<string> lstring;
vector<string> label_errors;

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

string bit_convertor(int x){
    
 int count;
 char k,p;
 string retstr;
 int i = 0;

 while(x != 0){
  count = x % 2;
  k = count + '0';
  retstr += k;
  x/=2;
  i++;  
 }

 while(i < 6){
  retstr += '0';
  i++;
 }

 for(unsigned m = 0; m < retstr.length()/2; m++){
  p = retstr[m];
  retstr[m] = retstr[5-m];
  retstr[5-m] = p;
 }

 return retstr;

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

string vChecker(string inside){

 transform(inside.begin(), inside.end(), inside.begin(), ::tolower);
 if(inside == "r0"){
  return "00";
 }
 else if(inside == "r1"){
  return "01";
 }
 else if(inside == "r2"){
  return "10";
 }
 else if(inside == "r3"){
  return "11";
 }
 return "";

}

bool cForRs(string k){

 if(k == "r0" || k == "r1" || k == "r2" || k == "r3")
  return true;
 return false;

}

string string_convertor(vector<string> ops, int counter, int pass){

 string inner;
 int ahead = 0;

 for(unsigned i = 0; i < ops.size(); i++){
  string inside = ops.at(i);
  transform(inside.begin(), inside.end(), inside.begin(), ::tolower);
  if(inside == "add"){
   inner += "00";
   inner += vChecker(ops.at(i+2));
   inner += vChecker(ops.at(i+3));
   inner += vChecker(ops.at(i+1));
   }
  else if(inside == "and"){
   inner += "01";
   inner += vChecker(ops.at(i+2));
   inner += vChecker(ops.at(i+3));
   inner += vChecker(ops.at(i+1));
   }
  else if(inside == "not"){
   inner += "10";
   inner += vChecker(ops.at(i+2));
   inner += "00";
   inner += vChecker(ops.at(i+1));
   }
   //treat r1 as 
  else if(inside == "bnz"){
    ahead = 1;
    inner += "11";
   //cout<<ops.at(i+1)<<endl;
    if(m.find(ops.at(i+1)) != m.end()){
    //cout<< m.find(ops.at(i+1))->second;
    inner += bit_convertor(m.find(ops.at(i+1))->second);
    //cout<< "Here:" << inner << '\n';
    }
    else if(pass == 1){
    string o = "Error: Label " + ops.at(i+1) + " at line ";
    o = o + to_string(counter + 1) + " is not in the symbol table.";
    errm.insert({o, counter});
    inner += "000000";
    }
    else 
     inner += "000100"; 
  }
  else if(!cForRs(inside) && ahead == 0 && pass == 0){
   string s = ops.at(i);
   size_t pos = s.find(':');
   if(pos != string::npos){
    s.erase(pos);    
   }
   if(m.find(s) == m.end())
    m.emplace(s, counter);
   else{
    string f;
    f = "Error: label " + s + " already defined.";
    label_errors.push_back(f);
   }
    //m.insert({s, counter});
  }
 }

 return inner;

}

bool allVar(string s){
 transform(s.begin(), s.end(), s.begin(), ::tolower);
 if(s=="r0" || s=="r1" || s=="r2" || s=="r3" || s=="and" || s=="not" || s=="add" || s=="bnz" || s=="inc" || s=="dec" || s=="mov")
  return false;
 return true;
}

void convertor(vector<string> input){ 
 vector<string> output_string;
 int pass = 0;
 int counter = 0;
 vector<vector<string>> inputstr;

 for(unsigned i = 0; i < input.size(); i++){
    
  string s = input.at(i);
  size_t pos = s.find(';');
  if(pos != string::npos){
   s.erase(pos);    
  }
  if(s.length() == 0)
   continue;
  stringstream X(s);
  string input_string;
  vector<string> ops;

  while(X >> input_string){
   ops.push_back(input_string);
  }

  string simple;

  for(unsigned m = 0; m < ops.size(); m++){
  //size_t pos1 = ops.at(m).find(':');
  // if(pos1 == string::npos || (m == 0 && allVar(ops.at(m))))
  //     simple = simple + ops.at(m) + " ";
   if(m == 0 && allVar(ops.at(m)));
   else
    simple = simple + ops.at(m) + " ";
 }
  if(simple.length() != 0)
  lstring.push_back(simple);

  string_convertor(ops,counter,pass);
  counter++;
  inputstr.push_back(ops);
 }

// for (auto const &pair: m) {
//     std::cout << "{" << pair.first << ": " << pair.second << "}\n";
// }

 pass++;
 int inner_counter = 0;
 for(unsigned k = 0; k < inputstr.size(); k++){
 output_string.push_back(string_convertor(inputstr.at(k),inner_counter,pass));
 inner_counter++;
}
    


 for(unsigned m = 0; m < output_string.size(); m++){
  output.push_back(hexconvertor(output_string.at(m)));
 }
}

int main(int argc, char** argv){
    
 if(argc < 3 || !strcmp(argv[2], "-l") || !strcmp(argv[1], "-l")){
  cout<<"USAGE: fiscas <source file> <object file> [-l]\n";
  return 0;
 }
    
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

 convertor(fl);

 // for(unsigned k = 0; k < output.size(); k++)
 //     cout<< output.at(k) << " ";
 // cout<<'\n';

 ofstream F_output;
 F_output.open(argv[2]);

 if(!F_output){
  std::cerr<<"Failed to open file.\n";
  return 0;
 }
    
 F_output << "v2.0 raw\n";

 for(unsigned k = 0; k < output.size(); k++){
  F_output << output.at(k);
  F_output << '\n';
 }


 // for(unsigned m = 0; m < lstring.size(); m++)
 //     cout<<lstring.at(m)<<'\n';

 if(argc == 4){
  if(!strcmp(argv[3], "-l")){
    
   map <int, string> tempmap;
   unsigned lstr = 0;
   cout<< "***LABEL LIST***\n";

   for(auto const &pair: m) {
    if(pair.first.size() > lstr)
     lstr = pair.first.size();    
    tempmap.insert({pair.second, pair.first});
   }

    //cout << lstr << endl;
    
   for(auto const &pair: tempmap) {
    unsigned q = lstr - pair.second.size();
    cout << pair.second << setw(q);
    string r;
    for(unsigned l= 0; l < 5 + q; l++ )
     r += " ";
    cout << r << pair.first<<'\n';
    }

    for(unsigned f = 0; f < label_errors.size(); f++){
     cout << label_errors.at(f) << '\n';
    }

    cout << "***MACHINE PROGRAM***\n";

    for(unsigned i = 0; i < output.size(); i++){
    
    for(auto const &pa: errm){
     int g = (int) i;
     if(pa.second == g)
      cout<< pa.first <<'\n';
    }

    if(i < 9)
     cout << "0" << i+1 << ":" << output.at(i) << "  " << lstring.at(i) << '\n';
    else
     cout << i+1 << ":" << output.at(i) << "  " << lstring.at(i) << '\n';
   }

  }
}

}