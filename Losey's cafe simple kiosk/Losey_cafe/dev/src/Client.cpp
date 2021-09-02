#include "../inc/Client.h"
#include "../inc/common.h"
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <string.h>

bool Client::order() {
	int server_fifo_fd, client_fifo_fd;
    data_t my_data;
    char client_fifo[256];

    server_fifo_fd = open(SERVER_FIFO_NAME, O_WRONLY);
    if(server_fifo_fd==-1){
       exit(-1);
    }

    my_data.client_pid = getpid();
    sprintf(client_fifo, CLIENT_FIFO_NAME, my_data.client_pid);
    if(mkfifo(client_fifo, 0777)==-1){
        exit(-1);
    }

	int count = 0, quit = 1, coupon = 0, ok2 = 1;
	string ok1, answer, re_enter, coffee_choice, check;
	bool *order_available;
	string answer1;
	bool manager_mode=false;
	
	system("clear");
	cout << "Welcome, Client!" << endl;
	while (quit == 1){
		cout << "Do you want order?(Y/N)" << endl;
		cin >> answer1;

		if(answer1 == "N" || answer1 == "n") {
			quit = 0; manager_mode=true;
		}
		if(answer1 == "Y" || answer1 == "y"){
		server_fifo_fd = open(SERVER_FIFO_NAME, O_WRONLY);
		strcpy(my_data.data, "showCoffee");
        write(server_fifo_fd, &my_data, sizeof(my_data));
        close(server_fifo_fd);
        client_fifo_fd = open(client_fifo, O_RDONLY);
        if(client_fifo_fd != -1){
            if(read(client_fifo_fd, &my_data, sizeof(my_data))>0){
    			order_available = my_data.address;
				cout << my_data.data<<endl;
				int j=0;
				for(int i=0;i<4;i++){
					if(order_available[i]==true){
						cout << " " << i+1 << ".\t" << my_data.menu[0][i] << "\t" <<my_data.menu[1][i]<<endl;
						j++;
					}
				}

				if (j == 0) {
					cout << endl << "There is no menu available to order." << endl;
					cout << "Sorry, We'll refill our stock soon." << endl << endl;
					cout << "Press <Enter>...";
					cin.ignore();
					cin.get();
				}
			}
            close(client_fifo_fd);
        } 
		
		//orderable menu
		count = 0;
		for (int i = 0; i < 4; i++) {
			if (order_available[i] == true)
				count++;
		}

		if (count > 0) { //If we have a menu that client can order,
			cout << "What would you like to order? (Please enter a number)" << endl;
			cout << "(Press <quit> to cancel the order.)" << endl;
			cout << ">> ";
			cin >> coffee_choice;

			int num = atoi(coffee_choice.c_str()) - 1;

			if (coffee_choice == "quit") {quit = 0; manager_mode=true;}
			else if (num >= 0 && num <= 3) {
				if (order_available[num] == true) {//order
					check = "0";
					while (check != "quit") {//coupon
						cout << endl << "Would you like to use a coupon? (Y/N)" << endl;
						cout << ">> ";
						cin >> answer;

						if ((answer == "Y" || answer == "y")) {//coupon use
							int changenum = 0;
							while (check != "quit") {
								cout << endl << "Please enter your coupon number." << endl;
								cout << "(Enter <quit> to cancel input)" << endl;
								cout << ">> ";
								cin >> check; //check == coupon number(and key can exit)

								if (check != "quit") {
									int i = 0;
									int check1 = 0; //check is number = 0, char = 1

									while (check[i] != '\0') {
										if (isdigit(check[i]) != 0) ;
										else check1 = 1;
										i++;
									}

									if (check1 == 0) {//check(coupon number) is number
										changenum = atoi(check.c_str());
										if (changenum <= 99 && changenum >= 1) {//correct
											server_fifo_fd = open(SERVER_FIFO_NAME, O_WRONLY);
											strcpy(my_data.data,"checkCoupon");
											my_data.changenum = changenum;
											write(server_fifo_fd, &my_data, sizeof(my_data));
											close(server_fifo_fd);
											client_fifo_fd = open(client_fifo, O_RDONLY);
											if(client_fifo_fd != -1){
												if(read(client_fifo_fd, &my_data, sizeof(my_data))>0){
													if(my_data.result){
														cout << "500 Won coupon was used." << endl;
														coupon = 500;
														check = "quit";
													}
												}
												close(client_fifo_fd);
											}
										}

										if (check != "quit") {//incorrect
											ok2 = 1;
											while (ok2 == 1) {
												cout << endl << "<WARN> The coupon number is incorrect." << endl;
												cout << "Do you want to re-enter?(Y/N)" << endl; //coupon number
												cout << ">> ";
												cin >> re_enter;
												if (re_enter == "Y" || re_enter == "y") {
													check = "0";
													ok2 = 0;
												} else if (re_enter == "N" || re_enter == "n") {
													ok2 = 0;
													check = "quit";
												} else cout << endl << "<WARN> Please enter only Y/N..." << endl;
											}
										}
									} else //check(coupon number) is char
										cout << endl << "<WARN> Please enter in number." << endl;

									cout << "Press <Enter>...";
									cin.ignore();
									cin.get();
								}
							}
						} else if (answer == "N" || answer == "n") {
							check = "quit";
						} else {
							cout << endl << "<WARN> Please enter only Y/N..." << endl;
							check = "0";
						}
					}

					//order
					server_fifo_fd = open(SERVER_FIFO_NAME, O_WRONLY);
					strcpy(my_data.data,"TakeOrder");
					my_data.changenum = num+1;
					my_data.couponnum = coupon;
					write(server_fifo_fd, &my_data, sizeof(my_data));
					close(server_fifo_fd);
					client_fifo_fd = open(client_fifo, O_RDONLY);
					if(client_fifo_fd != -1){
						if(read(client_fifo_fd, &my_data, sizeof(my_data))>0){
							cout << "Here's your "<< my_data.menu[0][num] << "!"<<endl;
						}
						close(client_fifo_fd);
					}

					bool give;
					server_fifo_fd = open(SERVER_FIFO_NAME, O_WRONLY);
					strcpy(my_data.data,"CouponSize");
					write(server_fifo_fd, &my_data, sizeof(my_data));
					close(server_fifo_fd);
					client_fifo_fd = open(client_fifo, O_RDONLY);
					if(client_fifo_fd != -1){
						if(read(client_fifo_fd, &my_data, sizeof(my_data))>0){
							if ((++people) % 2 == 0 && my_data.changenum < 5) {
								give = true;
							}
						}
						close(client_fifo_fd);
					}
					
					if(give == true){
						server_fifo_fd = open(SERVER_FIFO_NAME, O_WRONLY);
						strcpy(my_data.data,"giveCoupon");
						write(server_fifo_fd, &my_data, sizeof(my_data));
						close(server_fifo_fd);
						client_fifo_fd = open(client_fifo, O_RDONLY);
						if(client_fifo_fd != -1){
							if(read(client_fifo_fd, &my_data, sizeof(my_data))>0){
								cout << my_data.data;
								cout << "\tPlease remember, Your coupon number is " <<my_data.couponnum << "." << endl;
								give = false;
							}
						}
					}

					ok2 = 1;
					while (ok2 == 1) {//re	1-order
						cout << endl << "Would you like to order more? (Y/N)" << endl;
						cout << ">> ";
						cin >> ok1;
						if (ok1 == "Y" || ok1 == "y") {
							ok2 = 0;
							system("clear");
						} else if (ok1 == "N" || ok1 == "n") {
							coffee_choice = "quit";
							quit = 0;
							ok2 = 0;
							manager_mode=true;
						} else
							cout << endl << "<WARN> Please enter only Y/N..." << endl;
					}
				} else {
					system("clear");
					cout << endl << "<WARN> It's not our menu. Please order again." << endl;
				}
			} else {
				system("clear");
				cout << endl << "<WARN> It's not our menu. Please order again." << endl;
			}
		} else
			break;
		}

		if(manager_mode==true){
			cout<<"(selecting mode in manager...)"<<endl;
			server_fifo_fd = open(SERVER_FIFO_NAME, O_WRONLY);
			strcpy(my_data.data, "manager");
			write(server_fifo_fd, &my_data, sizeof(my_data));
			close(server_fifo_fd);
			client_fifo_fd = open(client_fifo, O_RDONLY);
			if(client_fifo_fd != -1){
				if(read(client_fifo_fd, &my_data, sizeof(my_data))>0){
					if(strcmp(my_data.data, "Cafe Closed...")==0)
						return false;
				}
				close(client_fifo_fd);
			}
			manager_mode=false;
		}
	}

	close(server_fifo_fd);
    unlink(client_fifo);
	return true;
}

int main() {
	Client client;
	string answer2;
	while(1){
		if(client.order()==false){	//new client
			return 0;
		}
		cout << endl << "Thank you for using it... <Please Enter Y>" << endl;
		cin >> answer2;
		if(answer2 == "manager") break;	//this password know only manager!!
	}
	return 0;
}