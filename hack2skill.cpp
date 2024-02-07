#include <iostream>
#include <unordered_map>
#include<string>
#include <vector>

using namespace std;

// Structure to represent a merchant
struct Merchant {
    string name;
    // Additional details of merchant can be added here
};

// Function to add merchant and pincode details to the data structures
void addMerchantDetails(vector<vector<int>>& sparseMatrix, unordered_map<int, vector<Merchant>>& pincodeMerchants, const string& merchantName, const vector<int>& pincodes) {
    // Generate a unique merchant ID (index) for each merchant
    int merchantID = pincodeMerchants.size(); // Current size acts as ID
    // Update sparse matrix with merchant ID and corresponding pin codes
    for (int pincode : pincodes) {
        sparseMatrix[merchantID].push_back(pincode);
        pincodeMerchants[pincode].push_back({merchantName});
    }
}

// Function to search merchants serving a given pin code
vector<Merchant> searchMerchants(const unordered_map<int, vector<Merchant>>& pincodeMerchants, int pincode) {
    if (pincodeMerchants.count(pincode)) {
        return pincodeMerchants.at(pincode);
    } else {
        return {}; // Return empty vector if pincode not found
    }
}

int main() {
    // Example sparse matrix dimensions
    const int numMerchants = 10000000; // 10M merchants
    const int numPincodes = 30000;     // 30K pincodes

    // Example input data (sparse matrix representation)
    vector<vector<int>> sparseMatrix(numMerchants); // CSR representation

    // Example input data (merchant details)
    unordered_map<int, vector<Merchant>> pincodeMerchants; // Hash table for pincode-merchants mapping

    // Input merchant and pincode details from user
    int numMerchantsInput;
    cout << "Enter the number of merchants: ";
    cin >> numMerchantsInput;
     cin.ignore();
    for (int i = 0; i < numMerchantsInput; ++i) {
        string merchantName;
        int numPincodes;
        cout << "Enter merchant name: ";
        getline(cin,merchantName);
        cout << "Enter the number of pin codes served by " << merchantName << ": ";
        cin >> numPincodes;
        
        cin.ignore();
        
        vector<int> pincodes(numPincodes);
        cout << "Enter the pin codes served by " << merchantName << ": ";
        for (int j = 0; j < numPincodes; ++j) {
            cin >> pincodes[j];
        }

        addMerchantDetails(sparseMatrix, pincodeMerchants, merchantName, pincodes);

        cin.ignore();
    }

    // Prompt user to enter a pin code
    int queryPincode;
    cout << "Enter a pin code to search for merchants: ";
    cin >> queryPincode;

    // Perform search based on user input
    vector<Merchant> merchants = searchMerchants(pincodeMerchants, queryPincode);

    // Display the merchants serving the queried pin code
    if (merchants.empty()) {
        cout << "No merchants found for pin code " << queryPincode << endl;
    } else {
        cout << "Merchants serving pin code " << queryPincode << ":" << endl;
        for (const auto& merchant : merchants) {
            cout << "- " << merchant.name << endl;
        }
    }

    return 0;
}