#include <stdio.h>
#include <map>
#include <string>


using namespace std; // namespace std

int main(){
 
int z;
    cin>>z;
    vector<int> input_data;
    string buffer;
    int data;
    getline(cin, buffer);
    getline(cin, buffer);
    istringstream iss(buffer);
    
    
    while (iss >> data)
        input_data.push_back(data);
    
    int n= input_data.size();
    
    
    int security_value[n];
        for (int i = 0; i < n; i++) {
            security_value[i] = input_data[i];
        } 
    int no_of_stocks_purchased = securitiesBuying(z,n,security_value);
    cout << no_of_stocks_purchased;
}