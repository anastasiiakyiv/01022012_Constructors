#include <iostream>
#include <string>
#include <vector>

class ObjectOfOwnership {
private:
	std::string* addressPtr;
	std::string objectName;
	int objectPrice;
public:
	ObjectOfOwnership(std::string* address, const std::string name, int price) :
		addressPtr(address), objectName(name), objectPrice(price) {};

	~ObjectOfOwnership() {
		delete addressPtr;
	}

	void setAddress(std::string* object) {
		addressPtr = object;
	}

	std::string* getAddress() const {
		return addressPtr;
	}

	std::string getName() const {
		return objectName;
	}

	int getPrice() const {
		return objectPrice;
	}
};

class Owner {
private:
	int ID;
	std::string FN;
	std::string LN;
	int funds;
	std::vector<ObjectOfOwnership*> ownedObjects;
public:
	Owner(int ID, std::string FN, std::string LN, int funds, std::vector<ObjectOfOwnership*> ownedObjects) :
		ID(ID), FN(FN), LN(LN), funds(funds), ownedObjects(ownedObjects) {}

	int getID() const {
		return ID;
	}

	std::string getFirstName() const {
		return FN;
	}

	std::string getLastName() const {
		return LN;
	}

	int getFunds() {
		return funds;
	}

	void addObject(ObjectOfOwnership* address) {
		ownedObjects.push_back(address);
	}


	void transferFunds(int amount, Owner& recipient) {
		if (funds >= amount) {
			funds -= amount;
			recipient.receiveFunds(amount);
		}
		else {
			std::cout << "Недостатність коштів на балансі." << std::endl;
		}
	}

	void receiveFunds(int amount) {
		funds += amount;
	}

	void transferOwnership(ObjectOfOwnership* object, Owner& newOwner) {
		auto it = std::find(ownedObjects.begin(), ownedObjects.end(), object);
		if (it != ownedObjects.end()) {
			ownedObjects.erase(it);
			newOwner.ownedObjects.push_back(object);
		}
	}

	void printOwnedObjects() const {
		std::cout << FN << " " << LN << " володіє об'єктами:" << std::endl;
		for (const auto& object : ownedObjects) {
			std::cout << object->getName() << ", адреса: " << *(object->getAddress()) << ", ціна: " << object->getPrice() << " грн." << std::endl;
		}
	}
};

int main() {
	system("chcp 1251>null");
	ObjectOfOwnership* object1 = new ObjectOfOwnership(new std::string("вул. Павла Потоцького, 15"), "Будинок", 13383500);
	ObjectOfOwnership* object2 = new ObjectOfOwnership(new std::string("вул. Зелена, 8"), "Будинок", 3770000);
	ObjectOfOwnership* object3 = new ObjectOfOwnership(new std::string("вул. Садова, 26"), "Таунхаус", 754000);
	ObjectOfOwnership* object4 = new ObjectOfOwnership(new std::string("вул. Березняківська, 10, кв. 251"), "Квартира", 3580140);

	std::vector<ObjectOfOwnership*> firstOwner = { object1, object2 };
	std::vector<ObjectOfOwnership*> secondOwner = { object3 };
	std::vector<ObjectOfOwnership*> thirdOwner = { object4 };

	Owner owner1(532298, "Аліса", "Проценко", 10000000, firstOwner);
	Owner owner2(154490, "Максим", "Войченко", 4000000, secondOwner);
	Owner owner3(671248, "Ольга", "Шевченко", 6000000, thirdOwner);

	owner1.printOwnedObjects();
	std::cout << "Стан рахунку: " << owner1.getFunds() << " грн" << std::endl;
	std::cout << std::endl;
	owner2.printOwnedObjects();
	std::cout << "Стан рахунку: " << owner2.getFunds() << " грн" << std::endl;
	std::cout << std::endl;
	owner3.printOwnedObjects();
    std::cout << "Стан рахунку: " << owner3.getFunds() << " грн" << std::endl;
	std::cout << std::endl;

	owner1.transferOwnership(object2, owner3);
	owner3.transferFunds(3770000.0, owner1);

	std::cout << "< Після передачі об'єкта >" << std::endl;
	std::cout << std::endl;
	owner1.printOwnedObjects();
	std::cout << "Стан рахунку: " << owner1.getFunds() << " грн" << std::endl;
	std::cout << std::endl;
	owner2.printOwnedObjects();
	std::cout << "Стан рахунку: " << owner2.getFunds() << " грн" << std::endl;
	std::cout << std::endl;
	owner3.printOwnedObjects();
	std::cout << "Стан рахунку: " << owner3.getFunds() << " грн" << std::endl;

	delete object1;
	delete object2;
	delete object3;
	delete object4;

	return 0;
}