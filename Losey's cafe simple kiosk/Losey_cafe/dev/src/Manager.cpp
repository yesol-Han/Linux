#include "../inc/common.h"
#include "../inc/Manager.h"
#include <ctime>
#include <string.h>
#include <string>

Manager::Manager()
{ //first, give material that can order coffee each 2
	material_3[0] = 12;
	material_3[1] = 6;
	material_3[2] = 8;
	material_3[3] = 2;
	income = 0;
	spending = 0;
}

bool Manager::service(data_t &my_data)
{ //0. Manager Service
	int keep = 1;
	string enter;
	while (keep == 1)
	{
		system("clear");

		string number = "6";
		cout << "Welcome, manager!" << endl << "What kind of service would you like ? " << endl << endl;
		cout << "1. Material Check and Order." << endl;
		cout << "2. Makeable coffee check. (Client & Manager)" << endl;
		cout << "3. Sales and net income check." << endl;
		cout << "4. View coupons issued." << endl;
		cout << "5. Manager mode Exit." << endl;
		cout << "6. Machine Exit." << endl;
		cout << ">> ";
		cin >> number;

		system("clear");
		if (number == "1")
			showmaterial();
		else if (number == "2")
			showCoffee_manager();
		else if (number == "3")
			showSales();
		else if (number == "4")
			showCoupon();
		else if (number == "5"){
			cout << "Exit Manager mode." << endl << endl;
			keep = 0;
		}else{
			cout<<"EXIT"<<endl;
			strcpy(my_data.data,"Cafe Closed...");
			keep = 0;
			return false;
		}

		cout << "Press <Enter>...";
		cin.ignore();
		cin.get();
	}
	return true;
}

void Manager::showmaterial() { //1. Material Check and Order
	string answer;

	while (true) {
		material_menu();

		cout << endl << "Would you like to order more? (Y/N)" << endl << ">> ";
		cin >> answer;
		if (answer == "Y" || answer == "y") {
			order_material();
			system("clear");
		} else if (answer == "N" || answer == "n") {
			cout << endl << "Go to the previous window..." << endl;
			break;
		} else {
			system("clear");
			cout << endl << "<WARN> Please re-enter..." << endl;
		}
	}
}

void Manager::showCoffee(data_t &my_data){ //2. Makeable coffee check client
	for (int i = 0; i < 4; i++)
		order_available[i] = false;

	//orderable menu
	if (material_3[0] >= 2 && material_3[1] >= 1) order_available[0] = true;
	if (material_3[0] >= 2 && material_3[1] >= 2) order_available[1] = true;
	if (material_3[0] >= 1 && material_3[2] >= 2) order_available[2] = true;
	if (material_3[0] >= 1 && material_3[2] >= 2 && material_3[3] >= 1) order_available[3] = true;

	//Confirm menu is orderable
	int j = 0;
	strcpy(my_data.data,"\nThis is menu..\n\n******* < menu > ****** < price > ***\n");
	for (int i = 0; i < 4; i++) {
		my_data.address[i] = order_available[i];
		if (order_available[i] == true) {
			strcpy(my_data.menu[0][i], menu[0][i].c_str());
			strcpy(my_data.menu[1][i], menu[1][i].c_str());
			j++;
		}
	}
}

bool* Manager::showCoffee_manager() {	//2. Makeable coffee check manager

	cout << endl << "This is menu.." << endl << endl;
	cout << "******* < menu > ****** < price > ***" << endl;
	for (int i = 0; i < 4; i++) order_available[i] = false;

	//orderable menu
	if (material_3[0] >= 2 && material_3[1] >= 1) order_available[0] = true;
	if (material_3[0] >= 2 && material_3[1] >= 2) order_available[1] = true;
	if (material_3[0] >= 1 && material_3[2] >= 2) order_available[2] = true;
	if (material_3[0] >= 1 && material_3[2] >= 2 && material_3[3] >= 1)	order_available[3] = true;

	//Confirm menu is orderable
	int j = 0;
	for (int i = 0; i < 4; i++) {
		if (order_available[i] == true) {
			cout << "  " << (i + 1) << ".\t" << menu[0][i] << "\t  " << menu[1][i] << endl;
			j++;
		}
	}

	//No menu available to order
	if (j == 0) {
		cout << "There is no menu available to order." << endl;
		cout << "Sorry, We'll refill our stock soon.";
	}

	cout << endl;
	return order_available;
}

void Manager::showSales()
{ //3. Sales and net income check
	cout << endl << " Sales >> " << income << " Won." << endl;
	cout << " net income >> " << income - spending << " Won." << endl << endl;
}

void Manager::showCoupon()
{ //4. View coupons issued
	int i = 0;
	int checking;
	for (; i < CouponSize(); i++)
	{
		checking = Coupon.front();
		Coupon.pop_front();
		cout << i + 1 << ". " << checking << endl;
		Coupon.push_back(checking);
	}

	if (i == 0)
		cout << endl << "There are no coupons issued at this time." << endl;

	cout << endl;
}

///////////////////////////////////////////////////////////////////////////////////

void Manager::TakeOrder(int coffee_choice, int coupon) { //5. Client chooses coffee
	switch (coffee_choice)
	{
	case 1:
		Americano(coupon);
		break;
	case 2:
		Espresso(coupon);
		break;
	case 3:
		Cafelatte(coupon);
		break;
	case 4:
		Vanillalatte(coupon);
		break;
	default:
		break;
	}
}

void Manager::Americano(int coupon)
{
	material_3[0] -= 2;
	material_3[1] -= 1;
	income += (1500 - coupon);
}

void Manager::Espresso(int coupon)
{
	material_3[0] -= 2;
	material_3[1] -= 2;
	income += (2000 - coupon);
}

void Manager::Cafelatte(int coupon)
{
	material_3[0] -= 1;
	material_3[2] -= 2;
	income += (2000 - coupon);
}

void Manager::Vanillalatte(int coupon)
{
	material_3[0] -= 1;
	material_3[2] -= 2;
	material_3[3] -= 1;
	income += (2500 - coupon);
}

//////////////////////////////////////////////////////////////////////////////////

void Manager::order_material()
{ //1-1. Order Material
	string name;
	string add;

	system("clear");
	material_menu();

	cout << endl << "Please enter the material name to order." << endl;
	cout << "(Please enter <quit> to cancel your order.)" << endl;
	cout << ">> ";
	cin >> name;
	if (name == "quit" || name == "QUIT") ;
	else if (name == material_1[0] || name == material_1[1] || name == material_1[2] || name == material_1[3]){
		int num = 0;
		while (true) {
			cout << endl << "Please enter the amount of material you want to order" << endl;
			cout << "(Please enter <quit> to cancel your order.)" << endl;
			cout << ">> ";
			cin >> add;
			if (add != "quit" && add != "0") {
				int i = 0;
				int check1 = 0;
				while (add[i] != '\0') {
					if (isdigit(add[i]) != 0) ;
					else check1 = 1;
					i++;
				}

				if (check1 == 0) {
					num = atoi(add.c_str());
					if (num >= 1)
						break;
				}

				cout << endl << "<WARN> Please enter in number." << endl;

				cout << "Press <Enter>...";
				cin.ignore();
				cin.get();
			} else
				break;
		}
		addmaterial(name, num);
	} else {
		cout << endl << "<WARN> Name is not in the material list." << endl;

		cout << "Press <Enter>...";
		cin.ignore();
		cin.get();
	}
}

void Manager::material_menu()
{ //1-2. Material Check
	cout << endl << "This is Material..." << endl << endl;
	cout << "*** name ****** price * num ***" << endl;
	for (int i = 0; i < 4; i++)
		cout << i + 1 << ".  " << material_1[i] << "\t" << material_2[i] << "\t" << material_3[i] << endl;
}

void Manager::addmaterial(string name, int add)
{ //1-3. Add Material
	int i = 0;
	for (; i < 4 && name != material_1[i]; i++)
		;
	material_3[i] += add;
	spending += material_2[i] * add;
	if (add != 0)
	{
		cout << endl << "Material added." << endl;
	}
	else
	{
		cout << endl << "Canceled" << endl;
	}
	cout << "Press <Enter>...";
	cin.ignore();
	cin.get();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Manager::checkCoupon(int check, int condition)
{ //View coupons issued
	int checking = 0, temp = 0;
	for (int i = 0; i < CouponSize(); i++)
	{
		checking = Coupon.front();
		Coupon.pop_front();
		if (checking == check)
		{
			temp = 1; //The coupon number is correct.
		}
		else
		{
			Coupon.push_back(checking);
			temp = 2; //The coupon number is incorrect.
		}

		if (temp == condition)
			break;
	}
	if (temp == condition)
		return true;
	return false;
}

void Manager::giveCoupon(data_t &my_data)
{
	strcpy(my_data.data,"*** Congratulations, You won a 500 Won discount coupon! ***\n");
	srand((unsigned)time(NULL));
	int tempnum, ispush = 0;

	while (CouponSize() <= 5 && ispush == 0)
	{
		tempnum = (rand() % 98) + 1; //1~99

		if (CouponSize() == 0)
		{
			ispush = 1;
		}
		else
		{
			if (checkCoupon(tempnum, 2))
				ispush = 1;
		}
	}
	Coupon.push_back(tempnum);

	my_data.couponnum = tempnum;
}

int Manager::CouponSize()
{
	return Coupon.size();
}

int main() {
	Manager manager;
	int server_fifo_fd, client_fifo_fd;
	data_t my_data;
	int read_res;
	char client_fifo[256];
	char *char_ptr;

	mkfifo(SERVER_FIFO_NAME, 0777);
	printf("opening pipe and waiting client's connection\n");
	server_fifo_fd = open(SERVER_FIFO_NAME, O_RDONLY);
	if(server_fifo_fd == -1){ exit(-1); }

	string answer;
	bool out = false;
	do{	if(out == false){
		printf("waiting client's input\n");
		read_res = read(server_fifo_fd, &my_data, sizeof(my_data));
		printf("received %s from pid %d\n", my_data.data ,my_data.client_pid);
		if(read_res>0){				//여기에 조건쓰기
			if(strcmp(my_data.data, "showCoffee")==0){
				manager.showCoffee(my_data);
			} else if(strcmp(my_data.data,"checkCoupon")==0){
				my_data.result = manager.checkCoupon(my_data.changenum, 1);
			} else if(strcmp(my_data.data, "TakeOrder")==0){
				manager.TakeOrder(my_data.changenum, my_data.couponnum);
			} else if(strcmp(my_data.data, "CouponSize")==0){
				my_data.changenum = manager.CouponSize();
			} else if(strcmp(my_data.data, "giveCoupon")==0){
				manager.giveCoupon(my_data);
			} else if(strcmp(my_data.data, "manager")==0){
				cout<<"Do you want manager mode?(Y/N)"<<endl;
				cin>>answer;
				if(answer=="Y"||answer=="y"){out = !(manager.service(my_data));}
			} 

			sprintf(client_fifo, CLIENT_FIFO_NAME, my_data.client_pid);
			client_fifo_fd = open(client_fifo, O_WRONLY);
			if(client_fifo_fd != -1){
				write(client_fifo_fd, &my_data, sizeof(my_data));
				close(client_fifo_fd);
			}
		}
	}
    }while(read_res>0 && out == false);
	if(out == false){
		close(client_fifo_fd);
		unlink(CLIENT_FIFO_NAME);
	}
    close(server_fifo_fd);
    unlink(SERVER_FIFO_NAME);
	return 0;
}