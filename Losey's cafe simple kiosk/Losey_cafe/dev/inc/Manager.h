#ifndef MANAGER_H
#define MANAGER_H
#include "../inc/common.h"
#include <string>
#include <iostream>
using namespace std;
#include <list>

class Manager {
	//material
	string material_1[4] = { "been", "water", "milk", "vanilla" };		//material_name
	int material_2[4] = { 300, 100, 300, 200 };							//material_price
	int material_3[4];													//material_amount
	bool order_available[4];

	//money
	int income;
	int spending;

	//menu
	string menu[2][4] = { {"Americano","Espresso", "Cafelatte","Vanillalatte" },{ "1500", "2000", "2000", "2500"} };

	list<int> Coupon;

	void order_material();							//Order Material
	void material_menu();							//Material Check
	void addmaterial(string name, int add);			//Add Material

	void showmaterial();							//1. Material Check and Order
	void showSales();								//3. Sales and net income check
	void showCoupon();								//4. View coupons issued

	//Order Menu by Client
	void Americano(int coupon);
	void Espresso(int coupon);
	void Cafelatte(int coupon);
	void Vanillalatte(int coupon);

public:
	Manager();
	bool service(data_t &my_data);					//0. Manager Service
	void showCoffee(data_t &my_data);				//2. Makeable coffee check (Client & Manager)
	bool* showCoffee_manager();
	void TakeOrder(int coffee_choice, int coupon);	//Client chooses coffee

	bool checkCoupon(int check, int condition);	//Check and use issued coupons
	void giveCoupon(data_t &my_data);								//Give Coupon
	int CouponSize();								//Coupon Size
};

#endif