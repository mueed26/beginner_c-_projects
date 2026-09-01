#include<iostream>
#include<string>
#include<iomanip>
#include<cmath> //validation for paddyFieldSize (fmod)
using namespace std;



class PaddyBaseInfo { //paddyBaseClass
private:
	//necessary data
	double basePricePerTon;
	double subsidyPerTon;
	double plantingCRelong;
public:
	//necessary methods
	PaddyBaseInfo(double, double, double);
	void setPaddyBaseInfo(double, double, double);
	double getBasePrice();
	double getsubsity();
	double getPlantingCost();
	~PaddyBaseInfo() {} // destructor

};
//overloaded construtor for parameterized and non-parameterized constructor
PaddyBaseInfo::PaddyBaseInfo(double basePricePerTon = 0.0, double subsidyPerTon = 0.0, double plantingCRelong = 0.0)
{
	setPaddyBaseInfo(basePricePerTon, subsidyPerTon, plantingCRelong);
}

void PaddyBaseInfo::setPaddyBaseInfo(double basePricePerTon, double subsidyPerTon, double plantingCRelong)
{
	this->basePricePerTon = basePricePerTon;
	this->subsidyPerTon = subsidyPerTon;
	this->plantingCRelong = plantingCRelong;
}

double PaddyBaseInfo::getBasePrice() {
	return basePricePerTon;
}
double PaddyBaseInfo::getsubsity() {
	return subsidyPerTon;
}
double PaddyBaseInfo::getPlantingCost() {
	return plantingCRelong;
}





class farmerInfo { //farmerInfo class
private:
	string name;
	int farmerID;
public:
	farmerInfo(string, int);
	void setFarmerInfo(string, int);
	string getName();
	int getID();
	~farmerInfo() {

	}
};

farmerInfo::farmerInfo(string name = "", int farmerID = 0) {
	setFarmerInfo(name, farmerID);
}
void  farmerInfo::setFarmerInfo(string name, int farmerID) {
	this->farmerID = farmerID;
	this->name = name;
}
string farmerInfo::getName() {
	return name;

}
int farmerInfo::getID() {
	return farmerID;
}


class paddySalesInfo : public farmerInfo { //paddySalesInfo inherited from farmerInfo class
private:
	double fieldSizeInRelong;
	double paddyWeight;
	double weightDeductionPercentage;
public:
	paddySalesInfo();
	//alternate constructor
	paddySalesInfo(string name, int farmerID, double fieldSizeInRelong, double paddyWeight,
		double weightDeductionPercentage) :farmerInfo(name, farmerID) {
		SetPaddySales(fieldSizeInRelong, paddyWeight, weightDeductionPercentage);
	}

	void SetPaddySales(double, double, double);
	double getFieldSize();
	double getPaddyWeight();
	double getDecuctionPercent();

	double calculateNetWeight();
	~paddySalesInfo() {

	}
};

paddySalesInfo::paddySalesInfo() {
	fieldSizeInRelong = paddyWeight = weightDeductionPercentage = 0.0;
}

void paddySalesInfo::SetPaddySales(double fieldSizeInRelong, double paddyWeight,
	double weightDeductionPercentage) {
	this->fieldSizeInRelong = fieldSizeInRelong;
	this->paddyWeight = paddyWeight;
	this->weightDeductionPercentage = weightDeductionPercentage;
}
double paddySalesInfo::getFieldSize() {
	return fieldSizeInRelong;

}
double paddySalesInfo::getPaddyWeight() {
	return paddyWeight;

}
double paddySalesInfo::getDecuctionPercent() {
	return weightDeductionPercentage;

}

double paddySalesInfo::calculateNetWeight() { // calculate netWeight based on deduction and paddy weight
	return paddyWeight - (weightDeductionPercentage / 100.0) * paddyWeight;
}



class paddyRevenue { // paddyRevenue class which has instance of paddyBaseInfo and paddySalesInfo
private:
	PaddyBaseInfo baseInfo;
	paddySalesInfo salesInfo; //default const called
	double TotalPaddyPrice;
	double totalSubsidy;
	string ProductivityRate;
	double incentive;
	double TotalCostIncurred;
	double grossRevenue;
	double NetIncome;
public:
	paddyRevenue();

	paddyRevenue(double, double, double, string, int, double, double, double);

	//using the following two functions to set the input that we got from friend function.
	void setbaseInfo(double, double, double);
	void setsalesInfo(string, int, double, double,
		double);
	double getTotalPaddyPrice();

	double getTotalSubsidy();
	string GetProductivityRate();

	double Getincentive();

	double getTotalCostIncurred();
	double getgrossRevenue();
	double GetNetIncome();

	void calculateTotalPaddyPrice();
	void calculateTotalSubsidyAmount();

	void DetermineProductivityRate();
	void calculateIncentive();
	void calculateTotalCostIncurred();
	void calculateGrossRevenue();
	void CalculateNetIncome();
	void DisplayPaddySalesInfo();



	void DisplayPadyyRevenueInformation();
	void DisplayFarmerProductivityInfo();
	friend void userInputPaddybaseInfo(paddyRevenue&);
	friend void userInputPaddySales(paddyRevenue&);

	~paddyRevenue() {
	}
};
paddyRevenue::paddyRevenue() {
	TotalPaddyPrice = totalSubsidy = incentive = TotalCostIncurred = grossRevenue = NetIncome = 0.0;
	ProductivityRate = " ";
}


//when array is created the deafult constructor is called and when objects from other classes are set as variable then their default is called as well

paddyRevenue::paddyRevenue(double basePricePerTon, double subsidyPerTon, double plantingCRelong, string name, int farmerID, double fieldSizeInRelong, double paddyWeight, double weightDeductionPercentage) {

	TotalPaddyPrice = totalSubsidy = incentive = TotalCostIncurred = grossRevenue = NetIncome = 0.0;
	ProductivityRate = " ";

	baseInfo.setPaddyBaseInfo(basePricePerTon, subsidyPerTon, plantingCRelong);  // now we call the setter functions of the composition objects inside the constructor

	salesInfo.setFarmerInfo(name, farmerID);

	salesInfo.SetPaddySales(fieldSizeInRelong, paddyWeight, weightDeductionPercentage);
}

void paddyRevenue::setbaseInfo(double baseP, double subsidyP, double plantingCost) { //here we call base Infos own setter
	baseInfo.setPaddyBaseInfo(baseP, subsidyP, plantingCost);
}
void paddyRevenue::setsalesInfo(string n, int fID, double fieldSize, double paddyW,
	double weightDeductionP) {
	salesInfo.setFarmerInfo(n, fID); // we can access it bc it is inherited from the farmer class sales info is inherited from farmer class
	salesInfo.SetPaddySales(fieldSize, paddyW, weightDeductionP);
}
double paddyRevenue::getTotalPaddyPrice() {
	return TotalPaddyPrice;
}

double paddyRevenue::getTotalSubsidy() {
	return totalSubsidy;
}
string paddyRevenue::GetProductivityRate() {
	return  ProductivityRate;
}

double paddyRevenue::Getincentive() {
	return incentive;
}

double paddyRevenue::getTotalCostIncurred() {
	return TotalCostIncurred;
}
double paddyRevenue::getgrossRevenue() {
	return grossRevenue;
}
double paddyRevenue::GetNetIncome() {
	return NetIncome;
}

void paddyRevenue::calculateTotalPaddyPrice() {  //calculate paddy price from netWeight and basePrice
	TotalPaddyPrice = baseInfo.getBasePrice() * salesInfo.calculateNetWeight();
}

void paddyRevenue::calculateTotalSubsidyAmount() {
	totalSubsidy = baseInfo.getsubsity() * salesInfo.calculateNetWeight();
}
void paddyRevenue::DetermineProductivityRate() {  //set Productivity rate
	if (salesInfo.getPaddyWeight() > 1.5 * salesInfo.getFieldSize())  
		ProductivityRate = "high";
	else if (salesInfo.getPaddyWeight() > 1 * salesInfo.getFieldSize() && salesInfo.getPaddyWeight() < 1.5 * salesInfo.getFieldSize())
		ProductivityRate = "moderate";
	else
		ProductivityRate = "low";

}
void paddyRevenue::calculateIncentive() {  //calculate incentive based on productivity rate
	if (ProductivityRate == "high")
		incentive = 200 * salesInfo.getFieldSize();
}
void paddyRevenue::calculateTotalCostIncurred() {
	TotalCostIncurred = salesInfo.getFieldSize() * 800;
}
void paddyRevenue::calculateGrossRevenue() {   //add up paddyPrice, subsidyPrice ,and incentive.
	grossRevenue = TotalPaddyPrice + totalSubsidy + incentive;
}
void paddyRevenue::CalculateNetIncome() {
	NetIncome = grossRevenue - TotalCostIncurred;
}

//setwidth and setPrecision for the output
void paddyRevenue::DisplayPaddySalesInfo() {
	cout << std::left;
	cout << setw(20) << "name: " << salesInfo.getName() << endl;
	cout << setw(20) << "Farmer ID:" << salesInfo.getID() << endl;

	cout << setw(20) << "paddy field size: " << salesInfo.getFieldSize() << endl;
	cout << setw(20) << "paddy weight in tons:" << salesInfo.getPaddyWeight() << endl;
	cout << setw(20) << "Deduction in %:" << salesInfo.getDecuctionPercent() << endl;
	cout << setw(20) << "Net Weight:" << fixed << showpoint << setprecision(2) << salesInfo.calculateNetWeight() << endl;


}




void paddyRevenue::DisplayPadyyRevenueInformation() {

	cout << fixed << showpoint << setprecision(2) << endl;
	cout << left;
	cout << setw(20) << "Paddy Price RM: " << TotalPaddyPrice << endl;

	cout << setw(20) << "Subsidy RM:" << totalSubsidy << endl;
	cout << setw(20) << "Productivity:" << ProductivityRate << endl;
	cout << setw(20) << "Incentive RM:" << incentive << endl;
	cout << setw(20) << "planting cost RM:" << TotalCostIncurred << endl;
	cout << setw(20) << "grossRevenue:" << grossRevenue << endl;
	cout << setw(20) << "NetIncome:" << NetIncome << endl;
	
	cout << endl;
}

void paddyRevenue::DisplayFarmerProductivityInfo() {
	cout << "Farmer Name: " << salesInfo.getName() << "    Productivity: " << GetProductivityRate() << endl;
	cout << endl;
}






// friend functions
void userInputPaddybaseInfo(paddyRevenue& obj) {
	double baseP;
	double subsidyP;
	double plantingC;
	cout << "paddy base price per ton:";
	cin >> baseP;
	while (cin.fail() || baseP < 0) { // ci.fail() becomes true when the expected input is entered 

		cin.clear(); // cin goes to fail state when input is entered wrong so we need to clear that up
		cin.ignore(10000, '\n'); // Ignore the rest of the line up to a large number of characters ... to clear  the invalid input
		cout << "Invalid input. Please enter a positive number: ";
		cin >> baseP;

	}
	cout << "subsidy per ton:";
	cin >> subsidyP;
	while (cin.fail() || subsidyP < 0) {

		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Invalid input. Please enter a positive number: ";
		cin >> subsidyP;

	}
	cout << "cost planting paddy per relong:";
	cin >> plantingC;
	while (cin.fail() || plantingC < 0) {

		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Invalid input. Please enter a positive number: ";
		cin >> plantingC;

	}
	obj.setbaseInfo(baseP, subsidyP, plantingC);
	cout << endl;
}

void userInputPaddySales(paddyRevenue& obj) {
	string name;
	int ID;
	double fsize, padyw, weightpercentD;
	cout << "Name:";
	cin.ignore();
	getline(cin, name);
	cout << "Farmer ID:";

	cin >> ID;
	while (cin.fail() || ID < 0) {

		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Invalid input. Please enter a positive number: ";
		cin >> ID;

	}
	cout << "Paddy field size in Relong(0.5,0.75,1,1.25,2.5......):";
	cin >> fsize;
	while (fsize <= 0 || fmod(fsize, 0.25) != 0 || cin.fail()) {   // input validation for sizeOfPaddyField as it should be in the multiples of 0.25
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Invalid input. Please enter a positive number: ";
		cin >> fsize;
	}
	//fmod calculates the remainder of two flaoting point numbers so we check if the number is divisible by 0.25 or not


	cout << "paddy weight:";
	cin >> padyw;
	while (cin.fail() || padyw < 0) {

		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Invalid input. Please enter a positive number: ";
		cin >> padyw;

	}
	cout << "deduction in %(Max 10%):";
	cin >> weightpercentD;
	while (cin.fail() || weightpercentD < 0 || weightpercentD>10) {

		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Invalid input. Please enter a positive number: ";
		cin >> weightpercentD;

	}
	obj.setsalesInfo(name, ID, fsize, padyw, weightpercentD);

	cout << endl;
}
int main() {
	const int size = 1;
	paddyRevenue farmer[size];  // create an object of array from the class paddyRevenue


	int choice;
	bool valid = true;   // when this becomes false the loop ends
	int selectedFarmerIndex = 0;
	system("CLS");  // Clear screen at the beginning
	cout << "*****************************\n";
	cout << "* Welcome to InforX App*\n";
	cout << "*****************************\n\n";


	do {




		cout << "\nMenu:\n";
		cout << "1. input paddy base Information\n";
		cout << "2. input paddy sales info \n";
		cout << "3. calculate and dispaly paddy Revenue and sales Information\n";
		cout << "4. List farmers and their productivity\n";
		cout << "5. Quit\n";
		cout << "choose A valid option(1,2,3,or 4):";
		cin >> choice;

		cout << endl << endl;






		switch (choice) {
		case 1:
			system("CLS");
			cout << "--------- Paddy Base Information ---------\n\n";
			for (int i = 0; i < size; i++) {

				//input information for all farmers which is common data

				cout << "Enter Information for farmer " << i + 1 << ":\n";
				userInputPaddybaseInfo(farmer[i]);  // using friend function for the paddyBaseInput


			}
			cin.ignore();
			cout << "press Enter to Continue....\n";
			cin.get();  // to pause the program
			break;

		case 2:
			system("CLS");
			cout << "--------- Paddy Sales Information ---------\n\n";
			for (int i = 0; i < size; i++) {
				cout << "Enter sales Information for farmer " << i + 1 << ":\n";
				userInputPaddySales(farmer[i]);   // to input paddy sales information


			}
			cin.ignore();
			cout << "press Enter to Continue....\n";
			cin.get();


			break;
		case 3:
			system("CLS");
			cout << "--------- Paddy Revenue and Sales Information ---------\n\n";
			cout << "Select the farmer number (1-" << size << "): ";
			cin >> selectedFarmerIndex;
			while (selectedFarmerIndex <= 0 || selectedFarmerIndex > size || cin.fail()) {
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "Invalid farmer number. try entering again:\n";
				cin >> selectedFarmerIndex;
			}


			selectedFarmerIndex -= 1;//adjusting as index starts from 0.



			farmer[selectedFarmerIndex].calculateTotalPaddyPrice();
			farmer[selectedFarmerIndex].calculateTotalSubsidyAmount();
			farmer[selectedFarmerIndex].DetermineProductivityRate();
			farmer[selectedFarmerIndex].calculateIncentive();
			farmer[selectedFarmerIndex].calculateGrossRevenue();
			farmer[selectedFarmerIndex].calculateTotalCostIncurred();
			farmer[selectedFarmerIndex].CalculateNetIncome();

			farmer[selectedFarmerIndex].DisplayPaddySalesInfo();
			cout << endl << endl;

			farmer[selectedFarmerIndex].DisplayPadyyRevenueInformation();

			cin.ignore();
			cout << "press Enter to Continue....\n";
			cin.get();

			break;

		case 4:
			system("CLS");
			cout << "Farmers and their Productivity:\n\n";
			for (int i = 0; i < size; i++) {
				farmer[i].DisplayFarmerProductivityInfo();
			}
			cin.ignore();
			cout << "Press Enter to continue...";
			cin.get();
			break;
		case 5:
			valid = false;
			break;
		default:
			cout << "invalid choice! please enter 1,2,3,4 or 5:\n";
		}


	} while (valid);



	return 0;
}



