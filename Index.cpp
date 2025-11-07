// store.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

const int MAX_ITEMS = 200;
const string FILENAME = "inventory.txt";

struct Item
{
  int id;
  string name;
  string category;
  int quantity;
  double price;
  string supplier;
};

// Function declarations
void loadFromFile(Item items[], int &count, int &nextID, const string &filename);
void saveToFile(Item items[], int count, const string &filename);
void addItem(Item items[], int &count, int &nextID);
void displayItems(Item items[], int count);
int findItemByID(Item items[], int count, int id);
void searchByName(Item items[], int count, const string &name);
void updateItem(Item items[], int count);
void deleteItem(Item items[], int &count);
void pause();
int getIntInput(const string &prompt);
double getDoubleInput(const string &prompt);
string getLineTrimmed(const string &prompt);

int main()
{
  Item items[MAX_ITEMS];
  int count = 0;
  int nextID = 1;

  // Load existing data
  loadFromFile(items, count, nextID, FILENAME);

  while (true)
  {
    cout << "\n====== Store Management System ======\n";
    cout << "1. Add new item\n";
    cout << "2. Display all items\n";
    cout << "3. Search item by name\n";
    cout << "4. Update item (by ID)\n";
    cout << "5. Delete item (by ID)\n";
    cout << "6. Save inventory to file\n";
    cout << "7. Load inventory from file (overwrite current)\n";
    cout << "0. Exit\n";
    cout << "Choose an option: ";

    int choice;
    if (!(cin >> choice))
    {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Invalid input. Try again.\n";
      continue;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear newline

    switch (choice)
    {
    case 1:
      addItem(items, count, nextID);
      break;
    case 2:
      displayItems(items, count);
      break;
    case 3:
    {
      string nm = getLineTrimmed("Enter name (or partial name) to search: ");
      searchByName(items, count, nm);
      break;
    }
    case 4:
      updateItem(items, count);
      break;
    case 5:
      deleteItem(items, count);
      break;
    case 6:
      saveToFile(items, count, FILENAME);
      break;
    case 7:
      loadFromFile(items, count, nextID, FILENAME);
      break;
    case 0:
      cout << "Saving before exit...\n";
      saveToFile(items, count, FILENAME);
      cout << "Goodbye.\n";
      return 0;
    default:
      cout << "Unknown option. Try again.\n";
    }
  }

  return 0;
}

// Helper for trimmed getline prompt
string getLineTrimmed(const string &prompt)
{
  cout << prompt;
  string s;
  getline(cin, s);
  // trim left & right
  size_t start = s.find_first_not_of(" \t\r\n");
  size_t end = s.find_last_not_of(" \t\r\n");
  if (start == string::npos)
    return "";
  return s.substr(start, end - start + 1);
}

int getIntInput(const string &prompt)
{
  while (true)
  {
    cout << prompt;
    int v;
    if (cin >> v)
    {
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      return v;
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Invalid integer. Try again.\n";
  }
}

double getDoubleInput(const string &prompt)
{
  while (true)
  {
    cout << prompt;
    double v;
    if (cin >> v)
    {
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      return v;
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Invalid number. Try again.\n";
  }
}

void addItem(Item items[], int &count, int &nextID)
{
  if (count >= MAX_ITEMS)
  {
    cout << "Inventory full. Cannot add more items.\n";
    return;
  }
  Item it;
  it.id = nextID++;

  it.name = getLineTrimmed("Enter item name: ");
  it.category = getLineTrimmed("Enter category: ");
  it.quantity = getIntInput("Enter quantity: ");
  it.price = getDoubleInput("Enter unit price: ");
  it.supplier = getLineTrimmed("Enter supplier name: ");

  items[count++] = it;
  cout << "Item added (ID = " << it.id << ").\n";
}

void displayItems(Item items[], int count)
{
  if (count == 0)
  {
    cout << "No items to display.\n";
    return;
  }
  cout << left << setw(6) << "ID" << setw(20) << "Name" << setw(12) << "Category"
       << setw(10) << "Qty" << setw(10) << "Price" << setw(20) << "Supplier" << "\n";
  cout << string(78, '-') << "\n";
  for (int i = 0; i < count; ++i)
  {
    cout << left << setw(6) << items[i].id
         << setw(20) << items[i].name.substr(0, 19)
         << setw(12) << items[i].category.substr(0, 11)
         << setw(10) << items[i].quantity
         << setw(10) << fixed << setprecision(2) << items[i].price
         << setw(20) << items[i].supplier.substr(0, 19)
         << "\n";
  }
}

int findItemByID(Item items[], int count, int id)
{
  for (int i = 0; i < count; ++i)
  {
    if (items[i].id == id)
      return i;
  }
  return -1;
}

void searchByName(Item items[], int count, const string &name)
{
  if (count == 0)
  {
    cout << "No items in inventory.\n";
    return;
  }
  bool found = false;
  string lowerName = name;
  for (auto &c : lowerName)
    c = tolower(c);

  for (int i = 0; i < count; ++i)
  {
    string cur = items[i].name;
    for (auto &c : cur)
      c = tolower(c);
    if (cur.find(lowerName) != string::npos)
    {
      if (!found)
      {
        cout << "Matches:\n";
        cout << left << setw(6) << "ID" << setw(20) << "Name" << setw(10) << "Qty" << setw(10) << "Price" << "\n";
        cout << string(50, '-') << "\n";
      }
      cout << left << setw(6) << items[i].id
           << setw(20) << items[i].name.substr(0, 19)
           << setw(10) << items[i].quantity
           << setw(10) << fixed << setprecision(2) << items[i].price << "\n";
      found = true;
    }
  }
  if (!found)
    cout << "No items match \"" << name << "\".\n";
}

void updateItem(Item items[], int count)
{
  if (count == 0)
  {
    cout << "Inventory empty.\n";
    return;
  }
  int id = getIntInput("Enter ID of item to update: ");
  int idx = findItemByID(items, count, id);
  if (idx == -1)
  {
    cout << "Item with ID " << id << " not found.\n";
    return;
  }
  cout << "Updating item: " << items[idx].name << " (ID " << items[idx].id << ")\n";
  cout << "Leave input blank to keep existing value.\n";

  cout << "Current name: " << items[idx].name << "\n";
  string s = getLineTrimmed("New name: ");
  if (!s.empty())
    items[idx].name = s;

  cout << "Current category: " << items[idx].category << "\n";
  s = getLineTrimmed("New category: ");
  if (!s.empty())
    items[idx].category = s;

  cout << "Current quantity: " << items[idx].quantity << "\n";
  cout << "Enter new quantity (or empty to keep): ";
  string temp;
  getline(cin, temp);
  if (!temp.empty())
  {
    try
    {
      items[idx].quantity = stoi(temp);
    }
    catch (...)
    {
      cout << "Invalid number — quantity unchanged.\n";
    }
  }

  cout << "Current price: " << items[idx].price << "\n";
  cout << "Enter new price (or empty to keep): ";
  getline(cin, temp);
  if (!temp.empty())
  {
    try
    {
      items[idx].price = stod(temp);
    }
    catch (...)
    {
      cout << "Invalid number — price unchanged.\n";
    }
  }

  cout << "Current supplier: " << items[idx].supplier << "\n";
  s = getLineTrimmed("New supplier: ");
  if (!s.empty())
    items[idx].supplier = s;

  cout << "Item updated.\n";
}

void deleteItem(Item items[], int &count)
{
  if (count == 0)
  {
    cout << "Inventory empty.\n";
    return;
  }
  int id = getIntInput("Enter ID of item to delete: ");
  int idx = findItemByID(items, count, id);
  if (idx == -1)
  {
    cout << "Item with ID " << id << " not found.\n";
    return;
  }
  cout << "Deleting item: " << items[idx].name << " (ID " << items[idx].id << "). Confirm (y/n): ";
  char c;
  cin >> c;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  if (c == 'y' || c == 'Y')
  {
    // shift left
    for (int i = idx; i < count - 1; ++i)
    {
      items[i] = items[i + 1];
    }
    count--;
    cout << "Item deleted.\n";
  }
  else
  {
    cout << "Delete cancelled.\n";
  }
}

void loadFromFile(Item items[], int &count, int &nextID, const string &filename)
{
  ifstream fin(filename);
  if (!fin)
  {
    cout << "No existing file found. Starting with empty inventory.\n";
    count = 0;
    nextID = 1;
    return;
  }
  count = 0;
  string line;
  int maxID = 0;
  while (getline(fin, line))
  {
    if (line.empty())
      continue;
    // format: id|name|category|quantity|price|supplier
    stringstream ss(line);
    string token;
    Item it;
    try
    {
      getline(ss, token, '|');
      it.id = stoi(token);
      getline(ss, it.name, '|');
      getline(ss, it.category, '|');
      getline(ss, token, '|');
      it.quantity = stoi(token);
      getline(ss, token, '|');
      it.price = stod(token);
      getline(ss, it.supplier, '|');
    }
    catch (...)
    {
      cout << "Skipping malformed line in file: " << line << "\n";
      continue;
    }
    items[count++] = it;
    if (it.id > maxID)
      maxID = it.id;
    if (count >= MAX_ITEMS)
      break;
  }
  fin.close();
  nextID = maxID + 1;
  cout << "Loaded " << count << " items from file.\n";
}

void saveToFile(Item items[], int count, const string &filename)
{
  ofstream fout(filename);
  if (!fout)
  {
    cout << "Error: can't open file for writing.\n";
    return;
  }
  for (int i = 0; i < count; ++i)
  {
    // id|name|category|quantity|price|supplier
    // replace any '|' in strings with '-'
    string name = items[i].name;
    for (auto &c : name)
      if (c == '|')
        c = '-';
    string category = items[i].category;
    for (auto &c : category)
      if (c == '|')
        c = '-';
    string supplier = items[i].supplier;
    for (auto &c : supplier)
      if (c == '|')
        c = '-';

    fout << items[i].id << '|' << name << '|' << category << '|' << items[i].quantity
         << '|' << items[i].price << '|' << supplier << '\n';
  }
  fout.close();
  cout << "Saved " << count << " items to file \"" << filename << "\".\n";
}
