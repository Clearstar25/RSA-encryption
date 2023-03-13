
#include <iostream>
#include <cmath>
#include <string>
#include <bitset>
#include <random>

using namespace std;

void primenumbergen(int, int, int&, int&);
int gcd(int a, int b);
int randgen(int low, int high);
int gene (int low, int high, int, int);
int get_inv(int a, int totient);
int ciphnum(char mess, int e, int n);
string tobin (int c, bitset<16> foo);
string encrypt(string message, int e, int n, bitset<16> foo, string cipher, int size);
int binto (string cipher);
string decrypt(string cipher, int e, int n, int totient);
int menu();

int main() {
bitset<16> foo;
  bool check = false;
  string message;
  string cipher = ""; 
  int p;
int q;
  primenumbergen(11, 100, p, q);
  int totient = (p - 1)*(q - 1);
int e = gene(10, totient, p, q);
int n = p*q;
int selection;
  do{
  do{
    selection = menu();
  }while(selection == 10);

  if(selection == 1){

  cout << "Please enter a message:" << endl;
   getline(cin, message);
cipher = encrypt(message, e, n, foo, cipher, message.size());
  cout << "The cipher is: " << cipher << endl;
    }
  else if(selection == 2){
    do{
    cout << "Please enter a cipher in base 16:" << endl;
     getline(cin, cipher);
  for(int i = 0; i < cipher.size(); i++){
    if(cipher.size() % 16 != 0){
      cout << "The cipher must have a multiple of 16 characters" << endl;
      check = false;
      break;
    }
    else if(cipher[i] != '1' && cipher[i] != '0'){
      cout << "Characters must be 1 or 0" << endl;
      check = false;
      break;
    }
    else
      check = true;
  }
      
      }while(!check);

    message = decrypt(cipher, e, n, totient);
    cout << "The message is: " << message << endl;
  }  

    }while(selection != 0);
}

int randgen(int low, int high){
  std::random_device device;
std::mt19937 generator(device());
  std::uniform_int_distribution<int> distribution(low, high);
   return (distribution(generator));
}
void primenumbergen(int low, int high, int& p, int& q){ 
vector <int> primnum;
int seed, seed2;
  for(int i = low; i <= high; i++){
    primnum.push_back(i);
  }
  int a = primnum.size()/2;
for(int l = 2; l < a; l++){
for(int i = 0; i < primnum.size(); i++){

  if(gcd(primnum.at(i), l) != 1 && l != primnum.at(i) && l < primnum.at(i) || primnum.at(i) == 1){
    primnum.erase(primnum.begin()+i);
    i--;
  }
  
}
  }
   seed = randgen (0, primnum.size() - 1);

 p = primnum.at(seed);

  do{
 seed2 = randgen (0, primnum.size() - 1);
    }while(seed == seed2);

  q = primnum.at(seed2);
}
int gcd(int a, int b){
  int c;
  do{
c = a % b;
a = b;
b = c;
    
  }while(c != 0);

  return a;
  }
int gene (int low, int high, int p, int q){
int totient = (p - 1)*(q - 1);
int e;
  do{
  e = randgen(low, high); 
    }while(e == q || e == p || gcd(e, totient) != 1);
  return e;
}
int get_inv(int a, int totient){
bool check = false;
  int x = 0;
  do{
x++;
    if((a * x) % totient == 1)
      check = true;
  }while(!check);
  return x;
}
int ciphnum(char mess, int e, int n){
int c = 1;
  for(int i = 0; i < e; i++){
  c = c * (int) mess % n;
 }
  return c;
}
string tobin(int c, bitset<16> foo){

  for(int i = 15; i >= 0; i--){

    if(c >= pow(2, i)){
      foo[i] = 1;

      c -= pow(2, i);
    }
   else{
     foo[i] = 0;
   }
  }
return foo.to_string();
}
string encrypt(string message, int e, int n, bitset<16> foo, string cipher, int size){
  int c;
for(int i = 0; i < size; i++){

c = ciphnum(message[i], e, n);


 cipher += tobin(c, foo);
  
  }
  return cipher;
}
int binto (string cipher){
 int x = 0;
  int c = 0; 
  
  for(int i = 15; i >= 0; i--){
   
  
    if(cipher[x] == '1'){
     
      c += pow(2, i);
    
    }
x++;    
  }
  return c;
}
string decrypt(string cipher, int e, int n, int totient){
  string message;
for(int l = 0; l < cipher.size()/16; l++){
int c;
   c = binto(cipher.substr(16*l, 16));
  
    int y = 1;
  for(int i = 0; i < get_inv(e, totient); i++){
  y = y * c % n;
 }
message += y; 
    }
  return message;
}
int menu() {
  char choice;
  cout << "Do you want to: " << endl;
  cout << "(E)ncrypt" << endl
       << "(D)ecrypt\n"
       << "(Q)uit\n";
  cin >> choice;
  if (choice == 'e' || choice == 'E') {
    cin.ignore(80, '\n');
    return 1;
  } else if (choice == 'd' || choice == 'D') {
    cin.ignore(80, '\n');
    return 2;
  } else if (choice == 'q' || choice == 'Q') {
    cin.ignore(80, '\n');
    return 0;
  } else {
    cin.ignore(80, '\n');
    return 10;
  }
}