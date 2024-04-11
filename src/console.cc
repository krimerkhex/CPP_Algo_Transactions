#include "console.h"

int input() {
  int choice(0);
  std::cin >> choice;
  return choice;
}

int askForStructType() {
  std::cout << "WHAT KEY-VALUE STORE STRUCT TYPE U WANNA USE?\n1. HASH "
               "TABLE.\n2. RED-BLACK TREE.\n3. EXIT.\n"
            << std::endl;
  return input();
}

int askForCommand() {
  std::cout
      << "COMMAND LIST:\n"
      << "1.  SET (key, surname name birthyear city coins time(if you need)).\n"
      << "2.  GET (key).\n"
      << "3.  EXISTS (key).\n"
      << "4.  DEL (key).\n"
      << "5.  UPDATE (key surname name birthyear city coins).\n"
      << "6.  KEYS ().\n"
      << "7.  RENAME (source dist).\n"
      << "8.  TTL (key).\n"
      << "9.  FIND (surname name birthyear city coins).\n"
      << "10. SHOWALL ().\n"
      << "11. UPLOAD (filepath).\n"
      << "12. EXPORT (filepath).\n"
      << "13. GETBACK TO CHOICE STRUCT TYPE\n"
      << std::endl;
  return input();
}

std::vector<std::string> obtainingRecordInfo() {
  std::string temp;
  std::getline(std::cin, temp);
  std::stringstream slines(temp);
  std::vector<std::string> r_value;
  std::string token;
  while (std::getline(slines, token, ' ')) {
    r_value.push_back(token);
  }
  return r_value;
}

std::string getKey() {
  std::string temp;
  std::cin >> temp;
  return temp;
}

void interactionWithStruct(std::vector<s21::Methods *> &structurs,
                           const unsigned &index) {
  int flag(0);
  s21::Methods *ptr = structurs[index];
  std::vector<std::string> tokens;
  std::size_t size = 0;
  while (flag != 13) {
    flag = askForCommand();
    switch (flag) {
      case 1:
        tokens = obtainingRecordInfo();
        size = tokens.size();
        if (size == 7) {
          ptr->set(tokens[0], tokens[1], tokens[2], std::stoi(tokens[3]),
                   tokens[4], std::stoi(tokens[5]), std::stod(tokens[6]));
        } else if (size == 6) {
          ptr->set(tokens[0], tokens[1], tokens[2], std::stoi(tokens[3]),
                   tokens[4], std::stoi(tokens[5]));
        }
        break;
      case 2:
        ptr->get(getKey());
        break;
      case 3:
        ptr->exists(getKey());
        break;
      case 4:
        ptr->del(getKey());
        break;
      case 5:
        tokens = obtainingRecordInfo();
        if (tokens.size() == 6)
          ptr->update(tokens[0], tokens[1], tokens[2], std::stoi(tokens[3]),
                      tokens[4], std::stoi(tokens[5]));
        break;
      case 6:
        ptr->keys();
        break;
      case 7:
        tokens = obtainingRecordInfo();
        if (tokens.size() == 2) ptr->rename(tokens[0], tokens[1]);
        break;
      case 8:
        ptr->ttl(getKey());
        break;
      case 9:
        tokens = obtainingRecordInfo();
        if (tokens.size() == 5)
          ptr->find(tokens[0], tokens[1], std::stoi(tokens[2]), tokens[3],
                    std::stoi(tokens[4]));
        break;
      case 10:
        ptr->showall();
        break;
      case 11:
        std::cout << "Give path to file" << std::endl;
        ptr->upload(getKey());
        break;
      case 12:
        std::cout << "Give path to file" << std::endl;
        ptr->exportt(getKey());
        break;
      case 13:
        std::cout << "You ended working with struct" << std::endl;
        break;
      default:
        std::cout << "You gave bad value, please read more attentively list of "
                     "commands"
                  << std::endl;
        break;
    }
  }
}

std::vector<s21::Methods *> initStruct() {
  std::vector<s21::Methods *> structurs;
  structurs.push_back(new s21::HashTable());
  structurs.push_back(new s21::SelfBalancingBinarySearchTree());
  return structurs;
}

void deleteStruct(std::vector<s21::Methods *> structures) {
  delete structures[0];
  delete structures[1];
}

void core() {
  bool unstopable(true);
  std::vector<s21::Methods *> structurs(initStruct());
  int flag(4);
  while (unstopable) {
    flag = askForStructType();
    switch (flag) {
      case 1:
        interactionWithStruct(structurs, 0);
        break;
      case 2:
        interactionWithStruct(structurs, 1);
        break;
      case 3:
        std::cout << "THANKS FOR USING THIS CONSOLE APPLICATION" << std::endl;
        unstopable = false;
      default:
        break;
    }
  }
  deleteStruct(structurs);
}

int main() {
  core();
  return 0;
}